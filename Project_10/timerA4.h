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

// Backlite status register management
#define BACKLITE_STATUS(x)        (backlite_status_reg & x)
#define BACKLITE_ENABLE(x)        (backlite_status_reg |= x)
#define BACKLITE_DISABLE(x)       (backlite_status_reg &= ~x)
#define BACKLITE_ADJUSTING         (0x01)

#ifndef  BACKLITE_BRIGHTNESS_LEVELS
#define  BACKLITE_BRIGHTNESS_LEVELS

typedef enum {
  NO_LIGHTING = 0,
  QUART_BRIGHTNESS = 0x4000,
  HALF_BRIGHTNESS  = 0x8000,
  FULL_BRIGHTNESS  = 0xFFFF
} backlite_brightness_t;

#endif

void init_Timer_A4(void);
void dim_lcd(uint32_t preferred_brightness);

extern uint16_t current_lcd_brightness;       // Preferred LCD brightness level
extern uint8_t backlite_status_reg;