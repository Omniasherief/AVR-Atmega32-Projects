/*
 * EEPROM_prog.c
 *
 *  Created on: Jan 30, 2024
 *      Author: omnia sherief
 */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>

#include "TWI_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_prv.h"
#include "EEPROM_cfg.h"

void EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress,uint8 copy_u8DataByte)
{
	/*Get the 7 bit slave address*/
	uint8 Local_u8SlaveAddress= EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2u) |((Copy_u16LocAddress>>8) & 0x3);

	/*Send Start Condition*/
	TWI_enuSendStartCondition();

	/*SEND THE 7BIT SLA With Write request*/
    TWI_enuSendSlaveAddressWithWrite(Local_u8SlaveAddress);
    /*Send the rest 10 bits of location address*/
    TWI_enuMstrWriteDataByte((uint8) Copy_u16LocAddress);
    /*Send the data to be written inside the memory location */
    TWI_enuMstrWriteDataByte(copy_u8DataByte);
    /*Send Stop Condition*/
    TWI_voidSendStopCondition();
    /*wait until the $$ Write cycle is finished*/
    _delay_ms(10);
}
uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress )
{
	uint8 Local_u8LocationData;

	/*Get the 7 bit slave address*/
	uint8 Local_u8SlaveAddress= EEPROM_FIXED_ADDRESS | (A2_CONNECTION << 2u) |((Copy_u16LocAddress>>8) & 0x3);

	/*Send Start Condition*/
	TWI_enuSendStartCondition();

	/*SEND THE 7BIT SLA With Write request*/
    TWI_enuSendSlaveAddressWithWrite(Local_u8SlaveAddress);
    /*Send the rest 10 bits of location address*/
    TWI_enuMstrWriteDataByte((uint8) Copy_u16LocAddress);
    /*send epeated start to change from write to read*/
    TWI_enuSendRepeatedStart();
    /*send the 7 bits with read request*/
    TWI_enuSendSlaveAddressWithRead(Local_u8SlaveAddress);
    /*Read from the EEPROM*/
    TWI_enuMstrReadDataByte(& Local_u8LocationData);
    /*Send Stop condition to end communication */
    TWI_voidSendStopCondition();

    return Local_u8LocationData;
}
