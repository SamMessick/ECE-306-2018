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

uint16_t delay_time;

void WHEELS_test(void);

void update_motor_state(void){
    if(Motors_Enabled)
    {
      if(Time_Sequence < Motors_Off_Time)
        P3OUT |= (L_FORWARD | R_FORWARD);
      
      else if(Time_Sequence >= Motors_Off_Time)    
        P3OUT &= ~(L_FORWARD | R_FORWARD);
    }
}

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
  if(left_reverse_flag)                         // If left motor is not set to move backward already
  {
    TB0CCR4 = speed*DUTY_CYCLE_DIVISOR;         // Set left motor forward speed as one of 255 settings
    left_forward_flag = true;                   // Prevent left motor from moving backward simultaneously
  }
}

void Right_Motor_ON_FORWARD(uint8_t speed){
  if(right_reverse_flag)                        // If right motor is not set to move backward already
  { 
    TB0CCR6 = speed*DUTY_CYCLE_DIVISOR;         // Set right motor forward speed as one of 255 settings
    right_forward_flag = true;                  // Prevent right motor from moving backward simultaneously
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
  if(!left_forward_flag)                        // If left motor is not set to move forward already
  { 
    TB0CCR3 = speed*DUTY_CYCLE_DIVISOR;         // Set left motor reverse speed as one of 255 settings
    left_reverse_flag = true;                   // Prevent left motor from moving forward simultaneously
  }
}

void Right_Motor_ON_REVERSE(char speed){
  if(!right_forward_flag)                       // If right motor is not set to move forward already
  {
    TB0CCR5 = speed*DUTY_CYCLE_DIVISOR;         // Set right motor reverse speed as one of 255 settings
    right_reverse_flag = true;                  // Prevent right motor from moving forward simultaneously
  }
}

void Drive_Straight_REVERSE(uint8_t speed){
  Left_Motor_ON_REVERSE(speed);
  Right_Motor_ON_REVERSE(speed);
}

//------------------------
// Driving in shapes
//------------------------
//**********
// Circle  *
//**********
void drive_in_circle(void){
  static uint8_t circles_left_to_drive = NUM_TRIALS;
  static uint8_t instruction_label;
  
  if(shape_routine_begin)
    switch(instruction_label)
    {
        
    case INSTRUCTION1: /* wait two seconds before beginning */
      delay_time = TWO_SEC;                         // send delay time to global accessible by timer A1
      //TA1CCTL2 |= CCIE;                           // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION2: /* drive in circle counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_LCIRC_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_LCIRC_SPEED);
      delay_time = CIR_SEC;                         // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                             // enable timer A1.2 to count time
      if(--circles_left_to_drive)
        instruction_label = INSTRUCTION2;           // drive in circles until there are no circles left to drive
      else 
        instruction_label++; break;                 // end shape routine
      
        
    default:           /* turn off wheels and return permanently to main */
      Wheels_OFF();
      instruction_label = INSTRUCTION1;
      circles_left_to_drive = NUM_TRIALS;
    }
}

//**********
// Figure-8*
//**********
void drive_in_figure8(void){
  static uint8_t figure8s_left_to_drive = NUM_TRIALS;
  static uint8_t instruction_label;
  if(shape_routine_begin)
    switch(instruction_label)
    {
        
    case INSTRUCTION1: /* wait two seconds before beginning */
      delay_time = TWO_SEC;                         // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                             // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION2: /* drive in circle counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_FIG8L_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FIG8L_SPEED);
      delay_time = FOR_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* drive in circle clockwise */
      Left_Motor_ON_FORWARD(LEFT_FIG8R_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FIG8R_SPEED);
      delay_time = FOR_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      if(--figure8s_left_to_drive)
        instruction_label = INSTRUCTION2;          // drive in figure-8s until there are no more left to drive
      else 
        instruction_label++; break;                // end shape routine
        
        
    default:          /* turn off wheels and return permanently to main */
      Wheels_OFF();
      instruction_label = INSTRUCTION1;
      figure8s_left_to_drive = NUM_TRIALS;
    }
}

//**********
// Triangle*
//**********
void drive_in_triangle(void){
  static uint8_t edges_left_to_drive = NUM_TRIANGLE_EDGES;
  static uint8_t instruction_label;
  if(shape_routine_begin)
    switch(instruction_label)
    {
    case INSTRUCTION1: /* wait two seconds before beginning */
      delay_time = TWO_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      instruction_label++;
      break;
        
        
    case INSTRUCTION2: /* drive along triangle edge */
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
      delay_time = ONE_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* turn 60 degrees counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_LTURN_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_LTURN_SPEED);
      delay_time = ONE_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      if(--edges_left_to_drive)
        instruction_label = INSTRUCTION2;           // drive in figure-8s until there are no more left to drive
      else 
        instruction_label++; break;                 // end shape routine
      
      
    default:          /* turn off wheels and return permanently to main */
      Wheels_OFF();
      instruction_label = INSTRUCTION1;
      edges_left_to_drive = NUM_TRIANGLE_EDGES;
    }
}
