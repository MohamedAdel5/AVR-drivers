/*
 * dc_motor.h
 *
 *  Created on: Oct 6, 2019
 *      Author: DR. ADEL
 */

#ifndef DC_MOTOR_DC_MOTOR_H_
#define DC_MOTOR_DC_MOTOR_H_

/*********************************************************************
						   Include Files
 ********************************************************************/
#include "../std/std.h"
#include "../timer0_pwm/timer0_pwm.h"

/*********************************************************************
						 Configurations
********************************************************************/

/*The driver assumes the clock is 8MHZ and it uses TIMER0 in fast pwm mode so OC0 pin is taken*/
/*The operating frequency is 500HZ*/
#define DC_MOTOR_IN_PORT_DIR DDRD
#define DC_MOTOR_IN_PORT PORTD

#define DC_MOTOR_IN1 PD5
#define DC_MOTOR_IN2 PD6

/*********************************************************************
						 Functions prototypes
********************************************************************/
void DC_MOTR_init(void);
void DC_MOTR_deinit(void);
void DC_MOTR_rotateCW(void);
void DC_MOTOR_rotateCCW(void);
void DC_MOTOR_stop(void);
void DC_MOTOR_setSpeed(uint8 dutyCycle);
#endif /* DC_MOTOR_DC_MOTOR_H_ */
