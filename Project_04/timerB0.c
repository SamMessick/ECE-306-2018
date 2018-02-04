//===============================================================
//  File Name: timerB0.c
//  Description: This file contains the functions needed for PWM
//                    operation with the left and right motors
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerB0.h"

// Initialize motor PWM registers
void Init_TimerB0(void){
  TB0CTL    = TASSEL__SMCLK;            // Select SMCLK for source
  TB0CTL   |= (MC_1|TBCLR);             // Up mode; clear Timer B0 register
  TB0CCR0   = MOTOR_PERIOD;             // PWM period
 
  // Set all motor pins to Reset/Set mode, 0% duty cycle
  TB0CCTL3 |= OUTMOD_7;                 //  Reset/Set mode
  TB0CCTL4 |= OUTMOD_7;                 
  TB0CCTL5 |= OUTMOD_7;                 
  TB0CCTL6 |= OUTMOD_7;                 
  TB0CCR3   = MOTOR_OFF;                //  Begin with motor off
  TB0CCR4   = MOTOR_OFF;                
  TB0CCR5   = MOTOR_OFF;                
  TB0CCR6   = MOTOR_OFF;                
}