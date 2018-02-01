//===============================================================
//  File Name: init.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    init.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "ports.h"
#include <stdbool.h>
#include <stdint.h>
#define LCD_RESET_STATE      (0)
#ifndef INIT_ENUMS_H
#define INIT_ENUMS_H

// enum for display row numbers
typedef enum{
  LINE1 = 0,
  LINE2,
  LINE3,
  LINE4,
  LINE_NUM_LINES,
}Display_Line_t;

// enum for display column numbers
typedef enum{
  COLUMN1 = 0,
  COLUMN2,
  COLUMN3,
  COLUMN4,
  COLUMN5,
  COLUMN6,
  COLUMN7,
  COLUMN8,
  COLUMN9,
  COLUMN10,
  COLUMN11,
  COLUMN_NUM_COLUMNS
}Display_Column_t;

#endif

// Initialization prototypes
void Init_Conditions(void);
void enable_interrupts(void);

/* Assignments found in LCD.c; arrays 
 *   and variables controlling text
 *   output to LCD
 */
extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;

