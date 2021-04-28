/*
 * i2c.c
 *
 *  Created on: Oct 4, 2019
 *      Author: Mohamed Adel
 */
/**************************************************************
 	 	 	 	 	 	 	 Includes
 **************************************************************/
#include "i2c.h"
/**************************************************************
						 Data members(private)
 **************************************************************/
static void(*g_fptr_callBackFunction)(void) = NULLPTR;
/**************************************************************
 	 	 	 	 	 	 Functions defintions
 **************************************************************/
void TWI_init(TWI_config* a_pconfig)
{
	/*To calculate frequency of SCL use the equation: SCL(HZ) = FCPU / (16 + 2(TWBR).prescalar)*/
	/*Prescalar = 4^(value of TWPS)*/
	/*TWPS = 0,1,2,3*/
	/*From previous equation TWBR = (FCPU/SCL(HZ) - 16)/(2*prescalar)*/


	/*This may be changed later to be configurable*/
	/*Working with SCL frequency = 400KHZ so the values of TWPS and TWBR are 1 and 0 respectively*/

	TWBR = 0x02;			/*TWBR = 2*/

	CLEAR_BIT(TWSR, TWPS0);	/*Prescalar value = 1*/
	CLEAR_BIT(TWSR, TWPS1);

	/*This may be changed later to be configurable*/

	TWAR = (a_pconfig->slaveAddress) << 1;			/*disables general call recognition and setting slave address*/

	SET_BIT(TWCR, TWEN);	/*Enables TWI*/

}
void TWI_deinit(void)
{
	CLEAR_BIT(TWCR, TWEN);	/*Disables TWI*/
}
void TWI_setDeviceAddress(const uint8 a_address)
{
	TWAR = (a_address << 1) | (TWAR & 0x01);
}
TWI_status TWI_StartBit(void)
{
	SET_BIT(TWCR, TWSTA);
	SET_BIT(TWCR, TWINT);
	while(BIT_IS_CLEAR(TWCR, TWINT));
	if(TWI_getStatus() == MT_START)
	{
		CLEAR_BIT(TWCR, TWSTA);
		return TWI_SUCCESS;
	}
	else
	{
		return TWI_ERROR;
	}
}
void TWI_StopBit(void)
{
	SET_BIT(TWCR, TWSTO);				/*Sets stop bit*/
	SET_BIT(TWCR, TWINT);				/*Clear interrupt flag*/
}
TWI_status TWI_sendData(const uint8 a_data)
{
	TWDR = a_data;						/*Sets data to be sent*/
	SET_BIT(TWCR, TWINT);				/*Clear interrupt flag => starts sending data*/
	while(BIT_IS_CLEAR(TWCR, TWINT));	/*Wait till data is sent and ACK is sent back*/
	if(TWI_getStatus() == MT_SLA_W_ACK)	/*Check if the process is successful*/
	{
		return TWI_SUCCESS;
	}
	else
	{
		return TWI_ERROR;
	}
}
TWI_status TWI_readDataAck(uint8* a_pdata)
{
	SET_BIT(TWCR, TWEA);				/*Sets ACK enable bit to send ACK after reception*/
	SET_BIT(TWCR, TWINT);				/*Clear interrupt flag => starts receiving data*/
	while(BIT_IS_CLEAR(TWCR, TWINT));	/*Wait till data is received*/
	if(TWI_getStatus() == MR_SLA_R_ACK)	/*Check if the process is successful*/
	{
		*a_pdata = TWDR;
		return TWI_SUCCESS;
	}
	else
	{
		return TWI_ERROR;
	}

}
TWI_status TWI_readDataNack(uint8* a_pdata)
{
	CLEAR_BIT(TWCR, TWEA);				/*Clears ACK enable bit to send NACK after reception*/
	SET_BIT(TWCR, TWINT);				/*Clear interrupt flag => starts receiving data*/
	while(BIT_IS_CLEAR(TWCR, TWINT));	/*Wait till data is received*/
	if(TWI_getStatus() == MR_SLA_R_NACK)	/*Check if the process is successful*/
	{
		*a_pdata = TWDR;
		return TWI_SUCCESS;
	}
	else
	{
		return TWI_ERROR;
	}

}
uint8 TWI_getStatus(void)
{
	return (TWSR & 0xF8);	/*Returns Status register with the first 3 bits unmasked*/
}
void TWI_interruptEnable(void(*a_fptr_callBackFunction)(void))
{

	if(a_fptr_callBackFunction != NULLPTR)
	{
		g_fptr_callBackFunction = a_fptr_callBackFunction;
		SET_BIT(TWCR, TWIE);
	}
}
ISR(TWI_vect)
{
	(*g_fptr_callBackFunction)(); 	/*Callback function*/
	SET_BIT(TWCR, TWINT);			/*Clears interrupt flag because it is not cleared automatically*/
}
