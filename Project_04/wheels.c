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

void WHEELS_test(void);
void Wheels_OFF(void);
//------------------------
// Turning wheels off
//------------------------
void Left_Motor_OFF(void){
  P3OUT &= ~(L_FORWARD | L_REVERSE);
  left_forward_flag = left_reverse_flag = 0;
}
void Right_Motor_OFF(void){
  P3OUT &= ~(R_FORWARD | R_REVERSE);
  right_forward_flag = right_reverse_flag = 0;
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
  switch(left_reverse_flag)
  {
  case true: break;
  case false: 
    P3OUT |= L_FORWARD;
    left_forward_flag = 1;
  }
}

void Right_Motor_ON_FORWARD(uint8_t speed){
  switch(right_reverse_flag)
  {
  case true: break;
  case false: 
    P3OUT |= R_FORWARD;
    right_forward_flag = 1;
  }
}

void Wheels_ON_FORWARD(uint8_t speed){
  Left_Motor_ON_FORWARD(speed);
  Right_Motor_ON_FORWARD(speed);
}
  
//**********
// Reverse *
//**********
void Left_Motor_ON_REVERSE(uint8_t speed){
  switch(left_forward_flag)
  {
  case true: break;
  case false: 
    P3OUT |= L_REVERSE;
    left_reverse_flag = 1;
  }
}

void Right_Motor_ON_REVERSE(char speed){
  switch(right_forward_flag)
  {
  case true: break;
  case false: 
    P3OUT |= R_REVERSE;
    right_reverse_flag = 1;
  }
}

void Wheels_ON_REVERSE(uint8_t speed){
  Left_Motor_ON_REVERSE(speed);
  Right_Motor_ON_REVERSE(speed);
}
