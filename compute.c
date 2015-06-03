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
	if (DEBUG)
		sendStr(" Data recorded succesfully.\n");
}
/*
 * Get distance
 */

int getDistance() {
	int j, max;
	for (max=j=ignore; j<BANK; j++) {		// 110 to ignore first 1m
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
	if (DEBUG)
		sendStr(" Correlating...\n");
	VEC=5*cycles*totCyc;

	for (i=0; i<BANK-VEC; ++i) {
		l=0;
		for (j=nPat-1; j>=0; j--) {
			for (k=0; k<pattern[j]*cycles*5; k++)
				data[i]+=data[i+l++];
			--j;
			for (k=0; k<pattern[j]*cycles*5; k++)
				data[i]-=data[i+l++];
			//l+=pattern[j-1]*cycles*5;
		}
	}
	//sendStr(intToStr(l));					//Use this line to check length of vector actually correlated with
	if (DEBUG)
		sendStr(" Complete.\n");
}

/*
 * Set cycles for TX
 */

void setCycles(uint32_t c, uint32_t i) {
	cycles=c;
	nPat=0;
	totCyc=0;
	while (i>0) {
		pattern[nPat]=i%10;
		totCyc+=pattern[nPat++];
		i/=10;
	}
	sendStr(" Cycles updated successfully.\n");
}

/*
 * Look-up table for gain and cycles values.
 */

void setGain() {
	if (prev<60) {
		setCntl(0.8);
		cycles=2;
	}
	else if (prev<120) {
		setCntl(1);
		cycles=2;
	}
	else if (prev<200) {
		setCntl(1.2);
		cycles=4;
	}
	else if (prev<300) {
		setCntl(1.5);
		cycles=4;
	}
	else if (prev<400) {
		setCntl(1.6);
		cycles=4;
	}
	else if (prev<500) {
		setCntl(1.7);
		cycles=6;
	}
	else if (prev<600) {
		setCntl(1.9);
		cycles=6;
	}
	else if (prev<700) {
		setCntl(2.1);
		cycles=6;
	}
	else if (prev<800) {
		setCntl(2.2);
		cycles=6;
	}
	else if (prev<900) {
		setCntl(2.4);
		cycles=6;
	}
	else {
		setCntl(2.6);
		cycles=10;
	}
	if (prev<300)
		ignore=10/.085;
	else
		ignore=60/.085;
}
