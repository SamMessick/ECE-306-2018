//===============================================================
//  File Name: menu.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    menu.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "LCD.h"
#include "adc12_B.h"
#include "clocks.h"
#include "serial.h"
#include "timerA4.h"
#include "wheels.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define COUNTER_RESET        (0)
#define ASCII_NUM_SHIFT      (48)
#define HTHOUSAND            (100000)
#define TTHOUSAND            (10000)
#define THOUSAND             (1000)
#define HUNDRED              (100)
#define TEN                  (10)
#define ONE                  (1)

// Device settings stored in struct referencing locations in .info FRAM
#ifndef DEVICE_SETTINGS_AND_PRESETS
#define DEVICE_SETTINGS_AND_PRESETS

typedef struct { 
  char*       user_name;
  char*       wifi_ssid;
  uint8_t*    wifi_privacy_mode;
  char*       wifi_password;
  char*       wifi_ip_hostname;
  uint16_t*   lcd_brightness;
} user_settings_t;

#define PRESET_USER_NAME           (0x1800) 
#define PRESET_WIFI_SSID           (0x1810) 
#define PRESET_WIFI_PRIVACY_MODE   (0x1819) 
#define PRESET_WIFI_PASSWORD       (0x1820) 
#define PRESET_WIFI_IP_HOSTNAME    (0x1830) 
#define PRESET_LCD_BRIGHTNESS      (0x1840)
#define INVALID_PRESET             (0xFF)
#define WPA_PERSONAL               (2)
                           
#endif

#define UCA_BRW_115          (4)
#define UCA_BRW_460          (17)
#define UCA_MCTL_115         (0x5551)
#define UCA_MCTL_460         (0x4A10)
#define LOWER_BAUD           (115200)
#define HIGHER_BAUD          (460800)

void init_Menu(void);
void LCD_print(char first_line[COLUMN_NUM_COLUMNS], char second_line[COLUMN_NUM_COLUMNS], char third_line[COLUMN_NUM_COLUMNS], char fourth_line[COLUMN_NUM_COLUMNS]);   // Prints 4 lines to LCD screen
void hex_to_dec(char* output_line, uint32_t hexadecimal); // Converts hexadecimal to a 4-character decimal string for printing
void update_string(char *string_data, int string);
void print_baud_rate(void);

extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;
extern user_settings_t device_settings;           // persisting device settings stored in .info 
extern int8_t menu_counter;                       // displays which option has been chosen by the buttons
extern uint8_t calibrated;                        // boolean to determine whether black and white calibration have ocurred

extern char* word1;
extern char* word2;
extern char* word3;
extern char* word4;