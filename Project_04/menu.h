//===============================================================
//  File Name: menu.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    display.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "LCD.h"
#include "switches.h"
#include "wheels.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
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
  COLUMN_NUM_COLUMNS
}Display_Column_t;

// enum for menu options
typedef enum{
  OPTION1 = 1,
  OPTION2,
  PENULT_OPTION,
  MENU_NUM_OPTIONS
}Menu_Option_t;

#endif

void update_menu(void);
void LCD_print(char first_line[10], char second_line[10], char third_line[10], char fourth_line[10]);
void update_string(char *string_data, int string);
void delay(uint16_t msecs);
void update_text_size(void);


extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;
extern int8_t menu_counter;            // displays which option has been chosen by the buttons
