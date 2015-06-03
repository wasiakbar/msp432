/*
 * compute.h
 *
 *  Created on: May 14, 2015
 *      Author: prachetverma
 */

#ifndef COMPUTE_H_
#define COMPUTE_H_

#include "essential.h"

/*
 * Computation functions
 */

void transaction(void);
int getDistance(void);
void movingAvg(uint8_t samples);
void correlate(void);
uint8_t initialisationSequence(void);
void setCycles(uint32_t, uint32_t);
void setGain();


#endif /* COMPUTE_H_ */
