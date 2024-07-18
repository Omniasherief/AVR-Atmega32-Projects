/*
 * EEPROM_interface.h
 *
 *  Created on: Jan 30, 2024
 *      Author: omnia sherief
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_

void EEPROM_voidWriteDataByte(uint16 Copy_u16LocAddress,uint8 copy_u8DataByte);
uint8 EEPROM_u8ReadDataByte(uint16 Copy_u16LocAddress );

#endif /* EEPROM_INTERFACE_H_ */
