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
//
// **Operation adapted from main "while" loop by Carlson
//     --Time_Sequence continues to update but loops every second
//------------------------------------------------------------------------------
  for(;;) {                      
    Switches_Process();                // Check for switch state change
    update_menu();                     // Check for menu state change
    update_motor_state();              // Update pseudo-PWM in wheels
    Display_Process();                 // Update screen text
    update_text_size();                // Vary big/small text every second
    }
  }
}
