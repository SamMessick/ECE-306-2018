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
// This is the main initialization of the car. Execution of code starts here.
// The operating system is Back Ground Fore Ground... but mainly Fore Ground lol
//
//------------------------------------------------------------------------------
  
  init_Ports();                        
  ACTIVATE_PREVIOUS_PORT_SETTINGS;
  
  init_Clocks();                       
  init_Conditions();                   
  Init_LCD();              // XXXXXXXXXXXXXXXXXX To fix: move to lowercase once source obtained XXXXXXXXXXXXXXXXXXXX                          
  init_Timers();            
  init_ADC();
  init_Serial();
  init_PID();
  
  init_Menu();
  
  // Only begin with remote control
  init_IoT();

  // Loop infinitely through transmitting and receiving messages
  for(;;)
  {
    
    // Processing for IOT commands
    // assume held in Main_Char_Rx[]
    if(connection_lost)
      init_IoT();                            // Soft Reset IoT module and provide new IP address
    if(IOT_STATUS(AUTONOMOUS))
    {
      update_ir_reading();
      pid_udpate_left();                     // Update wheel speeds during autonomous driving
    }

    check_for_input();                       // Read in updates and commands from IoT module
  }
}