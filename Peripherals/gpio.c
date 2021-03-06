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

	/*
	 * Initialise buttons
	 */

	P1OUT |= (BIT1 | BIT4);                          // Pull-up resistor on P1.1
	P1REN |= (BIT1 | BIT4);                          // Select pull-up mode for P1.1
	P1DIR &= ~(BIT1 | BIT4);                         // Set all but P1.1 to input direction

}

/*
 * 	TX n cycles.
 */

void ultraTX(uint8_t n) {
	txr=1;
	TA0CCR0 = 37;
	Ncyc=n*2;
	while(Ncyc);
}

/*
 *  Wait n cycles
 */

void waitTX(uint8_t n) {
	txr=0;
	TA0CCR0 = 37;
	Ncyc=n*2;
	while(Ncyc);
}
