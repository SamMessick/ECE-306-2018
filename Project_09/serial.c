//===============================================================
//  File Name: serial.c
//  Description: This file contains the Initialization and
//                    interrupts for serial I/O
//
//  Author: Sam Messick
//  Date Mar. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "serial.h"

volatile uint8_t iot_tx_wr;                                   // IOT transmit buffer index
volatile uint8_t iot_status_reg = SOFT_RESET;                 // Register for managing IOT flags
uint8_t main_ring_rd;
int8_t chars_to_read; 
char IOT_Char_Rx[SMALL_RING_SIZE];
char IP_line1[COLUMN_NUM_COLUMNS] = "          ";
char IP_line2[COLUMN_NUM_COLUMNS] = "          ";
char Main_Char_Rx[SMALL_RING_SIZE];
char* sock_init_command = "AT+S.SOCKD=32000\r\n";
char* sock_ping_command = "AT+S.PING=152.1.14.14\r\n";

void Init_Serial(void){
  Init_Serial_UCA0();
  Init_Serial_UCA3();
}

void Init_Serial_UCA0(void){
  // Confiure UART 0
  UCA0CTLW0  = REGISTER_WORD_SIZE;    // Use word-size register (16-bit)
  UCA0CTLW0 |= UCSSEL__SMCLK;         // Set SMCLK as frequency source
  UCA0CTLW0 |= UCSWRST;               // Set software reset enable
  UCA0BRW    = UCA_BRW_115;           // ~115200 Baud
  UCA0MCTLW  = UCA_MCTL_115;
  UCA0CTL1  &= ~UCSWRST;              // Release from software reset
  UCA0IE    |= UCRXIE;
  UCA0IFG   &= ~(UCRXIFG);
}

void Init_Serial_UCA3(void){
  // Confiure UART 3
  UCA3CTLW0  = REGISTER_WORD_SIZE;    // Use word-size register (16-bit)
  UCA3CTLW0 |= UCSSEL__SMCLK;         // Set SMCLK as frequency source
  UCA3CTLW0 |= UCSWRST;               // Set software reset enable
  UCA3BRW    = UCA_BRW_115;           // ~115200 Baud
  UCA3MCTLW  = UCA_MCTL_115;
  UCA3CTL1  &= ~UCSWRST;              // Release from software reset
  UCA3IE    |= UCRXIE;
  UCA3IFG   &= ~(UCRXIFG);
}

void Init_IoT(void){
  
  Wheels_OFF();                        // Stop vehicle from unwanted movement
  P3IE      &= ~IOT_FACTORY;           // Begin reset hold
  P3OUT     &= ~IOT_RESET;
  IOT_ENABLE(SOFT_RESET);
  delay_time =  IOT_RESET_TIME;
  TA0CCTL0  |=  CCIE;
  word1 = " Scanning ";
  word2 = "          ";
  word3 = "          ";
  word4 = "          ";
  LCD_print(word1,word2,word3,word4);
  waiting = true;
  while(waiting);
  P3OUT     |=  IOT_RESET;             // Release reset hold -- wait for IoT connection initialization
  P3IE      |=  IOT_FACTORY;
  connection_lost = false;
}

void transmit_charA3(char character){
  while (UCA3STATW & UCBUSY); // Transmit complete interrupt flag
    UCA3TXBUF = character;
}

void transmit_charA0(char character){
  while (UCA0STATW & UCBUSY); // Transmit complete interrupt flag
    UCA0TXBUF = character;
}

void check_for_input(void){
  static uint8_t string_index;
    if(IOT_STATUS(IP_READY))
    {
      // Print out WiFi module IP address on lines 3 and 4 of LCD
      strncpy(IP_line1, IOT_Char_Rx + CHAR2, CHAR7);
      strncpy(IP_line2, IOT_Char_Rx + CHAR9, CHAR7);
      // Establish Socket connection
      for(string_index = BEGINNING; string_index < SOCKET_INIT_SIZE; string_index++)
        transmit_charA3(sock_init_command[string_index]);
      for(string_index = BEGINNING; string_index < SOCKET_PING_SIZE; string_index++)
        transmit_charA3(sock_ping_command[string_index]);
      word1 = "   ncsu   ";
      word2 = "Port:32000";
      word3 = IP_line1;
      word4 = IP_line2;
      LCD_print(word1,word2,word3,word4);
      iot_tx_wr = BEGINNING;
      IOT_DISABLE(IP_READY);
      IOT_DISABLE(SOFT_RESET);
    }
    if(IOT_STATUS(CHECK_FOR_COMMAND))
      if(Main_Char_Rx[CHAR1] == COMMAND_START)
      {
        parse_command();
        IOT_DISABLE(CHECK_FOR_COMMAND);
      }
      else if(Main_Char_Rx[CHAR1] == TEST_START)
      {
        parse_test();
        IOT_DISABLE(CHECK_FOR_COMMAND);
      }
    read_into_buffer();
    //UCA3IE |= UCRXIE;
}

