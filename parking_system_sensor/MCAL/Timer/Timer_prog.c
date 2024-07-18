/*IMSK
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

/*General Functions*/
void Timer_voidInterruptEnable(Timer_INT_SOURCE_t Copy_enuInterruptSource)
{



	switch(Copy_enuInterruptSource)
    {
	case INT_T0_OC:  SET_BIT(TIMSK,OCIE0);  break;
	case INT_T0_OVF: SET_BIT(TIMSK,TOIE0);  break;
	case INT_T1_IC:  SET_BIT(TIMSK,TICIE1);  /*input capture Interrupt*/SET_BIT(TCCR1B,ICNC1); /*INPUT CAPTURE noise cancler*/ break;
	case INT_T1_OCA: SET_BIT(TIMSK,OCIE1A); break;
	case INT_T1_OCB: SET_BIT(TIMSK,OCIE1B); break;
	case INT_T1_OVF: SET_BIT(TIMSK,TOIE1);  break;
	case INT_T2_OC:  SET_BIT(TIMSK,OCIE2);            break;
	case INT_T2_OVF:  SET_BIT(TIMSK,TOIE2);            break;




    }
}
void Timer_voidInterruptDisable(Timer_INT_SOURCE_t Copy_enuInterruptSource)
{
	switch(Copy_enuInterruptSource)
	{

	case INT_T0_OC:  CLR_BIT(TIMSK,OCIE0);  break;
		case INT_T0_OVF: CLR_BIT(TIMSK,TOIE0);  break;
		case INT_T1_IC:  CLR_BIT(TIMSK,TICIE1);  /*input capture Interrupt*/CLR_BIT(TCCR1B,ICNC1); /*INPUT CAPTURE noise cancler*/ break;
		case INT_T1_OCA: CLR_BIT(TIMSK,OCIE1A); break;
		case INT_T1_OCB: CLR_BIT(TIMSK,OCIE1B); break;
		case INT_T1_OVF: CLR_BIT(TIMSK,TOIE1);  break;
		case INT_T2_OC:  CLR_BIT(TIMSK,OCIE2);            break;
		case INT_T2_OVF:  CLR_BIT(TIMSK,TOIE2);            break;


	}

}
uint8 Timer_u8SetCallBackFunction(Timer_INT_SOURCE_t Copy_enuInterruptSource, void(*CallBackFunc)(void))
{
	uint8 Local_u8ErrorState =OK;
	if(CallBackFunc !=NULL)
	{
		Timer_pvCallBackFunc[Copy_enuInterruptSource]=CallBackFunc;

	}
	else

	{
		Local_u8ErrorState= NULL_PTR_ERR;

	}

 return Local_u8ErrorState;

}

/*Timer 0*/

uint8 Timer0_voidInit(Timer0_Config_t * Copy_pstTimerconfig)
{

	uint8 Local_u8ErrorState =OK;
		if(Copy_pstTimerconfig !=NULL)
		{
			/*set waveform generation mode */
			TCCR0 &= T0_2_WGM_MASK; //clear bits before put value
			TCCR0 |=Copy_pstTimerconfig->WGM;

			/*Set output compare mode */
			TCCR0 &= T0_2_OCM_MASK;
			TCCR0 |=Copy_pstTimerconfig->OC_Mode;

			/*Set prescaler*/
			TCCR0 &=CLK_MASK;
			TCCR0 |= Copy_pstTimerconfig->CLK;
		}
		else

		{
			Local_u8ErrorState=NULL_PTR_ERR;

		}

	 return Local_u8ErrorState;


}
void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadVal)
{
	TCNT0=Copy_u8PreloadVal;
}
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchVal)
{
	OCR0=Copy_u8CompareMatchVal;


}
uint8 Timer0_GetCompareMatch()
{

    return TCCR0;


}
void Timer0_voidSetPrescaler(Timer0_1_prescaler_t Copy_enPrescaler)
{
	TCCR0 &=CLK_MASK;
	TCCR0 |= Copy_enPrescaler;

}
void Timer0_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{




	TCCR0 &=T0_2_WGM_MASK;
	TCCR0 |= Copy_enuWGM;



}
void Timer0_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM)
{

    TCCR0 &=T0_2_OCM_MASK;
    TCCR0 |= Copy_enuOCM;


}

