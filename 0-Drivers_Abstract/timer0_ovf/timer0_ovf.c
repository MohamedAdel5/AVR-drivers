/*
 * timer0_ovf.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 */
/*******************************************************************************
*                    				Includes
 *******************************************************************************/
#include "timer0_ovf.h"
/*******************************************************************************
*                    			Data members(private)
 *******************************************************************************/
static void(*g_fptr_callBackFunction)(void) = NULLPTR;
static TIMER0_CLOCK g_clock = 0;
/*******************************************************************************
*                    			Functions Definitions
 *******************************************************************************/
void TIMER0_OVF_init(TIMER0_CLOCK a_clock)
{
	/*Disable Force compare output on OC0 pin*/
	CLEAR_BIT(TCCR0, FOC0);
	/*Choosing Timer mode => Normal(overflow)*/
	CLEAR_BIT(TCCR0, WGM00);
	CLEAR_BIT(TCCR0, WGM01);
	/*Disable (disconnect) OC0 pin => normal mode*/
	CLEAR_BIT(TCCR0, COM00);
	CLEAR_BIT(TCCR0, COM01);
	TCNT0 = 0;
	g_clock = a_clock;
}
void TIMER0_OVF_deinit(void)
{
	/*Disconnect clock and reinitialize TCCR0*/
	TCCR0 = 0;
	TCNT0 = 0;
	CLEAR_BIT(TIMSK, TOIE0); /*Disables interrupts*/
	SET_BIT(TIFR, TOV0);
	SET_BIT(TIFR, OCF0);
	g_fptr_callBackFunction = NULLPTR;
}
void TIMER0_OVF_stop(void)
{
	TCCR0 &= 0xF8;	/*Disconnect Clock*/
}
void TIMER0_OVF_start(const uint8 a_startValue)
{
	TCNT0 = a_startValue;
	TCCR0 = (TCCR0 & 0xF8) | (g_clock & 0x07);
}
void TIMER0_OVF_setStartValue(const uint8 a_startValue)
{
	TCNT0 = a_startValue;
}
void TIMER0_OVF_interruptEnable(void (*a_fptr_callBackFunction)())
{
	if(a_fptr_callBackFunction != NULLPTR)
	{
		SET_BIT(TIMSK, TOIE0);								/*Enable interrupts*/
		g_fptr_callBackFunction = a_fptr_callBackFunction;	/*Sets call back function*/
	}
}
ISR(TIMER0_OVF_vect)
{
	if(g_fptr_callBackFunction != NULLPTR)
	{
		(*g_fptr_callBackFunction)();
	}
	/*The interrupt flag is cleared automatically*/
}
