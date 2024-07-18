/*
 * DashBoard.c
 *
 *  Created on: Dec 8, 2023
 *      Author: omnia sherief
 */

#include "STD_TYPES.h"
#include "KPD_Interface.h"
#include"CLCD_interface.h"
#include "Dashboard.h"
#include<util/delay.h>
uint8 Scan_u8Option(uint8 Local_u8KeypadKey)
{
	Local_u8KeypadKey = 0xff ;
	while(1)
			{
				while(Local_u8KeypadKey == 0xff)
				{
					Local_u8KeypadKey = KPD_u8GetPressedKey();
				}

				if(Local_u8KeypadKey == 1 || Local_u8KeypadKey == 2)
				{
					break;
				}
				else
				{
					Local_u8KeypadKey =0xff;
				}
			}

	return Local_u8KeypadKey ;
}
void void_HamokshaF()
{
	uint8 Local_u8HamokshaPattern4[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001010,
	                                         0b00001010,0};
		uint8 Local_u8HamokshaPattern5[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001001,
	                                         0b00001001,0};

		uint8 i=0;
		while(i<16)
			{   CLCD_voidClear();
		   	//CLCD_VoidGoToXY(5,0);
		   	//CLCD_u8SendString("WELCOME");
			    CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i++,1);
				_delay_ms(40);
				CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern5,i,1);
				_delay_ms(40);
				        i++;
            }
}
void void_HamokshaB()
{

	uint8 Local_u8HamokshaPattern4[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001010,
	                                         0b00001010,0};
		uint8 Local_u8HamokshaPattern5[8]= //rRUN
	                                        {0b00001110,
	                                         0b00001110,
	                                         0b00000100,
	                                         0b00000100,
	                                         0b00000100
	                                        ,0b00001001,
	                                         0b00001001,0};

	uint8 i=16;
	  while(i<=16)
		   	{   CLCD_voidClear();
		   //	CLCD_VoidGoToXY(5,0);
		   	//CLCD_u8SendString("DONE");
		   		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern4,i--,1);
		   		_delay_ms(40);
		   		CLCD_u8SpecialCharacter(0,Local_u8HamokshaPattern5,i,1);
		   		_delay_ms(40);
		   		        i--;

		   	}
}
