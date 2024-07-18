/*
 * main.c+
 *
 *  Created on: Dec 8, 2023
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"
#include "ErrType.h"

#include<util/delay.h>
#include"DIO_interface.h"
#include"PORT_interface.h"
#include"CLCD_interface.h"
#include"DCMotor_interface.h"
#include"StepperMotor_interface.h"
#include"KPD_interface.h"
#include "DashBoard.h"
STEP_cfg_t Local_StepperMotor={
			.u8PORT=DIO_u8PORTB,
			.u8BluePin =DIO_u8PIN0,
			.u8PinkPin=DIO_u8PIN1,
            .u8YellowPin =  DIO_u8PIN2,
            .u8OrangePin= DIO_u8PIN3
};

void main(void)
{

PORT_voidInit();
CLCD_VoidInit();
uint8 Local_u8KeypadKey= 0xff ;
CLCD_VoidGoToXY(5,0);
CLCD_u8SendString("Welcome");
_delay_ms(1000);

void_HamokshaF();



///while(1){}

CLCD_voidClear();
CLCD_VoidGoToXY(0,0);
CLCD_u8SendString("1 -> DC Motor");
CLCD_VoidGoToXY(0,1);
CLCD_u8SendString("2 -> Step Motor");





Local_u8KeypadKey= Scan_u8Option(Local_u8KeypadKey);

   if (Local_u8KeypadKey==1)
   {

	   CLCD_voidClear();
	   CLCD_VoidGoToXY(0,0);
	   CLCD_u8SendString("1->CW");
	   CLCD_VoidGoToXY(0,1);
	   CLCD_u8SendString("2->CCW");

	   Local_u8KeypadKey = Scan_u8Option(Local_u8KeypadKey);
	   if (Local_u8KeypadKey==1)
	   {
		 DcMotor_CW();
		 _delay_ms(5000);
		 DcMotor_Stop();
	   }
	   else if(Local_u8KeypadKey==2)
	   {

		   DcMotor_CCW();
		   		 _delay_ms(5000);
		   		//DcMotor_Stop();
	   }
	   CLCD_voidClear();
	   CLCD_VoidGoToXY(5,0);
	   CLCD_u8SendString("THANKS <3");
	   _delay_ms(2000);

	   void_HamokshaB();

   }

   /*Stepper Motor Option*/
   else if(Local_u8KeypadKey==2)
   {
	   uint8 Local_u8KeypadKey= 0xff ;
	   uint8 Local_u8Angle=0,Local_u8Direction=0;

	   CLCD_voidClear();
	  	   CLCD_VoidGoToXY(0,0);
	  	   CLCD_u8SendString("1->CW");
	  	   CLCD_VoidGoToXY(0,1);
	  	   CLCD_u8SendString("2->CCW");

	  	 Local_u8KeypadKey=Scan_u8Option(Local_u8KeypadKey);

       if(Local_u8KeypadKey==1)
		{Local_u8Direction=CW;
		}
		else if(Local_u8KeypadKey==2)
		{Local_u8Direction=CCW;
		}
       //scan angle
       CLCD_voidClear();
       CLCD_VoidGoToXY(0,0);
      CLCD_u8SendString("Angle:");
      Local_u8KeypadKey = 0xff;
      while(1)
      				{

      					while(Local_u8KeypadKey == 0xff)
      					{
      						Local_u8KeypadKey = KPD_u8GetPressedKey() ;
      					}

      					if(Local_u8KeypadKey =='D')
      					{
      						break;
      					}
      					else
      					{
      						CLCD_voidSendNumber(Local_u8KeypadKey);
      						Local_u8Angle = Local_u8Angle * (uint16)10 + (uint16)Local_u8KeypadKey;
      						Local_u8KeypadKey = 0xff;
      					;
      					}

      				}
       STEP_u8Rotate ( &Local_StepperMotor, Local_u8Direction, Local_u8Angle);

       CLCD_voidClear();
       CLCD_VoidGoToXY(4,0);
      CLCD_u8SendString("FINISHED");
      _delay_ms(2000);
      void_HamokshaB();
   }
}







