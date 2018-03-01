//===============================================================
//  File Name: adc12_B.c
//  Description: This file contains the Initialization of the 
//               analog-to-digital converter as well as its 
//               interrupt service routine
//
//  Author: Sam Messick
//  Date Jan. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "adc12_B.h"

volatile uint16_t ADC_Thumb;
volatile uint16_t ADC_Right_Detector;
volatile uint16_t ADC_Left_Detector;

void Init_ADC(void){
  ADC12CTL0  = ADC_RESET_STATE;
  /* Configure ADC sampling; power on
   * -----------------
   * ADC12SHT0_2: 16 ADC12CLK cycles in sampling period
   * ADC12SHT1_2: 16 ADC12CLK cycles in sample-and-hold time 
   *                     (ADC12MEM0 to ADC12MEM7 || ADC12MEM24 to ADC12MEM31)
   * ADC12MSC   : First rising edge of SHI signal triggers sampling timer
   * ADC12ON    : ADC12_B powered ON
   */
  
  ADC12CTL0 |= (ADC12SHT0_2 | 
                ADC12SHT1_2 | 
                ADC12MSC    | 
                ADC12ON);
  
  /////////////////////////////////////////////////////////////////////////////
  
  ADC12CTL1  = ADC_RESET_STATE;
  /* Configure ADC clocking
   * -----------------
   * ADC12PDIV_0  : Predivide ADC12CLK by 1
   * ADC12SHS_0   : ADC12SC as sample-and-hold source 
   * ADC12SHP     : SMPCON signal sourced from sampling timer
   * ADC12ISSH_0  : Sample-input signal is not inverted
   * ADC12DIV_0   : ADC12CLK divided by 1 
   * ADC12SSEL0   : ADC12_B clock source select (MODOSC)
   * ADC12CONSEQ_3: Sequence-of-channels conversion sequence mode 
   */
  
  ADC12CTL1 |= (ADC12PDIV_0 | 
                ADC12SHS_0  | 
                ADC12SHP    | 
                ADC12ISSH_0 | 
                ADC12DIV_0  | 
                ADC12SSEL0  |
                ADC12CONSEQ_3);
  
  /////////////////////////////////////////////////////////////////////////////
  
  ADC12CTL2  = ADC_RESET_STATE;
  /* Configure conversion settings
   * -----------------
   * ADC12RES_2   : 12-bit conversion result resolution (14 clock cycle conv.)
   * ADC12DF_0    : Result data stored as binary unsigned, right justified
   * ADC12PWRMD_0 : Regular power mode (not LPM) where sample rate 
   *                            not restricted
   */
  
  ADC12CTL2 |= (ADC12RES_2  | 
                ADC12DF_0   | 
                ADC12PWRMD_0); 
  
  /////////////////////////////////////////////////////////////////////////////
  
  ADC12CTL3  = ADC_RESET_STATE;
  /* Configure ADC input channels
   * -----------------
   * ADC12ICH3MAP_0 : External pin selected for ADC input channel A26
   * ADC12ICH2MAP_0 : External pin selected for ADC input channel A27
   * ADC12ICH1MAP_0 : External pin selected for ADC input channel A28
   * ADC12ICH0MAP_0 : External pin selected for ADC input channel A29
   * ADC12TCMAP_1   : Internal temperature sensor for ADC input channel A30
   * ADC12BATMAP_1  : 1/2 AVCC channel sel. for ADC input channel A31
   * ADC12CSTARTADD0: ADC12MEM0 set as conversion start address (in sequence)
   */
  
  ADC12CTL3 |= (ADC12ICH3MAP_0 | 
                ADC12ICH2MAP_0 | 
                ADC12ICH1MAP_0 | 
                ADC12ICH0MAP_0 | 
                ADC12TCMAP_1   | 
                ADC12BATMAP_1  |
                ADC12CSTARTADD0); 
  
  /////////////////////////////////////////////////////////////////////////////
  
  ADC12MCTL0 = ADC12MCTL1
             = ADC12MCTL2
             = ADC_RESET_STATE;
  
  /* Configure ADC input channels
   * -----------------
   * ADC12WINC_0 : Comparator window disabled
   * ADC12DIF_0  : Single-ended mode enabled
   * ADC12VRSEL_0: VR+ = AVCC, VR- = AVSS
   * ADC12INCH_x : channel = Ax
   * ADC12EOS    : End of sequence
   */
  
  ADC12MCTL0 |= (ADC12WINC_0  |
                 ADC12DIF_0   |
                 ADC12VRSEL_0 |
                 ADC12INCH_2);
  
  ADC12MCTL1 |= (ADC12WINC_0  |
                 ADC12DIF_0   |
                 ADC12VRSEL_0 |
                 ADC12INCH_4);
  
  ADC12MCTL2 |= (ADC12WINC_0  |
                 ADC12DIF_0   |
                 ADC12VRSEL_0 |
                 ADC12INCH_5);
  
  /////////////////////////////////////////////////////////////////////////////
  STABILIZE_REFERENCE
  
  ADC12IER0  |= (ADC12IE2     | // Enable interrupts for new sample results
                 ADC12IE4     |
                 ADC12IE5);
  ADC12CTL0  |= (ADC12ENC |  // Enable Conversion
                 ADC12SC);
}

#pragma vector = ADC12_B_VECTOR
__interrupt void ADC12_ISR(void){
  ADC12IER0  &= ~(ADC12IE2     | // Enable interrupts for new sample results
                 ADC12IE4     |
                 ADC12IE5);
  ADC_Thumb = ADC12MEM0;
  ADC_Right_Detector = ADC12MEM1;
  ADC_Left_Detector = ADC12MEM2;
}