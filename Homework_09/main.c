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
  Init_PID();
  Init_ADC();
  
  
//------------------------------------------------------------------------------
// Begining of the Interrupt-Based Operating System
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// TimerA0: controls LCD update, button debouncing and timed delays
// -------          defers to state machine in menus.c following push-button
//                  interrupts.
//               
// TimerB0: controls wheel PWM
//------------------------------------------------------------------------------
  // Display splash screen
  lcd_BIG_mid();
  LCD_print("   Sam    ", "HOMEWORK 9"," Messick  ", "          ");
  
  // Begin infinite for loop menuing bullshit
  for(;;)
  { 
    while(ADC12CTL0 & ADC12BUSY);
    if(time_for_menu_update_lol)
      update_menu();
    enable_adc();
  }
}