//===============================================================
//  File Name: timerA1.c
//  Description: This file contains the initialization of timer
//                    A1--the variable millisecond timer--and the 
//                    LCD refresh routine.
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerA1.h"

uint16_t counter_A11;           // Timer A1.1 interrupt occurences counter (range 0 - 1000)
uint16_t counter_A12;           // Timer A1.2 interrupt occurences counter (range 0 - 1000)
volatile uint16_t delay_time;         // Timer A1.2 counter assignment -- receives input from main

void Init_Timer_A1(void) {
  // Initialize Timer A1 and activate display update
  TA1CTL = TASSEL__SMCLK;
  TA1CTL |= (TACLR | MC_1 | ID_3);       // SMCLK Clock source on up mode at 1 MHz
  TA1CCR0 = MSEC;                        // interrupt time set to 1/1000 second
  TA1CCR1 = MSEC;                        // interrupt time set to 1/1000 second
  TA1CCR2 = MSEC;                        // interrupt time set to 1/1000 second
  
  TA1CCTL0 |= CCIE;                      // Enable clock interrupts every 1/1000 second
  TA1CCTL1 &= ~CCIE;
  TA1CCTL2 &= ~CCIE;
  TA1CTL &= ~(TAIFG);                    // Clear Timer A1 interrupt flag and interrupt enable
}

////////////////////////////////////
//Interrupt timer update functions//
/////////////////////////////////////////////////////////////////////////////////////////////////
void handle_quart_second_delay(void){
  // Debouncing delay for Buttons 1 and 2
  counter_A11++;                         // Increment debounce counter by 1 msec
  if(!(counter_A11 % QUART_SEC_DELAY))   // **If debounce counter has counter 250 msec
  {
    TA1CCTL1 &= ~CCIE;                   //     Disable debounce delay routine                 
    counter_A11 = COUNTER_RESET;         //     reset timer A11 counter 
    debounced = true;                    //     Allow switch to reactivate button interrupt routine
    update_menu();                       //     Update menu state machine
  }
}

void handle_procedural_delay(void){     
  // General delay for menu state machine
  counter_A12++;                         // Increment delay counter by 1msec
  if(!(counter_A12 % delay_time))        // **If debounce counter has counter of delay_time msec
  {
    TA1CCTL2 &= ~CCIE;                   //     Disable procedural delay routine                
    counter_A12 = COUNTER_RESET;         //     Reset timer A11 counter
    delay_time  = COUNTER_RESET;         //     Reset delay_time to 0 msec
    update_menu();                       //     Enable pending menu state machine instruction
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////


//   Timer A1.0 interrupt routine  //
// ------LCD Display Updater------ //
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void){
  static uint16_t counter_A10;           // 1 msec counting interval for Timer A1.0
  counter_A10++;                         // Increment counter by 1 msec for each 1 msec interrupt
  switch(counter_A10 % ONE_SEC)          // **If one second has elapsed
  {                                     
  case COUNTER_RESET:                    // ---One second elapsed---
    lcd_BIG_mid();                       // Turn on large LCD text
    display_changed = true;            
    counter_A10 = COUNTER_RESET; break;  // Reset 1 msec interrupt counter
  case HALF_SEC:                         // ---Half second elapsed---  
    lcd_4line();                         // Turn on small LCD text
    display_changed = true; break;       
  }
  Display_Process();                     // Refresh LCD screen
  TA1CTL &= ~(TAIFG);                    // Update Timer A1.0 interrupt queue
}

//   Timer A1 interrupt routines   //
//         **OVERFLOW**            //
// ------.25 second delay--------- // <-- Highest Priority (debounce)
// ----- Procedural delay -------- //                      (pauses for delay_time in msecs)
#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR(void){
  // Check and handle interrupt vector
  switch(TA1IV)
  {
  case TA1IV_1:                                   // ------Button Press Debounce------ //
    handle_quart_second_delay();
    break;
  case TA1IV_2:                                   // ------ Procedural Delay---------- // 
    handle_procedural_delay();
    break;
  case (TA1IV_1 | TA1IV_2):                       // Procedural delay and button press //
    handle_quart_second_delay();
    handle_procedural_delay();
  }
  TA1CTL &= ~(TAIFG);                             // Update Timer A1.1-2 interrupt queue
}
