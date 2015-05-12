/*
 * clock.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#include "clock.h"

/*
 * 	 Initialise Clock for 24 MHz operation
 *	 Settings:
 *	 DCO = 24 MHz
 *	 REFO = 32 KHz
 *
 *	 MCLK <- DCO
 *	 SMCLK <- DCO
 *	 ACLK <- REFO
 */

void initClock(void) {
	CSKEY = 0x695A;                        // Unlock CS module for register access
	CSCTL0 = 0;                            // Reset tuning parameters
	CSCTL0 = DCORSEL_4;      			 // Set DCO to 24MHz centre frequency
											// (nominal, center of 16-32MHz range)
											// Set DCOTUNE to 0x3FF to tune to 32 MHz
	// Select ACLK = REFO, SMCLK = MCLK = DCO
	CSCTL1 = SELA_2 | SELS_3 | SELM_3;
	CSKEY = 0;
}
