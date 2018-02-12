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
uint8_t delay_flag;

void update_menu(void){
  switch(menu_counter)
  {
  case OPTION1: // circle
    LCD_print("Circ. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    if(delay_flag)
      delay();
    else
      drive_in_circle();
    break;
  case OPTION2: // figure 8
    LCD_print("Fig8. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    if(delay_flag)
      delay();
    else
      drive_in_figure8();
    break;
  case PENULT_OPTION: // triangle
    LCD_print("Trng. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    if(delay_flag)
      delay();
    else
      drive_in_triangle();
    break;
  default:
    LCD_print("   NCSU   ", "Sam M. Car", "          ", "  ECE306  ");
      Wheels_OFF();
    break;
  }
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
}

void delay(){
  static unsigned int Time_Sequence_tmp = Time_Sequence-
  uint16_t counter;
  
  if(counter == delay_time)
  {
      counter = COUNTER_RESET;
      delay_flag = false;
  }
  
  if(Time_Sequence != Time_Sequence_tmp)
  {
      counter++;
      Time_Sequence_tmp = Time_Sequence;
  }
}

void update_text_size(void){
 switch(Time_Sequence){
      case 100:                        // 1000 msec
        if(one_time){
          lcd_BIG_mid();
          display_changed = true;
          one_time = false;
          Time_Sequence = 0;
        }
        break;
      case 50:                         // 500 msec
        if(one_time){
          lcd_4line();
          display_changed = true;
          one_time = false;
        }
        break;   
 }
}
