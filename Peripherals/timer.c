/*
 * timer.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#include "timer.h"

/*
 * 	Initialise timer settings
 */


void initTimer(void) {
	TA1CCTL0 = CCIE;                       	// CCR0 interrupt enabled
	TA1CCR1 = 100;							// 64 is 270k sampling
	TA1CTL = TASSEL__SMCLK | MC__UP;   		// SMCLK, up mode
	NVIC_ISER0 = 1 << ((INT_TA1_N - 16) & 31);

	if (DEBUG)
		sendStr("\n\n\r Timer Initialisation complete.");
}

/*
 * Interrupt Service Routine triggered by TimerA0_0
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */
void TimerA0_0IsrHandler(void) {
	TA0CCTL0 &= ~CCIFG;
	//toggleLED();
	//startConversion();

}

void TimerA1_0IsrHandler(void) {
	TA1CCTL1 &= ~CCIFG;
	//toggleLED();
	startConversion();

}


void TimerA1_NIsrHandler(void) {
	TA1CCTL1 &= ~CCIFG;
	//toggleLED();
	startConversion();

}
