/*
 * LDR_prog.c
 *
 *  Created on: Feb 24, 2024
 *      Author: omnia sherief
 */
#include "STD_TYPES.h"
#include "LDR_interface.h"
uint16 LDR_u16GetLightLevel(uint8 Copy_u8ChannelReading)
{
	uint16 Local_u16LightLevel= (uint16) (((uint32)Copy_u8ChannelReading * 5000UL) / 256UL);/*8 bit Res*/
	return Local_u16LightLevel;
}
