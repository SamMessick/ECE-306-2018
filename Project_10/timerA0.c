//===============================================================
//  File Name: timerA0.c
//  Description: This file contains the initialization of timer
//                    A1--the variable millisecond timer--and the 
//                    LCD refresh routine.
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerA0.h"

uint16_t counter_A01;                        // Timer A1.1 interrupt occurences counter (range 0 - 1000)
uint16_t counter_A02;                        // Timer A1.2 interrupt occurences counter (range 0 - 1000)
volatile uint16_t counter_A00;               // 1 msec counting interval for Timer A1.0
volatile uint16_t delay_time;                // Timer A1.2 counter assignment -- receives input from main
volatile uint32_t time_ms;                   // Total time elapsed during course run
volatile uint32_t aux_time_ms;               // Time elapsed used by delay functions in clocks.c
volatile uint8_t  ir_ready_to_print;
volatile uint8_t waiting;

void init_Timer_A0(void) {
  // Initialize Timer A1 and activate display update
  TA0CTL = TASSEL__ACLK;
  TA0CTL |= (TACLR | MC_1 | ID_1);       // AClock source on up mode at 32 KHz
  TA0CTL |= TAIDEX__1;                   
  TA0CCR0 = MSEC;                        // interrupt time set to 1/1000 second
  TA0CCR1 = MSEC;                        // interrupt time set to 1/1000 second
  TA0CCR2 = MSEC;                        // interrupt time set to 1/1000 second
  
  //TA0CCTL0 |= CCIE;
  TA0CTL &= ~(TAIFG);                    // Clear Timer A1 interrupt flag and interrupt enable
}

////////////////////////////////////
//Interrupt timer update functions//
/////////////////////////////////////////////////////////////////////////////////////////////////
void handle_quart_second_delay(void){
  // Debouncing delay for Buttons 1 and 2
  counter_A01++;                         // Increment debounce counter by 1 msec
  if(!(counter_A01 % QUART_SEC))   // **If debounce counter has counter 250 msec
  {
    TA0CCTL1 &= ~CCIE;                   //     Disable debounce delay routine        
    P3OUT    |= IOT_RESET;               //     Reenable IOT module
    counter_A01 = COUNTER_RESET;         //     reset timer A11 counter 
    debounced = true;                    //     Allow switch to reactivate button interrupt routine
    //defer_to_shape_menu();                       //     Update menu state machine
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
    Wheels_OFF();
    waiting     = false;
    //defer_to_shape_menu();                       //     Enable pending menu state machine instruction
  }
}
//////////////////////////////////////////////////////////////////////////////////////////////////

//   Timer A0.0 interrupt routine  //
// ------    Ping update    ------ //
#pragma vector = TIMER0_A0_VECTOR
__interrupt void Timer0_A0_ISR(void){
  static uint8_t string_index;
  counter_A00++;                         // Increment counter by 1 msec for each 1 msec interrupt
  aux_time_ms++;
  
  if(!(counter_A00 % SECOND_MS))
  {
    for(string_index = BEGINNING; string_index < SOCKET_PING_SIZE; string_index++)     // Ping host every period once established
        transmit_charA3(sock_ping_command[string_index]);
    counter_A00 = COUNTER_RESET;
  }
  
  if(IOT_STATUS(COURSE_BEGIN))               // If inside course, begin timer display on second LCD line
  {
    time_ms++;
    /*
    if((time_ms % TWO_MS) == COUNTER_RESET)  // two milliseconds elapsed
    {
      hex_to_dec(word2, time_ms);
      word2[CHAR7] = word2[CHAR6];
      word2[CHAR6] = word2[CHAR5];
      word2[CHAR5] = word2[CHAR4];           // Shift digits over one to add decimal point
      word2[CHAR4] = '.';
      LCD_print(word1, word2, word3, word4);
    }
    */
  }   
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
