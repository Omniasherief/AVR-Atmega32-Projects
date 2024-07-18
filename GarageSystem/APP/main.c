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
#include "ADC_interface.h"
#include "LDR_interface.h"
#include "LDR_cfg.h"
#include "Garage.h"
#include <util/delay.h>

void main (void)
{ uint16 Local_u16Level0,Local_u16Digital0,Local_u16Level1,Local_u16Digital1;
  uint8 Local_u8Available=GARAGE_LIMIT,	Local_u8CurrentUse=0;
	PORT_voidInit();
	CLCD_VoidInit();
	ADC_voidInit();
	while(1){
		// Read light intensity from the first LDR (channel 0)
		ADC_u8StartSingleConversionSync(0, &Local_u16Digital0);
		Local_u16Level0 = LDR_u16GetLightLevel(Local_u16Digital0);

		// Read light intensity from the second LDR (channel 7)
		ADC_u8StartSingleConversionSync(7, &Local_u16Digital1);
		Local_u16Level1 = LDR_u16GetLightLevel(Local_u16Digital1);

		// Display Available and Current Use values
		CLCD_VoidGoToXY(0, 0);
		CLCD_u8SendString("Available: ");
		CLCD_VoidGoToXY(0, 1);
		CLCD_u8SendString("Current Use: ");
		CLCD_VoidGoToXY(12, 0);
		CLCD_u8SendString("   ");
		CLCD_VoidGoToXY(12, 0);
		CLCD_voidSendNumber(Local_u8Available);

		                                       //  CLCD_voidSendNumber(Local_u16Level0);/*Testing*/
//_delay_ms(300);

		CLCD_VoidGoToXY(12, 1);
		CLCD_u8SendString("   ");
		CLCD_VoidGoToXY(12, 1);
		CLCD_voidSendNumber(Local_u8CurrentUse);

		                                       // CLCD_voidSendNumber(Local_u16Level1);/*Testing*/


		// Check if a car has entered
		if (Local_u16Level0 < 180) {
			if (Local_u8CurrentUse < 40) {
			        Local_u8CurrentUse++;
			        _delay_ms(3000);       /*handle it */
			    }

			    // Decrement Local_u8Available if within limits
			    if (Local_u8Available > 0) {
			        Local_u8Available--;
			        _delay_ms(3000);/*handle it */
		}
		}

		// Check if a car has left
		else if (Local_u16Level1 < LIGHT_INTENSITY) {
			 if (Local_u8Available < 40) {
			        Local_u8Available++;
			        _delay_ms(3000);/*handle it */
			    }

			    // Decrement Local_u8CurrentUse if within limits
			    if (Local_u8CurrentUse > 0) {
			        Local_u8CurrentUse--;
			        _delay_ms(3000);/*handle it */
			    }
		}
		  else
		   {
			//Do  nothing

		   }
	}
}
