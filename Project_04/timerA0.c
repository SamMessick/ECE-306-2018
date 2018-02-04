//===============================================================
//  File Name: timerA0.c
//  Description: This file contains the initialization of timer
//                    A0
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerA0.h"

void Init_Timer_A0(void) {
  TA0CTL = TASSEL__SMCLK;
  TA0CTL |= (TACLR | MC__CONTINUOUS | ID__2);
  
  TA0EX0 = TAIDEX_7;
  
  TA0CCR0 = 10000;
  TA0CCTL0 |= CCIE;
  
  TA0CTL &= ~(TAIE | TAIFG);
}

// Timer A0 interrupt handler
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  
}