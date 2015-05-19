/*
 * compute.c
 *
 *  Created on: May 14, 2015
 *      Author: prachetverma
 */

#include "compute.h"

/*
 *	 Transmit pattern and record data. Pattern is stored in REVERSE order!!
 */

void transaction(void) {
	int8_t i;
	for (i=nPat-1; i>0; i-=2) {
		ultraTX(cycles*pattern[i]);
		waitTX(cycles*pattern[i-1]);

	}
	ultraTX(cycles*pattern[0]);
	recordData();
	sendStr(" Data recorded succesfully.\n");
}
/*
 * Get distance
 */

int getDistance() {
	int j, max;
	for (max=1200, j=1200; j<BANK; j++) {		// 110 to ignore first 1m
		if (data[max]<data[j])
			max=j;
	}
	max+=VEC;

	/*
	 * Calculation:
	 * ADC sampling rate 200ksps
	 * Time between samples 5us
	 *    s	= v * t
	 * 		= 340m/s * N/2 * 5us
	 * 		= 170 * 100 * 5u * N cm
	 * 		= 0.085N cm
	 * 	where N is the reading of interest
	 */

	return ((85*max)/1000);
}

/*
 * Moving average
 */

void movingAvg(uint8_t samples) {
	int i,j;
	for (i=0; i<BANK-samples; ++i) {
		for (j=1; j<samples; ++j)
			data[i]+=data[i+j];
		data[i]/=(samples);
	}
}

/*
 * Correlation
 */

void correlate(void) {
	uint16_t i, l;
	int16_t j, k;
	sendStr(" Correlating...\n");
	VEC=5*cycles*totCyc;

	for (i=0; i<BANK-VEC; ++i) {
		l=0;
		for (j=nPat-1; j>=0; j-=2)
			for (k=0; k<pattern[j]*cycles*5; k++)
				data[i]+=data[i+l++];
	}

	sendStr(" Complete.\n");
}
