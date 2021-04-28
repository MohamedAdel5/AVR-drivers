/*
 * spi.c
 *
 *  Created on: Oct 1, 2019
 *      Author: DR. ADEL
 */

/**************************************************************
 	 	 	 	 	 		Includes
 **************************************************************/
#include "spi.h"
/**************************************************************
						Data members(private)
 **************************************************************/
static void (*g_fptr_callBackFunction)(void) = NULLPTR;
static uint8 SPI_mode = 0; /*0: not initialized, 1: master, 2: slave*/
/**************************************************************
 	 	 	 	 		Functions prototypes
 **************************************************************/
void SPI_masterInit(const SPI_config* config)
{
	SPI_mode = 1; 					/*mode = master*/
	/*Configure pins I/O port*/
	DDRB = (DDRB & 0x0F) | (0xB0);	/*MOSI => output pin,  MISO => input pin, SS => output pin, SCK => output pin*/

	switch(config->clock)
	{
	default:	/*default value of SPI frequency will be Fcpu/4*/
	case F_CPU_4:
		CLEAR_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
		break;
	case F_CPU_16:
		SET_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	case F_CPU_64:
		CLEAR_BIT(SPCR, SPR0);
		SET_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	case F_CPU_128:
		SET_BIT(SPCR, SPR0);
		SET_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	case F_CPU_2:
		CLEAR_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		SET_BIT(SPSR, SPI2X);
			break;
	case F_CPU_8:
		SET_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		SET_BIT(SPSR, SPI2X);
			break;
	case F_CPU_32:
		CLEAR_BIT(SPCR, SPR0);
		SET_BIT(SPCR, SPR1);
		SET_BIT(SPSR, SPI2X);
			break;
	}

	switch(config->dataMode)
	{
	default: 	/*default data mode is data mode 0 (for more info about this mode refer to the header file or the datasheet)*/
	case DATA_MODE_0:
		CLEAR_BIT(SPCR, CPHA);
		CLEAR_BIT(SPCR, CPOL);

		break;
	case DATA_MODE_1:
		SET_BIT(SPCR, CPHA);
		CLEAR_BIT(SPCR, CPOL);

		break;
	case DATA_MODE_2:
		CLEAR_BIT(SPCR, CPHA);
		SET_BIT(SPCR, CPOL);
		break;
	case DATA_MODE_3:
		SET_BIT(SPCR, CPHA);
		SET_BIT(SPCR, CPOL);
		break;
	}
	switch(config->dataOrder)
	{
	default: /*The default is to transmit the most significant bit first*/
	case MSB:
		CLEAR_BIT(SPCR, DORD);
		break;
	case LSB:
		SET_BIT(SPCR, DORD);
		break;
	}

	SET_BIT(SPCR, MSTR);	/*Select SPI mode as master*/
	SET_BIT(SPCR, SPE); 	/*Enables SPI*/

}
void SPI_slaveInit(const SPI_config* config)
{
	SPI_mode = 1; 					/*mode = slave*/
	/*Configure pins I/O port*/
	DDRB = (DDRB & 0x0F) | (0x40);	/*MOSI => input  pin,  MISO => output pin, SS => input pin, SCK => input pin*/

	switch(config->clock)
	{
	default:	/*default value of SPI frequency will be Fcpu/4*/
	case F_CPU_4:
		CLEAR_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
		break;
	case F_CPU_16:
		SET_BIT(SPCR, SPR0);
		CLEAR_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	case F_CPU_64:
		CLEAR_BIT(SPCR, SPR0);
		SET_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	case F_CPU_128:
		SET_BIT(SPCR, SPR0);
		SET_BIT(SPCR, SPR1);
		CLEAR_BIT(SPSR, SPI2X);
			break;
	}

	switch(config->dataMode)
	{
	default: 	/*default data mode is data mode 0 (for more info about this mode refer to the header file or the datasheet)*/
	case DATA_MODE_0:
		CLEAR_BIT(SPCR, CPHA);
		CLEAR_BIT(SPCR, CPOL);

		break;
	case DATA_MODE_1:
		SET_BIT(SPCR, CPHA);
		CLEAR_BIT(SPCR, CPOL);

		break;
	case DATA_MODE_2:
		CLEAR_BIT(SPCR, CPHA);
		SET_BIT(SPCR, CPOL);
		break;
	case DATA_MODE_3:
		SET_BIT(SPCR, CPHA);
		SET_BIT(SPCR, CPOL);
		break;
	}
	switch(config->dataOrder)
	{
	default: /*The default is to transmit the most significant bit first*/
	case MSB:
		CLEAR_BIT(SPCR, DORD);
		break;
	case LSB:
		SET_BIT(SPCR, DORD);
		break;
	}

	CLEAR_BIT(SPCR, MSTR);	/*Select SPI mode as slave*/
	SET_BIT(SPCR, SPE); 	/*Enables SPI*/
}
void SPI_deinit(void)
{
	SPI_mode = 0; 			/*mode = uninitialized*/
	SET_BIT(SPCR, SPE); 	/*Disables SPI*/
	CLEAR_BIT(SPCR, SPIE); 	/*Disables SPI interrupts*/
}
void SPI_sendByte(uint8 data)
{
	if(SPI_mode == 2)	/*If the SPI is currently a slave*/
	{
		SPDR = data;
		return;
	}

	/*If the SPI is currently a master and this send function is called then it can send and receive at the same time*/

	SPDR = data;						/*Sends data*/
	while(BIT_IS_CLEAR(SPSR, SPIF));	/*Waits till the data is transmitted(SPIF flag is triggered)*/
	data = SPDR; 						/*Accesses SPDR to clear interrupt flag*/
	/*SPIF flag is cleared by reading SPSR then accessing SPDR*/

}
uint8 SPI_receiveByte(void)
{
	if(SPI_mode == 1)	/*If the SPI is currently a master*/
	{
		SPDR = 0;							/*Any value to be transmitted to the slave in order to receive the data in its register*/
		while(BIT_IS_CLEAR(SPSR, SPIF));	/*Waits till the data is transmitted(SPIF flag is triggered)*/
		return SPDR;						/*Clears SPIF flag and returns the RECEIVED data*/
	}
	while(BIT_IS_CLEAR(SPSR, SPIF));	/*Waits till the data is transmitted(SPIF flag is triggered)*/
	return SPDR;						/*Clears SPIF flag and returns the data*/
}
uint8 SPI_getReceivedData(void)
{
	return SPDR;
}
void SPI_sendString(const uint8* str)
{
	while(*str != '\0')
	{
		SPI_sendByte(*str);
		str++;
	}
}
void SPI_receiveString(uint8* str)
{
	uint8 ch = SPI_receiveByte();
	if(ch == SPI_TERMINATING_CHARACTER) return;
	else
	{
		*str = ch;
		ch = SPI_receiveByte();
	}
	while(ch != SPI_TERMINATING_CHARACTER)
	{

		str++;
		*str = ch;
		ch = SPI_receiveByte();
	}
	str++;
	*str = '\0';

}
void SPI_interrupt_enable(void (*a_fptr_callBackFunction)(void))
{
	SET_BIT(SPCR, SPIE); 	/*Enables SPI interrupts*/
	g_fptr_callBackFunction = a_fptr_callBackFunction;
}
ISR(SPI_STC_vect)
{
	if(g_fptr_callBackFunction != NULLPTR)
	{
		(*g_fptr_callBackFunction)();
	}

}
