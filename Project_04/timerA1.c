//===============================================================
//  File Name: timerA1.c
//  Description: This file contains the initialization of timer
//                    A1, the "one second" timer
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerA1.h"

volatile uint8_t counter_A11;
volatile uint8_t counter_A12;
uint16_t delay_time;

void Init_Timer_A1(void) {
  // Initialize Timer A1 and activate display update
  TA1CTL = TASSEL__SMCLK;
  TA1CTL |= (TACLR | MC_1 | ID_3);    // SMCLK Clock source on up mode at 1 MHz
  TA1CCR0 = MSEC;                     // interrupt time set to 1/1000 second
  TA1CCR1 = MSEC;                     // interrupt time set to 1/1000 second
  TA1CCR2 = MSEC;                     // interrupt time set to 1/1000 second
  
  TA1CCTL0 |= CCIE;                   // Enable clock interrupts every 1/1000 second
  TA1CCTL1 &= ~CCIE;
  TA1CCTL2 &= ~CCIE;
  TA1CTL &= ~(TAIFG);                 // Clear Timer A1 interrupt flag and interrupt enable
}

////////////////////////////////////
//Interrupt timer update functions//
/////////////////////////////////////////////////////////////////////////////////////////////////
void handle_quart_second_delay(void){
  counter_A11++;
  switch(counter_A11 % QUART_SEC_DELAY)
  {
  case COUNTER_RESET:                    // **If delay is complete
    TA1CCTL1 &= ~CCIE;                   // Disable debounce delay routine                 
    counter_A11 = COUNTER_RESET;
    debounced = true; break;             // Allow switch to reactivate button interrupt routine
  default:
    break;
  }
}

void handle_procedural_delay(void){
  counter_A12++;
  switch(counter_A12 % delay_time)
  {
  case COUNTER_RESET:
    TA1CCTL2 &= ~CCIE;                   // Disable procedural delay routine                
    counter_A12 = COUNTER_RESET; 
    delay_continue = false; break;       // Enable pending background instruction
  default:
    break;
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////


//   Timer A1.0 interrupt routine  //
// ------LCD Display Updater------ //
#pragma vector = TIMER1_A0_VECTOR
__interrupt void Timer1_A0_ISR(void){
  static uint8_t counter_A10;
  counter_A10++;
  switch(counter_A10 % ONE_SEC)
  {
  case COUNTER_RESET:
    lcd_BIG_mid();
    display_changed = true;
    counter_A10 = COUNTER_RESET; break;
  case HALF_SEC:
    lcd_4line();
    display_changed = true; break;
  }
  Display_Process();
  TA1CTL &= ~(TAIFG);
}

//   Timer A1 interrupt routines   //
//         **OVERFLOW**            //
// ------.25 second delay--------- // <-- Highest Priority (debounce)
// ----- Procedural delay -------- //                      (pauses whenever called in delay(uint8_t msecs))
#pragma vector = TIMER1_A1_VECTOR
__interrupt void Timer1_A1_ISR(void){
  // Check and handle interrupt vector
  switch(TA1IV)
  {
  case TA1IV_1:                                   // ------.25 second delay----------- //
    handle_quart_second_delay();
    break;
  case TA1IV_2:                                   // ------ Procedural Delay---------- // 
    handle_procedural_delay();
    break;
  case (TA1IV_1 | TA1IV_2):                       // Procedural delay and button press //
    handle_quart_second_delay();
    handle_procedural_delay();
  }
  TA1CTL &= ~(TAIFG);
}
