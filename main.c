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
	uint16_t i;
	WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

	initClock();

	P1OUT &= ~BIT0;                           // Clear LED to start
	P1DIR |= BIT0;                            // Set P1.0/LED to output

	__enable_interrupt();
	initUART();
	initADC();
	initTimer();

	sendStr("\n\n\r All initialisations complete.");

	while (1)
	{
		for (i = 20000; i > 0; i--);            // Delay
		//set(1,0);
		//startConversion();
		__sleep();

		__no_operation();                       // For debugger
	}

	__no_operation();                       // For debugger
}

