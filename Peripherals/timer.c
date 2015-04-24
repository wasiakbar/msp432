/*
 * timer.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#include "adc.h"

/*
 * 	Initialise timer settings
 */

void initTimer(void) {
	TA0CCTL0 = CCIE;                       	// CCR0 interrupt enabled
	TA0CCR0 = 64;							// 64 is 240k sampling
	TA0CTL = TASSEL__SMCLK | MC__UP;   		// SMCLK, up mode
	NVIC_ISER0 = 1 << ((INT_TA0_0 - 16) & 31);

	if (DEBUG)
		sendStr("\n\n\r Timer Initialisation complete.");
}

/*
 * Interrupt Service Routine triggered by TimerA0_0
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */
void TimerA0_0IsrHandler(void) {
	TA0CCTL0 &= ~CCIFG;
	startConversion();

}
