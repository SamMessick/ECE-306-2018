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
uint8_t changed_options;                // Flag protecting against random menu bit setting
uint8_t prev_menu_frame;                // Previous menu boolean (inner or outer menu)
uint8_t prev_menu_option;               // Previous main menu selection
uint8_t current_menu_option;            // Current  main menu selection
uint8_t prev_sub_menu_option;           // Previous sub  menu selection
uint8_t current_sub_menu_option;        // Current  sub  menu selection
uint8_t reset_ADC_Thumb_min;            // Flag to reset text scrolling in Red and White Song

user_settings_t device_settings = 
  {
    .user_name = (char*)PRESET_USER_NAME,
    .wifi_ssid = (char*)PRESET_WIFI_SSID,
    .wifi_privacy_mode = (uint8_t*)PRESET_WIFI_PRIVACY_MODE,
    .wifi_password = (char*)PRESET_WIFI_PASSWORD,
    .wifi_ip_hostname = (char*)PRESET_WIFI_IP_HOSTNAME,
    .lcd_brightness = (uint16_t*)PRESET_LCD_BRIGHTNESS,
  };

void init_Menu(void){
  //strcpy(device_settings.user_name, "Sam       ");
  //strcpy(device_settings.wifi_ssid, "ncsu      ");
  //*(device_settings.wifi_privacy_mode) = 0;
  //strcpy(device_settings.wifi_ip_hostname, "ECE_306_06");
  LCD_print("          ", "          ", "          ", "          ");
  P5OUT |= LCD_BACKLITE;
  delay(SECOND_MS);
  
  lcd_BIG_mid();
  LCD_print("          ", " ^______^ ", "          ", "          ");
  delay(SECOND_MS);
  LCD_print("          ", " ^______- ", "          ", "          ");
  delay(QUART_SECOND_MS);
  LCD_print("          ", " ^______^ ", "          ", "          ");
  delay(SECOND_MS);
  P5OUT &= ~LCD_BACKLITE;
  
  lcd_4line();
  if(device_settings.user_name[CHAR1] == INVALID_PRESET); // have user print name (thumb to choose letter, right/left button to navigate)
  LCD_print("  Hello   ", "  there   ", device_settings.user_name, "----------");
  delay(SECOND_MS);
  if(device_settings.wifi_ssid[CHAR1] == INVALID_PRESET); // have user print ssid (thumb to choose letter, right/left button to navigate)
  LCD_print("You will  ", "connect to", device_settings.wifi_ssid, "----------");
  delay(SECOND_MS);
  if(*(device_settings.wifi_privacy_mode) == (uint8_t)INVALID_PRESET); // have user print mode (thumb to choose mode; right/left button to navigate)
    if(*(device_settings.wifi_privacy_mode) == WPA_PERSONAL); // have user enter password if necessary
    LCD_print("Network ", " password:", device_settings.wifi_ssid, "----------");
    delay(SECOND_MS);
  if(device_settings.wifi_ip_hostname[CHAR1] == INVALID_PRESET); // have user print hostname (thumb to choose letter, right/left button to navigate)
  LCD_print("My name is", "   now:   ", device_settings.wifi_ip_hostname, "----------");
  delay(SECOND_MS);
  if(*(device_settings.lcd_brightness) == (uint16_t)INVALID_PRESET);          // have user adjust LCD brightness (thumb to choose brightness level)
  LCD_print(" That's a ", "  better  ", "lighting! ", "----------");
  delay(SECOND_MS);
  
  lcd_BIG_mid();
  LCD_print("<<<<<<<<<<", " Let's go ", ">>>>>>>>>>", "          ");
  delay(THREE_SECOND_MS);
  lcd_4line();
}

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