//===============================================================
//  File Name: wheels.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    wheels.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "ports.h"
#include "timerB0.h"
#include <stdint.h>
#include <stdbool.h>
#define LEFT_FORWARD_SPEED      (255)
#define RIGHT_FORWARD_SPEED      (80)
#define LEFT_LCIRC_SPEED        (200)
#define RIGHT_LCIRC_SPEED       (100)
#define LEFT_RCIRC_SPEED        (255)
#define RIGHT_RCIRC_SPEED        (50)
#define LEFT_LTURN_SPEED        (255)
#define RIGHT_LTURN_SPEED         (0)

// Wheel operation
void WHEELS_test(void);
void Wheels_OFF(void);
void Left_Motor_OFF(void);
void Right_Motor_OFF(void);
void Wheels_OFF(void);
void Left_Motor_ON_FORWARD(uint8_t speed);
void Right_Motor_ON_FORWARD(uint8_t speed);
void Drive_Straight_Forward(uint8_t speed);
void Left_Motor_ON_REVERSE(uint8_t speed);
void Right_Motor_ON_REVERSE(char speed);
void Drive_Straight_REVERSE(uint8_t speed);

void drive_in_circle(void);
void drive_in_figure8(void);
void drive_in_triangle(void);

extern uint8_t delay_continue;
extern uint16_t delay_time;