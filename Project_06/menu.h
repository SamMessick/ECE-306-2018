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
#include "adc12_B.h"
#include "wheels.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define IR_ACTIVE_READING   (270)
#define THUMB_ACTIVE_READING (1000)
#define COUNTER_RESET        (0)
#define ASCII_NUM_SHIFT      (48)
#define THOUSAND             (1000)
#define HUNDRED              (100)
#define TEN                  (10)
#define ONE                  (1)

void update_menu(void);
void LCD_print(char first_line[COLUMN_NUM_COLUMNS], char second_line[COLUMN_NUM_COLUMNS], char third_line[COLUMN_NUM_COLUMNS], char fourth_line[COLUMN_NUM_COLUMNS]);
void update_string(char *string_data, int string);
void delay(uint16_t msecs);
void print_detector_values(void);


extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;
extern int8_t menu_counter;            // displays which option has been chosen by the buttons
