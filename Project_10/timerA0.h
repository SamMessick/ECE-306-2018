//===============================================================
//  File Name: timerA0.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    timerA0.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "serial.h"
#include "LCD.h"
#include <stdint.h>
#include <stdbool.h>

#define TA0IV_1                  (0x2)
#define TA0IV_2                  (0x4)
#define COUNTER_RESET            (0)
#ifndef TIMERA01_TIMES_ENUM
#define TIMERA01_TIMES_ENUM

typedef enum {
  QUART_SECOND_MS = 200,
  SECOND_MS       = 1000,
  TWO_SECOND_MS   = 2000,
  THREE_SECOND_MS = 3000,
  FOUR_SECOND_MS  = 4000,
  FIVE_SECOND_MS  = 5000,
  SIX_SECOND_MS   = 6000,
  SEVEN_SECOND_MS = 7000,
  EIGHT_SECOND_MS = 8000,
  NINE_SECOND_MS  = 9000,
  TEN_SECOND_MS   = 10000
} timerA01_times_t;
#endif

#define ENABLE_PING_INTERRUPT    (TA0CCTL0 |= CCIE)

void init_Timer_A0(void);
void handle_procedural_delay(void);
void handle_quart_second_delay(void);


extern volatile uint8_t debounced;           // Timer A1.1 flag: delays button 1 and 2 interrupt refresh by .25 seconds
extern volatile uint16_t counter_A00;
extern uint16_t counter_A01;                 // Timer A1.1 interrupt occurences counter (range 0 - 1000)
extern uint16_t counter_A02;                 // Timer A1.2 interrupt occurences counter (range 0 - 1000)
extern volatile uint16_t delay_time;         // Timer A1.2 counter assignment -- receives input from main
extern volatile uint32_t time_ms;            // Total time elapsed during course run
extern volatile uint32_t aux_time_ms;        // Total time elapsed for delay functions
extern volatile uint8_t  ir_ready_to_print;
