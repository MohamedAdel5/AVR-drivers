/*
 * main.c
 *
 *  Created on: Sep 17, 2019
 *      Author: DR. ADEL
 */


#include "adc.h"
#include"lcd.h"

int main(void)
{
	LCD_init();
	ADC_init(ADC_AREF, ADC_RESULT_ADJUST_RIGHT, 8, NULL);

	LCD_displayString("Temp = ");
	while(1)
	{
		uint16 reading = ADC_readChannel(2);
		if(reading < 10)
		{
			/*The negative values are NOT Accurate because the output valtage of the
			 * temp sensor ranges from 0V -> 0.05V
			 * which is mapped in the ADC by the values 0 -> 10
			 * which corresponds to the temp values -55 -> 0
			*/
			LCD_displayInteger((reading*55/10)-55);
		}
		else
		{
			LCD_displayInteger((reading-10)*150/308);
		}
		LCD_displayString("   ");
		LCD_goToRowColumn(1,8);
	}
	return 0;
}
