/*
 * main.c
 *
 *  Created on: Feb 1, 2024
 *      Author: omnia sherief
 */
#include "STD_TYPES.h"
#include"DIO_interface.h"
#include "PORT_interface.h"
#include "TWI_interface.h"
#include "EEPROM_interface.h"

void main(void)
{
	uint8 Local_u8ReadData=0u;
  PORT_voidInit();

  TWI_voidMasterInit(0);

  EEPROM_voidWriteDataByte(0,10);

  Local_u8ReadData=EEPROM_u8ReadDataByte(0);

  if(Local_u8ReadData==10)
  {

	  DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);

  }

  while(1){



  }



}



