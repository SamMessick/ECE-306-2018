//------------------------------------------------------------------------------
//  File name: main.c
//  Description: This file contains the MSP430 Car's Operating System
//
//
//  Sam Messick
//  Jan 2018
//  Built with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include "main.h"

void main(void){
//------------------------------------------------------------------------------
// Main Program
// This is the main routine for the program. Execution of code starts here.
// The operating system is Back Ground Fore Ground.
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

// Place the contents of what you want on the display, in between the quotes
// Limited to 10 characters per line
//

  strcpy(display_line[LINE1], "   NCSU   ");
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], "Sam M. Car");
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE4], "  ECE306  ");
  update_string(display_line[LINE4], LINE4);
  enable_display_update();
//  Display_Update(3,1,0,0);

//------------------------------------------------------------------------------
// Begining of the "While" Operating System
//------------------------------------------------------------------------------
  while(true) {                      // Can the Operating system run
    switch(Time_Sequence){
      case CASE5:                        // 1000 msec
        if(one_time){
          lcd_BIG_mid();
          display_changed = true;
          one_time = false;
        }
        Time_Sequence = true;             //
        break;
      case CASE4:                        // 1000 msec
        if(one_time){
          one_time = false;
        }
        break;
      case CASE3:                         // 750 msec
        if(one_time){
          one_time = false;
        }
        break;
      case CASE2:                         // 500 msec
        if(one_time){
          lcd_4line();
          display_changed = true;
          one_time = false;
        }
        break;
      case  CASE1:                        // 250 msec
        if(one_time){
          one_time = false;
        }
        break;                         //
      default: break;
    }
    Switches_Process();                // Check for switch state change
    //Display_Process();
  }
}
//------------------------------------------------------------------------------