/*
 * timer0_ctc.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 */

#ifndef TIMER0_CTC_H_
#define TIMER0_CTC_H_
/*******************************************************************************
 *                     		 		Includes
 *******************************************************************************/
#include "microcontroller_config.h"
#include "std_types_def.h"
#include "common_macros.h"
/*******************************************************************************
*                    			Types definitions
 *******************************************************************************/

typedef enum
{
	NO_CLOCK,
	F_CPU_1,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024,
	EXTERNAL_T0,
	EXTERNAL_T1
}TIMER0_CTC_CLOCK;
/*******************************************************************************
 *                      		Functions Prototypes
 *******************************************************************************/
void TIMER0_CTC_init(TIMER0_CTC_CLOCK a_clock);
void TIMER0_CTC_deinit(void);
void TIMER0_CTC_stop(void);
void TIMER0_CTC_start(const uint8 a_startValue, const uint8 a_endValue);
void TIMER0_CTC_OC0Toggle(const uint8 a_endValue);
void TIMER0_CTC_setStartValue(const uint8 a_startValue);
void TIMER0_CTC_setEndValue(const uint8 a_endValue);
void TIMER0_CTC_interruptEnable(void (*a_fptr_callBackFunction)());

#endif /* TIMER0_CTC_H_ */
