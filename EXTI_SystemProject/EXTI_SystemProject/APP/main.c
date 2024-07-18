/*
 * main.c
 *
 *  Created on: Jan 26, 2024
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"
#include "ErrType.h"


#include  "PORT_interface.h"
#include  "DIO_interface.h"
#include  "CLCD_interface.h"
#include  "KPD_interface.h"
#include  "EXTI_interface.h"
#include  "GIE_interface.h"
#include  "DCMotor_interface.h"
#include <util/delay.h>

uint8 Global_u8Flag = 0 ;
void flag (void)
{
	 Global_u8Flag = 1;
}
void main(void )
{

 uint8 Local_u8KeyPadKey=0xff;
 uint16 local_u16PASS=0;

 uint8 Local_u8Flag = 1;

PORT_voidInit();
EXTI_voidInit();
CLCD_VoidInit();

/*ISR function address*/
EXTI_u8SetCallBack(INT2,&flag);
/*Global interrupt enable*/
GIE_voidEnableGlobal();
while(1)
{
  EXTI_u8EnableIntChannel(INT2);       /*Enable  INT2*/
  while(Global_u8Flag==1)
  {
     void_HamokshaF();
     CLCD_voidClear();
	 EXTI_u8DisableIntChannel(INT2);   /*Disable  INT2*/
	 uint8 Local_u8Counter=3;
	 uint8 Local_u8Counter1=0;
	 CLCD_VoidGoToXY(0,0);
	 	CLCD_u8SendString("ID:");


	 do{

	 		do {
	 			 	 Local_u8KeyPadKey = KPD_u8GetPressedKey();


	 		   }while ((Local_u8KeyPadKey == 0xff));
	 	 	            Local_u8Counter++; //POSITION
	 		            CLCD_VoidGoToXY( Local_u8Counter,0);
	 			 		CLCD_voidSendNumber(Local_u8KeyPadKey);
	 	if (Local_u8KeyPadKey=='=')
	 	{
	 		Local_u8Counter=5;
	 		CLCD_voidClear();
	 		CLCD_VoidGoToXY(0,0);
	 		CLCD_u8SendString("PASS:");


	 		 while(Local_u8Counter1<3)
	 		 {

AGAIN:
	 			do
	 				{
	 				 Local_u8KeyPadKey= KPD_u8GetPressedKey();

	 				}while(Local_u8KeyPadKey == 0xff);

	 			     Local_u8Counter++;
	 			    CLCD_VoidGoToXY(Local_u8Counter,0);
	 			   CLCD_voidSendNumber(Local_u8KeyPadKey);
	 			   _delay_ms(80);
	 			    CLCD_VoidGoToXY(Local_u8Counter,0);
	 			     CLCD_u8SendString("*");

	 			if (Local_u8KeyPadKey=='=')
	 			{

	 		        if(local_u16PASS==332)
	 		         {
	 		        	/*righ password ->enable stop system*/
	 		        	Global_u8Flag = 0;
	 		        	EXTI_u8EnableIntChannel(INT2);

	 			       CLCD_voidClear();
	 			       CLCD_VoidGoToXY(5,0);
	 			       CLCD_u8SendString("Correct");
	 			      DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
	 			       DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_HIGH);
	 			       DcMotor_CW();
	 			       _delay_ms(1000);
	 			       DcMotor_Stop();
	 			      _delay_ms(400);
	 			       DcMotor_CCW();
	 			       _delay_ms(1000);
	 			      Local_u8Flag=0;
	 			      break;

	 		         }
	 		         else
	 		            {
	 		        	Local_u8Counter=5;
	 		        	local_u16PASS=0;
	 		             DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
	 		             CLCD_voidClear();
	 		            if( Local_u8Counter1==2)
	 		           	 		            {
	 		           	 		            	Global_u8Flag = 0;
	 		           	 		            	Local_u8Flag=0;
	 		           	 		            }
	 		             CLCD_VoidGoToXY(4,0);

	 		             CLCD_u8SendString("Try Again");
	 		             _delay_ms(300);
	 		        	CLCD_voidClear();
	 		        	 		CLCD_VoidGoToXY(0,0);
	 		        	 		CLCD_u8SendString("PASS:");


	 		            Local_u8Counter1++;

	 		            if( Local_u8Counter1==2)
	 		            {
	 		            	Global_u8Flag = 0;
	 		            	Local_u8Flag=0;
	 		            }
goto AGAIN;
	 		            }
	 		    }
	 			 else if((Local_u8KeyPadKey>=0 )&&(Local_u8KeyPadKey<=9))
	 			{
	 			 local_u16PASS = local_u16PASS*(uint16)10 + (uint16)Local_u8KeyPadKey;
	 			//CLCD_VoidGoToXY(4,1); FOR TEST
	 			// CLCD_voidSendNumber(local_u16PASS);

	 			}
	 		 }

	 }


 }while(Local_u8Flag==1);

	/*if Global flag =0  close the system */
	if( Global_u8Flag == 0 )
	{
		CLCD_voidClear();
		 DcMotor_Stop();
		DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
		 DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
		CLCD_VoidGoToXY(5,0);
		CLCD_u8SendString("Closed");
		_delay_ms(1000);
		void_HamokshaB();
        CLCD_voidClear();
		Local_u8Flag=1;
		break;
	}



}
}
}


