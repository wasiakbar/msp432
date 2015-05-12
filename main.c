//*****************************************************************************
//
// MSP432 main.c for Ultrasonic Sensor
// Created on: Apr 16, 2015
//      Author: prachetverma
//
//****************************************************************************

#include "essential.h"

#define ADC 0
#define I2C 0
#define TX 1
#define MALLI 0

int main(void)
{
	int i,j;
	float x=0,y=1;
	WDTCTL = WDTPW | WDTHOLD;               // Stop watchdog timer

	data=(uint32_t*)malloc(BANK*sizeof(uint32_t));


	if (ADC) {
		initClock();
		initGPIO();

		initUART();

		__enable_interrupt();
		initADC();
		initTimer();

		ultraTX(10);
		recordData();
		for (i=0; i<BANK; ++i) {
			sendStr(intToStr(data[i]));
		}


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
		initClock();
		initGPIO();
		initTimer();
		initADC();
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
			ultraTX(10);
			recordData();
			for (j=0;j<4;++j)
				__delay_cycles(30000);
		}
	}

	if (MALLI) {
		initClock();
		initGPIO();
		enablePower();

		__enable_interrupt();
		initI2C();

		setBoost(11);
		setBuck(5);
		setLDO(4.2);
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

