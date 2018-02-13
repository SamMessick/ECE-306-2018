//===============================================================
//  File Name: timerB0.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    timerB0.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "ports.h"
#include <stdint.h>
#include <stdbool.h>
#define MOTOR_PERIOD       (0xFFFF)         // PWM period
#define MOTOR_OFF               (0)         // 0 percent duty cycle
#define DUTY_CYCLE_DIVISOR  (0x101)         // Allows for 256 speed options between 0 and 255

void Init_Timer_B0(void);

extern uint8_t motor_speed;