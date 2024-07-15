/*
 * Buzzer_interface.h
 *
 *  Created on: Apr 14, 2024
 *      Author: omnia sherief
 */

#ifndef BUZZER_INTERFACE_H_
#define BUZZER_INTERFACE_H_

typedef enum
 {
	Buzz_Active_high=1u,
	Buzz_Actve_low=0u
 }Buzz_ACTIVE_t;

typedef struct
 {
	uint8 u8Port;
	uint8 u8Pin;
	Buzz_ACTIVE_t u8ActiveType;
 }Buzz_config_t;

uint8 Buzz_u8On(const Buzz_config_t* Copy_pstConfig);
uint8 Buzz_u8Off(const Buzz_config_t* Copy_pstConfig);
uint8 Buzz_u8Toggle(const Buzz_config_t* Copy_pstConfig);
#endif /* BUZZER_INTERFACE_H_ */
