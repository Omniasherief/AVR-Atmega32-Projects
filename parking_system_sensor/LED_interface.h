/*
 * LED_interface.h
 *
 *  Created on: Dec 5, 2023
 *      Author: omnia sherief
 */

#ifndef LED_INTERFACE_H_
#define LED_INTERFACE_H_

typedef enum {
	Active_Low =0u,
	Active_High =1u
}LED_ACT_t;

typedef struct
{
	uint8 LED_u8PORT;
	uint8 LED_u8PIN;
	LED_ACT_t  LED_u8ACTIVE_TYPE;

}LED_Cfg_t;

uint8 LED_u8SetON (const LED_Cfg_t* Copy_pConfig);
uint8 LED_u8SetOFF (const LED_Cfg_t* Copy_pConfig);
uint8 LED_u8Toggle (const LED_Cfg_t* Copy_pConfig);


#endif /* LED_INTERFACE_H_ */
