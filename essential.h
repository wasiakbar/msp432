/*
 * essential.h
 *
 *  Created on: Apr 16, 2015
 *      Author: prachetverma
 */

#ifndef ESSENTIAL_H_
#define ESSENTIAL_H_

/*
 * Include predefined libraries.
 */

#include "msp.h"
#include <string.h>
#include <stdlib.h>

/*
 * Include user defined libraries
 */

#include "Peripherals/clock.h"
#include "Peripherals/gpio.h"
#include "Peripherals/adc.h"
#include "Peripherals/uart.h"
#include "Peripherals/timer.h"
#include "Peripherals/i2c.h"

#include "compute.h"


/*
 * Preprocessor definitions
 */

#define DEBUG 1
#define BANK 10000
#define VEC 550

/*
 * Global variables definitions
 */

uint32_t *data;
uint16_t ctr;

char str[12];
uint32_t temp;
uint16_t Ncyc;
uint8_t txr;

char cmd[20];
uint8_t cmdPtr;

/*
 * Preprocessor directives to make bitwise
 * port operations easy.
 * 1. Set pin
 * 2. Unset pin
 * 3. Toggle pin
 */

#define set(x, y) P##x##OUT |= BIT##y
#define unset(x, y) P##x##OUT &= ~BIT##y
#define toggle(x, y) P##x##OUT ^= BIT##y

/*
 * Additional functions
 */
void delayMillis(uint16_t T);


#endif /* ESSENTIAL_H_ */
