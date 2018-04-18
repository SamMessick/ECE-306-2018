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

char USB_Char_Rx[SMALL_RING_SIZE]  = "          ";
volatile uint8_t usb_rx_ring_wr;
volatile uint8_t usb_rx_ring_rd;
volatile uint8_t begin_transmission;
volatile uint8_t transmitting;
volatile uint8_t receive_ready;
char baud_rate[COLUMN_NUM_COLUMNS] = "115200    ";
char* string_to_transmit;
uint8_t main_ring_rd;
char Main_Char_Rx[SMALL_RING_SIZE] = "          \r\n";

void Init_Serial(void){
  //Init_Serial_UCA0();
  Init_Serial_UCA3();
}

void Init_Serial_UCA3(void){
  // Confiure UART 3
  UCA3CTLW0  = REGISTER_WORD_SIZE;    // Use word-size register (16-bit)
  UCA3CTLW0 |= UCSSEL__SMCLK;         // Set SMCLK as frequency source
  UCA3CTLW0 |= UCSWRST;               // Set software reset enable
  UCA3BRW    = UCA_BRW_115;                    // 9600 Baud
  UCA3MCTLW  = UCA_MCTL_115;
  UCA3CTL1  &= ~UCSWRST;              // Release from software reset
  UCA3IE    |= UCRXIE;
  UCA3IFG   &= ~(UCRXIFG);
}

void transmit_char(char character){
  while (UCA3STATW & UCBUSY); // Transmit complete interrupt flag
    UCA3TXBUF = character;
}

void wait_for_input(void){
  uint8_t string_index;
  for(string_index = BEGINNING; string_index < SMALL_RING_SIZE; string_index++)
    read_into_buffer();
  main_ring_rd = BEGINNING;
  usb_rx_ring_wr = BEGINNING;
  word1 = " Recieved ";
  word2 = "          ";
  // word 3 is baud rate
  word4 = Main_Char_Rx;
  LCD_print(word1,word2,word3,word4);
  UCA3IE |= UCRXIE;
}
  
void read_into_buffer(void){
  static uint8_t rx_wr_temp;
  
  while(rx_wr_temp != usb_rx_ring_wr)
    rx_wr_temp = usb_rx_ring_wr;
  while(main_ring_rd != rx_wr_temp)
  {
    Main_Char_Rx[main_ring_rd] = USB_Char_Rx[main_ring_rd];
    main_ring_rd++;
  }
}

#pragma vector = USCI_A3_VECTOR
__interrupt void USCI_A3_ISR(void){
  uint8_t temp;
  switch(__even_in_range(UCA3IV, eight))
  {
  case two:                                          // RXIFG
    if(UCA3RXBUF == '\0')
      break;
    if(UCA3RXBUF == '$')
      begin_transmission = true;
    if(begin_transmission)
    {
      temp = usb_rx_ring_wr;
      USB_Char_Rx[temp] = UCA3RXBUF;       // Receive USB_Char_Rx character
      if(++usb_rx_ring_wr >= (SMALL_RING_SIZE) || USB_Char_Rx[temp] == '\n')
      {
        UCA3IE &= ~(UCRXIE);
        wait_for_input();
      }
    }
    break;
  }
}