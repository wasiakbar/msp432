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

	initClock();
	initGPIO();

	__enable_interrupt();
	//initUART();
	//initADC();
	//initTimer();
	initI2C();

	if (DEBUG)
		sendStr("\n\n\r All initialisations complete.");

	setLED();
	setClmp(2.28);
	//setCntl(1.2);
	while(1);

	__sleep();

	__no_operation();                       // For debugger
}

