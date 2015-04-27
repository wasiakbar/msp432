/*
 * adc.c
 *
 *  Created on: Apr 22, 2015
 *      Author: prachetverma
 */

#include "adc.h"

/*
 * 	 Initialise ADC on port 6
 * 	 Use pin P6.1
 * 	 Single conversion mode enabled
 */

void initADC(void) {
	P6SEL1 |= BIT1;                           // Configure P6.1 for ADC
	P6SEL0 |= BIT1;

	/* Initialize ADC14 */
	NVIC_ISER0 = 1 << ((INT_ADC14 - 16) & 31);         // Enable ADC interrupt in NVIC module

	ADC14CTL0 = ADC14SSEL__SMCLK | ADC14CONSEQ_0 | ADC14SHT1_0 | ADC14SHP | ADC14ON;          // Sampling time, S&H=16, ADC14 on
	ADC14CTL1 = ADC14RES_3 | ADC14PWRMD_0;                   // Use sampling timer, 14-bit conversion results

	ADC14MCTL0 |= ADC14INCH_14;                // A14 ADC input select; Vref=AVCC
	ADC14IER0 |= ADC14IE0;                    // Enable ADC conv complete interrupt

	ADC14CTL0 |= ADC14ENC;						//Enable ADC for conversion

	if (DEBUG)
		sendStr("\n\n\r ADC Initialisation complete.");

}// End initADC function

/*
 * Start a single conversion on ADC14
 */

inline void startConversion(void) {
	ADC14CTL0 |= ADC14SC;        // Start sampling/conversion
}

/*
 * Interrupt Service Routine to read from ADC
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */

void ADC14ISRHandler(void) {
	temp = ADC14MEM0;               // ADC12MEM0 = A1 > 0.5AVcc?
	toggleLED();
}
