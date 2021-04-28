/*
 * dc_motor.c
 *
 *  Created on: Oct 6, 2019
 *      Author: DR. ADEL
 */
/*********************************************************************
						 Include files
********************************************************************/
#include "dc_motor.h"
/*********************************************************************
						 Functions definitions
********************************************************************/
void DC_MOTR_init(void)
{
	/*Set output pins*/
	SET_BIT(DC_MOTOR_IN_PORT_DIR, DC_MOTOR_IN1);
	SET_BIT(DC_MOTOR_IN_PORT_DIR, DC_MOTOR_IN2);
	DC_MOTOR_stop();
	TIMER0_PWM_init(F_CPU_64);	/*To work on frequency = 500HZ*/
}
void DC_MOTR_deinit(void)
{
	DC_MOTOR_stop();
	TIMER0_PWM_deinit();
}
void DC_MOTR_rotateCW(void)
{
	SET_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN1);
	CLEAR_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN2);
}
void DC_MOTOR_rotateCCW(void)
{
	CLEAR_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN1);
	SET_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN2);
}
void DC_MOTOR_stop(void)
{
	CLEAR_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN1);
	CLEAR_BIT(DC_MOTOR_IN_PORT, DC_MOTOR_IN2);
}
void DC_MOTOR_setSpeed(uint8 dutyCycle)
{
	TIMER0_PWM_start(NON_INVERTING, dutyCycle);
}
