/*
 * DCMotor_prog.c
 *
 *  Created on: Nov 27, 2023
 *      Author: omnia sherief
 */

#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "DCMotor_interface.h"
#include "DCMotor_cfg.h"

void DcMotor_CW()
{

	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_LOW);
	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_HIGH);

	//RELAY
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);

}
void DcMotor_CCW()
{
	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_HIGH);

	//RELAY
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
}
void DcMotor_Stop()
{
	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN0,DIO_u8PIN_LOW);
	//DIO_u8SetPinValue(DIO_u8PORTA,DIO_u8PIN1,DIO_u8PIN_LOW);

	//RELAY
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
}
