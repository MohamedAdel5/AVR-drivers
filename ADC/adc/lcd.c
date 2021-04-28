/*
 * lcd.c
 *
 *  Created on: Sep 13, 2019
 *      Author: DR. ADEL
 */

#include "lcd.h"


/****************************************************************
 * 						functions definitions
 *****************************************************************/
void LCD_init(void)
{
	LCD_CTRL_PORT_DIR |= (1 << RS)|(1 << RW)|(1 << E);		/*Sets Control port pins as output pins*/

	#if(LCD_DATA_BITS_MODE == 8)
		LCD_DATA_PORT_DIR = 0xFF; 							/*Sets all data port pins as output pins*/
		LCD_sendCommand(LCD_RETURN_HOME);					/*For clean initialization*/
	#elif(LCD_DATA_BITS_MODE == 4)
		#ifdef LCD_UPPER_PORT_PINS
			LCD_DATA_PORT_DIR |= 0xF0; 						/*Sets the upper 4 pins of data port output pins*/
			LCD_sendCommand(LCD_RETURN_HOME);				/*Required for 4-bit mode*/
		#else
			LCD_DATA_PORT_DIR |= 0x0F; 						/*Sets the lower 4 pins of data port output pins*/
			LCD_sendCommand(LCD_RETURN_HOME);
		#endif
	#endif



	LCD_sendCommand(LCD_DISPLAY_MODE);					/*Sets Display mode 2 line display and 8 or 4 -bit interface*/
	LCD_sendCommand(LCD_CURSOR_MODE);					/*Sets Cursor Mode ON/OFF and Blink ON/OFF*/
	LCD_sendCommand(LCD_CLEAR_DISPLAY);					/*Clears screen on initialization*/

}
void LCD_sendCommand(uint8 command)
{
	CLEAR_BIT(LCD_CTRL_PORT, RW);	/*Clears RW	=> write data*/
	CLEAR_BIT(LCD_CTRL_PORT, RS);	/*Clears RS => transfer instrucion data*/
	_delay_ms(1);					/*Delay tas - tr = 50 - 16 = 34ns [should be done in assembly (NOP) to be more precise]*/
	SET_BIT(LCD_CTRL_PORT, E);		/*Sets data Enable bit*/
	_delay_ms(1);					/*Delay tpw-tdsw = 290 - 100 = 190ns [should be done in assembly (NOP) to be more precise]*/
	#if(LCD_DATA_BITS_MODE == 8)
		LCD_DATA_PORT = command;		/*Sends the command*/
	#elif(LCD_DATA_BITS_MODE == 4)
		#ifdef LCD_UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (command & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((command >> 4) & 0x0F);
		#endif
		_delay_ms(1);					/*Delay tdsw = 100ns [should be done in assembly (NOP) to be more precise]*/
		CLEAR_BIT(LCD_CTRL_PORT, E);	/*Clears data Enable Bit*/
		_delay_ms(1);					/*Delay th = 13ns [should be done in assembly (NOP) to be more precise]*/
		SET_BIT(LCD_CTRL_PORT, E);		/*Sets data Enable bit*/
		_delay_ms(1);					/*Delay tpw-tdsw = 290 - 100 = 190ns [should be done in assembly (NOP) to be more precise]*/
		#ifdef LCD_UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((command << 4) & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (command & 0x0F);
		#endif
	#endif
	_delay_ms(1);					/*Delay tdsw = 100ns [should be done in assembly (NOP) to be more precise]*/
	CLEAR_BIT(LCD_CTRL_PORT, E);	/*Clears data Enable Bit*/
	_delay_ms(1);					/*Delay th = 13ns [should be done in assembly (NOP) to be more precise]*/
}
void LCD_displayOneCharacter(uint8 data)
{
	CLEAR_BIT(LCD_CTRL_PORT, RW);	/*Clears RW	=> write data*/
	SET_BIT(LCD_CTRL_PORT, RS);		/*Sets RS => transfer display data*/
	_delay_ms(1);					/*Delay tas - tr = 50 - 16 = 34ns [should be done in assembly (NOP) to be more precise]*/
	SET_BIT(LCD_CTRL_PORT, E);		/*Sets data Enable bit*/
	_delay_ms(1);					/*Delay tpw-tdsw = 290 - 100 = 190ns [should be done in assembly (NOP) to be more precise]*/
	#if(LCD_DATA_BITS_MODE == 8)
		LCD_DATA_PORT = data;		/*Sends the command*/
	#elif(LCD_DATA_BITS_MODE == 4)
		#ifdef LCD_UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | (data & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | ((data >> 4) & 0x0F);
		#endif
		_delay_ms(1);					/*Delay tdsw = 100ns [should be done in assembly (NOP) to be more precise]*/
		CLEAR_BIT(LCD_CTRL_PORT, E);	/*Clears data Enable Bit*/
		_delay_ms(1);					/*Delay th = 13ns [should be done in assembly (NOP) to be more precise]*/
		SET_BIT(LCD_CTRL_PORT, E);		/*Sets data Enable bit*/
		_delay_ms(1);					/*Delay tpw-tdsw = 290 - 100 = 190ns [should be done in assembly (NOP) to be more precise]*/
		#ifdef LCD_UPPER_PORT_PINS
			LCD_DATA_PORT = (LCD_DATA_PORT & 0x0F) | ((data << 4) & 0xF0);
		#else
			LCD_DATA_PORT = (LCD_DATA_PORT & 0xF0) | (data & 0x0F);
		#endif
	#endif
	_delay_ms(1);					/*Delay tdsw = 100ns [should be done in assembly (NOP) to be more precise]*/
	CLEAR_BIT(LCD_CTRL_PORT, E);	/*Clears data Enable Bit*/
	_delay_ms(1);					/*Delay th = 13ns [should be done in assembly (NOP) to be more precise]*/
}
void LCD_displayString(char* str)
{
	while((*str) != '\0')
	{
		LCD_displayOneCharacter(*str);
		++str;
	}
}
void LCD_clearScreen(void)
{
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
}
void LCD_goToRowColumn(uint8 row, uint8 col)
{
	if(col >= 1 && col <= 16)
	{
		switch(row)
		{
		case 1:
			LCD_sendCommand(LCD_SET_CURSOR_LOCATION | (col-1));
			break;
		case 2:
			LCD_sendCommand(LCD_SET_CURSOR_LOCATION | 0x40 | (col-1));
			break;
		case 3:
			LCD_sendCommand(LCD_SET_CURSOR_LOCATION | 0x10 | (col-1));
			break;
		case 4:
			LCD_sendCommand(LCD_SET_CURSOR_LOCATION | 0x50 | (col-1));
			break;
		default:
			break;
		}
	}
}
void LCD_displayStringAtRowColumn(uint8 row, uint8 col, char* str)
{
	LCD_goToRowColumn(row, col);
	LCD_displayString(str);
}
void LCD_displayInteger(int data)
{
	char str[11];			/*Maximum integer to be displayed is 10 digits + '/0' character*/
	itoa(data, str, 10);	/*Converts integer to string*/
	LCD_displayString(str);
}
uint8 LCD_readAddressCounter(void)
{
	uint8 data;
	LCD_DATA_PORT_DIR = 0x00;		/*Sets data port pins as input pins*/

	SET_BIT(LCD_CTRL_PORT, RS);
	SET_BIT(LCD_CTRL_PORT, RW);		/*Sets RW => read data*/
	_delay_ms(1);					/*Delay tas - tr = 50 - 16 = 34ns [should be done in assembly (NOP) to be more precise]*/
	SET_BIT(LCD_CTRL_PORT, E);		/*Sets data Enable bit*/
	_delay_ms(1);					/*Delay tddr = 150ns [should be done in assembly (NOP) to be more precise]*/
	data = LCD_DATA_PORT_READ;		/*Sends the data*/
	_delay_ms(1);					/*Delay tpw-tddr = 290 - 150 = 140ns [should be done in assembly (NOP) to be more precise]*/
	CLEAR_BIT(LCD_CTRL_PORT, E);	/*Clears data Enable Bit*/
	_delay_ms(1);					/*Delay th = 13ns [should be done in assembly (NOP) to be more precise]*/


	LCD_DATA_PORT_DIR = 0xFF; 		/*Sets data port pins as output pins*/
	return (data & (0x7F));			/*Return Address counter (right most 7 bits) Only*/
}
void LCD_wirteDataInByte(uint8 data, uint8 byteNum)
{

}
