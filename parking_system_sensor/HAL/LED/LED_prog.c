/*
 * LED_prog.c
 *
 *  Created on: Dec 5, 2023
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"

#include "LED_interface.h"
#include "LED_prv.h"
#include "LED_cfg.h"
#include"DIO_interface.h"
#include "ErrType.h"



uint8 LED_u8SetON (const LED_Cfg_t* Copy_pConfig)
{
	 uint8 Local_u8Err_State =OK;
	 if (Copy_pConfig != NULL)
	 {
		if(Copy_pConfig ->LED_u8ACTIVE_TYPE ==Active_High)
		{
			DIO_u8SetPinValue(Copy_pConfig->LED_u8PORT,Copy_pConfig->LED_u8PIN,DIO_u8PIN_HIGH);

		}
		else if (Copy_pConfig->LED_u8ACTIVE_TYPE==Active_Low)
		{
			DIO_u8SetPinValue(Copy_pConfig->LED_u8PORT,Copy_pConfig->LED_u8PIN,DIO_u8PIN_LOW);
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




uint8 LED_u8SetOFF (const LED_Cfg_t* Copy_pConfig)
{


		 uint8 Local_u8Err_State =OK;
		 if (Copy_pConfig != NULL)
		 {
			if(Copy_pConfig ->LED_u8ACTIVE_TYPE ==Active_High)
			{
				DIO_u8SetPinValue(Copy_pConfig->LED_u8PORT,Copy_pConfig->LED_u8PIN,DIO_u8PIN_LOW);

			}
			else if (Copy_pConfig->LED_u8ACTIVE_TYPE==Active_Low)
			{
				DIO_u8SetPinValue(Copy_pConfig->LED_u8PORT,Copy_pConfig->LED_u8PIN,DIO_u8PIN_HIGH);
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
uint8 LED_u8Toggle (const LED_Cfg_t* Copy_pConfig)
{
	uint8 LED_Local_u8Err_State=OK;
	if(Copy_pConfig !=NULL)
	{
		DIO_u8TogglePinValue(Copy_pConfig->LED_u8PORT,Copy_pConfig->LED_u8PIN);
	}
	else
	{
		LED_Local_u8Err_State=NULL_PTR_ERR;
	}
	return LED_Local_u8Err_State;
}


