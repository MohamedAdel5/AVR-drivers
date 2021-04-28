/*
 * keypad.c
 *
 *  Created on: Sep 13, 2019
 *      Author: Mohamed ADEL
 */

/*******************************************************************************
 *                              Includes
 *******************************************************************************/
#include "keypad.h"


/*******************************************************************************
 *                      Functions Prototypes(Private)
 *******************************************************************************/

/*adjustKeyNumber is a UTILITY  function that takes the key order(keys are ordered from 1 to 16 or 12)
 * and returns the value of the key to be used by the user(the value is a number or an ASCII value of a character)*/
#if (N_COL == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 keyNumber);
#elif (N_COL == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 keyNumber);
#endif

/*******************************************************************************
 *                        Functions Definitions
 *******************************************************************************/
uint8 KEYPAD_getKeyPressed(void)
{
	while(1)		/*Never get out without receiving an input from the user*/
	{
		uint8 row, col;
		for(col = 0; col < N_COL; ++col)
		{

#if(N_COL == 4)
			/*Set 1 pin to be output and 4 pins to be input the remaining 3 pins are to be inputs
			 * to ensure that they do not output any signal(1|0)*/
			KEYPAD_PORT_DIR = (0b00001000 >> col);
			/*Set the output pin to HIGH and the rest are set as pull ups*/
			KEYPAD_PORT_OUT = ~(KEYPAD_PORT_DIR);
#elif(N_COL == 3)
			/*Set 1 pin to be output and 4 pins to be input the remaining 2 pins are to be inputs
			* to ensure that they do not output any signal(1|0)*/
			KEYPAD_PORT_DIR = (KEYPAD_PORT_DIR & 0x80) | ((0b00000100 >> col) & 0x7F);
			/*Set the output pin to HIGH and the rest are set as pull ups*/
			KEYPAD_PORT_OUT = (KEYPAD_PORT_DIR & 0x80) | (~(KEYPAD_PORT_DIR) & 0x7F);
#endif

			for(row = 0; row < N_ROW; ++row)
			{
#if(N_COL == 4)
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN, (7-row)))
#elif(N_COL == 3)
				if(BIT_IS_CLEAR(KEYPAD_PORT_IN, (6-row)))
#endif
				{
					#if(N_COL == 4)
					return KEYPAD_4x4_adjustKeyNumber(row*4 + col + 1);
					#elif(N_COL == 3)
					return KEYPAD_4x3_adjustKeyNumber(row*3 + col + 1);
					#endif
				}
			}
		}
	}


}

#if (N_COL == 4)
static uint8 KEYPAD_4x4_adjustKeyNumber(uint8 keyNumber)
{
	/*For Porteus Keypad Interface*/

	switch(keyNumber)
	{
		case 1: return 7;
				break;
		case 2: return 8;
				break;
		case 3: return 9;
				break;
		case 4: return '/'; // ASCII Code of /
				break;
		case 5: return 4;
				break;
		case 6: return 5;
				break;
		case 7: return 6;
				break;
		case 8: return '*'; /* ASCII Code of '*' */
				break;
		case 9: return 1;
				break;
		case 10: return 2;
				break;
		case 11: return 3;
				break;
		case 12: return '-'; /* ASCII Code of '-' */
				break;
		case 13: return 13;  /* ASCII of Enter */
				break;
		case 14: return 0;
				break;
		case 15: return '='; /* ASCII Code of '=' */
				break;
		case 16: return '+'; /* ASCII Code of '+' */
				break;
		default: return keyNumber;
				break;
	}

	/*4 x 4 Matrix Keypad Membrane (16 Keys)*/
	/*switch(keyNumber)
	{
	case 4: return 'A';
	break;
	case 5: return 4;
		break;
	case 6: return 5;
		break;
	case 7: return 6;
		break;
	case 8: return 'B';
		break;
	case 9: return 7;
		break;
	case 10: return 8;
		break;
	case 11: return 9;
		break;
	case 12: return 'C';
		break;
	case 13: return '*';
		break;
	case 14: return 0;
		break;
	case 15: return '#';
		break;
	case 16: return 'D';
		break;
	}*/
}
#elif (N_COL == 3)
static uint8 KEYPAD_4x3_adjustKeyNumber(uint8 keyNumber)
{
	/**/
	switch(keyNumber)
		{
			case 10: return '*'; // ASCII Code of *
				break;
			case 11: return 0;
				break;
			case 12: return '#'; // ASCII Code of #
				break;
			default: return keyNumber;
				break;
		}

}
#endif