// Updates main buffer alongside iot buffer
void read_into_buffer(void){
  static uint8_t rx_wr_temp;
  while(rx_wr_temp != iot_tx_wr)
    rx_wr_temp = iot_tx_wr;
  while(main_ring_rd != rx_wr_temp/* || chars_to_read > COUNTER_RESET*/)
  {
    Main_Char_Rx[main_ring_rd] = IOT_Char_Rx[main_ring_rd];
    chars_to_read--;
    if(Main_Char_Rx[main_ring_rd] == '\n' || ++main_ring_rd >= SMALL_RING_SIZE)
    {
      main_ring_rd = BEGINNING;
      IOT_ENABLE(CHECK_FOR_COMMAND);
      break;
    }
  }
}

void parse_command(void){
  static char left_direction;
  static char right_direction;
  static uint8_t left_pwm;
  static uint8_t right_pwm;
  
  uint16_t password_attempt;   // Number between 0000-9999 validating user
  char command_identifier;
  
  password_attempt = (Main_Char_Rx[CHAR2] - ASCII_NUM_SHIFT)*THOUSAND +
                     (Main_Char_Rx[CHAR3] - ASCII_NUM_SHIFT)*HUNDRED  +
                     (Main_Char_Rx[CHAR4] - ASCII_NUM_SHIFT)*TEN      +
                     (Main_Char_Rx[CHAR5] - ASCII_NUM_SHIFT);
  
  if(password_attempt == COMMAND_PASS)
  {
    command_identifier = Main_Char_Rx[CHAR6];
    switch(command_identifier)
    {
    case LEFT_FORWARD:
    case LEFT_REVERSE:                    // A PWM value was specified
      
      // Retrieve PWM values
      left_direction = Main_Char_Rx[CHAR6];
      right_direction = Main_Char_Rx[CHAR7];
      
      left_pwm =     (Main_Char_Rx[CHAR8] - ASCII_NUM_SHIFT)*HUNDRED  +
                     (Main_Char_Rx[CHAR9] - ASCII_NUM_SHIFT)*TEN      +
                     (Main_Char_Rx[CHAR10] - ASCII_NUM_SHIFT);
      right_pwm =    (Main_Char_Rx[CHAR11] - ASCII_NUM_SHIFT)*HUNDRED  +
                     (Main_Char_Rx[CHAR12] - ASCII_NUM_SHIFT)*TEN      +
                     (Main_Char_Rx[CHAR13] - ASCII_NUM_SHIFT);
      
      left_pwm  %= MAX_PWM;     // Bring pwm values within range
      right_pwm %= MAX_PWM; 
      
      // Determine PWM direction
      switch(left_direction)
      {
      case LEFT_FORWARD:
        switch(right_direction)
        {
        case RIGHT_FORWARD:
          Wheels_OFF();
          Left_Motor_ON_FORWARD(left_pwm);
          Right_Motor_ON_FORWARD(right_pwm);
          break;
          
        case RIGHT_REVERSE:
          Wheels_OFF();
          Left_Motor_ON_FORWARD(left_pwm);
          Right_Motor_ON_REVERSE(right_pwm);
        }break;
        
      case LEFT_REVERSE:
        switch(right_direction)
        {
        case RIGHT_FORWARD:
          Wheels_OFF();
          Left_Motor_ON_REVERSE(left_pwm);
          Right_Motor_ON_FORWARD(right_pwm);
          break;
          
        case RIGHT_REVERSE:
          Wheels_OFF();
          Left_Motor_ON_REVERSE(left_pwm);
          Right_Motor_ON_REVERSE(right_pwm);
        }
      } break;
      
    case EMOTE1:                         // Print Samic fast meme to LCD
      word1 = " Gotta go ";
      word2 = "<<<<<<<<<<";
      word3 = "Samic fast";
      word4 = ">>>>>>>>>>";
      LCD_print(word1,word2,word3,word4);
      break;
      
    case EMOTE2:                         // Print Happy Car meme to LCD
      word1 = "I'm afraid";
      word2 = "I can't do";
      word3 = "that Dave.";
      word4 = "  o___o!  ";
      LCD_print(word1,word2,word3,word4);
      break;
      
    case EMOTE3:                         // Print Dank Memes ad to LCD
      word1 = " I am the ";
      word2 = "MSP430  JR";
      word3 = "----------";
      word4 = "Wazzup? :)";
      LCD_print(word1,word2,word3,word4);
      break;
      
    case EMOTE4:                         // Print cautionary meme to LCD
      word1 = "Sometimes,";
      word2 = " I dream  ";
      word3 = "  about   ";
      word4 = " cheese...";
      LCD_print(word1,word2,word3,word4);
      break;
      
    case BLACK_LINE_MODE:
      P5OUT &= ~IOT_RESET;   // Disable IOT device
      P8OUT |= IR_LED;       // Enable infrared LED for sensor readings
      
      /* Goal of code: drive in large circle, disabling white detection for 5 seconds
       *               enable white detection
       *               if white found, enable black detection
       *               if black found, stop, turn, follow black line
       *               after 20 seconds, turn car out of loop
       *               drive forward for 4 seconds and stop (display meme)
       */
    }
  }
}

