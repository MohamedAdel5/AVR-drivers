/*
 * adc.h
 *
 *  Created on: Sep 14, 2019
 *      Author: DR. ADEL
 */

#ifndef ADC_H_
#define ADC_H_

/*****************************************************************
 * 							includes
 *****************************************************************/

#include "../std/std.h"

/*****************************************************************
 * 							ADC macros
 *****************************************************************/
/*Voltage Reference options*/
#define ADC_AREF (uint8)0x00U			/*AREF, Internal Vref turned off*/
#define ADC_AVCC (uint8)0x01U			/*AVCC with external capacitor at AREF pin*/
#define ADC_INTERNAL_VREF (uint8)0x02U	/*Internal 2.56V Voltage Reference with external capacitor at AREF pin*/

/*Result direction adjusting options*/
#define ADC_RESULT_ADJUST_LEFT (uint8)0x00U	/*The result will be left adjusted*/
#define ADC_RESULT_ADJUST_RIGHT (uint8)0x01U	/*Default - The result will be right adjusted*/

/*Auto Trigger source options*/

/*
 * ..
 * ..
 * ..
 * ..
 * NOT SUPPORTED IN THIS DRIVER YET
 * */

/*****************************************************************
 * 							Function prototypes
 *****************************************************************/
/*Initialize ADC*/
/*a_voltSelect => voltage reference => AREF, AVCC or internal voltage reference*/
/*a_resultAdjust => Adjust result to left or right*/
/*a_prescalar => Adjust the frequency of ADC to F_CPU/prescalar, Values: 2,4,8,16,32,64,128*/
/*If this parameter is set then an interrupt will be enabled with the function passed to the parameter*/
void ADC_init(uint8 a_voltSelect, uint8 a_resultAdjust, uint8 a_prescalar, void (*funcPtr)(void));

void ADC_disable(void);											/*Disable ADC immediately and ignore any ongoing conversions*/
void ADC_adjustResult(uint8 a_resultAdjust);					/*Adjust result to left or right immediately*/

uint16 ADC_readChannel(uint8 a_channelNum);
void ADC_disableInterrupt(void);

#endif /* ADC_H_ */
