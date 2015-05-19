//*****************************************************************************
//
// MSP432 main.c for Ultrasonic Sensor
// Created on: Apr 16, 2015
//      Author: prachetverma
//
//****************************************************************************

#include "essential.h"

int main(void)
{
	WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

	/*
	 * Initialisation sequence.
	 */

	initClock();
	initGPIO();

	enablePower();
	delayMillis(500);
	setLED();

	initUART();
	initI2C();
	initTimer();
	initADC();

	__enable_interrupt();

	data=(uint32_t*)malloc(BANK*sizeof(uint32_t));
	cycles=10;
	nPat=3;
	pattern[0]=4;
	pattern[1]=3;
	pattern[2]=4;
	totCyc=11;
	recording=0;

	if (DEBUG)
		sendStr(" All initialisations complete.\n");

	/*
	 * Set up power supplies.
	 */

	setBoost(12);
	setBuck(5.5);
	setLDO(4.5);

	enableBoost();
	delayMillis(100);

	enableBuck();
	delayMillis(100);

	enableLDO();
	delayMillis(100);

	if (DEBUG)
		sendStr(" Power supply setup complete.\n");

	/*
	 * Set up sensor board.
	 */

	setOE();

	setG1();
	setG2();
	setClmp(2);
	setCntl(2);

	if (DEBUG)
		sendStr(" Sensor board setup complete.\n");

	while (1) {
		flag=1;
		sendStr(" %%%\n");
		while (flag);
		if (recording)
			transaction();
	}

	__sleep();

	__no_operation();                       // For debugger
}

