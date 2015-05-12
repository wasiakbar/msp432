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
	/*
	 * Trigger for ADC
	 * SMCLK is used to trigger. It runs at f=24 MHz
	 * Desired trigger frequency, fTrg = 200kHz
	 * CCR0 = 24M / 200k = 120
	 * CCR1 = CCR0/2 = 60
	 */

	TA1CCTL1 = OUTMOD_3;                      // CCR1 reset/set
	TA1CCR0 = 120;                         // PWM Period
	TA1CCR1 = 60;                            // CCR1 PWM duty cycle
	TA1CTL = TASSEL__SMCLK | MC__UP | TACLR;  // SMCLK, up mode, clear TAR

	/*
	 * Trigger for switching
	 * SMCLK is used. f=24 MHz
	 * It is divided by 8. f'=24/8 = 3 MHz
	 * Desired frequency, fTrg = 40 kHz
	 * CCR0 = 3M / 40k /2 = 37.5
	 */
	TA0CCTL0 = CCIE;                       	// CCR0 interrupt enabled
	//TA0CCR0 = 37;							// 37 is 40k, to be set only when needed
	TA0CTL = TASSEL__SMCLK | ID__8 | MC__UP;   		// SMCLK, Div by 8, up mode
	NVIC_ISER0 = 1 << ((INT_TA0_0 - 16) & 31);


	if (DEBUG)
		sendStr("\n\n\r Timer Initialisation complete.");
}

/*
 * Interrupt Service Routine triggered by TimerA0_0 for switching
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */
void TimerA0_0IsrHandler(void) {
	TA0CCTL0 &= ~CCIFG;
	if (Ncyc--)
		toggleTX();
	else {
		unsetTX();
		TA0CCR0 = 0;
	}
}
