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

uint16_t delay_time;
unsigned int L_FORWARD_on_time;       // Time out of 100ms that left motor turns on
unsigned int R_FORWARD_on_time;       // Time out of 100ms that right motor turns on 
unsigned int Motors_Enabled;          // Flag set if motors are to run

void WHEELS_test(void);

void update_motor_state(void){
    // Update motor's on/off state based on their PWM on/off times and Time_Sequence
    if(Motors_Enabled)
    {
      if((Time_Sequence % PWM_PERIOD) < R_FORWARD_on_time)
        P3OUT |=  R_FORWARD;
      else if((Time_Sequence % PWM_PERIOD) >= R_FORWARD_on_time)    
        P3OUT &= ~R_FORWARD;
        
      if((Time_Sequence % PWM_PERIOD) < L_FORWARD_on_time)
        P3OUT |=  L_FORWARD;
      else if((Time_Sequence % PWM_PERIOD) >= L_FORWARD_on_time)
        P3OUT &= ~L_FORWARD;
    }
}

void Wheels_OFF(void){
    L_FORWARD_on_time = MOTOR_OFF;
    R_FORWARD_on_time = MOTOR_OFF;
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
      L_FORWARD_on_time = LEFT_LCIRC_SPEED;
      R_FORWARD_on_time = RIGHT_LCIRC_SPEED;
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
      L_FORWARD_on_time = LEFT_FIG8L_SPEED;
      L_FORWARD_on_time = RIGHT_FIG8L_SPEED;
      delay_time = FOR_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* drive in circle clockwise */
      L_FORWARD_on_time = LEFT_FIG8R_SPEED;
      R_FORWARD_on_time = RIGHT_FIG8R_SPEED;
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
      Motors_Enabled = true;
      L_FORWARD_on_time = LEFT_FORWARD_SPEED;
      R_FORWARD_on_time = RIGHT_FORWARD_SPEED;
      delay_time = ONE_SEC;                        // send delay time to global accessible by timer A1
      TA1CCTL2 |= CCIE;                            // enable timer A1.2 to count time
      instruction_label++; break;
        
        
    case INSTRUCTION3: /* turn 60 degrees counterclockwise */
      L_FORWARD_on_time = LEFT_LTURN_SPEED;
      R_FORWARD_on_time = RIGHT_LTURN_SPEED;
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
