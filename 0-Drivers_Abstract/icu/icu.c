/*
 * icu.c
 *
 *  Created on: Sep 23, 2019
 *      Author: DR. ADEL
 */
/*****************************************************************
 							Includes
 *****************************************************************/
#include "icu.h"
/*****************************************************************
 						Data members(private)
 *****************************************************************/
static void(*g_ICU_callBackFunction)(void) = NULLPTR;
/*****************************************************************
 						Functions definitions
 *****************************************************************/


void ICU_init(const ICU_config* config)
{
	CLEAR_BIT(DDRD, PD6); /*Set ICP1 as input pin*/
	TCNT1 = 0;	/*Initial value for Timer*/
	ICR1 = 0; 	/*Initial value for ICU register*/
	TCCR1A = 0;
	switch(config->timerMode)
	{
	default:	/*DEFAULT value for any wrong inputs is NORMAL mode*/
	case NORMAL:
		CLEAR_BIT(TCCR1B, WGM12);
		break;
	case CTC:
		SET_BIT(TCCR1B, WGM12);
		break;
	}
	CLEAR_BIT(TCCR1B, WGM13); /*Cleared in both modes*/

	switch(config->noiseCanceler_enable)
	{
	default:	/*DEFAULT value for any wrong inputs is OFF*/
	case OFF:
		CLEAR_BIT(TCCR1B, ICNC1);
		break;
	case ON:
		SET_BIT(TCCR1B, ICNC1);
		break;
	}

	switch(config->clock)
	{
		case NO_CLOCK:
		case F_CPU_CLOCK:
		case F_CPU_8:
		case F_CPU_64:
		case F_CPU_256:
		case F_CPU_1024:
			TCCR1B = (TCCR1B & 0xF8) | ((config->clock) & 0x07);
			break;
		default:
			TCCR1B = (TCCR1B & 0xF8) | ((F_CPU_CLOCK) & 0x07); /*DEFAULT for wrong inputs is F_CPU_CLOCK*/
			break;
	}

	switch(config->edgeType)
	{
	default:
	case RISING:
		SET_BIT(TCCR1B, ICES1);
		break;
	case FALLING:
		CLEAR_BIT(TCCR1B, ICES1);
		break;
	}


	CLEAR_BIT(TCCR1B, 5); /*Datasheet requirement (reserved bit)*/

}
void ICU_setEdgeType(const ICU_edgeType edge)
{
	switch(edge)
	{
	default:
	case RISING:
		SET_BIT(TCCR1B, ICES1);
		break;
	case FALLING:
		CLEAR_BIT(TCCR1B, ICES1);
		break;
	}
}
uint16 ICU_pollCapturedValue(void)
{
	while(BIT_IS_CLEAR(TIFR, ICF1));
	return ICR1;
}
void ICU_clearTimer(void)
{
	TCNT1 = 0;
}
void ICU_interruptEnable(void (*ICU_callBackFunction)(void))
{
	g_ICU_callBackFunction = ICU_callBackFunction;
	SET_BIT(TIMSK, TICIE1);
}
void ICU_deinit(void)
{

	TCNT1 = 0; 		/*clear timer*/
	ICR1 = 0;		/*Clear ICU register*/
	TIFR |= (0x3C); /*clear all flags*/
	CLEAR_BIT(TIMSK, TICIE1); /*clear interrupt enable*/
	TCCR1B &= 0xF8; /*stop timer clock (NO_CLOCK)*/
}
ISR(TIMER1_CAPT_vect)
{
	if(g_ICU_callBackFunction != NULLPTR)
	{
		(*g_ICU_callBackFunction)();
		/*The interrupt flag is automatically cleared*/
	}
}
