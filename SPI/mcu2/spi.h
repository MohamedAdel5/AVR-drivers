/*
 * spi.h
 *
 *  Created on: Oct 1, 2019
 *      Author: DR. ADEL
 */

#ifndef SPI_H_
#define SPI_H_
/**************************************************************
 	 	 	 	 	 	 BUGS
 **************************************************************/
/*Mode0 with LSB mode on sending from slave to master(sends the data inverted and the last bit sent will be 1)*/
/*Mode0 with MSB mode on sending from slave to master(any ASCII data that is even number will be converted to the next character e.g: 'B'=>66 will be transmitted as 'C'=>67) this means that when the slave sends data the last sent bit always becomes 1*/
/*Mode1 works fine when sending from slave to master but it corrupts the data from master to slave*/
/*Mode2 and Mode3 both don't work*/

/**************************************************************
 	 	 	 	 	 	 Includes
 **************************************************************/
#include "microcontroller_config.h"
#include "std_types_def.h"
#include "common_macros.h"
/**************************************************************
 	 	 	 	 	 	configuration types definitions
 **************************************************************/
#define	SPI_TERMINATING_CHARACTER '#'

typedef enum
{
	MSB,		/*(0: MSB transmitted first) OR (1: LSB transmitted first)*/
	LSB
}SPI_data_order;
typedef enum
{
	DATA_MODE_0,	/*Start value: 0 & Sample on: rising edges*/
	DATA_MODE_1,	/*Start value: 0 & Sample on: falling edges*/
	DATA_MODE_2,	/*Start value: 1 & Sample on: falling edges*/
	DATA_MODE_3		/*Start value: 1 & Sample on: rising edges*/
}SPI_data_mode;
typedef enum
{
	F_CPU_4,
	F_CPU_16,
	F_CPU_64,
	F_CPU_128,
	/*the Following modes are NOT functional in slave mode because the double SPI speed bit works only in master mode*/
	F_CPU_2,
	F_CPU_8,
	F_CPU_32
}SPI_clock;		/*SCK frequency (minimum is F_CPU/4)*/

typedef struct
{
	SPI_data_order dataOrder;
	SPI_data_mode dataMode;
	SPI_clock clock;
}SPI_config;

/**************************************************************
 	 	 	 	 	 	 Functions prototypes
 **************************************************************/

void SPI_masterInit(const SPI_config* config);		/*Initialize(enable) SPI as master*/
void SPI_slaveInit(const SPI_config* config);		/*Initialize(enable) SPI as slave*/
void SPI_deinit(void);								/*Disable SPI*/

/*If you are a master:
 * You want to send only: use sendByte function and give it the data as a parameter
 * You want to receive only: use receiveByte function and take the received data as the function return value
 * You want to send and receive at the same time: use sendByte function and give it the data to be sent as a parameter then use getReceivedData function to get the received data
 * If you are a Slave:
 * You want to send only: use sendByte function and give it the data as a parameter and the master should receive your data
 * You want to receive only: use receiveByte function and take the received data as the function return value
 * You want to send and receive at the same time: use sendByte function and give it the data to be sent as a parameter then the master should receive your data(at this point you should put some delay because here the master should use sendByte function to send his data) then use getReceivedData function to get the received data
 * */
void SPI_sendByte(uint8 data);						/*Sends 1 Byte*/
uint8 SPI_receiveByte(void);						/*Receives 1 Byte*/
uint8 SPI_getReceivedData(void);					/*Returns the data in SPDR register*/
void SPI_sendString(const uint8* str);				/*Sends a string of bytes*/
void SPI_receiveString(uint8* str);					/*Receives a string of bytes*/
void SPI_interrupt_enable(void (*a_fptr_callBackFunction)(void));	/*Check for the WCOL(write collision) Flag in the call back function because it causes an interrupt too(check the datasheet), Also using the SS pin as input pin with master will trigger the interrupt flag if the SS pin is driven to LOW*/

#endif /* SPI_H_ */
