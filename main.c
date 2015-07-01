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

	data=(int32_t*)malloc(BANK*sizeof(int32_t));
	cycles=6;
	nPat=3;
	pattern[0]=1;
	pattern[1]=1;
	pattern[2]=3;
	totCyc=5;
	recording=0;
	initialise=0;
	ignore=60/.085;
	automatic=0;
	distance=0;
	reader=0;
	prev=0;
	first=1;

	if (DEBUG)
		sendStr(" All initialisations complete.\n");

	/*
	 * Set up power supplies.
	 */

	setBoost(12);
	setBuck(5.5);
	setLDO(4.9);

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

	temp=100;
	while (1) {
		uint8_t tracker=1;
		flag=1;
		sendChar('%');
		while (flag);
		if (recording) {
			transaction();
		}
		else if (initialise) {
			setCntl(1.7);
			cycles=6;
			transaction();
			correlate();
			prev=getDistance();
			transaction();
			correlate();
			distance=getDistance();
			do {
				if (DEBUG) {
					sendStr(" Iteration: ");
					sendStr(intToStr(tracker++));
					sendChar('\n');
				}
				if (abs(prev-distance)<60)
					setGain();
				else if (prev<500 && distance<500) {
					setCntl(1.4);
					cycles=4;
				}
				else if (tracker>2) {
					setCntl(2.6);
					cycles=10;
				}
				else {
					setCntl(2.2);
					cycles=6;
				}
				transaction();
				correlate();
				prev=getDistance();
				transaction();
				correlate();
				distance=getDistance();
			} while (!(abs(prev-distance)<15));
			setGain();
			transaction();
			correlate();
			prev=getDistance();
			if (DEBUG) {
				sendStr(" Found initialisation point at: ");
				sendStr(intToStr(prev));
				sendChar('\n');
			}
			unsetLED();
		}
		else if (reader) {
			setGain();
			transaction();
			correlate();
			distance=getDistance();
			if (abs(prev-distance)<30) {
				prev = distance;
				sendStr(intToStr(prev));
			}
			else {
				uint16_t temp;
				transaction();
				correlate();
				temp=getDistance();
				if (abs(distance-prev)<80) {
					if (abs(temp-prev)<abs(distance-prev))
						prev=temp;
					else
						prev=distance;
					sendStr(intToStr(prev));
				}
				else if (abs(temp-prev)<80) {
					prev=temp;
					sendStr(intToStr(prev));
				}
				else {
					if (DEBUG)
						sendStr(" Reinitialisation required\n");
				}
			}
			unsetLED();
		}
	}

	__sleep();

	__no_operation();                       // For debugger
}

