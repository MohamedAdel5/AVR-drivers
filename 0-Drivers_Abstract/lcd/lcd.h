/*
 * lcd.h
 *
 *  Created on: Sep 13, 2019
 *      Author: DR. ADEL
 */

#ifndef LCD_H_
#define LCD_H_
/****************************************************************
 * 							Included files
 *****************************************************************/

#include "../std/std.h"


/****************************************************************
 * 							LCD commands macros
 *****************************************************************/
/*Clears the display data*/
#define LCD_CLEAR_DISPLAY 0x01


/*Return Home*/
/*Required for 4-bit mode*/
#define LCD_RETURN_HOME 0X02	/*Move Cursor to address 0 in DDRAM(data display RAM) AND Returns display to its original state if it was shifted*/


/*Entry mode*/
/*When return home command is sent the shifting will be canceled*/
#define LCD_ENTRY_MODE_CURSOR_AUTO_INC 0x06 				/*When a character is written the cursor increments - Default entry mode*/
#define LCD_ENTRY_MODE_CURSOR_AUTO_DEC 0x04					/*When a character is written the cursor decrements*/
#define LCD_ENTRY_MODE_SHIFT_LEFT_CURSOR_AUTO_INC	0x07	/*When a character is written the cursor increments and the display is shifted left*/
#define LCD_ENTRY_MODE_SHIFT_RIGHT_CURSOR_AUTO_DEC 0x05		/*When a character is written the cursor decrements and the display is shifted right*/



/*Display options*/
#define LCD_DISPLAY_ON 0x0C				/*Display ON*/
#define LCD_DISPLAY_OFF 0x08			/*Display OFF*/
#define LCD_SHIFT_DISPLAY_LEFT 0x18		/*Shifts the entire display to the left by 1 bit (You can shift untill the line wraps up again)*/
#define LCD_SHIFT_DISPLAY_RIGHT 0x1C	/*Shifts the entire display to the right by 1 bit (You can shift untill the line wraps up again)*/

/*Set LCD Interfacing Modes*/
/*All the modes are 5x8 dots use the datasheet for 5x11 dots mode configuration*/
/*All modes are for two line mode use the datasheet for other modes configuration*/
#define LCD_TWO_LINE_8_BIT 0X38		/*8 bit interface*/
#define LCD_TWO_LINE_4_BIT 0X28		/*4 bit interface*/

/*Cursor Options*/
#define LCD_CURSOR_ON_BLINK_ON  0x0F			/*Cursor Blinks*/
#define LCD_CURSOR_ON_BLINK_OFF  0x0E			/*Cursor Blink OFF*/
#define LCD_CURSOR_OFF 0x0C						/*Cursor OFF*/
#define LCD_CURSOR_INC 0x14						/*Increment the Cursor position*/
#define LCD_CURSOR_DEC 0x10						/*Decrement the Cursor position*/
#define LCD_SET_CURSOR_LOCATION 0X80			/*Set Cursor location to a certain address*/
#define LCD_MOVE_CURSOR_TO_FIRST_LINE 0x80		/*Move Cursor to the beginning of the first line*/
#define LCD_MOVE_CURSOR_TO_SECOND_LINE 0xC0		/*Move Cursor to the beginning of the second line*/

/*Moving cursor to each byte in DDRAM [to be used for storing data]*/
#define LCD_MOVE_CURSOR_TO_BYTE_1 0x80
#define LCD_MOVE_CURSOR_TO_BYTE_2 0x88
#define LCD_MOVE_CURSOR_TO_BYTE_3 0x90
#define LCD_MOVE_CURSOR_TO_BYTE_4 0x98
#define LCD_MOVE_CURSOR_TO_BYTE_5 0xC0
#define LCD_MOVE_CURSOR_TO_BYTE_6 0xC8
#define LCD_MOVE_CURSOR_TO_BYTE_7 0xD0
#define LCD_MOVE_CURSOR_TO_BYTE_8 0xD8
/****************************************************************
 * 							LCD configurations
 *****************************************************************/

/*CONTROL PORT CONFIG*/
#define LCD_CTRL_PORT PORTA			/*Defines the port of the control register*/
#define LCD_CTRL_PORT_DIR DDRA		/*Defines the direction register of the control port*/
#define RS	PA2						/*Register select (HIGH: transfer display data, LOW:transfer instruction data)*/
#define RW	PA1						/*Read/Write select(HIGH:read, LOW:write)*/
#define E	PA0						/*Enable (HIGH:enable data, LOW: disable data)*/

/*DATA PORT CONFIG*/

#define LCD_DATA_PORT PORTC			/*defines the data port register*/
#define LCD_DATA_PORT_DIR DDRC
#define LCD_DATA_PORT_READ PINC

/*LCD display configurations*/

/*In 8-Bit interfacing the pins(D0:7) in the LCD are connected to the pins(0:7) of the output port*/
#define LCD_DATA_BITS_MODE 8
#if(LCD_DATA_BITS_MODE == 8)
	#define LCD_DISPLAY_MODE LCD_TWO_LINE_8_BIT
#elif(LCD_DATA_BITS_MODE == 4)
	#define LCD_DISPLAY_MODE LCD_TWO_LINE_4_BIT
#endif

#if(LCD_DATA_BITS_MODE == 4)
	/*#define LCD_UPPER_PORT_PINS*/		/*Use the upper pins(4:7) of the port \\\\ NOTE: Comment out this line if you want to use lower pins*/
#endif

#define LCD_CURSOR_MODE LCD_CURSOR_OFF

/****************************************************************
 * 							functions prototypes
 *****************************************************************/
void LCD_init(void);												/*initializes the LCD*/
void LCD_sendCommand(uint8 command);								/*Sends a command to the LCD*/
void LCD_displayOneCharacter(uint8 data);							/*Displays only 8-bit characters ( takes ASCII code of the char as input)*/
void LCD_displayString(char* str);									/*Displays a string (takes an input of up to 16 bits)*/
void LCD_clearScreen(void);											/*Clears the display screen*/
void LCD_goToRowColumn(uint8 row, uint8 col);						/*UTILITY FUNCTION it moves the cursor to a certain row and column*/
void LCD_displayStringAtRowColumn(uint8 row, uint8 col, char* str); /*Displays a given string starting from a given cell*/
void LCD_displayInteger(int data);									/*Displays a given integer*/
uint8 LCD_readAdressCounter(void);
void LCD_wirteDataInByte(uint8 data, uint8 byteNum);

#endif
