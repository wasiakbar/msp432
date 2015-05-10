/*
 * gpio.c
 *
 *  Created on: Apr 26, 2015
 *      Author: prachetverma
 */

#include "gpio.h"

/*
 * 	 Initialise GPIOs for various operations
 * 	 P4.0	G1	to VCA
 * 	 P4.1	G2 	to VCA
 * 	 P4.2	OE	for TXS0104 level translator
 * 	 P4.4	TX	switching input to sensor board
 * 	 P5.2	powEN	Main Power Enable (Active low)
 * 	 P5.4	boostEN	Enable for boost convertor (Active high)
 * 	 P5.6	buckEN	Enable for buck convertor (Active high)
 * 	 P5.7	ldoEN	Enable for sensor board LDO (Active low)
 */

void initGPIO(void) {
	P1OUT &= ~BIT0;                           // Clear LED to start
	P4OUT &= ~(BIT0 | BIT1 | BIT2 | BIT4);
	P5OUT &= ~(BIT2 | BIT4 | BIT6);
	P1DIR |= BIT0;                            // Set P1.0/LED to output
	P4DIR |= (BIT0 | BIT1 | BIT2 | BIT4);
	P5DIR |= (BIT2 | BIT4 | BIT6 | BIT7);
	P5OUT |= BIT7;							// Turn off sensor board LDO initially
}

/*
 * 	TX n cycles.
 */

void ultraTX(uint8_t n) {
	while (n--) {
		setTX();
		__delay_cycles(7);
		unsetTX();
		__delay_cycles(6);
	}
}

