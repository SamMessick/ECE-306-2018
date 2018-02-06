//===============================================================
//  File Name: wheels.c
//  Description: This file contains the functions needed for control
//                    operations of the wheels
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "wheels.h"

// H-bridge protection flags: 
// don't allow for motion forward/backward simultaneously in one motor

uint8_t left_forward_flag;
uint8_t left_reverse_flag;
uint8_t right_forward_flag;
uint8_t right_reverse_flag;

unit8_t delay_continue;

void delay(uint16_t msecs){
  delay_time     = msecs;                   // send delay time to global accessible by timer A1
  delay_continue = true;
  TA1CCTL2 |= CCIE;                    // enable timer A1.2 to count msecs time
  while(delay_continue){}
}

void WHEELS_test(void);
void Wheels_OFF(void);
//------------------------
// Turning wheels off
//------------------------
void Left_Motor_OFF(void){
  TB0CCR3 = MOTOR_OFF;         // Set PWM to 0 percent duty cycle
  TB0CCR4 = MOTOR_OFF;   
  left_forward_flag = left_reverse_flag = false;
}
void Right_Motor_OFF(void){
  TB0CCR5 = MOTOR_OFF;         // Set PWM to 0 percent duty cycle
  TB0CCR6 = MOTOR_OFF;         
  right_forward_flag = right_reverse_flag = false;
}
void Wheels_OFF(void){
  Left_Motor_OFF();
  Right_Motor_OFF();
}

//------------------------
// Turning wheels on
//------------------------
//**********
// Forward *
//**********
void Left_Motor_ON_FORWARD(uint8_t speed){
  switch(left_reverse_flag)                     // Do not attempt forward/backward driving at one time
  {
  case true: break;
  case false:
    TB0CCR4 = speed*DUTY_CYCLE_DIVISOR;         // Set speed as one of 255 settings
    left_forward_flag = true;
  }
}

void Right_Motor_ON_FORWARD(uint8_t speed){
  switch(right_reverse_flag)                    // Do not attempt forward/backward driving at one time
  {
  case true: break;
  case false: 
    TB0CCR6 = speed*DUTY_CYCLE_DIVISOR;         // Set speed as one of 255 settings
    right_forward_flag = true;
  }
}

void Drive_Straight_Forward(uint8_t speed){
  Left_Motor_ON_FORWARD(speed);
  Right_Motor_ON_FORWARD(speed);
}
  
//**********
// Reverse *
//**********
void Left_Motor_ON_REVERSE(uint8_t speed){
  switch(left_forward_flag)                     // Do not attempt forward/backward driving at one time
  {
  case true: break;
  case false: 
    TB0CCR3 = speed*DUTY_CYCLE_DIVISOR;         // Set speed as one of 255 settings
    left_reverse_flag = true;
  }
}

void Right_Motor_ON_REVERSE(char speed){
  switch(right_forward_flag)                    // Do not attempt forward/backward driving at one time
  {
  case true: break;
  case false: 
    TB0CCR5 = speed*DUTY_CYCLE_DIVISOR;         // Set speed as one of 255 settings
    right_reverse_flag = true;
  }
}

void Drive_Straight_REVERSE(uint8_t speed){
  Left_Motor_ON_REVERSE(speed);
  Right_Motor_ON_REVERSE(speed);
}

//------------------------
// Driving in shapes
//------------------------

void drive_in_circle(void){ 
  Left_Motor_ON_FORWARD(LEFT_LCIRC_SPEED);
  Right_Motor_ON_FORWARD(RIGHT_LCIRC_SPEED);
  delay(10000);
  Wheels_OFF();
}
void drive_in_figure8(void){
  Left_Motor_ON_FORWARD(LEFT_LCIRC_SPEED);
  Right_Motor_ON_FORWARD(RIGHT_LCIRC_SPEED);
  delay(10000);
  Left_Motor_ON_FORWARD(LEFT_RCIRC_SPEED);
  Right_Motor_ON_FORWARD(RIGHT_RCIRC_SPEED);
  Wheels_OFF();
}
void drive_in_triangle(void){ 
  uint8_t counter;
  for(;counter <= TRIANGLE_NUM_SIDES; counter++){
    Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
    Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
    delay(2000);
    //Turn to the left
    Left_Motor_ON_FORWARD(LEFT_LTURN_SPEED);
    Right_Motor_ON_FORWARD(RIGHT_RTURN_SPEED);
    delay(1500);
  }
}
