/*
 * keypad.h
 *
 *  Created on: Sep 13, 2019
 *      Author: Mohamed ADEL
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

/*******************************************************************************
 *                        		Includes
 *******************************************************************************/
#include "std_types_def.h"
#include "microcontroller_config.h"
#include "common_macros.h"

/*******************************************************************************
 *                        Keypad configurations
 *******************************************************************************/
/*The keypad uses 8 pins(1 Port) in case of 4x4 configuration*/
/*The keypad uses 7 pins(pins0:6) in case of 4x3 configuration*/

/*The keypad rows are connected to the last 4 pins in the port(rows1:4 connected to pins7:4) in case of 4x4 keypad*/
/*The keypad rows are connected to the last 4 pins in the port(rows1:4 connected to pins6:3) in case of 4x3 keypad*/

/*The keypad columns are connected to the first 4 pins in the port(cols1:4 connected to pins3:0)  in case of 4x4 keypad*/
/*The keypad columns are connected to the first 3 pins in the port(cols1:3 connected to pins2:0) in case of 4x3 keypad*/


#define N_COL 4		/*Choose 3 => for 3x4 keypad config    OR choose 4 => for 4x4 keypad config*/
#define N_ROW 4		/*NOT CONFIGURABLE till the moment so do not change it*/

/*Choose the PORT you want the keypad to be connected to*/
#define	KEYPAD_PORT_OUT PORTA
#define KEYPAD_PORT_IN	PINA
#define KEYPAD_PORT_DIR DDRA



/*******************************************************************************
 *                       Functions Prototypes
 *******************************************************************************/
uint8 KEYPAD_getKeyPressed(void);


#endif /* KEYPAD_H_ */
