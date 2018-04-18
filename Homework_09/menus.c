//===============================================================
//  File Name: menus.c
//  Description: This file contains the Initialization of all
//                    display values, and LCD menu functions
//
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "menus.h"

int8_t menu_counter;
char* word1;
char* word2;
char* word3;
char* word4;
char* shapes_strings[NUM_SUB_OPTIONS] = {"Circle    ", "Square    ", "Triangle  ", "Octagon   ", "Pentagon  ", "Hexagon   ", "Cube      ", "Oval      ", "Sphere    ", "Cylinder  "};
uint8_t changed_options;                // Flag protecting against random menu bit setting
uint8_t prev_menu_frame;                // Previous menu boolean (inner or outer menu)
uint8_t prev_menu_option;               // Previous main menu selection
uint8_t current_menu_option;            // Current  main menu selection
uint8_t prev_sub_menu_option;           // Previous sub  menu selection
uint8_t current_sub_menu_option;        // Current  sub  menu selection
uint8_t reset_ADC_Thumb_min;            // Flag to reset text scrolling in Red and White Song

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

void hex_to_dec(char* output_line, uint16_t hexadecimal){
 
  uint8_t Thousand = COUNTER_RESET;       // Counts thousands
  uint8_t Hundred = COUNTER_RESET;        // Counts hundreds
  uint8_t Ten = COUNTER_RESET;            // Counts tens
  uint8_t One = COUNTER_RESET;            // Counts ones
  
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
  if(Thousand > MAX_DIGIT)
    Thousand = MAX_DIGIT;
  output_line[COLUMN1] = Thousand + ASCII_NUM_SHIFT;
  output_line[COLUMN2] = Hundred  + ASCII_NUM_SHIFT;
  output_line[COLUMN3] = Ten      + ASCII_NUM_SHIFT;
  output_line[COLUMN4] = One      + ASCII_NUM_SHIFT;
}

void update_menu(void){
  time_for_menu_update_lol = false;
  
  if(using_inside_menu)
  { 
    switch(current_menu_option)
    {
    case MAIN_OPTION1:                                         // Resistors menu
      update_resistors_menu();
      break;
    case MAIN_OPTION2:                                         // Shapes menu
      update_shapes_menu();
      break;
    case MAIN_OPTION3:                                         // Obnoxious song that nobody sings; edgelord status = LV 100
      update_red_and_white_menu();
    }
  }
  else                                                         // Using outer menu
  {
    lcd_BIG_mid();
    
    if(ADC_Thumb < MAX_MAIN_OPTION1)
    {
      current_menu_option = MAIN_OPTION1;
        word1 = "   Menu   ";
        word2 = "RESISTORS ";
        word3 = " Select-> ";
      LCD_print(word1, word2, word3, "          ");
      return;
    }
    if(ADC_Thumb > MIN_MAIN_OPTION2 && ADC_Thumb < MAX_MAIN_OPTION2)
    {
      current_menu_option = MAIN_OPTION2;
        word1 = "   Menu   ";
        word2 = "  SHAPES  ";
        word3 = " Select-> ";
      LCD_print(word1, word2, word3, "          ");
      return;
    }
    if(ADC_Thumb > MIN_MAIN_OPTION3)
    {
      current_menu_option = MAIN_OPTION3;
        word1 = "   Menu   ";
        word2 = "RED&WHITE ";
        word3 = " Select-> ";
      LCD_print(word1, word2, word3, "          ");
    }
  }
}


void update_resistors_menu(void){
  lcd_4line();
      word1 = "COLOR     ";
      word3 = "VALUE     ";
      
      if(ADC_Thumb < MAX_OPTION1)                              // Black
      {
        word2 = "     Black";
        word4 = BLACK_R;
        current_sub_menu_option = SUB_OPTION1;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION2  && ADC_Thumb < MAX_OPTION2)  // Brown
      {
        word2 = "     Brown";
        word4 = BROWN_R;
        current_sub_menu_option = SUB_OPTION2;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION3  && ADC_Thumb < MAX_OPTION3)  // Red
      {
        word2 = "       Red";
        word4 = RED_R;
        current_sub_menu_option = SUB_OPTION3;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION4 && ADC_Thumb < MAX_OPTION4)   // Orange
      {
        word2 = "    Orange";
        word4 = ORANGE_R;
        current_sub_menu_option = SUB_OPTION4;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION5 && ADC_Thumb < MAX_OPTION5)   // Yellow
      {
        word2 = "    Yellow";
        word4 = YELLOW_R;
        current_sub_menu_option = SUB_OPTION5;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION6 && ADC_Thumb < MAX_OPTION6)   // Green
      {
        word2 = "     Green";
        word4 = GREEN_R;
        current_sub_menu_option = SUB_OPTION6;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION7 && ADC_Thumb < MAX_OPTION7)   // Blue
      {
        word2 = "      Blue";
        word4 = BLUE_R;
        current_sub_menu_option = SUB_OPTION7;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION8 && ADC_Thumb < MAX_OPTION8)   // Violet
      {
        word2 = "    Violet";
        word4 = VIOLET_R;
        current_sub_menu_option = SUB_OPTION8;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION9 && ADC_Thumb < MAX_OPTION9)   // Gray
      {
        word2 = "      Gray";
        word4 = GRAY_R;
        current_sub_menu_option = SUB_OPTION9;
          LCD_print(word1,word2,word3,word4);
        return;
      }
      if(ADC_Thumb > MIN_OPTION10)                             // White
      {
        word2 = "     White";
        word4 = WHITE_R;
        current_sub_menu_option = SUB_OPTION10;
          LCD_print(word1,word2,word3,word4);
        return;
      }
}

