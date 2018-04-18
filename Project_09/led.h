//===============================================================
//  File Name: led.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    led.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "ports.h"


// LED configuration functions
void Init_LEDs(void);
void IR_LED_control(char selection);
void Backlite_control(char selection);
void updateBacklight(void);