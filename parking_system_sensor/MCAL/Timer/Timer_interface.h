/*
 * Timer_interface.h
 *
 *  Created on: Dec 16, 2023
 *      Author: omnia sherief
 */

#ifndef TIMER_INTERFACE_H_
#define TIMER_INTERFACE_H_


#define Timer0_OVF_INT   0u //OVERFLOW
#define Timer0_OC_INT    1u //OUTPUT COMPARE

typedef enum
{
	No_Clk_SRC,
	No_Prescaler,
	Prescaler_8,
	Prescaler_64,
	Prescaler_256,
	prescaler_1024,
	EXT_Clk_Falling_Edge,
	EXT_Clk_Rising_Edge,

}Timer0_1_prescaler_t;

typedef enum
{
	    T2_No_Clk_SRC,
		T2_No_Prescaler,
		T2_Prescaler_8,
		T2_Prescaler_64,
		T2_Prescaler_256,
		T2_prescaler_1024,

}Timer2_prescaler_t;


typedef enum{

	//output compare mode
	OC_Disconnect=0u,
	OC_toggle=16u, //1 in com00 Bit4,0 in com01 Bit5
	OC_clr=32u,
	OC_set=48u
}Timer_OC_Mode_t;

typedef enum
{//interrupt sources generated by timers.
	INT_T0_OVF,
	INT_T0_OC,
	INT_T1_OVF,
	INT_T1_OCA,
	INT_T1_OCB,
	INT_T1_IC, //input capture
	INT_T2_OVF,
	INT_T2_OC,
}Timer_INT_SOURCE_t;

/*ENUM*/

typedef enum{
	//page 145 datasheet
	WGM_NORMAL=0u,
	WGM_T1_PWM_PHA_CORR_8=1u,
	WGM_T1_PWM_PHA_CORR_9=2u,
	WGM_T1_PWM_PHA_CORR_10=3u,
	WGM_CTC=8u, //0b00001000
	WGM_T1_FAST_PWM_8=9u,
	WGM_T1_FAST_PWM_9=10u,
	WGM_T1_FAST_PWM_10=11u,
	WGM_T1_PWM_PHA_FREQ_CORR_ICR1=16u,
	WGM_T1_PWM_PHA_FREQ_CORR_OCR1A=17u,
	WGM_T1_PWM_PHA_CORR_ICR1=18u,
	WGM_T1_PWM_PHA_CORR_OCR1A=19u,
	WGM_T1_CTC_ICR1=24u,
	WGM_T1_FAST_PWM_ICR1=26u,
	WGM_T1_FAST_PWM_OCR1A=27u,
	WGM_PHA_CORR = 64u, //0b01000000
	WGM_FAST_PWM = 72u 	//0b01001000
}TIMER_WGM_t;
typedef enum
{
	OCR1A_REG,
	OCR1B_REG
}Timer1_comp_Reg_t;

typedef struct
{
	TIMER_WGM_t WGM;
	Timer0_1_prescaler_t CLK;
	Timer_OC_Mode_t OC_Mode;
}Timer0_Config_t;

typedef struct
{
	TIMER_WGM_t WGM;
	Timer0_1_prescaler_t CLK;
	Timer_OC_Mode_t OC_Mode;
}Timer1_Config_t;

typedef struct
{
	TIMER_WGM_t WGM;
	Timer2_prescaler_t CLK;
	Timer_OC_Mode_t OC_Mode;
}Timer2_Config_t;

typedef enum
{
	ICU_RISING_EDGE,
	ICU_FALLING_EDGE
}ICU_TRIGGER_t;


/*General Functions*/
void Timer_voidInterruptEnable(Timer_INT_SOURCE_t Copy_enuInterruptSource);
void Timer_voidInterruptDisable(Timer_INT_SOURCE_t Copy_enuInterruptSource);
uint8 Timer_u8SetCallBackFunction(Timer_INT_SOURCE_t Copy_enuInterruptSource, void(*CallBackFunc)(void));

/*Timer 0*/

uint8 Timer0_voidInit(Timer0_Config_t * Copy_pstTimerconfig);
void Timer0_voidSetPreloadValue(uint8 Copy_u8PreloadVal);
void Timer0_voidSetCompareMatchValue(uint8 Copy_u8CompareMatchVal);
uint8 Timer0_GetCompareMatch();
void Timer0_voidSetPrescaler(Timer0_1_prescaler_t Copy_enPrescaler);
void Timer0_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer0_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM);

/*Timer 1*/
uint8 Timer1_voidInit(Timer1_Config_t * Copy_pstTimerconfig);
void Timer1_voidSetPreloadValue(uint16 Copy_u16PreloadVal);
uint8 Timer1_u8SetCompareMatchValue(Timer1_comp_Reg_t Copy_enuRegister , uint16 Copy_u16CompareMatchValue);
uint8 Timer1_GetCompareMatch();
void Timer1_voidSetPrescaler(Timer0_1_prescaler_t Copy_enPrescaler);
void Timer1_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer1_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM);

/*Input captrue unit function*/
void ICU_voidSetTriggerEvent(ICU_TRIGGER_t Copy_enuTriggerEvent);
uint16 ICU_u16GetReading();

/*Timer 2 */
uint8 Timer2_voidInit(Timer1_Config_t * Copy_pstTimerconfig);
void Timer2_voidSetPreloadValue(uint8 Copy_u8PreloadVal);
void Timer2_voidSetCompareMatchValue( uint8 Copy_u8CompaareMatchValue);
uint8 Timer2_GetCompareMatch(); //get timer value
void Timer2_voidSetPrescaler(Timer2_prescaler_t Copy_enPrescaler);
void Time2_voidSetWaveGenerationMode(TIMER_WGM_t Copy_enuWGM);
void Timer2_voidSetOutputCompareMode(Timer_OC_Mode_t Copy_enuOCM);




#endif /* TIMER_INTERFACE_H_ */
