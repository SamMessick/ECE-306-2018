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
#define TIME_CYCLES       (20)
#define HALF_CYCLES       (10)
#define TWO_SEC_DELAY     (40)
#define QUART_SEC_DELAY    (5)
#define TENTH_SEC_DELAY    (2)

#define MAX_BYTE_EVEN (0x1110)
#ifndef ENUM_TA1IV
#define ENUM_TA1IV
typedef enum{
  TWO      =          (0x0010),
  FOUR     =          (0x0100),
  SIX      =          (0x0110),
  EIGHT    =          (0x1000),
  TEN      =          (0x1010),
  TWELVE   =          (0x1100),
  FOURTEEN =          (0x1110)
}registers_ccra1_t;
#endif

void Init_Timer_A1(void);
void handle_procedural_delay(void);
void handle_quart_second_delay(void);

extern volatile uint8_t debounced; 
extern volatile uint8_t TWO_SEC_DELAY_COMPLETE;
extern volatile uint8_t counter_A11;
extern volatile uint8_t counter_A12;
