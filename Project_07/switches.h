//===============================================================
//  File Name: switches.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    switches.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "shapes_menu.h"
#include <stdint.h>
#include <stdbool.h>

void Init_Switches(void);
void enable_switch_BUTTON1(void);
void enable_switch_BUTTON2(void);
void Disable_Switches(void);
void disable_switch_BUTTON1(void);
void disable_switch_BUTTON2(void);

void measure_delay(void);
void out_control_words(void);