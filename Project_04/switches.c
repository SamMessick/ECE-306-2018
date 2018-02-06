//===============================================================
//  File Name: switches.c
//  Description: This file contains the functions needed for button
//                    operation of the LCD, wheels and LEDs
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
//----------------------------------------------------------------

void Switch1_Process(void){
  /*
   * Replaced with Port 5 interrupt routine
   *
  switch(flag_RED_LED_ON)
  {
  case false:
    switch(!(P5IN & BUTTON1))
    {
    case true:
      P1OUT |= RED_LED;
      menu_counter += PENULT_OPTION;
      menu_counter %= MENU_NUM_OPTIONS;
      flag_RED_LED_ON = 1;
    default:
      break;
    }
    break;
    
  case true:
    switch(!(P5IN & BUTTON1))
    {
    case false:
      P1OUT &= ~RED_LED;
      flag_RED_LED_ON = 0;
    default:
      break;
    }
    break;
  }
  */
}
void Switch2_Process(void){
  /*
   * Replaced with Port 5 interrupt routine
   *
  switch(flag_GRN_LED_ON)               // Check if green LED is on
  {
  case false:
    switch(!(P5IN & BUTTON2))           // Green LED off; check if button 2 is pushed
    {
    case true:                          // button 2 is pushed; turn on green LED
      P1OUT |= GRN_LED;                 
      menu_counter++;
      menu_counter %= MENU_NUM_OPTIONS;
      flag_GRN_LED_ON = 1;
      
    default:
      break;
    }
    break;
    
  case true:                            // Green LED on; check if button 2 is pushed
    switch(!(P5IN & BUTTON2))
    {
    case false:                         // button 2 is not pushed; turn off green LED
      P1OUT &= ~GRN_LED;
      flag_GRN_LED_ON = 0;
      break;
    default:
      break;
    }
    break;
  }
  */
}
void Switches_Process(void){
  Switch1_Process();
  Switch2_Process();
}