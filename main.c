//*****************************************************************************
//
// MSP432 main.c for Ultrasonic Sensor
// Created on: Apr 16, 2015
//      Author: prachetverma
//
//****************************************************************************

#include "essential.h"

int main(void)
{
  WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

  CSKEY = 0x695A;                        // Unlock CS module for register access
  CSCTL0 = 0;                            // Reset tuning parameters
  CSCTL0 = DCORSEL_3;                   // Set DCO to 12MHz (nominal, center of 8-16MHz range)
                                         // Select ACLK = REFO, SMCLK = MCLK = DCO
  CSCTL1 = SELA_2 | SELS_3 | SELM_3;
  CSKEY = 0;                             // Lock CS module from unintended accesses


  __sleep();
  __no_operation();                       // For debugger
}

