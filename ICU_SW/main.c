/*
 * main.c
 *
 *  Created on: Feb 16, 2024
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"

#include "PORT_interface.h"
#include "DIO_interface.h"
#include "EXTI_interface.h"
#include "GIE_interface.h"
#include "CLCD_interface.h"
#include "TIMER_interface.h"


void ICU_SW (void);
uint16 u16PeriodTicks=0;

uint16 u16OnTicks=0u;
void main (void)
{


   PORT_voidInit();
   CLCD_VoidInit();
   Timer0_voidInit(); //Generate pwm
   Timer0_voidSetCompareMatchValue(63u);
   Timer1_voidInit();
   EXTI_voidInit(); //ISR
   EXTI_u8SetCallBack(INT0,&ICU_SW);
   GIE_voidEnableGlobal();
  while(1)
  {
	  //waiting until both reading are ready
    while((u16PeriodTicks==0)&& (u16OnTicks==0));

       CLCD_VoidGoToXY(0,0);
       CLCD_voidSendNumber(u16OnTicks);
       CLCD_VoidGoToXY(0,1);
       CLCD_voidSendNumber(u16PeriodTicks);

  }




}
void ICU_SW (void)
{
	 volatile static uint8 Local_u8Counter =0u;
	 Local_u8Counter++;
	 if (Local_u8Counter==1u)
	 {
      Timer1_voidSetValue(0);
	 }
	 else if (Local_u8Counter== 2u)
	 {
		 /*Get timer reading -> peiod time number of ticks*/
       u16PeriodTicks=Timer1_u16GetTimerValue();
         /*Set EXTI trigger to falling edge */
       	   EXTI_u8setSenseCtrl(INT0,FALLING_EDGE);
	 }
	 else
	 {
      u16OnTicks=Timer1_u16GetTimerValue();
      u16OnTicks-= u16PeriodTicks;
      EXTI_u8DisableIntChannel(INT0);
	 }



}
