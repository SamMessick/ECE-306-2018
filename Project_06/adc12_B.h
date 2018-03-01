//===============================================================
//  File Name: clocks.h
//  Description: This file contains the prototypes of all functions,
//                    definitions of macros and header files used by 
//                    adc12_B.c
//  Author: Sam Messick
//  Date Feb. 2018
//  Compiler Build with IAR Embedded Workbench Version: V4.10A/W32 (7.11.2)
//===============================================================

#include "msp430.h"
#include <stdbool.h>
#include <stdint.h>
#define ADC_RESET_STATE     (0)
#define STABILIZE_REFERENCE {__delay_cycles(10000);}

void Init_ADC(void);

extern volatile uint16_t ADC_Thumb;
extern volatile uint16_t ADC_Right_Detector;
extern volatile uint16_t ADC_Left_Detector;