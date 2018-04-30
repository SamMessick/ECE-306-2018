//===============================================================
//  File Name: clocks.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    clocks.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include <stdbool.h>

// Clocks initialization
void init_Clocks(void);

// Clock control register macros
#define FLLN_BITS         (0x03ffu)
#define FLLN_255          (0x00ffu)
#define CSLOCK               (0x01) // Any incorrect password locks registers

// Port J Pins
#define XINR                 (0x10) // XINR
#define XOUTR                (0x20) // XOUTR
#define CLEAR_REGISTER     (0X0000)