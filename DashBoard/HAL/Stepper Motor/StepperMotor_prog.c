/*
 * StepperMotor_prog.c
 *
 *  Created on: Dec 3, 2023
 *      Author: omnia sherief
 */

#include "STD_TYPES.h"
#include "ErrType.h"
#include <util/delay.h>

#include "DIO_interface.h"
#include "StepperMotor_interface.h"
#include "StepperMotor_cfg.h"
#include "StepperMotor_prv.h"
uint8 STEP_u8Rotate (const STEP_cfg_t* Copy_cfg, uint8 Copy_Direction, uint16 Copy_Angle)
{

uint8 Local_u8LocalState=OK;


if(Copy_cfg!=NULL)
{   uint16 Local_u16Steps;
	Local_u16Steps = (uint16)( (  ( (uint32)Copy_Angle ) * (2048UL)  ) /360UL );
	if(Copy_Direction==CW)
	{//////360
		//Local_u16Steps=(uint16)(((uint32)Copy_Angle * 2048UL)/360UL);

		for(uint16 i=0; i<Local_u16Steps;i++)
		{
                //STEP 1
			if(i%4==0){
			    DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_LOW);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
				_delay_ms(3);
			}
                 //STEP 2
			else if(i%4==1){
				DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

			    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_LOW);

			    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

			    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
				_delay_ms(3);
			}
			else if(i%4==2){
				DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_LOW);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
				_delay_ms(3);
			}
			else if(i%4==3){
				DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

				DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_LOW);
				_delay_ms(3);
		  }
		}
	}
	else if(Copy_Direction==CCW)
			{//////360
				//Local_u16Steps=(uint16)(((uint32)Copy_Angle*2048UL)/360UL);

				for(uint16 i=0; i<Local_u16Steps;i++)
				{
		                //STEP 1
					if(i%4==0){
					    DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_LOW);
						_delay_ms(3);
					}
		                 //STEP 2
					else if(i%4==1){
						DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

					    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

					    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_LOW);

					    DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
						_delay_ms(3);
					}
					else if(i%4==2){
						DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_LOW);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
						_delay_ms(3);
					}
					else if(i%4==3){
						DIO_u8SetPinValue(Copy_cfg-> u8PORT ,Copy_cfg->u8BluePin ,DIO_u8PIN_LOW);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8PinkPin,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8YellowPin,DIO_u8PIN_HIGH);

						DIO_u8SetPinValue(Copy_cfg-> u8PORT,Copy_cfg->u8OrangePin,DIO_u8PIN_HIGH);
						_delay_ms(3);
				    }
				}
		   }



}
else
{
	Local_u8LocalState=NULL_PTR_ERR;

}

return Local_u8LocalState;
}











