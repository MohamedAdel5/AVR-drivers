/*
 * main.c
 *
 *  Created on: Sep 14, 2019
 *      Author: DR. ADEL
 */
#include "lcd.h"
#include"keypad.h"
void TIMER1_CTCA_init(void)
{
	TCNT1 = 0;
	OCR1A = 62500;
	TCCR1A = 0;
	TCCR1B = 0x0A;
}
int main(void)
{
	LCD_init();
	LCD_sendCommand(LCD_CLEAR_DISPLAY);
	LCD_sendCommand(LCD_CURSOR_ON_BLINK_OFF);


	uint8 ch = KEYPAD_getKeyPressed();
	/*Start timer*/
	TIMER1_CTCA_init();

	if(ch >= 0 && ch <= 10)
	{
		LCD_displayOneCharacter(ch+48);
	}
	else
	{
		LCD_displayOneCharacter(ch);
	}
	uint8 prevCh = ch;

	while(1)
	{
		ch = KEYPAD_getKeyPressed();

		/*prescalar =  8 ==> timer1*/
		if((ch != prevCh) || BIT_IS_SET(TIFR, OCIE1A))
		{
			if(ch >= 0 && ch <= 10)
			{
				LCD_displayOneCharacter(ch+48);
			}
			else
			{
				LCD_displayOneCharacter(ch);
			}
			prevCh = ch;

			if(BIT_IS_SET(TIFR, OCIE1A))
				SET_BIT(TIFR, OCIE1A);

			TCNT1 = 0;
		}
	}
	return 0;
}
