/*
 * uart.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#ifndef PERIPHERALS_UART_C_
#define PERIPHERALS_UART_C_

#include "../essential.h"

//Initialise
void initUART(void);

//Usage
void sendChar(char);
void sendStr(char *);

//Support
char* intToStr(uint16_t);

#endif /* PERIPHERALS_UART_C_ */
