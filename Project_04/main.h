//===============================================================
//  File Name: main.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    the mspCar's operating system
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

// Includes headers for ports, led, initialization
#include "msp430.h"
#include "clocks.h"
#include "menu.h"
#include "led.h"
#include "init.h"
#include "ports.h"
#include "timerB0.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>
#ifndef OS_LOOP_ENUMS_H
#define OS_LOOP_ENUMS_H

// enum for "while" OS loop cases
typedef enum{
  CASE1 = 25,
  CASE2 = 50,
  CASE3 = 75,
  CASE4 = 100,
  CASE5 = 125,
  CASE_NUM_CASES,
}OS_Case_t;

#endif

// Additional functions not yet defined by me
void Switches_Process(void); // switches.c

void lcd_BIG_mid(void);      // LCD.c
void lcd_4line(void);
void Display_Process(void);
void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4);
void enable_display_update(void);
void Init_LCD(void);
void lcd_clear(void);
void lcd_putc(char c);
void lcd_puts(char *s);
void lcd_power_on(void);
void lcd_write_line1(void);
void lcd_write_line2(void);

void Init_Timers(void);      // timers.c, timersA0.c ...
void Init_Timer_A0(void);
void Init_Timer_A1(void);
void Init_Timer_A2(void);
void Init_Timer_A3(void);
void Init_Timer_B0(void);
void Init_Timer_B1(void);
void Init_Timer_B2(void);

// OS control variables
volatile char slow_input_down;
unsigned char display_mode;
extern volatile unsigned char display_changed;
extern volatile unsigned int Time_Sequence;
extern volatile char one_time;