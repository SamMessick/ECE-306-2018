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

#define OTWENT_SEC    (0xC350)     // Timer counts to 50000, taking 1/20 second
#define MSEC            (1000)     // Timer counts to 1000, taking 1/1000 second
#define COUNTER_RESET      (0)               
#define ONE_SEC         (1000)     // Number of cycles for 1 second delay
#define HALF_SEC         (500)
#define QUART_SEC_DELAY   (40)

#define TA1IV_1          (0x2)
#define TA1IV_2          (0x4)

void Init_Timer_A1(void);
void handle_procedural_delay(void);
void handle_quart_second_delay(void);

extern volatile uint8_t debounced;
extern volatile uint8_t counter_A11;
extern volatile uint8_t counter_A12;
