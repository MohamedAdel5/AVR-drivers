/*
 * timer0_pwm.h
 *
 *  Created on: Oct 5, 2019
 *      Author: Mohamed Adel
 *
 *
 *		Fast PWM mode in TIMER0
 * */

#ifndef TIMER0_PWM_H_
#define TIMER0_PWM_H_

/*******************************************************************************
 *                    				Includes
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
}TIMER0_PWM_CLOCK;
typedef enum
{
	NON_INVERTING,
	INVERTING
}TIMER0_PWM_MODE;

/*******************************************************************************
*                    			Functions prototypes
 *******************************************************************************/

/*To configure the frequency of the PWM use the equation F(pwm) = FCPU/(256*prescalar)*/
/*NOTE!: Calling PWM_init() will configure pin OC0 as output pin*/

void TIMER0_PWM_init(TIMER0_PWM_CLOCK a_clock);
void TIMER0_PWM_deinit(void);
void TIMER0_PWM_stop(void);
void TIMER0_PWM_start(const TIMER0_PWM_MODE a_pwmMode, const uint8 a_dutyCycle);
void TIMER0_PWM_setDutyCycle(const uint8 a_endValue);

#endif /* TIMER0_PWM_H_ */
