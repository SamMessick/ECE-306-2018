//===============================================================
//  File Name: menu.c
//  Description: This file contains the Initialization of all
//                    display values, and LCD menu functions
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "menu.h"

int8_t menu_counter;
char* word1 = "          ";
char* word2 = "          ";
char* word3 = "          ";
char* word4 = "          ";

user_settings_t device_settings = 
  {
    .user_name = (char*)PRESET_USER_NAME,
    .wifi_ssid = (char*)PRESET_WIFI_SSID,
    .wifi_privacy_mode = (uint8_t*)PRESET_WIFI_PRIVACY_MODE,
    .wifi_password = (char*)PRESET_WIFI_PASSWORD,
    .wifi_ip_hostname = (char*)PRESET_WIFI_IP_HOSTNAME,
    .lcd_brightness = (uint16_t*)PRESET_LCD_BRIGHTNESS,
  };

void LCD_print(char first_line[COLUMN_NUM_COLUMNS], char second_line[COLUMN_NUM_COLUMNS], char third_line[COLUMN_NUM_COLUMNS], char fourth_line[COLUMN_NUM_COLUMNS]){
  strcpy(display_line[LINE1], first_line);
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], second_line);
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], third_line);
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4], fourth_line);
  update_string(display_line[LINE4], LINE4);
  display_changed = true; 
  update_display  = true;
  Display_Process();                     // Refresh LCD screen
}

void hex_to_dec(char* output_line, uint32_t hexadecimal){
  uint8_t HThousand = COUNTER_RESET;      // Counts hundred thousands
  uint8_t TThousand = COUNTER_RESET;      // Counts ten thousands
  uint8_t Thousand  = COUNTER_RESET;       // Counts thousands
  uint8_t Hundred   = COUNTER_RESET;        // Counts hundreds
  uint8_t Ten       = COUNTER_RESET;            // Counts tens
  uint8_t One       = COUNTER_RESET;            // Counts ones
  
  while(hexadecimal >= HTHOUSAND)
  {
    HThousand++;
    hexadecimal -= HTHOUSAND;
  }
  while(hexadecimal >= TTHOUSAND)
  {
    TThousand++;
    hexadecimal -= TTHOUSAND;
  }
  while(hexadecimal >= THOUSAND)
  {
    Thousand++;
    hexadecimal -= THOUSAND;
  }
  while(hexadecimal >= HUNDRED)
  {
    Hundred++;
    hexadecimal -= HUNDRED;
  }
  while(hexadecimal >= TEN)
  {
    Ten++;
    hexadecimal -= TEN;
  }
  while(hexadecimal >= ONE)
  {
    One++;
    hexadecimal--;
  }
  output_line[COLUMN1] = HThousand + ASCII_NUM_SHIFT;
  output_line[COLUMN2] = TThousand + ASCII_NUM_SHIFT;
  output_line[COLUMN3] = Thousand + ASCII_NUM_SHIFT;
  output_line[COLUMN4] = Hundred  + ASCII_NUM_SHIFT;
  output_line[COLUMN5] = Ten      + ASCII_NUM_SHIFT;
  output_line[COLUMN6] = One      + ASCII_NUM_SHIFT;
}

void print_baud_rate(){
  uint32_t baud_rate;
  
  switch(menu_counter)
  {           
  case OPTION1:
    baud_rate = LOWER_BAUD;
    hex_to_dec(word3, baud_rate);
    // Adjust baud rate
    UCA3CTLW0 |= UCSWRST;               // Set software reset enable
    UCA3BRW = UCA_BRW_115;
    UCA3MCTLW  = UCA_MCTL_115;
    UCA3CTL1  &= ~UCSWRST;              // Release from software reset
    break;
  case PENULT_OPTION:
    baud_rate = HIGHER_BAUD;
    hex_to_dec(word3, baud_rate);
    // Adjust baud rate
    UCA3CTLW0 |= UCSWRST;               // Set software reset enable
    UCA3BRW = UCA_BRW_460;
    UCA3MCTLW = UCA_MCTL_460;
    UCA3CTL1  &= ~UCSWRST;              // Release from software reset
    break;
  }
  //word2 = "          ";
  LCD_print(word1,word2, word3,word4);
}