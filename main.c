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
		sendStr("\n\n\r All initialisations complete.");

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
		sendStr("\n\n\r Power supply setup complete.");


	/*
	 * Set up sensor board.
	 */

	setOE();

	setG1();
	setG2();
	setClmp(2);
	setCntl(2);


	if (DEBUG)
		sendStr("\n\n\r Sensor board setup complete.");

	do {
		sendStr("\n\n\r ***Press S1 to start conversion***");
		while (P1IN & BIT1);
		unsetLED();
		ultraTX(10);
		recordData();
		sendStr("\n\n\r ***Press S2 to view data***");
		while (P1IN & BIT4);
		delayMillis(100);
		sendStr("\n\n\n\n");
		for (i=0; i<BANK/5; ++i) {
			sendStr(intToStr(data[i]));
		}
		sendStr("\n\n\n\n");
		while (P1IN & BIT4);
		delayMillis(100);
		for (; i<(BANK/5)*2; ++i) {
			sendStr(intToStr(data[i]));
		}
		sendStr("\n\n\n\n");
		while (P1IN & BIT4);
		delayMillis(100);
		for (; i<(BANK/5)*3; ++i) {
			sendStr(intToStr(data[i]));
		}
		sendStr("\n\n\n\n");
		while (P1IN & BIT4);
		delayMillis(100);
		for (; i<(BANK/5)*4; ++i) {
			sendStr(intToStr(data[i]));
		}
		sendStr("\n\n\n\n");
		while (P1IN & BIT4);
		delayMillis(100);
		for (; i<BANK; ++i) {
			sendStr(intToStr(data[i]));
		}
		setLED();
	} while (1);


	__sleep();

	__no_operation();                       // For debugger
}

