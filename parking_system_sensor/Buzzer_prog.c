/*
 * Buzzer_prog.c
 *
 *  Created on: Apr 14, 2024
 *      Author: omnia sherief
 */

#include"STD_TYPES.h"
#include"ErrType.h"

#include "DIO_interface.h"
#include "Buzzer_interface.h"

uint8 Buzz_u8On(const Buzz_config_t* Copy_pstConfig)
{
	 uint8 Local_u8Err_State =OK;
	 if(Copy_pstConfig!=NULL)
	 {
		 if (Copy_pstConfig->u8ActiveType==Buzz_Active_high)
		 {
			 DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_HIGH);
		 }
		 else if (Copy_pstConfig->u8ActiveType==Buzz_Actve_low)
		 {
			 DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		 }
		 else
		 {
			 Local_u8Err_State=NOK;
		 }
	 }

	 else
	 {
		 Local_u8Err_State=NULL_PTR_ERR;
	 }
 return Local_u8Err_State;
}
uint8 Buzz_u8Off(const Buzz_config_t* Copy_pstConfig)
{
	 uint8 Local_u8Err_State =OK;
	 if(Copy_pstConfig!=NULL)
	 {
		 if (Copy_pstConfig->u8ActiveType==Buzz_Active_high)
		 {
			 DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_LOW);
		 }
		 else if (Copy_pstConfig->u8ActiveType==Buzz_Actve_low)
		 {
			 DIO_u8SetPinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin,DIO_u8PIN_HIGH);
		 }
		 else
		 {
			 Local_u8Err_State=NOK;
		 }
	 }

	 else
	 {
		 Local_u8Err_State=NULL_PTR_ERR;
	 }
 return Local_u8Err_State;
}
uint8 Buzz_u8Toggle(const Buzz_config_t* Copy_pstConfig)
{
	uint8 Local_u8Err_State =OK;
   if(Copy_pstConfig!=NULL)
   {
	   DIO_u8TogglePinValue(Copy_pstConfig->u8Port,Copy_pstConfig->u8Pin);

   }
   else
   {

	   Local_u8Err_State=NULL_PTR_ERR;
   }
   return Local_u8Err_State;
}
