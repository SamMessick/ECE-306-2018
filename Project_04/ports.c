//===============================================================
//  File Name: ports.c
//  Description: This file contains the Initialization of all
//                    port pins
//
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "ports.h"

void Init_Port1(void){  // Initlizes all pins on Port 1
//=========================================================================
// RED_LED              (0x01) // RED LED 0
// GRN_LED              (0x02) // GREEN LED 1
// V_THUMB              (0x04) // ADC for Thumb Wheel
// TEST_PROBE           (0x08) // GP I/O Pin to use to check code operation
// V_DETECT_R           (0x10) // ADC for Right Detector
// V_DETECT_L           (0x20) // ADC for Left Detector
// SD_UCB0SIMO          (0x40) // SPI mode - slave in/master out for SD Card
// SD_UC0SOMI           (0x80) // SPI mode - slave out/master in for SD Card
//=========================================================================
  
  // Configure Port 1
  // P1_0
  P1SEL0 &= ~RED_LED;                   // RED_LED as GP I/O
  P1SEL1 &= ~RED_LED;                   // RED_LED as GP I/O
  P1OUT  &= ~RED_LED;                   // Set Red LED Off
  P1DIR  |= RED_LED;                    // Set Red LED direction to output

  // P1_1
  P1SEL0 &= ~GRN_LED;                   // GRN_LED as GP I/O
  P1SEL1 &= ~GRN_LED;                   // GRN_LED as GP I/O
  P1OUT  &= ~GRN_LED;                    // Set Green LED Off
  P1DIR  |= GRN_LED;                    // Set Green LED direction to output
  
  // P1_2
  P1SEL0 |= V_THUMB;                    // ADC input for Thumbwheel
  P1SEL1 |= V_THUMB;                    // ADC input for Thumbwheel
  P1DIR  |= V_THUMB;
  // P1_3
  P1SEL0 &= ~TEST_PROBE;                // TEST_PROBE as GP I/O
  P1SEL1 &= ~TEST_PROBE;                // TEST_PROBE as GP I/O
  P1OUT  &= ~TEST_PROBE;                // Set TEST_PROBE Off
  P1DIR  |=  TEST_PROBE;                // Set TEST_PROBE direction to output
  // P1_4
  P1SEL0 |= V_DETECT_R;                 // ADC input for Right Detector
  P1SEL1 |= V_DETECT_R;                 // ADC input for Right Detector
  // P1_5
  P1SEL0 |= V_DETECT_L;                 // ADC input for Left Detector
  P1SEL1 |= V_DETECT_L;                 // ADC input for Left Detector
  // P1_6
  P1SEL0 &= ~SD_UCB0SIMO;               // USCI_B1 MOSI pin
  P1SEL1 |= SD_UCB0SIMO;                // USCI_B1 MOSI pin
  // P1_7
  P1SEL0 &= ~SD_UC0SOMI;                // USCI_B1 MISO pin
  P1SEL1 |= SD_UC0SOMI;                 // USCI_B1 MISO pin
}
////////////////////////////////////////////////////////////////////////
void Init_Port2(void) { // Initlizes all pins on Port 2
//=========================================================================
// BCLUART_TXD          (0x01)
// BCLUART_RXD          (0x02)
// SD_SPICLK            (0x04)
// P2_3                 (0x08) // Port 2 Pin 3
// P2_4                 (0x10) // Port 2 Pin 4
// J4_34                (0x20)
// J4_35                (0x40)
// P2_7                 (0x80) // Port 2 Pin 7
//=========================================================================
  // Configure Port 2
  // P2_0
  P4SEL0 &= ~BCLUART_TXD;                // Set to GP I/O
  P4SEL1 &= ~BCLUART_TXD;                // Set to GP I/O
  P4OUT  &= ~BCLUART_TXD;                // Set out value Low [off]
  P4DIR  |= BCLUART_TXD;                 // Set direction to output
  // P2_1
  P4SEL0 &= ~BCLUART_RXD;                // Set to GP I/O
  P4SEL1 &= ~BCLUART_RXD;                // Set to GP I/O
  P4OUT  &= ~BCLUART_RXD;                // Set out value Low [off]
  P4DIR  |= BCLUART_RXD;                 // Set direction to output
  // P2_2
  P4SEL0 &= ~SD_SPICLK;                  // Set to GP I/O
  P4SEL1 &= ~SD_SPICLK;                  // Set to GP I/O
  P4OUT  &= ~SD_SPICLK;                  // Set out value Low [off]
  P4DIR  |= SD_SPICLK;                   // Set direction to output
  // P2_3
  P4SEL0 &= ~P2_3;                       // Set to GP I/O
  P4SEL1 &= ~P2_3;                       // Set to GP I/O
  P4OUT  &= ~P2_3;                       // Set out value Low [off]
  P4DIR  |= P2_3;                        // Set direction to output
  // P2_4
  P4SEL0 &= ~P2_4;                       // Set to GP I/O
  P4SEL1 &= ~P2_4;                       // Set to GP I/O
  P4OUT  &= ~P2_4;                       // Set out value Low [on]
  P4DIR  |= P2_4;                        // Set direction to output
  // P2_5
  P4SEL0 &= ~J4_34;                      // Set to GP I/O
  P4SEL1 &= ~J4_34;                      // Set to GP I/O
  P4OUT  &= ~J4_34;                      // Set out value Low [off]
  P4DIR  |= J4_34;                       // Set direction to output
  // P2_6
  P4SEL0 &= ~J4_35;                      // Set to GP I/O
  P4SEL1 &= ~J4_35;                      // Set to GP I/O
  P4OUT  &= ~J4_35;                      // Set out value Low [off]
  P4DIR  |= J4_35;                       // Set direction to output
  // P2_7
  P4SEL0 &= ~P2_7;                       // Set to GP I/O
  P4SEL1 &= ~P2_7;                       // Set to GP I/O
  P4OUT  &= ~P2_7;                       // Set out value Low [off]
  P4DIR  |= P2_7;                        // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port3(char use_smclk) { // Initlizes all pins on Port 3
//=========================================================================
// IOT_RESET            (0x01) // RESET
// IOT_STA_MINIAP       (0x02) // IOT_STA_MINIAP
// IOT_FACTORY          (0x04) // IOT_FACTORY
// IOT_WAKEUP           (0x08) // IOT_WAKEUP
// L_REVERSE            (0x10) // Left Reverse
// L_FORWARD            (0x20) // Left Forward
// R_REVERSE            (0x40) // Right Reverse
// R_FORWARD            (0x80) // Right Forward
//=========================================================================
  // Configure Port 3
  // P3_0
  P3SEL0 &= ~IOT_RESET;                 // Set to GP I/O
  P3SEL1 &= ~IOT_RESET;                 // Set to Gp I/Ovsa1
  P3OUT  &= ~IOT_RESET;                 // Set out value Low [active]
  P3DIR  |= IOT_RESET;                  // Set direction to output
  // P3_1
  P3SEL0 &= ~IOT_STA_MINIAP;            // Set to GP I/O
  P3SEL1 &= ~IOT_STA_MINIAP;            // Set to GP I/O
  P3OUT  |=  IOT_STA_MINIAP;            // Set out value no Mini AP
  P3DIR  |=  IOT_STA_MINIAP;            // Set direction to output
  // P3_2
  P3SEL0 &= ~IOT_FACTORY;               // Set to GP I/O
  P3SEL1 &= ~IOT_FACTORY;               // Set to GP I/O
  P3OUT  &= ~IOT_FACTORY;               // Set out value Low [off]
  P3DIR  |= IOT_FACTORY;                // Set direction to output
  // P3_3
  P3SEL0 &= ~IOT_WAKEUP;                // Set to GP I/O
  P3SEL1 &= ~IOT_WAKEUP;                // Set to GP I/O
  P3OUT  &= ~IOT_WAKEUP;                // Set out value Low [off]
  P3DIR  |= IOT_WAKEUP;                 // Set direction to output
  // P3_4 
  P3SEL0 |= L_REVERSE;                  // Set to TB0.4
  P3SEL1 &= ~L_REVERSE;                  
  P3DIR  |= L_REVERSE;
  // P3_5
  P3SEL0   |= L_FORWARD;                // Set to TB0.4
  P3SEL1   &= ~L_FORWARD;                  
  P3DIR    |= L_FORWARD;
  // P3_6
  P3SEL0 &= ~R_REVERSE;                 // Set to GP I/O
  P3SEL1 &= ~R_REVERSE;                 // Set to GP I/O
  P3OUT  &= ~R_REVERSE;                 // Set out value Low [off]
  P3DIR  |= R_REVERSE;                  // Set direction to output
  // P3_7
  P3SEL0 &= ~R_FORWARD;                 // Set to GP I/O
  P3SEL1 &= ~R_FORWARD;                 // Set to GP I/O
  P3OUT  &= ~R_FORWARD;                 // Set out value High [on]
  P3DIR  |= R_FORWARD;                  // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port4(void) { // Initlizes all pins on Port 4
//=========================================================================
// SD_CS                (0x01) // SD card clock signal
// J4_31                (0x02) //
// J4_32                (0x04) //
// J4_33                (0x08) //
// UCB1_CS_LCD          (0x10) //
// P4_5                 (0x20) // UNUSED
// P4_6                 (0x40) // UNUSED
// J3_29                (0x80) //
//=========================================================================
  // Configure Port 4
  // P4_0
  P4SEL0 &= ~SD_CS;                      // Set to GP I/O
  P4SEL1 &= ~SD_CS;                      // Set to GP I/O
  P4OUT  &= ~SD_CS;                      // Set out value Low [off]
  P4DIR  |= SD_CS;                       // Set direction to output
  // P4_1
  P4SEL0 &= ~J4_31;                      // Set to GP I/O
  P4SEL1 &= ~J4_31;                      // Set to GP I/O
  P4OUT  &= ~J4_31;                      // Set out value Low [off]
  P4DIR  |= J4_31;                       // Set direction to output
  // P4_2
  P4SEL0 &= ~J4_32;                      // Set to GP I/O
  P4SEL1 &= ~J4_32;                      // Set to GP I/O
  P4OUT  &= ~J4_32;                      // Set out value Low [off]
  P4DIR  |= J4_32;                       // Set direction to output
  // P4_3
  P4SEL0 &= ~J4_33;                      // Set to GP I/O
  P4SEL1 &= ~J4_33;                      // Set to GP I/O
  P4OUT  &= ~J4_33;                      // Set out value Low [off]
  P4DIR  |= J4_33;                       // Set direction to output
  // P4_4
  P4SEL0 &= ~UCB1_CS_LCD;                // Set to GP I/O
  P4SEL1 &= ~UCB1_CS_LCD;                // Set to GP I/O
  P4OUT  |= UCB1_CS_LCD;                 // Set out value High [on]
  P4DIR  |= UCB1_CS_LCD;                 // Set direction to output
  // P4_5
  P4SEL0 &= ~P4_5;                       // Set to GP I/O
  P4SEL1 &= ~P4_5;                       // Set to GP I/O
  P4OUT  &= ~P4_5;                       // Set out value Low [off]
  P4DIR  |= P4_5;                        // Set direction to output
  // P4_6
  P4SEL0 &= ~P4_6;                       // Set to GP I/O
  P4SEL1 &= ~P4_6;                       // Set to GP I/O
  P4OUT  &= ~P4_6;                       // Set out value Low [off]
  P4DIR  |= P4_6;                        // Set direction to output
  // P4_7
  P4SEL0 &= ~J3_29;                      // Set to GP I/O
  P4SEL1 &= ~J3_29;                      // Set to GP I/O
  P4OUT  &= ~J3_29;                      // Set out value Low [off]
  P4DIR  |= J3_29;                       // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port5(void) { // Initializes all pins on Port 5
//=========================================================================
// UCB1SIMO             (0x01) // UCB1SIMO
// UCB1SOMI             (0x02) // UBC1SIMO
// UCB1SCK              (0x04) // SPI mode - clock output - UCB1CLK
// RESET_LCD            (0x08) // LCD Reset
// P5_4                 (0x10) // UNUSED
// BUTTON2              (0x20) // Button 2
// BUTTON1              (0x40) // Button 1
// LCD_BACKLITE         (0x80) // LCD Backlite
//=========================================================================
  // Configure Port 5
  // P5_0
  P5SEL0 |= UCB1SIMO;                   // USCI_B1 SIMO pin
  P5SEL1 &= ~UCB1SIMO;                  // USCI_B1 SIMO pin
  P5OUT  &= ~UCB1SIMO;
  // P5_1
  P5SEL0 |= UCB1SOMI;                   // USCI_B1 SOMI pin
  P5SEL1 &= ~UCB1SOMI;                  // USCI_B1 SOMI pin
  P5OUT  &= ~UCB1SOMI;
  // P5_2
  P5SEL0 |= UCB1SCK;                    // USCI_B1 SCLK pin
  P5SEL1 &= ~UCB1SCK;                   // USCI_B1 SCLK pin
  P5OUT  &= ~UCB1SCK;
  // P5_3
  P5SEL0 &= ~RESET_LCD;                 // Set to GP I/O
  P5SEL1 &= ~RESET_LCD;                 // Set to GP I/O
  P5OUT  |= RESET_LCD;                  // Set out value High [off]
  P5DIR  |= RESET_LCD;                  // Set direction to output
  // P5_4
  P5SEL0 &= ~P5_4 ;                     // Set to GP I/O
  P5SEL1 &= ~P5_4 ;                     // Set to GP I/O
  P5OUT  |= P5_4;
  P5DIR  &= ~P5_4;                      // Set direction to output
  // P5_5
  P5SEL0 &= ~BUTTON2;                   // Set to GP I/O
  P5SEL1 &= ~BUTTON2;                   // Set to GP I/O
  P5OUT  |= BUTTON2;                    // Configure pullup resistor
  P5DIR  &= ~BUTTON2;                   // Set direction to input
  P5REN  |= BUTTON2;                    // Enable pullup resistor
  // P5_6
  P5SEL0 &= ~BUTTON1;                   // Set to GP I/O
  P5SEL1 &= ~BUTTON1;                   // Set to GP I/O
  P5OUT  |= BUTTON1;                    // Configure pullup resistor
  P5DIR  &= ~BUTTON1;                   // Set direction to input
  P5REN  |= BUTTON1;                    // Enable pullup resistor
  // P5_7
  P5SEL0 &= ~LCD_BACKLITE;              // Set to GP I/O
  P5SEL1 &= ~LCD_BACKLITE;              // Set to GP I/O
  P5OUT  |= LCD_BACKLITE;               // Set out value High [on]
  P5DIR  |= LCD_BACKLITE;               // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port6(void) { // Initializes all pins on Port 6
//=========================================================================
// UCA3TXD              (0x01) // 
// UCA3RXD              (0x02) //
// J1_5                 (0x04) //
// MAG_INT              (0x08) //
// P6_4                 (0x10) // UNUSED
// P6_5                 (0x20) // UNUSED
// P6_6                 (0x40) // UNUSED
// P6_7                 (0x80) // UNUSED
//=========================================================================
  // Configure Port 6
  // P6_0
  P4SEL0 |=  UCA3TXD;                   // Set to GP I/O
  P4SEL1 &= ~UCA3TXD;                   // Set to GP I/O
  P4OUT  &= ~UCA3TXD;                   // Set out value Low [off]
  P4DIR  |= UCA3TXD;                    // Set direction to output
  // P6_1
  P4SEL0 |=  UCA3RXD;                   // Set to GP I/O
  P4SEL1 &= ~UCA3RXD;                   // Set to GP I/O
  P4OUT  &= ~UCA3RXD;                   // Set out value Low [off]
  P4DIR  |= UCA3RXD;                    // Set direction to output
  // P6_2
  P4SEL0 &= ~J1_5;                      // Set to GP I/O
  P4SEL1 &= ~J1_5;                      // Set to GP I/O
  P4OUT  &= ~J1_5;                      // Set out value Low [off]
  P4DIR  |= J1_5;                       // Set direction to output
  // P6_3
  P4SEL0 &= ~MAG_INT;                   // Set to GP I/O
  P4SEL1 &= ~MAG_INT;                   // Set to GP I/O
  P4OUT  &= ~MAG_INT;                   // Set out value Low [off]
  P4DIR  |= MAG_INT;                    // Set direction to output
  // P6_4
  P4SEL0 &= ~P6_4;                      // Set to GP I/O
  P4SEL1 &= ~P6_4;                      // Set to GP I/O
  P4OUT  &= ~P6_4;                      // Set out value Low [off]
  P4DIR  |= P6_4;                       // Set direction to output
  // P6_5
  P4SEL0 &= ~P6_5;                      // Set to GP I/O
  P4SEL1 &= ~P6_5;                      // Set to GP I/O
  P4OUT  &= ~P6_5;                      // Set out value Low [off]
  P4DIR  |= P6_5;                       // Set direction to output
  // P6_6
  P4SEL0 &= ~P6_6;                      // Set to GP I/O
  P4SEL1 &= ~P6_6;                      // Set to GP I/O
  P4OUT  &= ~P6_6;                      // Set out value Low [off]
  P4DIR  |= P6_6;                       // Set direction to output
  // P6_7
  P4SEL0 &= ~P6_7;                      // Set to GP I/O
  P4SEL1 &= ~P6_7;                      // Set to GP I/O
  P4OUT  &= ~P6_7;                      // Set out value Low [off]
  P4DIR  |= P6_7;                       // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port7(void) { // Initializes all pins on Port 7
//=========================================================================
// I2CSDA               (0x01) //
// I2CSCL               (0x02) //
// SD_DETECT            (0x04) //
// J4_36                (0x08) // 
// P7_4                 (0x10) // UNUSED
// P7_5                 (0x20) // UNUSED
// P7_6                 (0x40) // UNUSED
// P7_7                 (0x80) // UNUSED
//=========================================================================
  // Configure Port 7
  // P7_0
  P4SEL0 &= ~I2CSDA;                    // Set to GP I/O
  P4SEL1 &= ~I2CSDA;                    // Set to GP I/O
  P4OUT  &= ~I2CSDA;                    // Set out value Low [off]
  P4DIR  |= I2CSDA;                     // Set direction to output
  // P7_1
  P4SEL0 &= ~I2CSCL;                    // Set to GP I/O
  P4SEL1 &= ~I2CSCL;                    // Set to GP I/O
  P4OUT  &= ~I2CSCL;                    // Set out value Low [off]
  P4DIR  |= I2CSCL;                     // Set direction to output
  // P7_2
  P4SEL0 &= ~SD_DETECT;                 // Set to GP I/O
  P4SEL1 &= ~SD_DETECT;                 // Set to GP I/O
  P4OUT  &= ~SD_DETECT;                 // Set out value Low [off]
  P4DIR  |= SD_DETECT;                  // Set direction to output
  // P7_3
  P4SEL0 &= ~J4_36;                     // Set to GP I/O
  P4SEL1 &= ~J4_36;                     // Set to GP I/O
  P4OUT  &= ~J4_36;                     // Set out value Low [off]
  P4DIR  |= J4_36;                      // Set direction to output
  // P7_4
  P4SEL0 &= ~P7_4;                      // Set to GP I/O
  P4SEL1 &= ~P7_4;                      // Set to GP I/O
  P4OUT  &= ~P7_4;                      // Set out value Low [off]
  P4DIR  |= P7_4;                       // Set direction to output
  // P7_5
  P4SEL0 &= ~P7_5;                      // Set to GP I/O
  P4SEL1 &= ~P7_5;                      // Set to GP I/O
  P4OUT  &= ~P7_5;                      // Set out value Low [off]
  P4DIR  |= P7_5;                       // Set direction to output
  // P7_6
  P4SEL0 &= ~P7_6;                      // Set to GP I/O
  P4SEL1 &= ~P7_6;                      // Set to GP I/O
  P4OUT  &= ~P7_6;                      // Set out value Low [off]
  P4DIR  |= P7_6;                       // Set direction to output
  // P7_7
  P4SEL0 &= ~P7_7;                      // Set to GP I/O
  P4SEL1 &= ~P7_7;                      // Set to GP I/O
  P4OUT  &= ~P7_7;                      // Set out value Low [off]
  P4DIR  |= P7_7;                       // Set direction to output
}
////////////////////////////////////////////////////////////////////////
void Init_Port8(void) { // Initializes all pins on Port 8
//=========================================================================
// IR_LED               (0x01) // Infrared LED
// OPT_INT              (0x02) // Optical INT
// TMP_INT              (0x04) // Temporary INT
// INT2                 (0x08) // INT2
//=========================================================================
  // Configure Port 8
  // P8_0
  P4SEL0 &= ~IR_LED;                     // Set to GP I/O
  P4SEL1 &= ~IR_LED;                     // Set to GP I/O
  P4OUT  &= ~IR_LED;                     // Set out value Low [off]
  P4DIR  |= IR_LED;                      // Set direction to output
  // P8_1
  P4SEL0 &= ~OPT_INT;                    // Set to GP I/O
  P4SEL1 &= ~OPT_INT;                    // Set to GP I/O
  P4OUT  &= ~OPT_INT;                    // Set out value Low [off]
  P4DIR  |= OPT_INT;                     // Set direction to output
  // P8_2
  P4SEL0 &= ~TMP_INT;                    // Set to GP I/O
  P4SEL1 &= ~TMP_INT;                    // Set to GP I/O
  P4OUT  &= ~TMP_INT;                    // Set out value Low [off]
  P4DIR  |= TMP_INT;                     // Set direction to output
  // P8_3
  P4SEL0 &= ~INT2;                       // Set to GP I/O
  P4SEL1 &= ~INT2;                       // Set to GP I/O
  P4OUT  &= ~INT2;                       // Set out value Low [off]
  P4DIR  |= INT2;                        // Set direction to output
}
/////////////////////////////////////////////////////////////////////////
void Init_PortJ(void) { // Initializes all pins on Port J
//=========================================================================
// PJ_0                 (0x01) // UNUSED
// PJ_1                 (0x02) // UNUSED
// PJ_2                 (0x04) // UNUSED
// PJ_3                 (0x08) // UNUSED
// LFXIN                (0x10) // LFX Input
// LFXOUT               (0x20) // LFX Output
// HFXIN                (0x40) // HFX Input
// HFXOUT               (0x80) // HFX Output
//=========================================================================
  // Configure Port J
  // PJ_0
  P4SEL0 &= ~PJ_0;                      // Set to GP I/O
  P4SEL1 &= ~PJ_0;                      // Set to GP I/O
  P4OUT  &= ~PJ_0;                      // Set out value Low [off]
  P4DIR  |= PJ_0;                       // Set direction to output
  // PJ_1
  P4SEL0 &= ~PJ_1;                      // Set to GP I/O
  P4SEL1 &= ~PJ_1;                      // Set to GP I/O
  P4OUT  &= ~PJ_1;                      // Set out value Low [off]
  P4DIR  |= PJ_1;                       // Set direction to output
  // PJ_2 
  P4SEL0 &= ~PJ_2;                      // Set to GP I/O
  P4SEL1 &= ~PJ_2;                      // Set to GP I/O
  P4OUT  &= ~PJ_2;                      // Set out value Low [off]
  P4DIR  |= PJ_2;                       // Set direction to output
  // PJ_3
  P4SEL0 &= ~PJ_3;                      // Set to GP I/O
  P4SEL1 &= ~PJ_3;                      // Set to GP I/O
  P4OUT  &= ~PJ_3;                      // Set out value Low [off]
  P4DIR  |= PJ_3;                       // Set direction to output
  // PJ_4
  P4SEL0 |= LFXIN;                      // Primary function selected
  P4SEL1 &= ~LFXIN;                     // Primary function selected
  P4OUT  &= ~LFXIN;                     // Set out value Low [off]
  P4DIR  |= LFXIN;                      // Set direction to output
  // PJ_5
  P4SEL0 |=  LFXOUT;                    // Primary function selected
  P4SEL1 &= ~LFXOUT;                    // Primary function selected
  P4OUT  &= ~LFXOUT;                    // Set out value Low [off]
  P4DIR  |= LFXOUT;                     // Set direction to output
  // PJ_6
  P4SEL0 &= ~HFXIN;                     // Set to GP I/O
  P4SEL1 &= ~HFXIN;                     // Set to GP I/O
  P4OUT  &= ~HFXIN;                     // Set out value Low [off]
  P4DIR  |= HFXIN;                      // Set direction to output
  // PJ_7
  P4SEL0 &= ~HFXOUT;                    // Set to GP I/O
  P4SEL1 &= ~HFXOUT;                    // Set to GP I/O
  P4OUT  &= ~HFXOUT;                    // Set out value Low [off]
  P4DIR  |= HFXOUT;                     // Set direction to output
}

void Init_Ports(void){ // Calls all port initialization functions
  Init_Port1();
  Init_Port2();
  Init_Port3(false);
  Init_Port4();
  Init_Port5();
  Init_Port6();
  Init_Port7();
  Init_Port8();
  Init_PortJ();
}