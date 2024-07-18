/*
 * LM35_prog.c
 *
 *  Created on: Feb 9, 2024
 *      Author: omnia sherief
 */
#include"STD_TYPES.h"
#include "LM35_inteface.h"
#include "ADC_interface.h"

uint8 LM35_GetTemp(uint8 Copy_u8Channel)
{
	uint16 Local_u16Digital,Local_u16Analog,Local_u8Temp;
	 ADC_u8StartSingleConversionSync ( Copy_u8Channel, &Local_u16Digital);
	 Local_u16Analog= (uint16) (((uint32)Local_u16Digital * 5000UL) / 256UL);
	 Local_u8Temp=(uint8)(Local_u16Analog/10u); /*10 mV to 1 c*/

	return Local_u8Temp;

}

