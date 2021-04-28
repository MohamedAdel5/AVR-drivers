/*
 * timer0_ovf.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 */

#ifndef TIMER0_OVF_H_
#define TIMER0_OVF_H_

/*******************************************************************************
 *                    				Includes
 *******************************************************************************/
#include "../std/std.h"

/*******************************************************************************
*                    			Types definitions
 *******************************************************************************/
#ifndef ENUM_CLOCK
#define ENUM_CLOCK
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
}TIMER0_CLOCK;
#endif
/*typedef struct
{
	TIMER0_OVF_CLOCK clock;
}TIMER0_OVF_config;*/
/*******************************************************************************
*                    			Functions prototypes
 *******************************************************************************/
void TIMER0_OVF_init(TIMER0_CLOCK a_clock);
void TIMER0_OVF_deinit(void);
void TIMER0_OVF_stop(void);
void TIMER0_OVF_start(const uint8 a_startValue);
void TIMER0_OVF_setStartValue(const uint8 a_startValue);
void TIMER0_OVF_interruptEnable(void (*a_fptr_callBackFunction)());
#endif /* TIMER0_OVF_H_ */
