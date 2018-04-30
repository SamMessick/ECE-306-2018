//===============================================================
//  File Name: iot.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    iot.c
//  Author: Sam Messick
//  Date Apr. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "ports.h"
#include "wheels.h"

void reset_iot(void);

extern uint8_t iot_ip_up;
