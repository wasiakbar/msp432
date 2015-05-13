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
 * 	 Single channel continuous conversion mode enabled
 */

void initADC(void) {
	P6SEL1 |= BIT1;                           // Configure P6.1 for ADC
	P6SEL0 |= BIT1;

	/* Initialize ADC14 */
	NVIC_ISER0 = 1 << ((INT_ADC14 - 16) & 31);         // Enable ADC interrupt in NVIC module

	ADC14CTL0 = ADC14SHS_3 | ADC14SSEL__SMCLK | ADC14CONSEQ_2 | ADC14ON;          // Sampling input from timer TA1CCR1, Sampling time equal to
																				  // ON time of timer out, SMCLK, Continuous sampling on single channel,
																				  // ADC14 on
	ADC14CTL1 = ADC14RES_3 | ADC14PWRMD_0;                   					  // 14-bit conversion results, regular power mode (since 14bit)

	ADC14MCTL0 |= ADC14INCH_14;                // A14 ADC input select; Vref=AVCC
	ADC14IER0 |= ADC14IE0;                    // Enable ADC conv complete interrupt

	if (DEBUG)
		sendStr("\n\n\r ADC Initialisation complete.");

}// End initADC function

void recordData(void) {
	ctr=0;
	ADC14CTL0 |= ADC14ENC;						//Enable ADC for conversion
	TA1CCR0 = 120;
	while(ctr<BANK);
}

/*
 * Interrupt Service Routine to read from ADC
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */

void ADC14ISRHandler(void) {
	if (ctr<BANK)
		data[ctr++]=ADC14MEM0;
	else {
		temp = ADC14MEM0;
		TA1CCR0=0;
		ADC14CTL0 &=~ ADC14ENC;
	}
	//toggleLED();
}
