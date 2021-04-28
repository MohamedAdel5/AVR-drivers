/*
 * timer1.h
 *
 *  Created on: Sep 16, 2019
 *      Author: DR. ADEL
 */

#ifndef TIMER1_H_
#define TIMER1_H_

/*****************************************************************
* 						  Includes
 *****************************************************************/
#include"std_types_def.h"
#include"common_macros.h"
#include"microcontroller_config.h"



/*****************************************************************
* 					Timer1 Configurations
 *****************************************************************/
/*Timer1 Clock and prescalar modes:*/
#define TIMER1_NO_CLOCK 0x00 					/*Timer1 OFF*/
#define TIMER1_PRESCALAR_1 0x01					/*Timer1 prescalar = 1 (no prescaling)*/
#define TIMER1_PRESCALAR_8 0x02 				/*Timer1 prescalar = 8*/
#define TIMER1_PRESCALAR_64 0x03 				/*Timer1 prescalar = 64*/
#define TIMER1_PRESCALAR_256 0x04 				/*Timer1 prescalar = 256*/
#define TIMER1_PRESCALAR_1024 0x05 				/*Timer1 prescalar = 1024*/
#define TIMER1_EXTERNAL_CLOCK_RISING_EDGE 0x06 	/*External clock on T1 pin (rising edge)*/
#define TIMER1_EXTERNAL_CLOCK_FALLING_EDGE 0x07	/*External clock on T1 pin (falling edge)*/

#define TIMER1_CLOCK TIMER1_PRESCALAR_1
/*----------------------------------------------------------------*/

/*Timer1 Modes:
 * CTC, FAST PWM & PWM PHASE CORRECT are configured using the OCR1A register NOT ICR1 register
 * Other Modes are not YET supported in this driver
 */
#define TIMER1_MODE_OVF 0x00 						/*overflow mode (normal mode)*/

#define TIMER1_MODE_CTC_NORMAL 0x01 				/*Normal port operation, OC1A/OC1B disconnected.*/
#define TIMER1_MODE_CTC_TOGGLE 0x02 				/*Toggle OC1A/OC1B on compare match*/
#define TIMER1_MODE_CTC_SET 0x03 					/*Clear OC1A/OC1B on compare match (Set output to low level)*/
#define TIMER1_MODE_CTC_CLEAR 0x04 					/*Set OC1A/OC1B on compare match (Set output to high level)*/


#define TIMER1_MODE_FAST_PWM_NORMAL_A 0x05 			/*Normal port operation, OC1A/OC1B disconnected.*/
#define TIMER1_MODE_FAST_PWM-TOGGLE_A 0x06 			/*Toggle OC1A on Compare Match, OC1B disconnected*/
#define TIMER1_MODE_FAST_PWM_INV_A 0x07 			/*Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,(non-inverting mode)*/
#define TIMER1_MODE_FAST_PWM_NON_INV_A 0x08 		/*Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM,(inverting mode)*/

#define TIMER1_MODE_FAST_PWM_NORMAL_B 0x09 			/*Normal port operation, OC1A/OC1B disconnected.*/
#define TIMER1_MODE_FAST_PWM-TOGGLE_B 0x0A 			/*Toggle OC1A on Compare Match, OC1B disconnected*/
#define TIMER1_MODE_FAST_PWM_INV_B 0x0B 			/*Clear OC1A/OC1B on compare match, set OC1A/OC1B at BOTTOM,(non-inverting mode)*/
#define TIMER1_MODE_FAST_PWM_NON_INV_B 0x0C 		/*Set OC1A/OC1B on compare match, clear OC1A/OC1B at BOTTOM,(inverting mode)*/


#define TIMER1_MODE_PHASE_CORRECT_NORMAL_A 0x0D 	/*Normal port operation, OC1A/OC1B disconnected.*/
#define TIMER1_MODE_PHASE_CORRECT_TOGGLE_A 0x0E 	/*Toggle OCnA on Compare Match, OCnB disconnected*/
#define TIMER1_MODE_PHASE_CORRECT_INV_A 0x0F 		/*Clear OC1A/OC1B on compare match when up-counting. Set OC1A/OC1B on compare match when downcounting.*/
#define TIMER1_MODE_PHASE_CORRECT_NON_INV_A 0x10 	/*Set OC1A/OC1B on compare match when upcounting. Clear OC1A/OC1B on compare match when downcounting.*/

#define TIMER1_MODE TIMER1_MODE_OVF
/*----------------------------------------------------------------*/

/*Timer1 Interrupts:*/
#define TIMER1_INTERRUPT_OVF
#define TIMER1_INTERRUPT_COMP_A
#define TIMER1_INTERRUPT_COMP_B

#define TIMER1_INTERRUPT_ENABLE 	/*Comment this Out to disable Interrupts*/
/*----------------------------------------------------------------*/


/*
 *
 * */
/*----------------------------------------------------------------*/

/*****************************************************************
 * 					Timer1 macros
 *****************************************************************/

#if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_A || TIMER1_MODE == TIMER1_MODE_CTC_SET_A || TIMER1_MODE == TIMER1_MODE_CTC_CLEAR_A)
	#define TIMER1_FOC1A_SET \
			TCCR1A |= (0b11001000);\
			CLEAR_BIT(TCCR1A,FOC1A);\
			if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_A)\
			{\
				CLEAR_BIT(TCCR1A,COM1A1);\
			}\
			else if(TIMER1_MODE == TIMER1_MODE_CTC_CLEAR_A)\
			{\
				CLEAR_BIT(TCCR1A,COM1A0);\
			}

	#define TIMER1_FOC1A_CLEAR \
			TCCR1A |= (0b10001000);\
			TCCR1A &= (0b10111111);\
			CLEAR_BIT(TCCR1A,FOC1A);\
			if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_A)\
			{\
				SET_BIT(TCCR1A,COM1A0);\
				CLEAR_BIT(TCCR1A,COM1A1);\
			}\
			else if(TIMER1_MODE == TIMER1_MODE_CTC_SET_A)\
			{\
				SET_BIT(TCCR1A,COM1A0);\
			}

#endif

#if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_B || TIMER1_MODE == TIMER1_MODE_CTC_SET_B || TIMER1_MODE == TIMER1_MODE_CTC_CLEAR_B)
	#define TIMER1_FOC1B_SET \
			TCCR1A |= (0b11001000);\
			CLEAR_BIT(TCCR1A,FOC1B);\
			if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_B)\
			{\
				CLEAR_BIT(TCCR1A,COM1B1);\
			}\
			else if(TIMER1_MODE == TIMER1_MODE_CTC_CLEAR_B)\
			{\
				CLEAR_BIT(TCCR1A,COM1B0);\
			}

	#define TIMER1_FOC1B_CLEAR \
			TCCR1A |= (0b10001000);\
			TCCR1A &= (0b10111111);\
			CLEAR_BIT(TCCR1A,FOC1B);\
			if(TIMER1_MODE == TIMER1_MODE_CTC_TOGGLE_B)\
			{\
				SET_BIT(TCCR1A,COM1B0);\
				CLEAR_BIT(TCCR1A,COM1B1);\
			}\
			else if(TIMER1_MODE == TIMER1_MODE_CTC_SET_B)\
			{\
				SET_BIT(TCCR1A,COM1B0);\
			}

#endif

/*****************************************************************
 * 					Functions prototypes
 *****************************************************************/
void TIMER1_OVF_init(uint8 start = 0, void (*funcPtr)(void) = ((void*)0));
void TIMER1_COMP_A_init(uint8 start = 0 );
void TIMER1_stop(void);	/*stop clock*/


#endif /* TIMER1_H_ */
