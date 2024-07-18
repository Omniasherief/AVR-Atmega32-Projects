/*
 * GIE_prog.c
 *
 *  Created on: Dec 6, 2023
 *      Author: omnia sherief
 */

#include"STD_TYPES.h"
#include"BIT_MATH.h"

#include "GIE_interface.h"
//MCAL



void GIE_voidEnableGlobal(void)
{
	__asm volatile("SEI");		/*Inline assembly: Set I-Bit*/

	/*SET_BIT(SREG, SREG_I);*/
}
void GIE_voidDisableGlobal (void)
{
	__asm volatile ("CLI"); //inline assembly :CLEAR I_BIT
	// CLR_BIT(SREG ,SREG_I);
}
