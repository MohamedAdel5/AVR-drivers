/*
 * icu.h
 *
 *  Created on: Sep 23, 2019
 *      Author: DR. ADEL
 */

#ifndef ICU_H_
#define ICU_H_
/*****************************************************************
 							  Includes
 *****************************************************************/
#include "../std/std.h"
/*****************************************************************
 							Defined Types
 *****************************************************************/
typedef enum
{
	FALLING,
	RISING
}ICU_edgeType;
typedef enum
{
	NO_CLOCK,
	F_CPU_CLOCK,
	F_CPU_8,
	F_CPU_64,
	F_CPU_256,
	F_CPU_1024,
	EXTERNAL_CLOCK_FALLING,
	EXTERNAL_CLOCK_RISING
}ICU_clock;
typedef enum
{
	NORMAL,
	CTC
}ICU_timerMode;
typedef enum
{
	OFF,
	ON
}ICU_noiseCancelerEnable;
typedef struct
{
	ICU_clock clock;			/*Choose a clock source (and a prescalar)*/
	ICU_edgeType  edgeType;		/*FALLING OR RISING*/
	ICU_timerMode timerMode;	/*Normal or CTC*/
	ICU_noiseCancelerEnable noiseCanceler_enable;	/*It causes a delay of 4 clock cycles as it considers a change only if it persists for at least 4 successive system clocks.*/

}ICU_config;
/*****************************************************************
 						Function prototypes
 *****************************************************************/
void ICU_init(const ICU_config* config);
void ICU_setEdgeType(const ICU_edgeType edge);
uint16 ICU_pollCapturedValue(void);
void ICU_clearTimer(void);
void ICU_interruptEnable(void (*ICU_callBackFunction)(void));
void ICU_deinit(void);


#endif /* ICU_H_ */
