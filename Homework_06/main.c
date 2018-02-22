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
  Init_LCD();                          // Initialize LCD
  Init_LEDs();
  Init_Timers();                       // Initialize Timers

// Update LCD display, check state machine, enter low power mode 1
  enable_display_update();
  update_menu();
//------------------------------------------------------------------------------
// Begining of the Interrupt-Based Operating System
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// TimerA1: controls LCD update, button debouncing and timed delays
// -------          defers to state machine in menu.c following push-button
//                  interrupts.
//               
// TimerB0: controls wheel PWM
//------------------------------------------------------------------------------
  for(;;);
}