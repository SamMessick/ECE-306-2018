//------------------------------------------------------------------------------
//
// Description: This file contains the LCD Routine
//
//
// Author: Sam Messick
// Date May 2018
// Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//------------------------------------------------------------------------------

#include "lcd.h"

//VARIABLES=====================================================================

extern unsigned char display_mode;

extern volatile unsigned char SPI_Char;
extern volatile unsigned char current_character;

unsigned char lcd_control;

char display_time[11];
char display_line[4][11];
char *display[4];
char posi_L1;
char posi_L2;
char posi_L3;
char posi_L4;

unsigned int char_count;
char current_line;
volatile unsigned int update_display_count;
volatile unsigned int display_update_time;
volatile unsigned char update_display;
volatile unsigned char display_changed;

//FUNCTIONS ====================================================================

void spi_chipselect_idle(void){
__delay_cycles(600);
P4OUT |= UCB1_CS_LCD;
}

void spi_chipselect_active(void){
P4OUT &= ~UCB1_CS_LCD;
__delay_cycles(10);
}

void spi_reset_idle(void){
P5OUT |= RESET_LCD;
}

void spi_reset_active(void){
P5OUT &= ~RESET_LCD;
}

void Display_Process(void){
if(update_display){
update_display = 0;
if(display_changed){
display_changed = 0;
Display_Update(0,0,0,0);
}
}
}

void Display_Update(char p_L1,char p_L2,char p_L3,char p_L4){
lcd_out(display_line[0], LCD_HOME_L1, p_L1);
lcd_out(display_line[1], LCD_HOME_L2, p_L2);
lcd_out(display_line[2], LCD_HOME_L3, p_L3);
lcd_out(display_line[3], LCD_HOME_L4, p_L4);
}

void enable_display_update(void){
TA0CCR2 = LCD_INTERVAL; // CCR2
TA0CCTL2 |= CCIE; // CCR2 enable interrupt
}

void WriteIns(char instruction){
//-----------------------------------------------------
// Func: WriteIns(instruction)
// Desc: sends instruction to display
//-----------------------------------------------------
spi_chipselect_active();
// CheckBusy();
SPI_B1_write(START_WR_INSTRUCTION); // Send 5 synchronisation bits, RS = 0, R/W = 0
SPI_B1_write(instruction & 0x0F); // Send lower data bits
SPI_B1_write((instruction>>4) & 0x0F); // Send higher data bits
spi_chipselect_idle();
}

void WriteData(char data){
//-----------------------------------------------------
//Func: WriteData(data)
//Desc: sends data to display
//-----------------------------------------------------
spi_chipselect_active();
// CheckBusy();
SPI_B1_write(START_WR_DATA); // Send 5 synchronisation bits, RS = 1, R/W = 0
SPI_B1_write(data & 0x0F); // Send lower data bits
SPI_B1_write((data>>4) & 0x0F); // Send higher data bits
spi_chipselect_idle();
}

void DisplayOnOff(char data){
//-----------------------------------------------------
// Func: DisplayOnOff(control)
// Desc: use definitions of header file to set display
//-----------------------------------------------------
WriteIns(0x08+data);
display_changed = 0;
}

void Init_SPI_B1(void){
//------------------------------------------------------------------------------
//SPI
//------------------------------------------------------------------------------
// Reset peripheral
UCB1CTLW0 = UCSWRST;

UCB1CTLW0 |= UCSSEL__SMCLK; // SMCLK is clock source
UCB1BRW = SPI_CLK_PRESCALER;
UCB1CTLW0 |= UCCKPL; // Clock polarity high
UCB1CTLW0 |= UCMST; // master mode
UCB1CTLW0 |= UCSYNC;
UCB1CTLW0 |= UCMODE_0;
UCB1CTLW0 &= ~UCMSB; // master mode, LSB transmitted first

// Enable peripheral
UCB1CTLW0 &= ~UCSWRST;

// Wait to ensure the peripheral is up
__delay_cycles(100);

//------------------------------------------------------------------------------
}

void Init_LCD(void){
//------------------------------------------------------------------------------
// P1OUT |= SPI_CS_LCD; // P1 SPI_CS_LCD Port Pin set high
// P1OUT |= RESET_LCD; // P1 RESET_LCD Port Pin set low
//------------------------------------------------------------------------------
Init_SPI_B1(); // Initialize SPI Port
// turn on power
spi_reset_idle();
spi_chipselect_idle();
// delay 1ms
__delay_cycles(8000);
// delay 400 ms
spi_reset_active();
__delay_cycles(300000);
spi_reset_idle();
__delay_cycles(300000);
// init Display
WriteIns(0x3A); //8-Bit data length extension Bit RE=1; REV=0
WriteIns(0x09); //4 line display
WriteIns(0x06); //Bottom view
WriteIns(0x1E); //Bias setting BS1=1
WriteIns(0x39); //8-Bit data length extension Bit RE=0; IS=1
WriteIns(0x1B); //BS0=1 -> Bias=1/6
WriteIns(0x6E); //Divider on and set value
WriteIns(0x55); //Booster on and set contrast (BB1=C5, DB0=C4)
WriteIns(0x76); //Set contrast (DB3-DB0=C3-C0)
WriteIns(0x38); //8-Bit data length extension Bit RE=0; IS=0
ClrDisplay();
DisplayOnOff(DISPLAY_ON);
__delay_cycles(8000);
}

void lcd_out(char *s, char line, char position){
// Write a string to the display, using lcd_putc.
WriteIns(line+position);
while (*s) {
WriteData(*s++);
}
}

void lcd_puts(char *s){
// Write a string to the display, using lcd_putc.
char_count = 1;
if (s == NULL){
return;
}
while (*s) {
WriteData(*s++);
}
}