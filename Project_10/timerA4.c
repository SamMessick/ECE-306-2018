//===============================================================
//  File Name: timerA4.c
//  Description: This file contains the initialization of timer
//                    A4 and the LCD Backlight's PWM
//
//  Author: Sam Messick
//  Date Apr. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "timerA4.h"

uint16_t current_lcd_brightness;
uint8_t backlite_status_reg;

void init_Timer_A4(void){

  TA4CTL  = TASSEL__ACLK;               // Select SMCLK for source
  TA4CTL |= (TACLR | MC_1 | ID_1);      // AClock source on up mode at 32 KHz
  TA4CTL |= TAIDEX__1; 
  TA4CTL &= ~(TAIFG);                    // Clear Timer A1 interrupt flag and interrupt enable
  
  TA4CCTL1 |= OUTMOD_7;                 //  LCD backlite in Reset/Set mode
  TA4CCR1   = NO_LIGHTING;              //  Begin with backlite off
}

void dim_lcd(uint32_t preferred_brightness) {
  current_lcd_brightness = preferred_brightness;
  TA4CCTL1 |= CCIE;
}

//   Timer A4 interrupt routines        //
//         **OVERFLOW**                 //
// ---Backlite brightness adjustment--- //
#pragma vector = TIMER4_A1_VECTOR
__interrupt void Timer4_A1_ISR(void){
  
  if(TA4CCR1 > current_lcd_brightness &&  
     TA4CCR1 != current_lcd_brightness)
      --TA4CCR1;                  // Dim Backlite to preferred brightness
    
  else if(TA4CCR1 < current_lcd_brightness &&
          TA4CCR1 != current_lcd_brightness)
      ++TA4CCR1;                 // Brighten Backlite to preferred brightness
  
  else
  {
    DISABLE_BACKLITE_INTERRUPT;
    BACKLITE_DISABLE(BACKLITE_ADJUSTING);
  }  
}