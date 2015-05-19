/*
 * uart.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#ifndef PERIPHERALS_UART_C_
#define PERIPHERALS_UART_C_

#include "../essential.h"
#include "timer.h"
#include "adc.h"

//Initialise
void initUART(void);

//Usage
void sendChar(char);
void sendStr(char *);

//Support
char* intToStr(uint32_t);
uint32_t strToInt(char *);

//Interactive
void executeCmd(void);
void pushData(void);

#endif /* PERIPHERALS_UART_C_ */
