/*
 * i2c.h
 *
 *  Created on: Apr 27, 2015
 *      Author: prachetverma
 */

#ifndef PERIPHERALS_I2C_H_
#define PERIPHERALS_I2C_H_

#include "../essential.h"

//Initialisation
void initI2C(void);

//Program pots for clmp and cntl
void setClmp(float);
void setCntl(float);
void setBoost(float);
void setBuck(float);
void setLDO(float);

#endif /* PERIPHERALS_I2C_H_ */
