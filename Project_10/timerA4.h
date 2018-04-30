//===============================================================
//  File Name: timerA4.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    timerA4.c
//  Author: Sam Messick
//  Date Apr. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include <stdint.h>

#define  ENABLE_BACKLITE_INTERRUPT  (TA4CCTL1 |= CCIE)
#define  DISABLE_BACKLITE_INTERRUPT (TA4CCTL1 &= ~CCIE)
#ifndef  BACKLITE_BRIGHTNESS_LEVELS
#define  BACKLITE_BRIGHTNESS_LEVELS

typedef enum {
  NO_LIGHTING = 0,
  QUART_LIGHTING = 0x4000,
  HALF_LIGHTING  = 0x8000,
  FULL_LIGHTING  = 0xFFFF
} backlite_brightness_t;

#endif

void init_Timer_A4(void);
void dim_lcd(uint16_t preferred_brightness);

extern uint16_t current_lcd_brightness;       // Preferred LCD brightness level