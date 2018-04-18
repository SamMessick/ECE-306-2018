//===============================================================
//  File Name: ir_menu.c
//  Description: This file contains the Initialization of the left
//                    and right IR detectors and the self-driving
//                    functions.
//
//  Author: Sam Messick
//  Date: Mar. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "ir_menu.h"

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