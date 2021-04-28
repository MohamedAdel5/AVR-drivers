/*
 * main.c
 *
 *  Created on: Oct 4, 2019
 *      Author: Mohamed Adel
 */


#include "eeprom.h"
#define F_CPU 8000000UL
#include "lcd/lcd.h"
int main(void)
{
	LCD_init();
	uint8 val;


	uint8* str = "abcdefg";
	uint8* ptr = str;
	EEPROM_init();
	for(uint8 i = 0; i < 7; i++)
	{
		EEPROM_writeByte(0x0F + i, str[i]);
		_delay_ms(10);
	}
	uint8 str2[10];
	for(uint8 i = 0; i < 7; i++)
	{
		EEPROM_readByte(0x0F + i, str2 + i);
		_delay_ms(10);
	}
	str2[7] = '\0';
	LCD_displayString(str2);
	
	EEPROM_deinit();
	while(1)
	{

	}

	return 0;
}
