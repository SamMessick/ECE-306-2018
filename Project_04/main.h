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
#include "LCD.h"
#include "led.h"
#include "init.h"
#include "ports.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// Additional functions not yet defined by me
void Switches_Process(void); // switches.c

void Init_Timers(void);      // timers.c, timersA0.c ...

// OS control variables