/*
 * main.c
 *
 *  Created on: Oct 1, 2019
 *      Author: DR. ADEL
 */


#include "spi.h"

int main(void)
{
	SPI_config spiConfig = {LSB, DATA_MODE_0, F_CPU_8};
	SPI_slaveInit(&spiConfig);

	SPI_sendByte(34);
	_delay_ms(1600);
	if(SPI_getReceivedData() == 'b')
	{
		SET_BIT(DDRA, PA0);
		SET_BIT(PORTA, PA0);
	}

	/*a = SPI_receiveByte();
	SPDR = 'B';
	a = SPI_receiveByte();
	SPDR = 'D';*/
	/*a = SPI_receiveByte();
	if(a == 'B')
	{
		SET_BIT(DDRA, PA0);
		SET_BIT(PORTA, PA0);
	}
	SPDR = 'C';
	a = SPI_receiveByte();
	if(a == 'D')
	{
		SET_BIT(DDRA, PA1);
		SET_BIT(PORTA, PA1);
	}*/
	while(1)
	{
	}
	return 0;
}
