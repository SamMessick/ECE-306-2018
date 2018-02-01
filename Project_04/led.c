//===============================================================
//  File Name: led.c
//  Description: This file contains the Initialization of all LED
//                    controlling I/O pins
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include  "led.h"

void Init_LEDs(void){
//------------------------------------------------------------------------------
// LED Configurations
//------------------------------------------------------------------------------
// Turns on both LEDs
  P1OUT |= RED_LED;
  P1OUT |= GRN_LED;
//------------------------------------------------------------------------------
}

void updateBacklight(void){
//------------------------------------------------------------------------------
// Checks if button 2 or 1 has been pressed and updates backlight accordingly
//------------------------------------------------------------------------------
  
  if((P3IN | BUTTON1)
     && ~(P1OUT | RED_LED)) // Button 1 pushed, Red LED off
    P1OUT |= RED_LED;       // Turn on Red LED
  else                     // ELSE
    P1OUT &= ~RED_LED;      // Turn off Red LED
      
  if(P3IN | BUTTON2        // Button 2 pushed, Green LED off
     && ~(P1OUT | GRN_LED)) 
    P1OUT |= GRN_LED;       // Turn on Green LED     
  else                     // ELSE
    P1OUT &= ~GRN_LED;      // Turn off Red LED
}