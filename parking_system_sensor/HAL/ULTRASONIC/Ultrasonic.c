/*
 * Ultrasonic.c
 *
 *  Created on: Apr 17, 2024
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "Timer_interface.h"
#include "Timer_reg.h"
#include "ultrasonic.h"
#include<util/delay.h>

uint8 Ultrasonic_u8GetDistance(PORT port, PIN pin)
{
	uint16 Local_u16Reading1,Local_u16Reading2,Local_u16Period;
    uint8	Local_u8Distance;

    Timer1_Config_t Timer1 ={

    	.WGM=WGM_NORMAL,
		.OC_Mode=OC_Disconnect,
		.CLK=No_Prescaler
    };

Timer1_voidInit(&Timer1);
SET_BIT(TIFR,ICF1);//clear the flag by logical 1
/*trigger pulse*/

	DIO_u8SetPinValue(port,pin,DIO_u8PIN_HIGH);
	_delay_us(20);
	DIO_u8SetPinValue(port,pin,DIO_u8PIN_LOW);
	/*First Rising edge*/
   SET_BIT(TCCR1B,ICES1); //Input Capture Edge Select, trigger on rising
   while(GET_BIT(TIFR,ICF1)==0);//pooling on flag until it's got triggerd

   Local_u16Reading1=ICR1; //value from start to first
   SET_BIT(TIFR,ICF1);//clear the flag by logical 1

/*First falling edge*/
   CLR_BIT(TCCR1B,ICES1); //.Trigger on Falling edge
   while(GET_BIT(TIFR,ICF1)==0);
   Local_u16Reading2=ICR1;
   SET_BIT(TIFR,ICF1);

   TCNT1=0;			/*important to reset counter */
   TCCR1B = 0;  		/* Stop the timer */

   	Local_u16Period  = (Local_u16Reading2-Local_u16Reading1);
   	Local_u8Distance=(uint8)((Local_u16Period*34600)/(16000000*2));//multiplying the timer period by the speed of sound, converting timer ticks to seconds using a system-specific clock factor, and then halving the result to account for the round trip,

   	return Local_u8Distance;

}
