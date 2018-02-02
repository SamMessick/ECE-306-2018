//===============================================================
//  File Name: display.c
//  Description: This file contains the Initialization of all
//                    display values, and LCD menu functions
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "display.h"

int8_t menu_counter;

void update_menu(void){
  switch(menu_counter)
  {
  case OPTION1: // circle
    LCD_print("Circ. Mode", "Sam M. Car", "          ", "  ECE306 "); 
    drive_in_circle();
    break;
  case OPTION2: // figure 8
    LCD_print("Fig8. Mode", "Sam M. Car", "          ", "  ECE306 "); 
    drive_in_figure8();
    break;
  case OPTION3: // square
    LCD_print("Squr. Mode", "Sam M. Car", "          ", "  ECE306 ");
    drive_in_square();
    break;
  case PENULT_OPTION: // triangle
    LCD_print("Trng. Mode", "Sam M. Car", "          ", "  ECE306 "); 
    drive_in_triangle();
    break;
  default:
    LCD_print("   NCSU   ", "Sam M. Car", "          ", "  ECE306 "); break;
    break;
  }
}

void LCD_print(char first_line[10], char second_line[10], char third_line[10], char fourth_line[10]){
  strcpy(display_line[LINE1], first_line);
  update_string(display_line[LINE1], LINE1);
  strcpy(display_line[LINE2], second_line);
  update_string(display_line[LINE2], LINE2);
  strcpy(display_line[LINE3], third_line);
  update_string(display_line[LINE3], LINE3);
  strcpy(display_line[LINE4], fourth_line);
  update_string(display_line[LINE4], LINE4);
}