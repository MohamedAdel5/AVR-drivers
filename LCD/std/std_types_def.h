/*
 * std_types_def.h
 *
 *  Created on: Sep 13, 2019
 *      Author: DR. ADEL
 */

#ifndef STD_TYPES_DEF_H_
#define STD_TYPES_DEF_H_
/*----------------------NULL----------------------------*/
#ifndef NULLPTR
#define NULLPTR ((void*)0)
#endif
/*----------------------Boolean----------------------------*/
#ifndef FALSE
#define FALSE (0U)
#endif

#ifndef TRUE
#define TRUE (1U)
#endif

#ifndef HIGH
#define HIGH
#endif

#ifndef LOW
#define LOW
#endif
/*----------------------integer----------------------------*/
/*1Byte*/
typedef unsigned char uint8;		/*0 -> 255*/
typedef signed char sint8;			/*-128 -> 127*/
/*2Bytes*/
typedef unsigned short uint16;		/*0 -> 65535*/
typedef signed short sint16;		/*-32768 -> 32767*/
/*4Bytes*/
typedef unsigned long uint32;		/*0 -> 4294967295*/
typedef signed long sint32;			/*-21474835648 -> 21474835647*/
/*8Bytes*/
typedef unsigned long long uint64;	/*0 -> 2^16*/
typedef signed long long sint64;	/*-2^15 -> 2^15 - 1*/

/*----------------------------------------------------------*/
/*----------------------float-------------------------------*/
/*4Bytes*/
typedef float float32;				/*1.2E-38 -> 3.4E+38*/
/*8Bytes*/
typedef double float64;				/*2.3E-308 -> 1.7E+308*/



#endif /* STD_TYPES_DEF_H_ */
