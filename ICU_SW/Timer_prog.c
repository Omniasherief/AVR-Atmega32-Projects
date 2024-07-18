/*
 * Timer_prog.c
 *
 *  Created on: Dec 17, 2023
 *      Author: omnia sherief
 */


#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "ErrType.h"


#include "Timer_interface.h"
#include "Timer_reg.h"
#include "Timer_cfg.h"
#include "Timer_prv.h"


static void (* Timer_pvCallBackFunc [8])(void)={NULL};

void Timer0_voidInit()
{


    /*Set PWM mode*/
  SET_BIT(TCCR0,TCCR0_WGM00);
  SET_BIT(TCCR0 , TCCR0_WGM01);
  /*Set Compare output mose :set on top clear on compare */
   CLR_BIT(TCCR0,TCCR0_COM00);
   SET_BIT(TCCR0,TCCR0_COM01);


  /*Clear prescaler bits "AS ENABLE FOR TIMER*/
      TCCR0 &=	0b11111000;

   /*Set prescaler to divide by 64*/
		TCCR0|= 0b011;

}
void  Timer1_voidInit(void)
{
	/*set normal mode*/


	/*set prescaler ,division by 64*/

	  /*Clear prescaler bits "AS ENABLE FOR TIMER*/
	      TCCR1B &=	0b11111000;

	   /*Set prescaler to divide by 64*/
			TCCR1B|= 0b011;

}

uint16 Timer1_u16GetTimerValue(void)
{
	return TCNT1;
}

uint8 Timer_u8SetCallBack(uint8 Copy_u8IntSource,void(*Copy_pvCallBackFunc)(void))
{
	uint8 Local_u8ErrorState=  OK	;
	if(Copy_pvCallBackFunc!=NULL)
	{
		Timer_pvCallBackFunc[Copy_u8IntSource]=Copy_pvCallBackFunc;

	}
	else
	{
		Local_u8ErrorState= NULL_PTR_ERR;

	}
return Local_u8ErrorState;
}

void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadVal)
{
    TCNT0 = Copy_u8PreloadVal;
}

void Timer1_voidSetValue(uint16 Copy_u16Value)
{
	TCNT1=Copy_u16Value;
}
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchVal)
{
    OCR0 = Copy_u8CompareMatchVal;
}

/*Timer 0 overflow ISR*/
 void __vector_11(void) __attribute__((signal));
 void __vector_11(void)
 {
	if (Timer_pvCallBackFunc[Timer0_OVF_INT]!=NULL)

	{

		Timer_pvCallBackFunc[Timer0_OVF_INT]();
	}
}
/*Timer0  compare match ISR	*/
 void __vector_10 (void) __attribute__((signal));	//Timer0 CTC
 void __vector_10 (void)
  {

	  if (Timer_pvCallBackFunc[Timer0_OC_INT]!=NULL)

	  	{

		  Timer_pvCallBackFunc[Timer0_OC_INT]();
	  	}


  }
