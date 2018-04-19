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
#include "wheels.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// Serial settings
#define BEGINNING            (0)
#define COUNTER_RESET        (0)
#define ASCII_NUM_SHIFT      (48)
#define NULL_CHAR            (0x10)
#define SMALL_RING_SIZE      (16)
#define DOUBLE_COMMAND_LENGTH (24)
#define BAUD_WORD_SIZE       (8)
#define REGISTER_WORD_SIZE   (0)
#define RXIFG                (2)
#define TXIFG                (4)

// Serial Initialization
#define UCA_BRW_115          (4)
#define UCA_BRW_460          (17)
#define UCA_MCTL_115         (0x5551)
#define UCA_MCTL_460         (0x4A10)
#define LOWER_BAUD           (115200)
#define HIGHER_BAUD          (460800)

// IP Status Verification
#define IP_LEAD_BYTE         ('1')
#define IOT_STATUS(x)        (iot_status_reg & x)
#define IOT_ENABLE(x)        (iot_status_reg |= x)
#define IOT_DISABLE(x)       (iot_status_reg &= ~x)
#define SOFT_RESET           (0x01)
#define IP_READY             (0x02)
#define CHECK_FOR_COMMAND    (0x04)
#define COMMAND_EXECUTING    (0x08)
#define IOT_RESET_TIME       (250)
#define IOT_INIT_TIME        (10000)
#define SOCKET_INIT_SIZE     (18)

// Command Constants
#define COMMAND_PASS         (8657)                         // Digit 2 through 5 of command; used to verify user
#define THOUSAND             (1000)
#define HUNDRED              (100)
#define TEN                  (10)

// Command Identification
#define COMMAND_START        ('*')    // First character in driving command
#define TEST_START           ('.')    // First character in test command
#define LEFT_FORWARD         ('K')    // Left  wheel spins forward
#define LEFT_REVERSE         ('M')    // Left  wheel spins backward
#define RIGHT_FORWARD        ('Q')    // Right wheel spins forward
#define RIGHT_REVERSE        ('S')    // Right wheel spins backward 
#define BLACK_LINE_MODE      ('L')    // Autonomous driving mode
#ifndef EMOTE_ENUM
#define EMOTE_ENUM                    // Button presses from Xbox controller
typedef enum {
  EMOTE1 = 'A',
  EMOTE2 = 'B',
  EMOTE3 = 'Y',
  EMOTE4 = 'X'
} emote_t;
#endif
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
#ifndef RING_STRING_ENUM   // it rhymes!
#define RING_STRING_ENUM
typedef enum{
  CHAR1 = 0,
  CHAR2,
  CHAR3,
  CHAR4,
  CHAR5,
  CHAR6,
  CHAR7,
  CHAR8,
  CHAR9,
  CHAR10,
  CHAR11,
  CHAR12,
  CHAR13,
  CHAR14,
  CHAR15,
  CHAR16,
  RING_NUM_CHARS
} ring_string_t;
#endif

void Init_Serial(void);
void Init_Serial_UCA0(void);
void Init_Serial_UCA3(void);
void Init_IoT(void);
void transmit_charA0(char character);
void transmit_charA3(char character);
void check_for_input(void);
void read_into_buffer(void);
void parse_command(void);
void parse_second_command(void);
void parse_test(void);
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
extern volatile uint8_t waiting_for_input;
extern uint8_t iot_ip_up;
extern volatile uint8_t iot_status_reg;