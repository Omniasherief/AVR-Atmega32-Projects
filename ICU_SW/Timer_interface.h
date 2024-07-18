/*
 * Timer_interface.h
 *
 *  Created on: Dec 16, 2023
 *      Author: omnia sherief
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define Timer0_OVF_INT   0u //OVERFLOW
#define Timer0_OC_INT    1u //OUTPUT COMPARE




void Timer0_voidInit();
uint8 Timer_u8SetCallBack(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFunc)(void));
 void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadVal);
 void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchVal);
void Timer0_GetCompareMatch();
void  Timer1_voidInit(void);
uint16 Timer1_u16GetTimerValue(void);
void Timer1_voidSetValue(uint16 Copy_u16Value);







#endif /* TIMER_INTERFACE_H_ */
