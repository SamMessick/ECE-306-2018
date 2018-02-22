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

#include "timerA0.h"

uint16_t counter_A01;           // Timer A1.1 interrupt occurences counter (range 0 - 1000)
uint16_t counter_A02;           // Timer A1.2 interrupt occurences counter (range 0 - 1000)
volatile uint16_t delay_time;         // Timer A1.2 counter assignment -- receives input from main

void Init_Timer_A0(void) {
  // Initialize Timer A1 and activate display update
  TA0CTL = TASSEL__SMCLK;
  TA0CTL |= (TACLR | MC_1 | ID_3);       // SMCLK Clock source on up mode at 1 MHz
  TA0CCR0 = MSEC;                        // interrupt time set to 1/1000 second
  TA0CCR1 = MSEC;                        // interrupt time set to 1/1000 second
  TA0CCR2 = MSEC;                        // interrupt time set to 1/1000 second
  
  TA0CCTL0 |= CCIE;                      // Enable clock interrupts every 1/1000 second
  TA0CTL &= ~(TAIFG);                    // Clear Timer A1 interrupt flag and interrupt enable
}

////////////////////////////////////
//Interrupt timer update functions//
/////////////////////////////////////////////////////////////////////////////////////////////////
void handle_quart_second_delay(void){
  // Debouncing delay for Buttons 1 and 2
  counter_A01++;                         // Increment debounce counter by 1 msec
  if(!(counter_A01 % QUART_SEC_DELAY))   // **If debounce counter has counter 250 msec
  {
    TA0CCTL1 &= ~CCIE;                   //     Disable debounce delay routine                 
    counter_A01 = COUNTER_RESET;         //     reset timer A11 counter 
    debounced = true;                    //     Allow switch to reactivate button interrupt routine
    update_menu();                       //     Update menu state machine
  }
}

void handle_procedural_delay(void){     
  // General delay for menu state machine
  counter_A02++;                         // Increment delay counter by 1msec
  if(!(counter_A02 % delay_time))        // **If debounce counter has counter of delay_time msec
  {
    TA0CCTL2 &= ~CCIE;                   //     Disable procedural delay routine                
    counter_A02 = COUNTER_RESET;         //     Reset timer A11 counter
    delay_time  = COUNTER_RESET;         //     Reset delay_time to 0 msec
    update_menu();                       //     Enable pending menu state machine instruction
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////


//   Timer A1.0 interrupt routine  //
// ------LCD Display Updater------ //
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  static uint16_t counter_A00;           // 1 msec counting interval for Timer A1.0
  counter_A00++;                         // Increment counter by 1 msec for each 1 msec interrupt
  switch(counter_A00 % ONE_SEC)          // **If one second has elapsed
  {                                     
  case COUNTER_RESET:                    // ---One second elapsed---
    if(debounced)
      P5OUT ^= LCD_BACKLITE;
    lcd_BIG_mid();                       // Turn on large LCD text
    display_changed = true;            
    update_display  = true;
    counter_A00 = COUNTER_RESET;         // Reset 1 msec interrupt counter
    Display_Process(); break;            // Refresh LCD screen 
  case HALF_SEC:                         // ---Half second elapsed---  
    lcd_4line();                         // Turn on small LCD text
    display_changed = true; 
    update_display  = true;
    Display_Process(); break;            // Refresh LCD screen     
  }
  TA0CTL &= ~(TAIFG);                    // Update Timer A1.0 interrupt queue
}

//   Timer A1 interrupt routines   //
//         **OVERFLOW**            //
// ------.25 second delay--------- // <-- Highest Priority (debounce)
// ----- Procedural delay -------- //                      (pauses for delay_time in msecs)
#pragma vector = TIMER0_A1_VECTOR
__interrupt void Timer0_A1_ISR(void){
  // Check and handle interrupt vector
  switch(TA0IV)
  {
  case TA0IV_1:                                   // ------Button Press Debounce------ //
    handle_quart_second_delay();
    break;
  case TA0IV_2:                                   // ------ Procedural Delay---------- // 
    handle_procedural_delay();
    break;
  case (TA0IV_1 | TA0IV_2):                       // Procedural delay and button press //
    handle_quart_second_delay();
    handle_procedural_delay();
  }
  TA0CTL &= ~(TAIFG);                             // Update Timer A1.1-2 interrupt queue
}
