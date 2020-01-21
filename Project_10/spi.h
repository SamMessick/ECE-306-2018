//===============================================================
//  File Name: spi.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    the LCD and SD card reader (SPI-based components)
//  Author: Sam Messick
//  Date May. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

//------------------------------------------------------------------------------
// Macro Configurations SPI

//------------------------------------------------------------------------------
// Functions

void Init_SPI_B1(void);
void SPI_B1_write(char byte);
void spi_rs_data(void);
void spi_rs_command(void);
void spi_LCD_idle(void);
void spi_LCD_active(void);
void SPI_test(void);