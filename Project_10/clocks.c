//------------------------------------------------------------------------------
//  File Name: clocks.c
//  Description: This file contains the Clock Initialization
//
//  Sam Messick
//  Jan 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

//------------------------------------------------------------------------------
#include  "clocks.h"

void init_Clocks(void){
//------------------------------------------------------------------------------
// Clock Configurtaions
// This is the clock initialization for the program.
//
// Initial clock configuration, runs immediately after boot.
// Disables 1ms watchdog timer,
//      configure MCLK to 8MHz
//      configure SMCLK to 8MHz.
// Since the X1 oscillator is not currently connected,
// X1CLK is an unknown speed (probably ~10kHz).
//------------------------------------------------------------------------------
  WDTCTL = WDTPW | WDTHOLD;  // Disable watchdog
//  PJSEL0 |= XINR;
//  PJSEL0 |= XOUTR;

// Clocks:
// Clock System Control 0 Register
  CSCTL0 = CSKEY;            // Unlock register

// Clock System Control 1 Register
  CSCTL1 = CLEAR_REGISTER;   // Clear register
  CSCTL1 = DCOFSEL_6;        // Set DCO setting for 8MHz
//  CSCTL1 &= ~DCORSEL;        // DCO range select. For high-speed devices,
                             // this bit can be written by the user.
                             // For low-speed devices, it is always reset.

// Clock System Control 2 Register
  CSCTL2 = CLEAR_REGISTER;   // Clear register
  CSCTL2 |= SELA__LFXTCLK;
  CSCTL2 |= SELS__DCOCLK;
  CSCTL2 |= SELM__DCOCLK;

// Clock System Control 3 Register
  CSCTL3 = CLEAR_REGISTER;   // Clear register
  CSCTL3 |= DIVA__1;         // set ACLK clock divider /1
  CSCTL3 |= DIVS__1;        // set SMCLK clock divider /1
  CSCTL3 |= DIVM__1;         // set MCLK clock divider /1

// Clock System Control 4 Register
//  CSCTL4 = CLEAR_REGISTER;   // Clear register
  CSCTL4 &= ~LFXTOFF;        // Enable LFXT1

  /*do                                                      ***This loop was preventing my system from running
  {                                                         So I commented it out
    CSCTL5 &= ~LFXTOFFG;     // Clear XT1 fault flag
    SFRIFG1 &= ~OFIFG;
  } while (SFRIFG1 & OFIFG); // Test oscillator fault flag
*/
  CSCTL0_H = false;            // Lock CS registers



//------------------------------------------------------------------------------
}

void delay(uint32_t delay_time_ms){
  TA0CCTL0 |= CCIE;                    // Ensure Timer interrupts are enabled
  aux_time_ms = COUNTER_RESET;
  while(aux_time_ms < delay_time_ms);
}