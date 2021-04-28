/*
 * uart.c
 *
 *  Created on: Sep 26, 2019
 *      Author: MOHAMED ADEL
 */
/***************************************************************
 	 	 	 	 	 	Includes
 ***************************************************************/

#include "uart.h"
/***************************************************************
 	 	 	 	 	 	Data members (Private)
 ***************************************************************/
static  void(*g_fptrCallBack_receive)(void) = NULLPTR;
static  void(*g_fptrCallBack_transmit_complete)(void) = NULLPTR;
static  void(*g_fptrCallBack_transmit_empty)(void) = NULLPTR;
/***************************************************************
 	 	 	 	 	 	Functions definitions
 ***************************************************************/
void UART_init(UART_config *config)
{
	/*RXC = 0 TXC = 0 UDRE = 0 FE = 0 DOR = 0 PE = 0 U2X = 1 MPCM = 0*/
	/*Receive flag is READ ONLY but also CLEARED as an initial value (redundant)
	 * Transmit flag is CLEARED as an initial value
	 * UART data register Empty flag is SET as an initial value
	 *the error flags are CLEARED for future compatibility
	 * Double UART transmission speed is ENABLED
	 * Multiprocessor communication mode is DISABLED*/
	UCSRA = 0x22;


	/*For 8-bit character size configuration*/

	CLEAR_BIT(UCSRB, UCSZ2);

	SET_BIT(UCSRC, URSEL);		/*enable editing UCSRC*/

	SET_BIT(UCSRC, UCSZ0);
	SET_BIT(UCSRC, UCSZ1);

	CLEAR_BIT(UCSRC, UMSEL);		/*ASYNC Operation*/
	CLEAR_BIT(UCSRC, UCPOL);		/*Clock polarity disabled because the Operation is ASYNC*/

	switch(config->parity)
	{
	default:
	case DISABLED:
		CLEAR_BIT(UCSRC, UPM0);
		CLEAR_BIT(UCSRC, UPM1);
		break;
	case EVEN:
		CLEAR_BIT(UCSRC, UPM0);
		SET_BIT(UCSRC, UPM1);
		break;
	case ODD:
		SET_BIT(UCSRC, UPM0);
		SET_BIT(UCSRC, UPM1);
		break;
	}
	switch(config->stopBit)
	{
	default:
	case STOP_BIT_1:
		CLEAR_BIT(UCSRC, USBS);
		break;
	case STOP_BIT_2:
		SET_BIT(UCSRC, USBS);
		break;
	}
	uint16 baud = (F_CPU/(8UL * config->baudRate))-1; /*UBBR equation for enabled Double UART transmission speed*/

	CLEAR_BIT(UCSRC, URSEL);		/*enable editing UBRRH*/

	UBRRH = (baud >> 8);
	UBRRL = baud;


	/*Finally Enable the UART*/
	switch(config->mode)
	{
	case T:
		SET_BIT(PORTD, PD1);	/*Sets TX pin as output pin(redundant because the UART overrides the i/o port functionality)*/
		SET_BIT(UCSRB, TXEN);	/*Enable Transmitting*/
		break;
	case R:
		CLEAR_BIT(PORTD, PD0);	/*Sets RX pin as input pin(redundant because the UART overrides the i/o port functionality)*/
		SET_BIT(UCSRB, RXEN);	/*Enable Receiving*/
		break;

	default: /*The default value is Transmit and receive*/
	case TR:
		SET_BIT(PORTD, PD1);
		CLEAR_BIT(PORTD, PD0);
		SET_BIT(UCSRB, TXEN);
		SET_BIT(UCSRB, RXEN);
		break;
	}

}
void UART_deinit(void)
{
	UCSRB = 0;	/*disable receive and transmit*/
}

void UART_sendByte(const uint8 data)
{



	while(BIT_IS_CLEAR(UCSRA, UDRE));
	UDR = data;

	/* OTHER METHOD:
	 *
	 * UDR = data;
	 * while(BIT_IS_CLEAR(UCSRA, TXC)); //this line can not be written before the "UDR = data" statement because it may cause an infinite loop
	 * SET_BIT(UCSRA, TXC);
	 */
}
UART_status UART_receiveByte(uint8 * const data)
{
	while(BIT_IS_CLEAR(UCSRA, RXC));	/*Polling for RXC*/

	if(BIT_IS_SET(UCSRA, FE) || BIT_IS_SET(UCSRA, PE))
	{
		return ERROR;
	}
	else
	{
		*data = UDR;		/*RXC is cleared on reading the UDR register*/
		return SUCCESS;
	}
}

void UART_sendString(const uint8* str)
{
	while(*str != '\0')
	{
		UART_sendByte(*str);
		str++;
	}
}
void UART_receiveString(uint8* str)
{
	uint8 receivedByte;
	UART_receiveByte(&receivedByte);
	while(receivedByte != UART_TERMINATING_CHARACTER) 	//till the user enters the terminating character
	{
		*str = receivedByte;
		str++;
		UART_receiveByte(&receivedByte);
	}
	*str = '\0';
}
void UART_interrupt_receive(void(*a_fptrCallBack_receive)())
{
	if(a_fptrCallBack_receive != NULLPTR)
	{
		SET_BIT(UCSRB, RXCIE);		/*Enable interrupt RXC*/
		g_fptrCallBack_receive = a_fptrCallBack_receive;
	}
}
void UART_interrupt_transmit_complete(void(*a_fptrCallBack_transmit_complete)())
{
	if(a_fptrCallBack_transmit_complete != NULLPTR)
	{
		SET_BIT(UCSRB, TXCIE);		/*Enable interrupt TXC*/
		g_fptrCallBack_transmit_complete = a_fptrCallBack_transmit_complete;
	}
}
void UART_interrupt_transmit_empty(void(*a_fptrCallBack_transmit_empty)())
{
	if(a_fptrCallBack_transmit_empty != NULLPTR)
	{
		SET_BIT(UCSRB, UDRIE);		/*Enable interrupt UDRE*/
		g_fptrCallBack_transmit_empty = a_fptrCallBack_transmit_empty;
	}
}
ISR(USART_RXC_vect)
{
	if(g_fptrCallBack_receive != NULLPTR)
		(*g_fptrCallBack_receive)();
	/*You must read UDR or clear RXCIE(disable RXC interrupt) bit otherwise a new interrupt will occur once the interrupt routine terminates. (You can't clear RXC flag because it's read only.. its only cleared when UDR is read)*/
}
ISR(USART_TXC_vect)
{
	if(g_fptrCallBack_transmit_complete != NULLPTR)
		(*g_fptrCallBack_transmit_complete)();

	/*TXC flag is automatically cleared after the execution of its ISR*/
}
ISR(USART_UDRE_vect)
{
	if(g_fptrCallBack_transmit_empty != NULLPTR)
		(*g_fptrCallBack_transmit_empty)();
	/*You must write in UDR or clear UDRIE(disable UDRE interrupt) bit otherwise a new interrupt will occur once the interrupt routine terminates. (You can't clear UDRE flag because it's read only.. its only cleared when UDR is written)*/
}
