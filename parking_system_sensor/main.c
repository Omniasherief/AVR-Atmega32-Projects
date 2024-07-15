/*
 * main.c
 *
 *  Created on: Apr 20, 2024
 *      Author: omnia sherief
 */
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "Buzzer_interface.h"
#include "LED_interface.h"
#include "Timer_interface.h"
#include "ultrasonic.h"
#include <util/delay.h>



void main (void)
{


   uint8 Local_u8Distance;
   PORT_voidInit();
   CLCD_VoidInit();

//ECHO pin in ICP1 PD6 INPUT
   LED_Cfg_t Local_stRedLED=
	{
			.LED_u8ACTIVE_TYPE = Active_High,
			.LED_u8PORT = DIO_u8PORTC,
			.LED_u8PIN = DIO_u8PIN0
	};

	LED_Cfg_t Local_stBlueLED=
	{
			.LED_u8ACTIVE_TYPE = Active_High,
			.LED_u8PORT = DIO_u8PORTC,
			.LED_u8PIN = DIO_u8PIN2
	};

	LED_Cfg_t Local_stGreenLED=
	{
			.LED_u8ACTIVE_TYPE = Active_High,
			.LED_u8PORT = DIO_u8PORTC,
			.LED_u8PIN = DIO_u8PIN1

	};

	Buzz_config_t Local_stBuzzer=
	{
			.u8ActiveType = Buzz_Active_high,
			.u8Port = DIO_u8PORTC,
			.u8Pin = DIO_u8PIN5
	};

	while(1)
	 {
 Local_u8Distance=Ultrasonic_u8GetDistance(DIO_u8PORTC,DIO_u8PIN4
		 );
 /*CLCD_VoidGoToXY(0,1);
 CLCD_u8SendString("Distance:");
 CLCD_VoidGoToXY(0,11);
 CLCD_voidSendNumber(Local_u8Distance);
  CLCD_u8SendString("cm ");*/




 if(Local_u8Distance < 10)
 		{
	        /*Set Green and Blue LED off*/
	  			LED_u8SetOFF(&Local_stBlueLED);
	  			LED_u8SetOFF(&Local_stGreenLED);
 			/*Toggle Red LED and Buzzer*/
	        LED_u8Toggle(&Local_stRedLED);
 			Buzz_u8Toggle(&Local_stBuzzer);


 			CLCD_VoidGoToXY(0,0);
 			CLCD_u8SendString("  HIGH RISK :'( !");
 			//CLCD_VoidGoToXY(0,1);
 			//CLCD_u8SendString("DISTANCE < 10 cm");

 			/* toggling speed*/
 			_delay_ms(100);
 		}

 else if((Local_u8Distance>10)&&(Local_u8Distance<25))
 {
	 /*Set RED and Blue LED off*/
		   LED_u8SetOFF(&Local_stBlueLED);
		   LED_u8SetOFF(&Local_stRedLED);

	 /*Toggle Green led*/
	   LED_u8Toggle(&Local_stGreenLED);
	   Buzz_u8Toggle(&Local_stBuzzer);



	  	CLCD_VoidGoToXY(0,0);
	  	CLCD_u8SendString(" BE CAREFUL :( ");


	  	_delay_ms(300);
 }
 else
 {
	 /*Set RED and Blue LED off*/
		    LED_u8SetOFF(&Local_stGreenLED);
			LED_u8SetOFF(&Local_stRedLED);

	     LED_u8Toggle(&Local_stBlueLED);
	     Buzz_u8Off(&Local_stBuzzer);


		//CLCD_voidClear();
		  CLCD_VoidGoToXY(0,0);
		  CLCD_u8SendString("  NO RISK :)  " );

 }

 }
}
