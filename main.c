//*****************************************************************************
//
// MSP432 main.c for Ultrasonic Sensor
// Created on: Apr 16, 2015
//      Author: prachetverma
//
//****************************************************************************

#include "essential.h"

#define ADC 1
#define I2C 0
#define TX 0
#define MALLI 0

int main(void)
{
	int i,j;
	float x=0,y=1;
	WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

	if (ADC) {
		initClock();
		initGPIO();

		__enable_interrupt();
		initADC();
		initTimer();


		while(1);
	}

	if (I2C) {
		initClock();
		initGPIO();

		__enable_interrupt();
		initI2C();

		setCntl(1.5);
		setClmp(1);

		while(1);
	}


	if (TX) {
		initGPIO();
		enablePower();

		__enable_interrupt();
		initI2C();
		unsetG1();
		unsetG2();
		setOE();

		setG1();
		setG2();
		setClmp(2);
		setCntl(2);

		while(1) {
			ultraTX(30);
			__delay_cycles(30000);
		}
	}

	if (MALLI) {
		initGPIO();
		enablePower();

		__enable_interrupt();
		initI2C();

		setBoost(11);
		setBuck(5);
		setLDO(4.5);
		enableBoost();
		enableBuck();
		enableLDO();

		setLED();
	}

	if (DEBUG)
		sendStr("\n\n\r All initialisations complete.");
	while(1);
	__sleep();

	__no_operation();                       // For debugger
}

