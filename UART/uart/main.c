/*
 * main.c
 *
 *  Created on: Sep 29, 2019
 *      Author: DR. ADEL
 */

#include "uart.h"
#include "keypad.h"



int main(void)
{
	UART_config config = {TR, BAUD_RATE_9600, EVEN, STOP_BIT_1};
	UART_init(&config);

	while(1)
	{

	}
	return 0;
}
