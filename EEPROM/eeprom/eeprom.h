/*
 * eeprom.h
 *
 *  Created on: Oct 4, 2019
 *      Author: Mohamed Adel
 */

#ifndef EEPROM_H_
#define EEPROM_H_
/**************************************************************
						   Includes
***************************************************************/
#include "microcontroller_config.h"
#include "std_types_def.h"
#include "common_macros.h"
#include "i2c.h"
/**************************************************************
						Types definitions
***************************************************************/

typedef uint8 EEPROM_status;
#define EEPROM_ERROR 0
#define EEPROM_SUCCESS 1

/**************************************************************
					 Functions prototypes
***************************************************************/
void EEPROM_init(void);		/*Initialize EEPROM => starts communication with EEPROM using TWI protocol*/
void EEPROM_deinit(void);	/*Deinitialize EEPROM => closes communication with EEPROM (disables TWI protocol)*/
EEPROM_status EEPROM_writeByte(const uint16 a_address, const uint8 a_data);	/*Write a byte in EEPROM at a certain address*/
EEPROM_status EEPROM_readByte(const uint16 a_address, uint8 *a_pdata);		/*Read a byte at a certain address in the EEPROM*/

#endif /* EEPROM_H_ */
