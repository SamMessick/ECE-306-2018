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
#define LEFT_FORWARD_SPEED      (253)
#define RIGHT_FORWARD_SPEED     (180)
#define LEFT_LCIRC_SPEED        (40)
#define RIGHT_LCIRC_SPEED       (253)
#define LEFT_FIG8L_SPEED        (20)
#define RIGHT_FIG8L_SPEED       (253)
#define LEFT_FIG8R_SPEED        (253)
#define RIGHT_FIG8R_SPEED       (20)
#define LEFT_LTURN_SPEED        (253)
#define RIGHT_LTURN_SPEED         (0)
#define NUM_TRIALS                (2)
#define NUM_TRIANGLE_EDGES        (6)      // goes around twice
#ifndef SHAPE_INSTR_ENUM
#define SHAPE_INSTR_ENUM

typedef enum{
  INSTRUCTION1 = 0,
  INSTRUCTION2,
  INSTRUCTION3,
  INSTRUCTION4,
  INSTRUCTION5,
  INSTRUCTION6,
  INSTRUCTION7,
  INSTRUCTION8,
  INSTRUCTION9,
  INSTRUCTION10,
  INSTRUCTION11
} shape_instr_enum_t;


#endif
#ifndef TIMER_INTV_ENUM
#define TIMER_INTV_ENUM

typedef enum{
  MSEC = (50000),                   // 8 MHz / 8 / (1/50 ms) = 50,000
  CIR_SEC = (130),
  TWO_SEC = (40),
  THR_SEC = (60),
  FOR_SEC = (70),
  SIX_SEC = (120),
  ONE_SEC = (20),
  HALF_SEC = (10),
  QUART_SEC = (5)
} timer_intv_t;

#endif

void initialize_delay(uint16_t delay);
void update_instruction_label(uint8_t* instruction_label);

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
void drive_back_and_forth(void);

extern volatile uint8_t delay_continue;
extern volatile uint16_t delay_time;
extern uint8_t instruction_label_tmp;