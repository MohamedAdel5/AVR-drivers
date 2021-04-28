/*
 * common_macros.h
 *
 *  Created on: Sep 13, 2019
 *      Author: MOHAMED ADEL
 */

#ifndef COMMON_MACROS_H_
#define COMMON_MACROS_H_

#define SET_BIT(REG, BIT_NUM) ((REG) |= (1 << (BIT_NUM)))
 /*Clears a bit in a given register*/
#define CLEAR_BIT(REG, BIT_NUM) ((REG) &= ~(1 << (BIT_NUM)))
/*Toggles a bit in a given register*/
#define TOGGLE_BIT(REG, BIT_NUM) ((REG) ^= (1 << (BIT_NUM)))
/*Rotates the bits of a given register to the right*/
/*Shifts the bits of a given register to the right and inserts the overflowed bits in the left*/
#define ROR(REG, NUM_OF_BITS) ((REG) = (((REG) >> (NUM_OF_BITS)) | ((REG) << (8*sizeof(REG) - (NUM_OF_BITS)))))
/*Rotates the bits of a given register to the left*/
/*Shifts the bits of a given register to the left and inserts the overflowed bits in the right*/
#define	ROL(REG, NUM_OF_BITS) ((REG) = (((REG) << (NUM_OF_BITS)) | ((REG) >> (8*sizeof(REG) - (NUM_OF_BITS)))))
/*Checks is a bit is set == 1*/
#define BIT_IS_SET(REG, BIT_NUM) (((REG) & (1 << BIT_NUM))?1:0)
/*Checks if a bit is clear == 0*/
#define BIT_IS_CLEAR(REG, BIT_NUM) (!((REG) & (1 << BIT_NUM)))

#define GLOBAL_INTERRUPT_ENABLE SET_BIT(SREG, 7)
#define GLOBAL_INTERRUPT_DISABLE CLEAR_BIT(SREG, 7)

#endif /* COMMON_MACROS_H_ */
