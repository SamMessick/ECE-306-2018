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
void Init_Timer_B0(void){
  TB0CTL    = TASSEL__SMCLK;            // Select SMCLK for source
  TB0CTL   |= (MC_2|TBCLR);             // Continuous mode; clear Timer B0 register                                                                               **MC_1
  //TB0CCR0   = MOTOR_PERIOD;             // PWM period
  TB0CCR4   = MOTOR_PERIOD;
  TB0CCR6   = MOTOR_PERIOD;
 
  //Garbage PWM
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/
  TB0CCTL0 |= CCIE;                   // Enable clock interrupts every 1/20 second
  TB0CCTL1 &= ~CCIE;
  TB0CCTL2 &= ~CCIE;
  TB0CCTL4 |= CCIE;
  TB0CCTL6 |= CCIE;
  TA1CCTL0 |= CCIE;                   // Enable clock interrupts every MOTOR_PERIOD/2
  TB0CTL &= ~(TBIFG);                 // Clear Timer A1 interrupt flag and interrupt enable
  
}
  
//   Timer B0.0 interrupt routine  //
// ------"PWM" Updater------------ //
#pragma vector = TIMER0_B0_VECTOR
__interrupt void Timer0_B0_ISR(void){
  P3OUT |= (L_FORWARD | R_FORWARD);   // Turn on Motors
  TB0CTL &= ~(TBIFG);
}
//   Timer B0.1-2 interrupt routine  //
// ------"PWM"  Updater-----------   //
#pragma vector = TIMER0_B1_VECTOR
__interrupt void Timer0_B1_ISR(void){
  switch(TB0IV)
  {
  case 0x08:                         // Right motor interrupt triggered
    P3OUT &= ~L_FORWARD;
    break;
  case 0xC:                         // Left motor interrupt triggered
    P3OUT &= ~R_FORWARD;
  }
  TB0CTL &= ~(TBIFG);
}
//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX/  
  /*
    Glorious, amazing, super-duper, BRILLIANT! PWM [my eyes!]

    TA1CCTL0 |= CCIE;                   // Enable clock interrupts every 1/20 second
    TA1CCTL1 &= ~CCIE;
    TA1CCTL2 &= ~CCIE;
    TA1CTL &= ~(TAIFG);                 // Clear Timer A1 interrupt flag and interrupt enable
  */
  
  // Set all motor pins to Reset/Set mode, 0% duty cycle
  //TB0CCTL3 |= OUTMOD_7;                 //  Reset/Set mode
  //TB0CCTL4 |= OUTMOD_7;                 
  //TB0CCTL5 |= OUTMOD_7;                 
  //TB0CCTL6 |= OUTMOD_7;
  //TB0CCR3   = MOTOR_OFF;                //  Begin with motor off
  //TB0CCR4   = MOTOR_OFF;                
  //TB0CCR5   = MOTOR_OFF;                
  //TB0CCR6   = MOTOR_OFF;                