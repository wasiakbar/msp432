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


/*
 * Preprocessor definitions
 */

#define DEBUG 0
#define BANK 200

/*
 * Global variables definitions
 */

uint32_t *data;
uint16_t ctr;



char str[8];
uint32_t temp;
uint16_t Ncyc;



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

#endif /* ESSENTIAL_H_ */
