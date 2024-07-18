/*
 * StepperMotor_interface.h
 *
 *  Created on: Dec 3, 2023
 *      Author: omnia sherief
 */

#ifndef STEPPERMOTOR_INTERFACE_H_
#define STEPPERMOTOR_INTERFACE_H_
#define CW 1
#define CCW 2
typedef struct {



	uint8 u8PORT;
	uint8 u8BluePin;
	uint8 u8PinkPin;
	uint8 u8YellowPin;
	uint8 u8OrangePin;
}STEP_cfg_t;


//typedef enum
//{
//	CW=0,CCW=1  /*ROTATE ClockWise or Counter Clockwise*/
//}Direction_t;


uint8 STEP_u8Rotate (const STEP_cfg_t* Copy_cfg,uint8 Copy_Direction, uint16 Copy_Angle);
#endif /* STEPPERMOTOR_INTERFACE_H_ */
