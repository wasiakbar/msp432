/*
 * essential.c
 *
 *  Created on: Apr 16, 2015
 *      Author: prachetverma
 */

#include "essential.h"

/*
 * Delay function
 */

void delayMillis(uint16_t T) {
	while (T--)
		__delay_cycles(6000);
}
