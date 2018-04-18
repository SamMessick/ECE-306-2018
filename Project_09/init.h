//===============================================================
//  File Name: init.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    init.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "shapes_menu.h"
#include "ports.h"
#include "timerA0.h"
#include "timerB0.h"
#include <stdbool.h>
#include <stdint.h>
#define LCD_RESET_STATE      (0)

// Initialization prototypes
void Init_Conditions(void);
void Init_Timers(void);
void enable_interrupts(void);

/* Assignments found in LCD.c; arrays 
 *   and variables controlling text
 *   output to LCD
 */
extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

