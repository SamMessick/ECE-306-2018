//===============================================================
//  File Name: shapes_menu.c
//  Description: This file contains the Initialization of all
//                    display values, and LCD menu functions
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "shapes_menu.h"

int8_t menu_counter;

uint8_t TThousand;
uint8_t THundred;
uint8_t TTen;
uint8_t TOne;
uint8_t RThousand;
uint8_t RHundred;
uint8_t RTen;
uint8_t ROne;
uint8_t LThousand;
uint8_t LHundred;
uint8_t LTen;
uint8_t LOne;
char* word1;
char word2[COLUMN_NUM_COLUMNS] = "    : RTDT";
char word3[COLUMN_NUM_COLUMNS] = "    : LFDT";
char* word4;

void defer_to_shape_menu(void){
  
  if(ADC_Thumb < THUMB_ACTIVE_READING)
    {
      return;
    }
  
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
    default:
      LCD_print("   Demo   ", " Complete ", "          ", "          ");
      drive_back_and_forth();
    }
    break;
    
    
  default:   // Do nothing
    LCD_print("   NCSU   ", "Sam M. Car", "          ", "  ECE306  "); 
    Wheels_OFF(); break;
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
  display_changed = true; 
  update_display  = true;
  Display_Process();                     // Refresh LCD screen
}

void print_detector_values(void)
{
  if(P8OUT | IR_LED)
  {
  if(ADC_Left_Detector >= IR_ACTIVE_READING)
    if(ADC_Right_Detector >= IR_ACTIVE_READING)
    {
      word4 = "  Black   ";
      Left_Motor_ON_FORWARD(LEFT_FORWARD_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_FORWARD_SPEED);
    }
    else
    {
      word4 = "  Left    ";
      Left_Motor_ON_FORWARD(LEFT_R_SEARCH_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_R_SEARCH_SPEED);
    }
  else 
    if(ADC_Right_Detector >= IR_ACTIVE_READING)
    {
      word4 = "  Right   ";
      Left_Motor_ON_FORWARD(LEFT_L_SEARCH_SPEED);
      Right_Motor_ON_FORWARD(RIGHT_L_SEARCH_SPEED);
    }
    else 
    {
      word4 = "  White   ";
      Wheels_OFF();
    }
  }
  else 
    Wheels_OFF();
  while(ADC_Right_Detector >= THOUSAND)
  {
    RThousand++;
    ADC_Right_Detector -= THOUSAND;
  }
  while(ADC_Right_Detector >= HUNDRED)
  {
    RHundred++;
    ADC_Right_Detector -= HUNDRED;
  }
  while(ADC_Right_Detector >= TEN)
  {
    RTen++;
    ADC_Right_Detector -= TEN;
  }
  while(ADC_Right_Detector >= ONE)
  {
    ROne++;
    ADC_Right_Detector--;
  }
  
  while(ADC_Left_Detector >= THOUSAND)
  {
    LThousand++;
    ADC_Left_Detector -= THOUSAND;
  }
  while(ADC_Left_Detector >= HUNDRED)
  {
    LHundred++;
    ADC_Left_Detector -= HUNDRED;
  }
  while(ADC_Left_Detector >= TEN)
  {
    LTen++;
    ADC_Left_Detector -= TEN;
  }
  while(ADC_Left_Detector >= ONE)
  {
    LOne++;
    ADC_Left_Detector--;
  }

  word2[COLUMN1] = RThousand + ASCII_NUM_SHIFT;
  word2[COLUMN2] = RHundred  + ASCII_NUM_SHIFT;
  word2[COLUMN3] = RTen      + ASCII_NUM_SHIFT;
  word2[COLUMN4] = ROne      + ASCII_NUM_SHIFT;
  word3[COLUMN1] = LThousand + ASCII_NUM_SHIFT;
  word3[COLUMN2] = LHundred  + ASCII_NUM_SHIFT;
  word3[COLUMN3] = LTen      + ASCII_NUM_SHIFT;
  word3[COLUMN4] = LOne      + ASCII_NUM_SHIFT;
  TThousand = COUNTER_RESET;
  THundred = COUNTER_RESET;
  TTen = COUNTER_RESET;
  TOne = COUNTER_RESET;
  RThousand = COUNTER_RESET;
  RHundred = COUNTER_RESET;
  RTen = COUNTER_RESET;
  ROne = COUNTER_RESET;
  LThousand = COUNTER_RESET;
  LHundred = COUNTER_RESET;
  LTen = COUNTER_RESET;
  LOne = COUNTER_RESET;
    
  if(P8OUT & IR_LED)
    word1 = "IR_EM ON  ";
  else
    word1 = "IR_EM OFF ";
    
  LCD_print(word1, word2, word3, word4);
}
