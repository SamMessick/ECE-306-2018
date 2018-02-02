//===============================================================
//  File Name: ports.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    switches.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "ports.h"
#include "display.h"
#include <stdint.h>
#include <stdbool.h>

void switch_control(void);
void Init_Switch(void);
void menu_act(void);
void menu_select(void);

void usleep(unsigned int usec);
void usleep10(unsigned int usec);
void five_msec_sleep(unsigned int msec);
void measure_delay(void);
void out_control_words(void);

// Switch on flags; used to "debounce"
uint8_t flag_RED_LED_ON;
uint8_t flag_GRN_LED_ON;