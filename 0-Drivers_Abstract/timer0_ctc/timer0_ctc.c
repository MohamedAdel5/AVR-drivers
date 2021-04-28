/*
 * timer0_ctc.c
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 */

/*******************************************************************************
 *                      		Includes
 *******************************************************************************/
#include "timer0_ctc.h"
/*******************************************************************************
*                    			Data members(private)
 *******************************************************************************/
static void(*g_fptr_callBackFunction)(void) = NULLPTR;
static TIMER0_CLOCK g_clock = 0;
/*******************************************************************************
 *                      		Functions Prototypes
 *******************************************************************************/
void TIMER0_CTC_init(TIMER0_CLOCK a_clock)
{
	/*Disable Force compare output on OC0 pin*/
	CLEAR_BIT(TCCR0, FOC0);
	/*Choosing Timer mode => CTC*/
	CLEAR_BIT(TCCR0, WGM00);
	SET_BIT(TCCR0, WGM01);
	/*Disable (disconnect) OC0 pin => normal mode*/
	CLEAR_BIT(TCCR0, COM00);
	CLEAR_BIT(TCCR0, COM01);
	TCNT0 = 0;
	g_clock = a_clock;
}
void TIMER0_CTC_deinit(void)
{
	/*Disconnect clock and reinitialize TCCR0 and OCR0*/
	TCCR0 = 0;
	TCNT0 = 0;
	OCR0 = 0;
	CLEAR_BIT(TIMSK, OCIE0); /*Disables interrupts*/
	SET_BIT(TIFR, OCF0);
	SET_BIT(TIFR, TOV0);
	g_fptr_callBackFunction = NULLPTR;
}
void TIMER0_CTC_stop(void)
{
	TCCR0 &= 0xF8;	/*Disconnect Clock*/
}
void TIMER0_CTC_start(const uint8 a_startValue, const uint8 a_endValue)
{
	TCNT0 = a_startValue;
	OCR0 = a_endValue;
	TCCR0 = (TCCR0 & 0xF8) | (g_clock & 0x07);
}
void TIMER0_CTC_OC0Toggle(const uint8 a_endValue)
{
	TIMER0_CTC_stop();
	SET_BIT(DDRB, PB3);		/*Set OC0 pin as output pin*/
	SET_BIT(TCCR0, COM00);	/*Set waveform mode to toggle on compare match*/
	CLEAR_BIT(TCCR0, COM01);
	TIMER0_CTC_start(0, a_endValue);	/*Sets end value at which the wave toggles its value*/
}
void TIMER0_CTC_setStartValue(const uint8 a_startValue)
{
	TCNT0 = a_startValue;
}
void TIMER0_CTC_setEndValue(const uint8 a_endValue)
{
	OCR0 = a_endValue;
}
void TIMER0_CTC_interruptEnable(void (*a_fptr_callBackFunction)())
{
	if(a_fptr_callBackFunction != NULLPTR)
	{
		SET_BIT(TIMSK, OCIE0);								/*Enable interrupts*/
		g_fptr_callBackFunction = a_fptr_callBackFunction;	/*Sets call back function*/
	}
}
ISR(TIMER0_COMP_vect)
{
	if(g_fptr_callBackFunction != NULLPTR)
	{
		(*g_fptr_callBackFunction)();
	}
	/*The interrupt flag is cleared automatically*/
}
