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

uint8_t left_forward_flag;     // Is left motor rotating forward?
uint8_t left_reverse_flag;     // Is left motor rotating reverse?
uint8_t right_forward_flag;    // Is right motor rotating forward?
uint8_t right_reverse_flag;    // Is right motor rotating reverse?
uint8_t instruction_label_tmp; // Global of current instruction step


void initialize_delay(uint16_t delay){
  delay_time = delay;                          // send delay time to global accessible by timer A1
  TA0CCTL2 |= CCIE;                            // enable timer A1.2 to count time
}

void update_instruction_label(uint8_t* instruction_label){
  (*instruction_label)++;                         // Set up next instruction
  instruction_label_tmp = *instruction_label;   // Set static instruction visable by menu to update LCD
}

void WHEELS_test(void);
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
  if(!left_reverse_flag)                         // If left motor is not set to move backward already
  {
    TB0CCR4 = speed*DUTY_CYCLE_DIVISOR;         // Set left motor forward speed as one of 255 settings
    left_forward_flag = true;                   // Prevent left motor from moving backward simultaneously
  }
}

void Right_Motor_ON_FORWARD(uint8_t speed){
  if(!right_reverse_flag)                        // If right motor is not set to move backward already
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
      initialize_delay(TWO_SEC);
      instruction_label++; break;
        
        
    case INSTRUCTION2: /* drive in circle counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_LCIRC_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_LCIRC_SPEED);
      initialize_delay(CIR_SEC);
      if(--circles_left_to_drive)
        instruction_label = INSTRUCTION2;     // drive in circles until there are no circles left to drive
      else 
        instruction_label++;                 // end shape routine
      break;
      
        
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
      initialize_delay(TWO_SEC);
      instruction_label++; break;
        
        
    case INSTRUCTION2: /* drive in circle counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_FIG8L_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FIG8L_SPEED);
      initialize_delay(FOR_SEC);
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* drive in circle clockwise */
      Left_Motor_ON_FORWARD(LEFT_FIG8R_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FIG8R_SPEED);
      initialize_delay(FOR_SEC);
      if(--figure8s_left_to_drive)
        instruction_label = INSTRUCTION2;    // drive in figure-8s until there are no more left to drive
      else 
        instruction_label++;                // end shape routine
      break;
        
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
      initialize_delay(TWO_SEC);
      instruction_label++;
      break;
        
        
    case INSTRUCTION2: /* drive along triangle edge */
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
      initialize_delay(ONE_SEC);
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* turn 60 degrees counterclockwise */
      Left_Motor_ON_FORWARD(LEFT_LTURN_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_LTURN_SPEED);
      initialize_delay(ONE_SEC);
      if(--edges_left_to_drive)
        instruction_label = INSTRUCTION2;    // drive in figure-8s until there are no more left to drive
      else 
        instruction_label++;                  // end shape routine
      break;
      
    default:          /* turn off wheels and return permanently to main */
      Wheels_OFF();
      instruction_label = INSTRUCTION1;
      edges_left_to_drive = NUM_TRIANGLE_EDGES;
    }
}

//**********
// Proj 5  *
//**********

void drive_back_and_forth(void){
  static uint8_t instruction_label;
  if(shape_routine_begin)
    switch(instruction_label)
    {
    case INSTRUCTION1: /* wait two seconds before beginning */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(TWO_SEC); break;
        
        
    case INSTRUCTION2: /* drive forward for one second */
      Wheels_OFF();
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
      initialize_delay(ONE_SEC);
      update_instruction_label(&instruction_label); break;
        
        
    case INSTRUCTION3: /* pause for one second */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(ONE_SEC); break;
      
      
    case INSTRUCTION4: /* travel backward for two seconds */
      Wheels_OFF();
      Left_Motor_ON_REVERSE(LEFT_FORWARD_SPEED);
      Right_Motor_ON_REVERSE(RIGHT_FORWARD_SPEED);
      initialize_delay(TWO_SEC);
      update_instruction_label(&instruction_label); break;
      
      
    case INSTRUCTION5: /* pause for one second */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(ONE_SEC); break;
      
      
    case INSTRUCTION6: /* travel forward for one second */
      Wheels_OFF();
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
      initialize_delay(ONE_SEC);
      update_instruction_label(&instruction_label); break;
      
      
    case INSTRUCTION7: /* pause for one second */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(ONE_SEC); break;
      
      
    case INSTRUCTION8: /* Spin in place clockwise for three seconds */
      Wheels_OFF();
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_REVERSE(RIGHT_FORWARD_SPEED);
      initialize_delay(THR_SEC);
      update_instruction_label(&instruction_label); break;
      
      
    case INSTRUCTION9: /* pause for two seconds */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(TWO_SEC); break;
      
      
    case INSTRUCTION10: /* Spin in place counter-clockwise for three seconds */
      Wheels_OFF();
      Left_Motor_ON_REVERSE(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
      initialize_delay(THR_SEC);
      update_instruction_label(&instruction_label); break;
      
      
    case INSTRUCTION11: /* pause for two seconds */
      Wheels_OFF();
      update_instruction_label(&instruction_label);
      initialize_delay(TWO_SEC); break;
      
    default:          /* turn off wheels and return permanently to main */
      Wheels_OFF();
      instruction_label = INSTRUCTION1;
    }
}
