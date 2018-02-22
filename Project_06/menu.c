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

void update_menu(void){
  switch(menu_counter)
  {
  case OPTION1: // circle
    LCD_print("Circ. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    drive_in_circle();
    break;
    
    
  case OPTION2: // figure 8
    LCD_print("Fig8. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    drive_in_figure8();
    break;
    
    
  case OPTION3: // triangle
    LCD_print("Trng. Mode", "Sam M. Car", "          ", "  ECE306  "); 
    drive_in_triangle();
    break;
    
    
  case PENULT_OPTION: // Back&Forth and Jazz hands
    switch(instruction_label_tmp)
    {
    case INSTRUCTION1:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  2  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION2:
      LCD_print("Driving   ", "Forward   ", "          ", "  1  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION3:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  1  sec  ");  
      drive_back_and_forth();
      break;
    case INSTRUCTION4:
      LCD_print("Driving   ", "Reverse   ", "          ", "  2  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION5:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  1  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION6:
      LCD_print("Driving   ", "Forward   ", "          ", "  1  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION7:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  1  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION8:
      LCD_print("Driving   ", "clockwise ", "          ", "  3  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION9:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  2  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION10:
      LCD_print("Driving   ", "cclockwise", "          ", "  3  sec  "); 
      drive_back_and_forth();
      break;
    case INSTRUCTION11:
      LCD_print("Pausing   ", "Now :)    ", "          ", "  2  sec  "); 
      drive_back_and_forth();
      break;
    }
    break;
    
    
  default:   // Do nothing
    LCD_print("   NCSU   ", "Sam M. Car", "          ", "  ECE306  ");
    //Wheels_OFF();
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
  
  Display_Process();                     // Refresh LCD screen
  Display_Process();                     // Refresh LCD screen
}
