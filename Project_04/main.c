//------------------------------------------------------------------------------
//  File name: main.c
//  Description: This file contains the MSP430 Car's Operating System
//
//
//  Sam Messick
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//**To fix: reenable PWM in ports.c, wheels.c ,timerB0.c;


#include "main.h"

extern volatile unsigned int Time_Sequence;     // Counting variable; increments every 5ms up to 125
extern volatile char one_time;



///////////////////////////////////
unsigned int Motors_Off_Time;         // Time out of 125 that motors turn off
unsigned int Motors_Enabled;          // Flag set if motors are to run


void update_motor_state(void){
    if(Motors_Enabled)
    {
      if(Time_Sequence < Motors_Off_Time)
        P3OUT |= (L_FORWARD | R_FORWARD);
      
      else if(Time_Sequence >= Motors_Off_Time)    
        P3OUT &= ~(L_FORWARD | R_FORWARD);
    }
}
///////////////////////////////////







void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main initialization of the car. Execution of code starts here.
// The operating system is Back Ground Fore Ground... but mainly Fore Ground lol
//
//------------------------------------------------------------------------------
  
  Init_Ports();                        // Initialize Ports
// Disable the GPIO power-on default high-impedance mode to activate
// previously configured port settings
  PM5CTL0 &= ~LOCKLPM5;
  Init_Clocks();                       // Initialize Clock System
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_Timers();                       // Initialize Timers
  Init_LCD();                          // Initialize LCD
  Init_LEDs();
  
  
//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  for(;;) {                      // Can the Operating system run
    update_motor_state();
    switch(Time_Sequence){
    case 150:
      if(one_time){
      }
    case 125:                          // 1250 msec
        if(one_time){
          one_time = 0;
        }
        Time_Sequence = 0;             //
        break;
      case 100:                        // 1000 msec
        if(one_time){
          lcd_BIG_mid();
          display_changed = 1;
          one_time = 0;
        }
        break;
      case 75:                         // 750 msec
        if(one_time){
          one_time = 0;
        }
        break;
      case 50:                         // 500 msec
        if(one_time){
          lcd_4line();
          display_changed = 1;
          one_time = 0;
        }
        break;
      case  25:                        // 250 msec
        if(one_time){
          one_time = 0;
        }
        break;                         //
        case 0: 
          int x = 1+1;
          break;
    }
    Switches_Process();                // Check for switch state change
    update_menu();
    Display_Process();
  }
}