/*
 * main.c
 *
 *  Created on: Oct 2, 2019
 *      Author: DR. ADEL
 */


#include "spi.h"
#include "lcd.h"
int main(void)
{
	LCD_init();
	SPI_config spiConfig = {LSB, DATA_MODE_0, F_CPU_8};
	SPI_masterInit(&spiConfig);
	_delay_ms(700);

	SPI_sendByte('b');
	_delay_ms(700);
	LCD_displayOneCharacter(SPI_getReceivedData());
	/*_delay_ms(700);
	SPI_sendByte('D');
	LCD_displayOneCharacter(SPDR);
	_delay_ms(700);
	SPI_sendByte('E');
	LCD_displayOneCharacter(SPDR);*/
	while(1)
	{

	}
	return 0;
}
