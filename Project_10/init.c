//===============================================================
//  File Name: init.c
//  Description: This file contains the Initialization of all
//                    display values, and enables interrupts
//
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "init.h"

void init_Conditions(void){
//------------------------------------------------------------------------------
  // Clears LCD
  int i;

  for(i=COLUMN1;i<=COLUMN_NUM_COLUMNS;i++){
    display_line[LINE1][i] = false;
    display_line[LINE2][i] = false;
    display_line[LINE3][i] = LCD_RESET_STATE;
    display_line[LINE4][i] = LCD_RESET_STATE;
  }
  for(i=LINE1;i<=LINE_NUM_LINES;i++){
    display[LINE1] = &display_line[i][COLUMN1];
  }
  update_display = LCD_RESET_STATE;
  update_display_count = LCD_RESET_STATE;

// Interrupts are disabled by default, enable them.
  enable_interrupts();
//------------------------------------------------------------------------------
}

void init_Timers(void){
  init_Timer_B0();                     // Initialize motor PWM behavior
  init_Timer_A0();                     // Initialize delay behavior and LCD updates
  init_Timer_A4();
}