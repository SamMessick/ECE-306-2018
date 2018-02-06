//===============================================================
//  File Name: ports.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    ports.c
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

//head first design patterns tell Kyle that Brody told him about book
#include  "msp430.h"
#include <stdbool.h>
#include <stdint.h>

// Port 1 Pins
#define RED_LED              (0x01) // RED LED 0
#define GRN_LED              (0x02) // GREEN LED 1
#define V_THUMB              (0x04) // ADC for Thumb Wheel
#define TEST_PROBE           (0x08) // GP I/O Pin to use to check code operation
#define V_DETECT_R           (0x10) // ADC for Right Detector
#define V_DETECT_L           (0x20) // ADC for Left Detector
#define SD_UCB0SIMO          (0x40) // SPI mode - slave in/master out for SD Card
#define SD_UC0SOMI           (0x80) // SPI mode - slave out/master in for SD Card

// Port 2 Pins
#define BCLUART_TXD          (0x01)
#define BCLUART_RXD          (0x02)
#define SD_SPICLK            (0x04)
#define P2_3                 (0x08) // Port 2 Pin 3
#define P2_4                 (0x10) // Port 2 Pin 4
#define J4_34                (0x20)
#define J4_35                (0x40)
#define P2_7                 (0x80) // Port 2 Pin 7

// Port 3 Pins
#define IOT_RESET            (0x01) // RESET
#define IOT_STA_MINIAP       (0x02) // IOT_STA_MINIAP
#define IOT_FACTORY          (0x04) // IOT_FACTORY
#define IOT_WAKEUP           (0x08) // IOT_WAKEUP
#define SMCLK_OUT            (0x10) // Subsystem Master Clock Output
#define L_REVERSE            (0x10) // Left Forward
#define L_FORWARD            (0x20) // Left Reverse
#define R_REVERSE            (0x40) // Right Reverse
#define R_FORWARD            (0x80) // Right Forward

//***Auxiliary Macros
#define M_FORWARD            (0xA0) // Left Forward, Right Forward
#define M_BACKWARD           (0x50) // Left Reverse, Right Reverse

// Port 4 Pins
#define SD_CS                (0x01) // SD card clock signal
#define J4_31                (0x02) //
#define J4_32                (0x04) //
#define J4_33                (0x08) //
#define UCB1_CS_LCD          (0x10) //
#define P4_5                 (0x20) // UNUSED
#define P4_6                 (0x40) // UNUSED
#define J3_29                (0x80) //

// Port 5 Pins
#define UCB1SIMO             (0x01) // UCB1SIMO
#define UCB1SOMI             (0x02) // UBC1SIMO
#define UCB1SCK              (0x04) // SPI mode - clock output - UCB1CLK
#define RESET_LCD            (0x08) // LCD Reset
#define P5_4                 (0x10) // UNUSED
#define BUTTON2              (0x20) // Button 2
#define BUTTON1              (0x40) // Button 1
#define LCD_BACKLITE         (0x80) // LCD Backlite

// Port 6 Pins
#define UCA3TXD              (0x01) // 
#define UCA3RXD              (0x02) //
#define J1_5                 (0x04) //
#define MAG_INT              (0x08) //
#define P6_4                 (0x10) // UNUSED
#define P6_5                 (0x20) // UNUSED
#define P6_6                 (0x40) // UNUSED
#define P6_7                 (0x80) // UNUSED

// Port 7 Pins
#define I2CSDA               (0x01) //
#define I2CSCL               (0x02) //
#define SD_DETECT            (0x04) //
#define J4_36                (0x08) // 
#define P7_4                 (0x10) // UNUSED
#define P7_5                 (0x20) // UNUSED
#define P7_6                 (0x40) // UNUSED
#define P7_7                 (0x80) // UNUSED

// Port 8 Pins
#define IR_LED               (0x01) // Infrared LED
#define OPT_INT              (0x02) // Optical INT
#define TMP_INT              (0x04) // Temporary INT
#define INT2                 (0x08) // INT2
 
// Port J Pins
#define PJ_0                 (0x01) // UNUSED
#define PJ_1                 (0x02) // UNUSED
#define PJ_2                 (0x04) // UNUSED
#define PJ_3                 (0x08) // UNUSED
#define LFXIN                (0x10) // LFX Input
#define LFXOUT               (0x20) // LFX Output
#define HFXIN                (0x40) // HFX Input
#define HFXOUT               (0x80) // HFX Output

///////////////////////////////////////////////////

// Interrupt Vector Pins
#define P5IFG_BUTTON_1        (0x20) // Right button interrupt flag bit
#define P5IFG_BUTTON_2        (0x40) // Left button interrupt flag bit

// Ports function prototypes
void Init_Ports(void);
void Init_Port1(void);
void Init_Port2(void);
void Init_Port3(char use_smclk);
void Init_Port4(void);
void Init_Port5(void);
void Init_Port6(void);
void Init_Port7(void);
void Init_Port8(void);
void Init_PortJ(void);
void update_menu(void);

#ifndef INIT_ENUMS_H
#define INIT_ENUMS_H

// enum for display row numbers
typedef enum{
  LINE1 = 0,
  LINE2,
  LINE3,
  LINE4,
  LINE_NUM_LINES,
}Display_Line_t;

// enum for display column numbers
typedef enum{
  COLUMN1 = 0,
  COLUMN2,
  COLUMN3,
  COLUMN4,
  COLUMN5,
  COLUMN6,
  COLUMN7,
  COLUMN8,
  COLUMN9,
  COLUMN10,
  COLUMN11,
  COLUMN_NUM_COLUMNS
}Display_Column_t;

// enum for menu options
typedef enum{
  OPTION1 = 1,
  OPTION2,
  OPTION3,
  PENULT_OPTION,
  MENU_NUM_OPTIONS
}Menu_Option_t;

#endif

extern volatile uint8_t debounced; 
extern int8_t menu_counter;            // displays which option has been chosen by the buttons