/*Timer 1*/
uint8 Timer1_voidInit(Timer1_Config_t * Copy_pstTimerconfig)
{
	uint8 Local_u8ErrorState =OK;
		if(Copy_pstTimerconfig !=NULL)
		{
			/*set waveform generation mode */
			TCCR1A &= T1_WGMA_MASK; //clear bits before put value
			TCCR1A |=(Copy_pstTimerconfig->WGM&T1_WGM_VALUE_MASK_A) ;

			TCCR1B &= T1_WGMB_MASK;
			TCCR1B |= (Copy_pstTimerconfig->WGM & T1_WGM_VALUE_MASK_B);
			/*Set output compare mode */
			switch(Copy_pstTimerconfig->OC_Mode)
			{
			case OC_Disconnect: CLR_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);CLR_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1); break;
			case OC_toggle:  SET_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);SET_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1); break;
			case OC_clr: CLR_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);CLR_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1); break;
			case OC_set: SET_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);SET_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1); break;


			}

			/*Set prescaler*/
			TCCR1B &=CLK_MASK;
			TCCR1B|= Copy_pstTimerconfig->CLK;
		}
		else

		{
			Local_u8ErrorState=NULL_PTR_ERR;

		}

	 return Local_u8ErrorState;


}
void Timer1_voidSetPreloadValue(uint16 Copy_u16PreloadVal)
{
	TCNT1=Copy_u16PreloadVal;
}
uint8 Timer1_u8SetCompareMatchValue(Timer1_comp_Reg_t Copy_enuRegister , uint16 Copy_u16CompareMatchValue)
{
   uint8 Local_ErrorState= OK;
   switch(Copy_enuRegister)
   {
   case OCR1A_REG:OCR1A=Copy_u16CompareMatchValue; break;
   case OCR1B_REG: OCR1B=Copy_u16CompareMatchValue; break;
   default : Local_ErrorState=NOK ; break;

   }
   return Local_ErrorState;
}
uint8 Timer1_GetCompareMatch()
{

 return TCNT1;
}
void Timer1_voidSetPrescaler(Timer0_1_prescaler_t Copy_enPrescaler)
{

	TCCR1B &=CLK_MASK;
	TCCR1B|=Copy_enPrescaler ;


}
void Timer1_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{  TCCR1A &= T1_WGMA_MASK;
   TCCR1A|= (Copy_enuWGM & T1_WGM_VALUE_MASK_A);

   TCCR1B &= T1_WGMB_MASK;
      TCCR1B|= (Copy_enuWGM & T1_WGM_VALUE_MASK_B);


}
void Timer1_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM)
{
	 switch(Copy_enuOCM){
	case OC_Disconnect: CLR_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);CLR_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1); break;
	case OC_toggle:  SET_BIT(TCCR1A,COM1A0);CLR_BIT(TCCR1A,COM1A1);SET_BIT(TCCR1A,COM1B0);CLR_BIT(TCCR1A,COM1B1); break;
	case OC_clr: CLR_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);CLR_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1); break;
	case OC_set: SET_BIT(TCCR1A,COM1A0);SET_BIT(TCCR1A,COM1A1);SET_BIT(TCCR1A,COM1B0);SET_BIT(TCCR1A,COM1B1); break;
	 }
}

/*Input captrue unit function*/
void ICU_voidSetTriggerEvent(ICU_TRIGGER_t Copy_enuTriggerEvent)
{
	switch (Copy_enuTriggerEvent)
	{
	case 	ICU_RISING_EDGE: SET_BIT(TCCR1B,ICES1); break;
	case ICU_FALLING_EDGE: CLR_BIT(TCCR1B, ICES1); break;
	}

}
uint16 ICU_u16GetReading()
{
	return ICR1;
}

/*Timer 2 */
uint8 Timer2_voidInit(Timer1_Config_t * Copy_pstTimerconfig)
{

	uint8 Local_u8ErrorState = OK;

		if(Copy_pstTimerconfig!= NULL)
		{
			/*Set Waveform generation mode*/
			TCCR2 &= T0_2_WGM_MASK;
			TCCR2 |= Copy_pstTimerconfig->WGM;

			/*Set Output Compare Mode*/
			TCCR2 &= T0_2_OCM_MASK;
			TCCR2 |= Copy_pstTimerconfig->OC_Mode;

			/*Set prescaler*/
			TCCR2 &= CLK_MASK;
			TCCR2 |= Copy_pstTimerconfig->CLK;
		}
		else
		{
			Local_u8ErrorState = NULL_PTR_ERR;
		}

		return Local_u8ErrorState;
}
void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadVal)
{
	TCNT2 = Copy_u8PreloadVal;
}
void Timer2_voidSetCompareMatchValue( uint8 Copy_u8CompaareMatchValue)
{

	OCR2 = Copy_u8CompaareMatchValue;

}

uint8 Timer2_GetCompareMatch()//get timer value
{
	return TCNT2;

}
void Timer2_voidSetPrescaler(Timer2_prescaler_t Copy_enPrescaler)
{

	TCCR2 &= CLK_MASK;
		TCCR2 |= Copy_enPrescaler;
}
void Time2_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM)
{
	TCCR2 &= T0_2_WGM_MASK;
		TCCR2 |= Copy_enuWGM;

}
void Timer2_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM)
{

	TCCR2 &= T0_2_OCM_MASK;
	TCCR2 |= Copy_enuOCM;

}

/*TIMER0 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_11(void);
void __vector_11(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T0_OVF]();
	}
}
/*TIMER0 Output Compare Interrupt ISR*/
__attribute__((signal)) void __vector_10(void);
void __vector_10(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T0_OC]();
	}
}

/*TIMER1 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_9(void);
void __vector_9(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T1_OVF]();
	}
}

/*TIMER1 Output Compare B Interrupt ISR*/
__attribute__((signal)) void __vector_8(void);
void __vector_8(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T1_OCB]();
	}
}

/*TIMER1 Output Compare A Interrupt ISR*/
__attribute__((signal)) void __vector_7(void);
void __vector_7(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T1_OCA]();
	}
}

/*TIMER1 Input Capture Interrupt ISR*/
__attribute__((signal)) void __vector_6(void);
void __vector_6(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T1_IC]();
	}
}

/*TIMER2 Overflow Interrupt ISR*/
__attribute__((signal)) void __vector_5(void);
void __vector_5(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T2_OVF]();
	}
}

/*TIMER2 output compare Interrupt ISR*/
__attribute__((signal)) void __vector_4(void);
void __vector_4(void)
{
	if(Timer_pvCallBackFunc != NULL)
	{
		Timer_pvCallBackFunc[INT_T2_OC]();
	}
}


