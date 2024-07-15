/*
 * Timer_prv.h
 *
 *  Created on: Dec 16, 2023
 *      Author: omnia sherief
 */

#ifndef TIMER_PRV_H_  // Header guard to prevent multiple inclusions
#define TIMER_PRV_H_

// Bit mask to isolate clock source bits in a timer register
#define CLK_MASK                 0b11111000

// Bit masks for timers 0 & 2:
//  - Isolate Waveform Generation Mode (WGM) bits
#define T0_2_WGM_MASK             0b10110111 //BIT 3,6
//  - Isolate Output Compare Match (OCM) bits
#define T0_2_OCM_MASK             0b11001111 //BIT 4,5

// Bit masks for Timer 1:
//  - Isolate WGM bits for Mode A
#define T1_WGMA_MASK             0b11111100
//  - Isolate bits holding WGM value for Mode A
#define T1_WGM_VALUE_MASK_A       0b00000011
//  - Isolate WGM bits for Mode B
#define T1_WGMB_MASK             0b11100111
//  - Isolate bits holding WGM value for Mode B
#define T1_WGM_VALUE_MASK_B       0b00011000
//  - Isolate Output Compare Match bits for channel A
#define T1_OCMA_MASK             0b00111111
//  - Isolate Output Compare Match bits for channel B
#define T1_OCMB_MASK             0b11001111

// Bit masks for Timer Interrupt Mask registers
#define T0_TIMSK_BITS_MASK        0b11111100 //BIT 1,0  // Isolate bits for Timer 0 interrupts
#define T1_TIMSK_BITS_MASK        0b11000011  // Isolate bits for Timer 1 interrupts
#define T2_TIMSK_BITS_MASK        0b00111111  // Isolate bits for Timer 2 interrupts

// Enumerated constants for Waveform Generation Modes (might differ based on microcontroller)
#define NORMAL_WGM               1u           // Normal mode
#define CTC_WGM                   2u           // Clear Timer on Compare Match mode
#define FAST_PWM_WGM              3u           // Fast PWM mode
#define PHASE_CORRECT_WGM         4u           // Phase Correct PWM mode

// Enumerated constants for timer state
#define IDLE                      0u           // Timer inactive (likely stopped)
#define BUSY                      1u           // Timer active (likely running)

#endif /* TIMER_PRV_H_ */
