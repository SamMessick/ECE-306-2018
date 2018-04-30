//===============================================================
//  File Name: switches.c
//  Description: This file contains the functions needed for controlling
//                    button enabled status.
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "switches.h"

//Enable right switch
void enable_switch_BUTTON1(void){
  P5OUT |= BUTTON1;                     // Select pull up resistor
  P5DIR &= ~BUTTON1;                    // Set direction to input
}

// Enable left switch
void enable_switch_BUTTON2(void){
  P5OUT |= BUTTON2;                     // Select pull up resistor
  P5DIR &= ~BUTTON2;                    // Set direction to input
}
//----------------------------------------------------------------
// Begin with switches enabled
void Init_Switches(void){               
  enable_switch_BUTTON1();
  enable_switch_BUTTON2();
}
//----------------------------------------------------------------
void disable_switch_BUTTON1(void){
  P5DIR |= BUTTON1;                     // Set direction to output
  P5OUT &= ~BUTTON1;                    // Set output to low
}
void disable_switch_BUTTON2(void){
  P5DIR |= BUTTON2;                     // Set direction to output
  P5OUT &= ~BUTTON2;                    // Set output to low
}
void Disable_Switches(void){               
  disable_switch_BUTTON1();
  disable_switch_BUTTON2();
}
//----------------------------------------------------------------