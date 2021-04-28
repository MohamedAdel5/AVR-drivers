/*
 * i2c.h
 *
 *  Created on: Oct 4, 2019
 *      Author: Mohamed Adel
 */
/**************************************************************
 	 	 	 	 	 To be done later
 **************************************************************/
/*Make the operating frequency configurable*/
/*Make the general call recognition enable bit configurable*/
/*Make Slave address configurable*/
/*No checking on word collision flag bit*/
/*Slave receiver and transmitter modes*/
/*Interrupts are not tested*/


#ifndef I2C_H_
#define I2C_H_

/**************************************************************
 	 	 	 	 	 	 Includes
 **************************************************************/
#include "microcontroller_config.h"
#include "std_types_def.h"
#include "common_macros.h"

/**************************************************************
 	 	 	 	 	 	 Type definitions
 **************************************************************/
/*For clear code*/
typedef uint8 TWI_status;
#define TWI_ERROR 0
#define TWI_SUCCESS 1

typedef struct
{
	uint8 slaveAddress;	/*The address has to be seven bit address.. NOTE!: the given 8-bits will be shifted left by 1*/
}TWI_config;
/**************************************************************
 	 	 	 	 	 	 TWI status macros
 **************************************************************/
/*Master Transmitter mode*/
#define MT_START 0x08
#define MT_REP_START 0x10
#define MT_SLA_W_ACK 0x18
#define MT_SLA_W_NACK 0x20
#define MT_DATA_ACK 0x28
#define MT_DATA_NACK 0x30
#define MT_ARB_lOST 0x38

/*Master Receiver mode*/
#define MR_START 0x08		/*Redundant*/
#define MR_REP_START 0x10	/*Redundant*/
#define MR_SLA_R_ACK 0x40
#define MR_SLA_R_NACK 0x48
#define MR_DATA_ACK 0x50
#define MR_DATA_NACK 0x58
#define MR_ARB_LOST 0x38

/**************************************************************
 	 	 	 	 	 	 Functions prototypes
 **************************************************************/
void TWI_init(TWI_config* a_pconfig);						/*Initializes TWI sets the operating frequency*/
void TWI_deinit(void);						/*De-initializes TWI*/
void TWI_setDeviceAddress(const uint8 a_address);	/*Sets the device address*/
TWI_status TWI_startBit(void);				/*Sends start bit, returns SUCCESS or ERROR*/
void TWI_stopBit(void);				/*Sends stop bit , returns SUCCESS or ERROR*/
TWI_status TWI_sendData(const uint8 a_data);		/*Sends the given data(SlaveAddress+R/W  or  a Byte to transmit)*/
TWI_status TWI_readDataAck(uint8* a_pdata);	/*Reads the received data and returns it in the parameter data then sends ACK*/
TWI_status TWI_readDataNack(uint8* a_pdata);	/*Reads the received data and returns it in the parameter data then sends NACK*/
uint8 TWI_getStatus(void);					/*Returns the status register data*/
void TWI_interruptEnable(void(*a_fptr_callBackFunction)(void));	/*Enable interrupts and sets the ISR with a callback function*/

#endif /* I2C_H_ */
