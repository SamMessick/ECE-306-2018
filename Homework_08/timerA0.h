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
#include "shapes_menu.h"
#include "serial.h"
#include "LCD.h"
#include <stdint.h>
#include <stdbool.h>

#define TA0IV_1          (0x2)
#define TA0IV_2          (0x4)
#define COUNTER_RESET      (0)

void Init_Timer_A0(void);
void handle_procedural_delay(void);
void handle_quart_second_delay(void);


extern volatile uint8_t debounced;           // Timer A1.1 flag: delays button 1 and 2 interrupt refresh by .25 seconds
extern volatile uint16_t counter_A00;
extern uint16_t counter_A01;                 // Timer A1.1 interrupt occurences counter (range 0 - 1000)
extern uint16_t counter_A02;                 // Timer A1.2 interrupt occurences counter (range 0 - 1000)
extern volatile uint16_t delay_time;         // Timer A1.2 counter assignment -- receives input from main
extern volatile uint8_t  ir_ready_to_print;
