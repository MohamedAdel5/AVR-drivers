/*
 * main.c
 *
 *  Created on: Sep 13, 2019
 *      Author: DR. ADEL
 */

#include "keypad.h"

int main(void)
{
	DDRC |= 0x0F; 		/*PORTB first 4 pins are output pins*/
	PORTC &= (0xF0); 	/*PORTB first 4 pins are cleared at the beginning of the program*/

	while(1)
	{
		uint8 ch = KEYPAD_getKeyPressed();
		if(ch >= 0 && ch <= 9)
			PORTC = (PORTC & 0xF0) | (ch & 0x0F);
		else if(ch == '+' || ch == '-' || ch == '/' || ch == '*' || ch == 13 || ch == '=' || ch == '#')
			PORTC = (PORTC & 0xF0) | 0x09;
	}
	return 0;
}
