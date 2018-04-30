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
#include "adc12_B.h"
#include "clocks.h"
#include "serial.h"
#include "shapes_menu.h"
#include "LCD.h"
#include "led.h"
#include "init.h"
#include "iot.h"
#include "ports.h"
#include <string.h>
#include <stdbool.h>
#include <stdint.h>

// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
#define ACTIVATE_PREVIOUS_PORT_SETTINGS  (PM5CTL0 &= ~LOCKLPM5)

// OS control variables
//volatile char slow_input_down;
//unsigned char display_mode;