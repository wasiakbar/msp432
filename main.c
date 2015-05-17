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
	int i,j;
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

	if (DEBUG)
		sendStr(" All initialisations complete.\n\n");

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
		sendStr("Power supply setup complete.\n\n");

	/*
	 * Set up sensor board.
	 */

	setOE();

	setG1();
	setG2();
	setClmp(2);
	setCntl(2.4);

	if (DEBUG)
		sendStr(" Sensor board setup complete.\n\n");

	do {
		sendStr(" ***Press S1 to start conversion***\n");
		while (P1IN & BIT1);
		unsetLED();

		ultraTX(10);
		ultraTX(10);
		ultraTX(10);
		ultraTX(10);
		waitTX(10);
		waitTX(10);
		waitTX(10);
		ultraTX(10);
		ultraTX(10);
		ultraTX(10);
		ultraTX(10);

		recordData();
		/*sendStr(" Distance by simple max: \n");
		sendStr(intToStr(getDistance()));*/
		sendStr(" Correlating...\n");
		correlate();
		sendStr(" Distance by correlation: \n");
		sendStr(intToStr((getDistance()+47)));

		sendStr(" ***Press S2 to get raw data***\n");
		while (P1IN & BIT4);
		delayMillis(100);
		sendStr(" $$$\n");
		for (i=0; i<BANK; ++i) {
			sendStr(intToStr(data[i]));
		}
		sendStr(" $$$\n");
		setLED();
	} while (1);


	__sleep();

	__no_operation();                       // For debugger
}

