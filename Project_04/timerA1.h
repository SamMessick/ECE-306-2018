//===============================================================
//  File Name: timerA1.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    timerA1.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "menu.h"
#include "LCD.h"
#include <stdint.h>
#include <stdbool.h>
#define COUNTER_RESET   (0x0)
#ifndef TIMER_INTV_ENUM
#define TIMER_INTV_ENUM

typedef enum{
  OTWENT_SEC = (0xC350),
  MSEC = (1000),
  TWO_SEC = (2000),
  ONE_SEC = (1000),
  HALF_SEC = (500),
  QUART_SEC_DELAY = (500)
} timer_intv_t;

#endif

#define TA1IV_1          (0x2)
#define TA1IV_2          (0x4)

void Init_Timer_A1(void);
void handle_procedural_delay(void);
void handle_quart_second_delay(void);


extern volatile uint8_t debounced;           // Timer A1.1 flag: delays button 1 and 2 interrupt refresh by .25 seconds
extern volatile uint16_t counter_A11;        // Timer A1.1 interrupt occurences counter (range 0 - 1000)
extern volatile uint16_t counter_A12;        // Timer A1.2 interrupt occurences counter (range 0 - 1000)
extern volatile uint16_t delay_time;         // Timer A1.2 counter assignment -- receives input from main
