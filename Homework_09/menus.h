//===============================================================
//  File Name: menus.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    menus.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "LCD.h"
#include "adc12_B.h"
#include "wheels.h"
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#define COUNTER_RESET        (0)
#define ASCII_NUM_SHIFT      (48)
#define THOUSAND             (1000)
#define HUNDRED              (100)
#define TEN                  (10)
#define ONE                  (1)
#define MAX_DIGIT            (9)

void LCD_print(char first_line[COLUMN_NUM_COLUMNS], char second_line[COLUMN_NUM_COLUMNS], char third_line[COLUMN_NUM_COLUMNS], char fourth_line[COLUMN_NUM_COLUMNS]);   // Prints 4 lines to LCD screen
void hex_to_dec(char* output_line, uint16_t hexadecimal); // Converts hexadecimal to a 4-character decimal string for printing
void update_string(char *string_data, int string);
void update_menu(void);

extern char display_line[LINE_NUM_LINES][COLUMN_NUM_COLUMNS];
extern char *display[LINE_NUM_LINES];
extern volatile unsigned char update_display;
extern volatile unsigned int update_display_count;
extern volatile unsigned char display_changed;
extern int8_t menu_counter;            // displays which option has been chosen by the buttons
extern uint8_t calibrated;             // boolean to determine whether black and white calibration have ocurred
extern char* word4;                    // provided for ADC writing "Cal. Black" or "Cal. White" to screen

/*needless bullshit*/
extern volatile uint8_t time_for_menu_update_lol;

//------------Menu 1--------------------//
#define BLACK_R  "         0";
#define BROWN_R  "         1";
#define RED_R    "         2";
#define ORANGE_R "         3";
#define YELLOW_R "         4";
#define GREEN_R  "         5";
#define BLUE_R   "         6";
#define VIOLET_R "         7";
#define GRAY_R   "         8";
#define WHITE_R  "         9";
#ifndef MAIN_OPTION_ENUM
#define MAIN_OPTION_ENUM
typedef enum{
  MAIN_OPTION1 = 0,
  MAIN_OPTION2,
  MAIN_OPTION3,
  NUM_MAIN_OPTIONS
} main_option_t;
#endif
#ifndef SUB_OPTION_ENUM
#define SUB_OPTION_ENUM
typedef enum{
  SUB_OPTION1 = 0,
  SUB_OPTION2,
  SUB_OPTION3,
  SUB_OPTION4,
  SUB_OPTION5,
  SUB_OPTION6,
  SUB_OPTION7,
  SUB_OPTION8,
  SUB_OPTION9,
  SUB_OPTION10,
  NUM_SUB_OPTIONS
} sub_option_t;
#endif
#ifndef MIN_MAX_SUB_OPTION_ENUM
#define MIN_MAX_SUB_OPTION_ENUM
typedef enum{
  MAX_OPTION1 = 495,
  MIN_OPTION2 = 505,
  MAX_OPTION2 = 895,
  MIN_OPTION3 = 905,
  MAX_OPTION3 = 1295,
  MIN_OPTION4 = 1305,
  MAX_OPTION4 = 1695,
  MIN_OPTION5 = 1705,
  MAX_OPTION5 = 2095,
  MIN_OPTION6 = 2105,
  MAX_OPTION6 = 2495,
  MIN_OPTION7 = 2505,
  MAX_OPTION7 = 2895,
  MIN_OPTION8 = 2905,
  MAX_OPTION8 = 3295,
  MIN_OPTION9 = 3305,
  MAX_OPTION9 = 3695,
  MIN_OPTION10 = 3705
} min_max_sub_option_t;
#endif
#ifndef MIN_MAX_MAIN_OPTION_ENUM
#define MIN_MAX_MAIN_OPTION_ENUM
typedef enum{
  MAX_MAIN_OPTION1 = 1375,
  MIN_MAIN_OPTION2 = 1425,
  MAX_MAIN_OPTION2 = 2975,
  MIN_MAIN_OPTION3 = 3025
} min_max_main_option_t;
#endif
#define PLUS_ONE               +1
#define MINUS_ONE              -1
#define IS_NEGATIVE            <0
#define BEGINNING              (0)
#define SONG_LYRICS_LENGTH     (234)
#define SONG_LYRICS1_LENGTH    (116)
#define ADC_MAX                (4095)
#define FUNCTION_CALL_PERIOD   (5)

void update_resistors_menu(void);
void update_shapes_menu(void);
void update_red_and_white_menu(void);

extern uint8_t reset_ADC_Thumb_min;            // Flag to reset text scrolling in Red and White Song