//===============================================================
//  File Name: serial.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    serial.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include "ports.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define BEGINNING         (0)
#define NULL_CHAR       (0x10)
#define SMALL_RING_SIZE  (16)
#define REGISTER_WORD_SIZE (0)

#define UCA_BRW_115          (4)
#define UCA_BRW_460          (17)
#define UCA_MCTL_115         (0x5551)
#define UCA_MCTL_460         (0x4A10)
#define LOWER_BAUD           (115200)
#define HIGHER_BAUD          (460800)

#ifndef COUNTING_ENUM
#define COUNTING_ENUM
typedef enum{ //WTF, Sam???????????
  zero = 0,
  one,
  two,
  three,
  four,
  five,
  six,
  seven,
  eight,
  nine,
  ten,
  COUNTING_ENUM_SIZE
} counting_enum_t;
#endif

void Init_Serial(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA3(void);
void transmit_string(char* character);
void wait_for_input(void);
void read_into_buffer(void);
void transmit_char(char character);

void LCD_print(char first_line[COLUMN_NUM_COLUMNS], char second_line[COLUMN_NUM_COLUMNS], char third_line[COLUMN_NUM_COLUMNS], char fourth_line[COLUMN_NUM_COLUMNS]);   // Prints 4 lines to LCD screen

extern char USB_Char_Rx[SMALL_RING_SIZE];
extern volatile uint8_t usb_rx_ring_wr;
extern volatile uint8_t usb_rx_ring_rd;
extern char baud_rate[COLUMN_NUM_COLUMNS];

extern uint8_t main_ring_rd;
extern char Main_Char_Rx[SMALL_RING_SIZE];

extern char* word1;
extern char* word2;
extern char* word3;
extern char* word4;

extern char* string_to_transmit;
extern volatile uint8_t transmitting;
extern uint8_t waiting_for_last_char;
extern volatile uint8_t receive_ready;