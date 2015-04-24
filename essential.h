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

/*
 * Include user defined libraries
 */

#include "Peripherals/clock.h"
#include "Peripherals/adc.h"
#include "Peripherals/uart.h"
#include "Peripherals/timer.h"


/*
 * Preprocessor definitions
 */

#define DEBUG 1


/*
 * Global variables definitions
 */

char str[8];
uint32_t temp;

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
