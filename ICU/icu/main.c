/*
 * main.c
 *
 *  Created on: Sep 23, 2019
 *      Author: DR. ADEL
 */

#include "icu.h"
#include "lcd.h"

volatile uint16 T1,T2,T3;
uint8 edge_num = 0;
void ICU_ISR(void);

int main(void)
{
	_delay_ms(100);
	LCD_init();
	GLOBAL_INTERRUPT_ENABLE;
	ICU_config config = {F_CPU_CLOCK, RISING, NORMAL, OFF};
	ICU_interruptEnable(ICU_ISR);
	ICU_init(&config);
	uint8 x= 0;

	while(1)
	{
		if(edge_num == 4)
		{
			if(x == 0 || x == 1)
			{

				LCD_sendCommand(LCD_RETURN_HOME);
				LCD_displayString("              ");
				LCD_sendCommand(LCD_RETURN_HOME);
				LCD_displayInteger(T1);
				LCD_displayString(" ");
				LCD_displayInteger(T2);
				LCD_displayString(" ");
				LCD_displayInteger(T3);
				x++;
			}
			uint32 duty_cycle = (float)(T3-T2)/(T3-T1)*100;
			LCD_sendCommand(LCD_MOVE_CURSOR_TO_SECOND_LINE);
			LCD_displayInteger(duty_cycle);

			ICU_deinit();
			edge_num++;
		}
	}
	return 0;
}
void ICU_ISR(void)
{

	switch(edge_num)
	{
	case 0:
		ICU_setEdgeType(FALLING);
		ICU_clearTimer();
		break;
	case 1:
		T1 = ICR1;
		ICU_setEdgeType(RISING);
		break;
	case 2:
		T2 = ICR1;
		ICU_setEdgeType(FALLING);

		break;
	case 3:
		T3 = ICR1;
		break;
	default:break;
	}

	edge_num++;
}