void update_shapes_menu(void){
  lcd_BIG_mid();
      
      if(ADC_Thumb < MAX_OPTION1)                              // Circle
      {
        current_sub_menu_option = SUB_OPTION10;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          LCD_print(word1,word2,"          ","          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION2  && ADC_Thumb < MAX_OPTION2)   // Square
      {
        current_sub_menu_option = SUB_OPTION9;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION3  && ADC_Thumb < MAX_OPTION3)   // Triangle
      {
        current_sub_menu_option = SUB_OPTION8;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION4 && ADC_Thumb < MAX_OPTION4)    // Octagon
      {
        current_sub_menu_option = SUB_OPTION7;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION5 && ADC_Thumb < MAX_OPTION5)   // Pentagon
      {
        current_sub_menu_option = SUB_OPTION6;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION6 && ADC_Thumb < MAX_OPTION6)   // Hexagon
      {
        current_sub_menu_option = SUB_OPTION5;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION7 && ADC_Thumb < MAX_OPTION7)   // Cube
      {
        current_sub_menu_option = SUB_OPTION4;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION8 && ADC_Thumb < MAX_OPTION8)   // Oval
      {
        current_sub_menu_option = SUB_OPTION3;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION9 && ADC_Thumb < MAX_OPTION9)   // Sphere
      {
        current_sub_menu_option = SUB_OPTION2;
          word1 = shapes_strings[current_sub_menu_option MINUS_ONE];
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print(word1,word2,word3,"          ");
        return;
      }
      if(ADC_Thumb > MIN_OPTION10)                             // Cylinder
      {
        current_sub_menu_option = SUB_OPTION1;
          word2 = shapes_strings[current_sub_menu_option];
          word3 = shapes_strings[current_sub_menu_option PLUS_ONE];
          LCD_print("          ",word2,word3,"          ");
        return;
      }
}

void update_red_and_white_menu(void){
  static uint8_t  red_and_white_top;              // Boolean for switching value of red and white
  static uint8_t  call_counter;                   // Counter describing number of times update_red_and_white_menu has been called
  static uint16_t ADC_Thumb_min = ADC_MAX;        // Minimum reading off of ADC_Thumb (prevents characters from advancing backward)
  static uint8_t  song_lyrics_offset;
  static char*    song_lyrics = "We're the Red and White from State And we know we are the best. A hand behind our back, We can take on all the rest. Come over the hill Carolina. Devils and Deacs stand in line. The Red and White from N.C. State. Go State!           \0";
  static char current_lyrics[LCD_WORD_SIZE];             // To be displayed on middle line of LCD
  
  // Update red and white border printout
  call_counter++;
  if(!(call_counter % FUNCTION_CALL_PERIOD))
  {
    red_and_white_top ^= BIT1;                   // Swap positions of "Red  White" / "White and Red"
    call_counter = COUNTER_RESET;
  }
  if(red_and_white_top)
  {
    word1 = "Red&White!";
    word3 = "White&Red!";
  }
  else
  {
    word1 = "White&Red!";
    word3 = "Red&White!";
  }
  
  //Update lyrics printout
  song_lyrics_offset = (uint8_t)((((double)(ADC_MAX - ADC_Thumb))/ ADC_MAX) * (SONG_LYRICS_LENGTH - LCD_WORD_SIZE));
  if(song_lyrics_offset > SONG_LYRICS_LENGTH - LCD_WORD_SIZE)
  {
    song_lyrics_offset = (SONG_LYRICS_LENGTH - LCD_WORD_SIZE);
  }
  
  // Update ADC_Thumb min and scrolling text
  if(reset_ADC_Thumb_min /* Changed back from outer menu */)
  {
    ADC_Thumb_min = ADC_Thumb;
    reset_ADC_Thumb_min = false;
  }
  
  if(ADC_Thumb > ADC_Thumb_min)                        // Back-scrolling not permitted
  {
    LCD_print(word1, current_lyrics, word3, word4);
  }
  else                                                 // Regular forward scroll
  {
    ADC_Thumb_min = ADC_Thumb;
    strncpy(current_lyrics, song_lyrics + song_lyrics_offset, LCD_WORD_SIZE);
    LCD_print(word1, current_lyrics, word3, word4);
  }
}

void print_detector_values(void){
  if(calibrated && (P8OUT & IR_LED))
  {
    pid_udpate_left();
  }
  else 
  {
    Wheels_OFF();
  
    hex_to_dec(word2, ADC_Thumb);
    hex_to_dec(word3, ADC_Left_Detector);
    
    if(P8OUT & IR_LED)
      word1 = "IR_EM ON  ";
    else
      word1 = "IR_EM OFF ";
    
    LCD_print(word1, word2, word3, word4);
  }
}
