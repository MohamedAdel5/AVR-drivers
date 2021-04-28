/*
 * microcontroller_config.h
 *
 *  Created on: Sep 13, 2019
 *      Author: DR. ADEL
 */

#ifndef MICROCONTROLLER_CONFIG_H_
#define MICROCONTROLLER_CONFIG_H_

/*Microcontroller operating frequency*/
#ifndef F_CPU
#define F_CPU (1000000U)
#endif

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#endif /* MICROCONTROLLER_CONFIG_H_ */
