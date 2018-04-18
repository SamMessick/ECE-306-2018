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
#include "adc12_B.h"
#include <stdint.h>
#include <stdbool.h>
#define L_PWM_MAX               (255)
#define L_PWM_MIN               (135)
#define R_PWM_MAX               (140)
#define R_PWM_MIN               (0)
#define LEFT_FORWARD_SPEED      (235)
#define RIGHT_FORWARD_SPEED     (145)

#define QUARTER_RIGHT            (90)

#ifndef TIMER_INTV_ENUM
#define TIMER_INTV_ENUM

typedef enum{
  MSEC = (3270),                   // 8 MHz / 8 / (1/50 ms) = 50,000
  SEC  = (32768),
  FIVE_MSEC = (1000),
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
#ifndef PID_STRUCT
#define PID_STRUCT

typedef struct{
  uint16_t windup_guard;
  double   p_gain;
  double   i_gain;
  double   d_gain;
  int16_t  prev_error;
  int16_t  i_error;
} PID;
#endif

#define IS_POSITIVE >0
#define IS_NEGATIVE <0

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

void turn(uint8_t degrees);
void drive_to_black_line(void);
void Init_PID(void);
void pid_udpate_left(void);
void pid_update_right(void);

extern volatile uint8_t delay_continue;
extern volatile uint16_t delay_time;
extern uint8_t instruction_label_tmp;
extern volatile uint8_t waiting;