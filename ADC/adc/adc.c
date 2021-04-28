/*
 * adc.c
 *
 *  Created on: Sep 14, 2019
 *      Author: DR. ADEL
 */

/*****************************************************************
 * 							Includes
 *****************************************************************/
#include"adc.h"

/*****************************************************************
 * 							Data members(Private)
 *****************************************************************/
static  volatile void volatile (* g_fPtrcallBack)(void) = NULLPTR;
/*****************************************************************
 * 							Functions definitions
 *****************************************************************/
void ADC_init(uint8 a_voltSelect, uint8 a_resultAdjust, uint8 a_prescalar,  void volatile (*  a_funcPtr)(void))
{
	/*Reference selection bits:*/
	switch(a_voltSelect)
	{
	case ADC_AREF:
		CLEAR_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
	default:	/*Set the default Volt reference(ADC_AVCC) if the input is wrong*/
	case ADC_AVCC:
		SET_BIT(ADMUX,REFS0);
		CLEAR_BIT(ADMUX,REFS1);
		break;
	case ADC_INTERNAL_VREF:
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);
		break;
	}
	switch(a_resultAdjust)
	{
	default:	/*Set the default result adjust(right) if the input is wrong*/
	case ADC_RESULT_ADJUST_RIGHT:
		CLEAR_BIT(ADMUX,ADLAR);
		break;
	case ADC_RESULT_ADJUST_LEFT:
		SET_BIT(ADMUX,ADLAR);

		break;
	}

	/*Prescalar configuration:*/
	switch(a_prescalar)
	{
	case 2:
		ADCSRA = (ADCSRA & 0xF8) | (0x00);
		break;
	case 4:
		ADCSRA = (ADCSRA & 0xF8) | (0x02);
		break;
	default:			/*Set the default prescalar(8) if the input is wrong*/
	case 8:
		ADCSRA = (ADCSRA & 0xF8) | (0x03);
		break;
	case 16:
		ADCSRA = (ADCSRA & 0xF8) | (0x04);
		break;
	case 32:
		ADCSRA = (ADCSRA & 0xF8) | (0x05);
		break;
	case 64:
		ADCSRA = (ADCSRA & 0xF8) | (0x06);
		break;
	case 128:
		ADCSRA = (ADCSRA & 0xF8) | (0x07);
		break;

	}


	/*Auto Trigger source configuration*/
	/*Auto TriggerNOT SUPPORTED IN THIS DRIVER YET so ADATE is cleared*/
	CLEAR_BIT(ADCSRA,ADATE);

	/*Interrupts configuration*/
	if(a_funcPtr != NULL)
	{
		SET_BIT(ADCSRA, ADIE);			/*Enable ADC interrupt*/
		g_fPtrcallBack = a_funcPtr;		/*Setting ADC ISR*/
	}

	/*Enable ADC*/
	SET_BIT(ADCSRA, ADEN);
}
uint16 ADC_readChannel(uint8 ch_num)
{
	ADMUX = (ADMUX & 0xF8) | (ch_num & 0x07);	/*Set the channel number*/
	SET_BIT(ADCSRA, ADSC);						/*start conversion*/
	if(g_fPtrcallBack == NULL)					/*if interrupt is NOT enabled*/
	{
		while(BIT_IS_CLEAR(ADCSRA, ADIF));		/*Polling for the result*//*You can poll for the ADSC flag too*/
		SET_BIT(ADCSRA, ADIF);					/*Clear the interrupt flag to re-check it again for further conversions*/
		return ADC;								/*returns the result of the conversion*/
	}

	return 0;									/*Dummy return value because in interrupt mode the value will be returned in the ISR*/
}
void ADC_adjustResult(uint8 a_resultAdjust)
{
	switch(a_resultAdjust)
		{
		default:
		case ADC_RESULT_ADJUST_RIGHT:
			CLEAR_BIT(ADMUX,ADLAR);
			break;
		case ADC_RESULT_ADJUST_LEFT:
			SET_BIT(ADMUX,ADLAR);
			break;
		}
}
void ADC_disable(void)
{
	CLEAR_BIT(ADCSRA, ADIE);
	CLEAR_BIT(ADCSRA, ADEN);
}
void ADC_disableInterrupt(void)
{
	g_fPtrcallBack = NULL;
}
ISR(ADC_vect)
{
	if(g_fPtrcallBack != NULL)
		(*g_fPtrcallBack)();	/*Call back function is called*/

	/*ADC  interrupt flag is automatically cleared*/
}
