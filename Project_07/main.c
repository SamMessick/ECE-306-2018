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
  Init_Conditions();                   // Initialize Variables and Initial Conditions
  Init_LCD();                          // Initialize LCD
  Init_LEDs();
  Init_Timers();                       // Initialize Timers
  Init_ADC();
  uint8_t one_time = true;

// Update LCD display, check state machine, enter low power mode 1
  enable_display_update();
  defer_to_shape_menu();
//------------------------------------------------------------------------------
// Begining of the Interrupt-Based Operating System
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
// TimerA1: controls LCD update, button debouncing and timed delays
// -------          defers to state machine in shapes_menu.c following push-button
//                  interrupts.]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]
//               
// TimerB0: controls wheel PWM
//------------------------------------------------------------------------------
//  int counter;
  for(;;)
  {
    while(ADC12CTL0 & ADC12BUSY);
    if(ADC_Left_Detector < IR_ACTIVE_READING && ADC_Right_Detector < IR_ACTIVE_READING)
      P5OUT &= ~LCD_BACKLITE;
    else
      P5OUT |= LCD_BACKLITE;
    if(ADC_Thumb > THUMB_ACTIVE_READING && one_time)
    {
      TA0CCTL0 &= ~CCIE;
      one_time = false;
      defer_to_shape_menu();
    }
    if(ADC_Thumb < THUMB_ACTIVE_READING)
    {
      TA0CCTL0 |= CCIE;
      TA0CCTL2 &= ~CCIE;
      Wheels_OFF();
      one_time = true;
    }
    ADC12IER0  |= (ADC12IE2     | // Enable interrupts for new sample results
                 ADC12IE4     |
                 ADC12IE5);
  }
}