void parse_test(void){
  uint8_t string_index;
  static char* higher_baud = "460800\r\n";
  static char* lower_baud  = "115200\r\n";
  
  switch(Main_Char_Rx[CHAR2])
  {
  case 'S': // 115200 baud
    UCA3CTLW0 |= UCSWRST;               // Set software reset enable
    UCA3BRW = UCA_BRW_115;
    UCA3MCTLW  = UCA_MCTL_115;
    UCA3CTL1  &= ~UCSWRST;              // Release from software reset
    UCA3IE    |= UCRXIE;
    for(string_index = BEGINNING; string_index < BAUD_WORD_SIZE; string_index++)
      transmit_charA0(lower_baud[string_index]);
    break;
  case 'F': // 460800 baud
    UCA3CTLW0 |= UCSWRST;               // Set software reset enable
    UCA3BRW = UCA_BRW_460;
    UCA3MCTLW = UCA_MCTL_460;
    UCA3CTL1  &= ~UCSWRST;              // Release from software reset
    UCA3IE    |= UCRXIE;
    for(string_index = BEGINNING; string_index < BAUD_WORD_SIZE; string_index++)
      transmit_charA0(higher_baud[string_index]);
  }
}

#pragma vector = USCI_A0_VECTOR
__interrupt void USCI_A0_ISR(void){
  switch(__even_in_range(UCA0IV, eight))
  {
  case RXIFG:
    if(UCA0RXBUF == '\0')
      break;
    // Transmit received character to IOT Module
    while(UCA3STATW & UCBUSY);
    UCA3TXBUF = UCA0RXBUF;
  }
}

#pragma vector = USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  uint8_t temp;
  switch(__even_in_range(UCA3IV, eight))
  {
  case RXIFG:
    //while(UCA0STATW & UCBUSY);
    UCA0TXBUF = UCA3RXBUF;             // Echo character to USB
    
    chars_to_read++;
    
    chars_to_read %= DOUBLE_COMMAND_LENGTH;
    temp = iot_tx_wr;
    IOT_Char_Rx[temp] = UCA3RXBUF;     // Read character into interrupt buffer
    
    if(++iot_tx_wr >= SMALL_RING_SIZE || UCA3RXBUF == '\n')
    {
      // Reset interrupt buffer index if end reached
      iot_tx_wr = BEGINNING;
      
      if(IOT_Char_Rx[CHAR1] == ':' &&
         IOT_Char_Rx[CHAR2] == IP_LEAD_BYTE &&
         IOT_STATUS(SOFT_RESET))
      {
        IOT_ENABLE(IP_READY);               // Notify main that IP address is received
      }
    }
    break;
  }
}