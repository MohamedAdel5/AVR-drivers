/*
 * uart.h
 *
 *  Created on: Sep 26, 2019
 *      Author: DR. ADEL
 */

#ifndef UART_H_
#define UART_H_
/***************************************************************
 	 	 	 	 	 	Includes
 ***************************************************************/
#include "../std/std.h"

/***************************************************************
 	 	 	 	 	 	New Types definitions
 ***************************************************************/
typedef enum
{
	ERROR,
	SUCCESS
}UART_status;

typedef enum
{
	BAUD_RATE_2400 = 2400,
	BAUD_RATE_4800 = 4800,
	BAUD_RATE_9600 = 9600,
	BAUD_RATE_19200 = 19200,
	BAUD_RATE_38400 = 38400

	/*Other values can be added
	 * for more general configuration*/

}UART_baudRate;

typedef enum
{
	T, 	/*Transmit*/
	R,	/*Receive*/
	TR	/*Transmit and receive*/
}UART_mode;
typedef enum
{
	DISABLED, /*No parity checking*/
	EVEN = 2,
	ODD
}UART_parity;
typedef enum
{
	STOP_BIT_1,
	STOP_BIT_2
}UART_stopBit;
typedef struct
{
	UART_mode mode;
	UART_baudRate baudRate;
	UART_parity parity;
	UART_stopBit stopBit;

}UART_config;
/***************************************************************
 	 	 	 	 	 	Configurations
 ***************************************************************/
#define UART_TERMINATING_CHARACTER '#'
/***************************************************************
 	 	 	 	 	 	Functions prototypes
 ***************************************************************/

void UART_init(UART_config *config);												/*initialize UART*/
void UART_deinit(void);																/*de-initialize UART (back to idle mode)*/

void UART_sendByte(const uint8 data);												/*send a byte*/
UART_status UART_receiveByte(uint8 * const data);									/*receive a byte*/

void UART_interrupt_receive(void(*a_fptrCallBack_receive)());						/*You must read UDR or clear RXCIE(disable RXC interrupt) bit otherwise a new interrupt will occur once the interrupt routine terminates. (You can't clear RXC flag because it's read only.. its only cleared when UDR is read)*/
void UART_interrupt_transmit_complete(void(*a_fptrCallBack_transmit_complete)());	/*TXC flag is automatically cleared after the execution of its ISR*/
void UART_interrupt_transmit_empty(void(*a_fptrCallBack_transmit_empty)());			/*You must write in UDR or clear UDRIE(disable UDRE interrupt) bit otherwise a new interrupt will occur once the interrupt routine terminates. (You can't clear UDRE flag because it's read only.. its only cleared when UDR is written)*/

void UART_sendString(const uint8* str);												/*send a string of bytes*/
void UART_receiveString(uint8* str);												/*receive a string of bytes*/

#endif /* UART_H_ */
