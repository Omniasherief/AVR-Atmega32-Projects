/*
 * main.c
 *
 *  Created on: Feb 9, 2024
 *      Author: omnia sherief
 */

#include "STD_TYPES.h"
#include "PORT_interface.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "ADC_interface.h"
#include<util/delay.h>
void main (void)
{
	uint16 Local_u16Digital, Local_u16Analog,Local_u16ResistorVal;
PORT_voidInit();
CLCD_VoidInit();
ADC_voidInit();

CLCD_VoidGoToXY(5,0);
CLCD_u8SendString("Ohmmeter");
_delay_ms(500);
CLCD_voidClear();



while(1)
{
 ADC_u8StartSingleConversionSync(0,&Local_u16Digital);
 Local_u16Analog= (uint16) (((uint32)Local_u16Digital * 5000UL) / 256UL);
 //CLCD_VoidGoToXY(0,1);
 //CLCD_voidSendNumber(Local_u16Analog);

	 Local_u16ResistorVal =(uint16)(((5000UL * 10000UL )/ (uint32)Local_u16Analog) - 10000UL); //10000 is known Res value

 CLCD_VoidGoToXY(0,0);
 CLCD_voidSendNumber(Local_u16ResistorVal);

}
}
