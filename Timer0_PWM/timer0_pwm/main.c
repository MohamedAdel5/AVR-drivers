/*
 * main.c
 *
 *  Created on: Oct 5, 2019
 *      Author: DR. ADEL
 */

#include "timer0_pwm.h"

int main(void)
{
	TIMER0_PWM_init(F_CPU_8);
	TIMER0_PWM_start(NON_INVERTING, 0);
	unsigned char duty;
	while(1)
	{
		for(duty = 0 ; duty < 100 ; duty++)
		{
			/*increase the LED light intensity*/

			TIMER0_PWM_start(NON_INVERTING, duty);
			_delay_ms(10);
		}
		_delay_ms(100);
		for(duty = 100 ; duty > 0 ; duty--)
		{
			/*decrease the LED light intensity*/
			TIMER0_PWM_start(NON_INVERTING, duty);
			_delay_ms(10);
		}
	}
}
