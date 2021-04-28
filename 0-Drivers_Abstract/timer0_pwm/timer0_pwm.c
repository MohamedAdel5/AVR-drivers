/*
 * timer0_pwm.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 */


/*******************************************************************************
*                    				Includes
 *******************************************************************************/
#include "timer0_pwm.h"
/*******************************************************************************
*                    			Data members(private)
 *******************************************************************************/
static TIMER0_CLOCK g_clock = 0;
/*******************************************************************************
*                    			Functions Definitions
 *******************************************************************************/
void TIMER0_PWM_init(TIMER0_CLOCK a_clock)
{
	SET_BIT(DDRB, PB3);		/*Set OC0 pin as output pin*/
	/*Disables Force compare output on OC0 pin => PWM modes have to disable this pin*/
	CLEAR_BIT(TCCR0, FOC0);
	/*Choosing Timer mode => FAST PWM*/
	SET_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);

	TCNT0 = 0;
	g_clock = a_clock;
}
void TIMER0_PWM_deinit(void)
{
	/*Disconnects clock and reinitialize TCCR0*/
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	SET_BIT(TIFR, OCF0);
	SET_BIT(TIFR, TOV0);
}
void TIMER0_PWM_stop(void)
{
	TCCR0 &= 0xF8;	/*Disconnects Clock*/
}
void TIMER0_PWM_start(const TIMER0_PWM_MODE a_pwmMode, const uint8 a_dutyCycle)
{
	switch(a_pwmMode)
	{
	default:
	case NON_INVERTING:
		CLEAR_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;
	case INVERTING:
		SET_BIT(TCCR0, COM00);
		SET_BIT(TCCR0, COM01);
		break;
	}
	TCNT0 = 0;
	OCR0 = (a_dutyCycle*255)/ 100;
	TCCR0 = (TCCR0 & 0xF8) | (g_clock & 0x07);	/*Start clock*/
}
void TIMER0_PWM_setDutyCycle(const uint8 a_dutyCycle)
{
	OCR0 = (a_dutyCycle*255) / 100;
}
