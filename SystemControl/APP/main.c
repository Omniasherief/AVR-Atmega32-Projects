/*
 * main.c
 *
 *  Created on: Feb 25, 2024
 *      Author: omnia sherief
 */

#include "STD_TYPES.h"

#include "DIO_interface.h"
#include "PORT_interface.h"
#include "CLCD_interface.h"
#include "KPD_interface.h"
#include "ADC_interface.h"
#include "LM35_inteface.h"
#include "LDR_interface.h"
#include "LDR_cfg.h"
#include "DCMotor_interface.h"
#include <util/delay.h>

void main (void)
{
	 uint8 Local_u8KeyPadKey=0xff,Local_u8Temp,Local_u8LedNum=0,Local_u8Flag=1;
	 uint16 local_u16PASS=0,Local_u16LightIntensity=0,Local_u16Digital;
	PORT_voidInit();
	CLCD_VoidInit();
	ADC_voidInit();



	              CLCD_VoidGoToXY(5,0);
               CLCD_u8SendString("WELCOME");
                  _delay_ms(500);
		                 void_HamokshaF();
					     CLCD_voidClear();
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
			 		 AGAIN:
			 		 		CLCD_voidClear();
			 		 		CLCD_VoidGoToXY(0,0);
			 		 		CLCD_u8SendString("PASS:");


			 		 		 while(Local_u8Counter1<3)
			 		 		 {


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


			 		 			       CLCD_voidClear();
			 		 			       CLCD_VoidGoToXY(5,0);
			 		 			       CLCD_u8SendString("Correct");
			 		 			       CLCD_voidClear();
			 		 			       while(1){
			 		 			       CLCD_VoidGoToXY(0,0);
			 		 			       CLCD_u8SendString("TEMP");
			 		 			       CLCD_VoidGoToXY(0,1);
			 		 			       CLCD_u8SendString("LEDS");
                                         Local_u8Temp=LM35_GetTemp(7);
                                         CLCD_VoidGoToXY(6,0);
                                         CLCD_voidSendNumber(Local_u8Temp);
                                         if(Local_u8Temp>35)
                                         {
                                        	 DcMotor_CW();      /*Open the fan*/

                                         }
                                         else if(Local_u8Temp<35)
                                         {
                                        	 DcMotor_Stop();
                                         }
                                         else
                                         {
                                        	//CLCD_u8SendString("PB IN FAN"); /*FOR TESTING*/
                                         }
                                         ADC_u8StartSingleConversionSync(0, &Local_u16Digital);
                                         Local_u16LightIntensity=LDR_u16GetLightLevel(Local_u16Digital);
                                          if(Local_u16LightIntensity<LOWEST_LIGHT_INTENSITY)
                                                                                  {
                                                    	                               Local_u8LedNum=8;
                                                                                  	DIO_u8SetPortValue(DIO_u8PORTC,DIO_u8PORT_HIGH);
                                                                                      }
                                                          else if((Local_u16LightIntensity>LOWEST_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID0_LIGHT_INTENSITY))
         						                                                                                      {   Local_u8LedNum=7;
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                           DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);

         						                                                                                      }
                                                          else if((Local_u16LightIntensity>MID0_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID1_LIGHT_INTENSITY))
                                                                                                                       { Local_u8LedNum=6;
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_HIGH);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                          DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
                                                                                                                       }
                                                           else if((Local_u16LightIntensity>MID0_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID1_LIGHT_INTENSITY))
                                                                                                                       {
                                                        	                                                             Local_u8LedNum=5;
         			 		 	                                                                                        DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
         			 		 	                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
         			 		 	                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_HIGH);
         			 		 	                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
         			 		 	                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
         			 		 	                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
         			 		 	                                                                                    }
                                                           else if((Local_u16LightIntensity>MID1_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID2_LIGHT_INTENSITY))
                                                                                                                    {
                                                        	                                                           Local_u8LedNum=4;
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_HIGH);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                    DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
                                                                                                                     }
                                                           else if((Local_u16LightIntensity>MID2_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID3_LIGHT_INTENSITY))
                                                                                                                     {
                                                        	                                                             Local_u8LedNum=3;
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_HIGH);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
                                                                                                                     }
                                                           else if((Local_u16LightIntensity>MID3_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID4_LIGHT_INTENSITY))
                                                                                                                    {   Local_u8LedNum=2;
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_HIGH);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
                                                                                                                }
                                                           else if((Local_u16LightIntensity>MID4_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=MID5_LIGHT_INTENSITY))
                                                                                                                    {   Local_u8LedNum=1;
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN1,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8PIN_LOW);
                                                                                                                     DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN7,DIO_u8PIN_HIGH);
                                                                                                                    }
                                                          else if((Local_u16LightIntensity>MID5_LIGHT_INTENSITY)&&(Local_u16LightIntensity<=HIGHEST_LIGHT_INTENSITY))
                                                                                                                   {        Local_u8LedNum=0;
                                                                                                                  DIO_u8SetPortValue(DIO_u8PORTC,DIO_u8PORT_LOW);
                                                                                                                  }
                                                                                                                     CLCD_VoidGoToXY(5,1);
                                                                                                                     CLCD_voidSendNumber( Local_u8LedNum);


			 		 			       }


			 		 		         }
			 				         else
			 			 		            {
			 			 		        	Local_u8Counter=5; //POSITION
			 			 		        	local_u16PASS=0;

			 			 		             CLCD_voidClear();
			 			 		            if( Local_u8Counter1==2)
			 			 		           	 		            {
			 			 		            	                                        CLCD_voidClear();
			 			 		            	                                      CLCD_VoidGoToXY(5,0);
			 			 		            	                                     DIO_u8SetPortValue(DIO_u8PORTC,DIO_u8PORT_LOW);
			 			 		            				 			 		       CLCD_u8SendString("CLOSED");
			 			 		          	                                            Local_u8Flag=0;
                                                                                        break;
			 			 		           	 		            }
			 			 		             CLCD_VoidGoToXY(4,0);

			 			 		             CLCD_u8SendString("Try Again");
			 			 		             _delay_ms(300);

			 			 		            Local_u8Counter1++;
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
	}
//}














