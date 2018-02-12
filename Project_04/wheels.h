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
#include <stdint.h>
#include <stdbool.h>
#define LEFT_FORWARD_SPEED      (99)               // 253 o.o 255          (253/255) * 1000
#define RIGHT_FORWARD_SPEED     (99)               // 180 o.o 255          (180/255) * 1000
#define LEFT_LCIRC_SPEED        (16)               // 40  o.o 255          ( 40/255) * 1000
#define RIGHT_LCIRC_SPEED       (99)               // 253 o.o 255          (253/255) * 1000
#define LEFT_FIG8L_SPEED         (8)               // 20  o.o 255          ( 20/255) * 1000
#define RIGHT_FIG8L_SPEED       (99)               // 253 o.o 255          (253/255) * 1000
#define LEFT_FIG8R_SPEED        (99)               // 253 o.o 255          (253/255) * 1000
#define RIGHT_FIG8R_SPEED        (8)               // 20  o.o 255          ( 20/255) * 1000
#define LEFT_LTURN_SPEED        (99)               // 253 o.o 255          (253/255) * 1000
#define RIGHT_LTURN_SPEED        (0)               // 0   o.o 255          (  0/255) * 1000
#define NUM_TRIALS               (2)                
#define NUM_TRIANGLE_EDGES       (6)               // goes around twice

#define MOTOR_OFF                (0)

#define COUNTER_RESET_STATE      (0)
#ifndef SHAPE_INSTR_ENUM
#define SHAPE_INSTR_ENUM

typedef enum{
  INSTRUCTION1 = 0,
  INSTRUCTION2,
  INSTRUCTION3
} shape_instr_enum_t;


#endif
#ifndef TIMER_INTV_ENUM
#define TIMER_INTV_ENUM

typedef enum{
  OTWENT_SEC = (0xC350),
  MSEC = (1000),
  CIR_SEC = (6500),
  TWO_SEC = (2000),
  FOR_SEC = (3500),
  SIX_SEC = (6000),
  ONE_SEC = (1000),
  HALF_SEC = (500),
  QUART_SEC_DELAY = (50)
} timer_intv_t;

#endif

// Wheel operation
void WHEELS_test(void);
void update_motor_state(void);
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

extern unsigned int Motors_Off_Time;         // Time out of 100ms after which motors turn off
extern unsigned int Motors_Enabled;          // Flag set if motors are to run
extern volatile unsigned int Time_Sequence;  // Timer variable
