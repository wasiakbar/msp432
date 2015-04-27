/*
 * gpio.c
 *
 *  Created on: Apr 26, 2015
 *      Author: prachetverma
 */

#include "gpio.h"

/*
 * 	 Initialise GPIOs for various operations
 * 	 P4.0	G1	Open Drain
 * 	 P4.1	G2 	Open Drain
 * 	 P4.2	OE	Push Pull
 * 	 P4.4	TX	Push Pull
 */

void initGPIO(void) {
	P1OUT &= ~BIT0;                           // Clear LED to start
	P4OUT &= ~(BIT0 | BIT1 | BIT2 | BIT4);
	P5OUT &= ~BIT5;
	P1DIR |= BIT0;                            // Set P1.0/LED to output
	P4DIR |= (BIT0 | BIT1 | BIT2 | BIT4);
	P5DIR |= BIT5;
}

