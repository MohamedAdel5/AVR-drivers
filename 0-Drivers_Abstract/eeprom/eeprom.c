/*
 * eeprom.c
 *
 *  Created on: Oct 4, 2019
 *      Author: Mohamed Adel
 */

/**************************************************************
						   Includes
***************************************************************/
#include "eeprom.h"

/**************************************************************
					   Functions definitions
***************************************************************/
void EEPROM_init(void)
{
	TWI_config twi_config_struct = {0x01};	/*Setting the slave address of the MCU by any value*/
	TWI_init(&twi_config_struct);	/*Enables communication with EEPROM using TWI protocol*/
}
void EEPROM_deinit(void)
{
	TWI_deinit();	/*Disables communication with EEPROM*/
}
EEPROM_status EEPROM_writeByte(const uint16 a_address, const uint8 a_data)
{
	uint8 SLA = 0xA0;
	if(TWI_startBit() != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(SLA | ((a_address >> 7) & 0x0E)) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(a_address) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(a_data) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	TWI_stopBit();
	return EEPROM_SUCCESS;
}
EEPROM_status EEPROM_readByte(const uint16 a_address, uint8 *a_pdata)
{
	uint8 SLA = 0xA0;
	if(TWI_startBit() != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(SLA | ((a_address >> 7) & 0x0E)) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(a_address) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_startBit() != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_sendData(SLA | ((a_address >> 7) & 0x0E) | 0x01) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	if(TWI_readDataNack(a_pdata) != TWI_SUCCESS)
	{
		return EEPROM_ERROR;
	}
	TWI_stopBit();
	return EEPROM_SUCCESS;
}
