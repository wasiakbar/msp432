/*
 * i2c.c
 *
 *  Created on: Apr 27, 2015
 *      Author: prachetverma
 */

#include "i2c.h"

uint8_t TXData[2];        // Pointer to TX data
uint8_t TXByteCtr;

const float VDD = 4.9;
const uint8_t R=100;
const uint8_t R1=200;			//Kilo ohms
const uint8_t R2=15;			//Kilo ohms
const uint8_t R3=47;			//Kilo ohms

const uint8_t potVGAAddr=0x51;
const uint8_t pot12Addr=0x52;
const uint8_t pot4Addr=0x54;

const uint8_t clmpReg=0x00;
const uint8_t cntlReg=0x01;
const uint8_t boostReg=0x00;
const uint8_t buckReg=0x00;
const uint8_t ldoReg=0x01;


/*
 * 	Initialise I2C
 */

void initI2C(void) {
	// Configure Pins for I2C
	P6SEL0 |= BIT4 | BIT5;                            // I2C pins

	NVIC_ISER0 = 1 << ((INT_EUSCIB1 - 16) & 31); // Enable eUSCIB1 interrupt in NVIC module

	// Configure USCI_B3 for I2C mode
	UCB1CTLW0 |= UCSWRST;                             // put eUSCI_B in reset state
	UCB1CTLW0 |= UCMODE_3 | UCMST | UCSSEL__ACLK;		// I2C master mode, ACLK
	UCB1BRW = 24;                                 // baudrate = SMCLK /24
	UCB1CTLW0 &=~ UCSWRST;                            // clear reset register
	UCB1IE |= UCTXIE0 | UCNACKIE;                     // transmit and NACK interrupt enable

	if (DEBUG)
		sendStr(" I2C Initialisation complete.\n");
}

/*
 * Send data on I2C to set Clmp and Cntl
 */

void setClmp(float volts) {
	int i;
	UCB1I2CSA = potVGAAddr;
	if (volts < 0)
		volts = 0.0;
	else if (volts > 2.6)
		volts = 2.6;
	TXData[0]=(volts/VDD)*256;
	TXData[1]=clmpReg;
	TXByteCtr=2;
	while (UCB1CTLW0 & UCTXSTP);                      // Ensure stop condition got sent
	UCB1CTLW0 |= UCTR | UCTXSTT;                      // I2C TX, start condition
	if (DEBUG)
			sendStr(" Pot set for Vclmp.\n");
	for (i=0; i<30000; i++);				//Delay
	for (i=0; i<30000; i++);				//Delay
}

void setCntl(float volts) {
	int i;
	UCB1I2CSA = potVGAAddr;
	if (volts < 0)
		volts = 0.0;
	else if (volts > 2.6)
		volts = 2.6;
	TXData[0]=(volts/VDD)*256;
	TXData[1]=cntlReg;
	TXByteCtr=2;
	while (UCB1CTLW0 & UCTXSTP);                      // Ensure stop condition got sent
	UCB1CTLW0 |= UCTR | UCTXSTT;                      // I2C TX, start condition
	if (DEBUG)
		sendStr(" Pot set for Vcntl.\n");
	for (i=0; i<30000; i++)	;				//Delay
	for (i=0; i<30000; i++);				//Delay
}

void setBoost(float volts) {
	int i;
	float Rset = (R1/((volts/1.229)-1))-R2;
	UCB1I2CSA = pot12Addr;
	TXData[0]=(1-Rset/R)*256;
	TXData[1]=boostReg;
	TXByteCtr=2;
	while (UCB1CTLW0 & UCTXSTP);                      // Ensure stop condition got sent
	UCB1CTLW0 |= UCTR | UCTXSTT;                      // I2C TX, start condition
	if (DEBUG)
		sendStr(" Pot set for boost.\n");
	for (i=0; i<30000; i++)	;				//Delay
}

void setBuck(float volts) {
	int i;
	float Rset = (R1/((volts/0.5)-1))-R2;
	UCB1I2CSA = pot4Addr;
	TXData[0]=(1-Rset/R)*256;
	TXData[1]=buckReg;
	TXByteCtr=2;
	while (UCB1CTLW0 & UCTXSTP);                      // Ensure stop condition got sent
	UCB1CTLW0 |= UCTR | UCTXSTT;                      // I2C TX, start condition
	if (DEBUG)
		sendStr(" Pot set for buck.\n");
	for (i=0; i<30000; i++)	;				//Delay
}

void setLDO(float volts) {
	int i;
	float Rset = (R1/((volts/1.182)-1))-R3;
	UCB1I2CSA = pot4Addr;
	TXData[0]=(1-Rset/R)*256;
	TXData[1]=ldoReg;
	TXByteCtr=2;
	while (UCB1CTLW0 & UCTXSTP);                      // Ensure stop condition got sent
	UCB1CTLW0 |= UCTR | UCTXSTT;                      // I2C TX, start condition
	if (DEBUG)
		sendStr(" Pot set for ldo.\n");
	for (i=0; i<30000; i++)	;				//Delay
}
/*
 * Interrupt Service Routine triggered by I2C_EUSCI_B
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */

void eUSCIB1IsrHandler(void)
{
	if (UCB1IFG & UCNACKIFG)
	{
		UCB1IFG &= ~ UCNACKIFG;
		UCB1CTL1 |= UCTXSTT;                  // I2C start condition
	}
	if (UCB1IFG & UCTXIFG0)
	{
		UCB1IFG &= ~ UCTXIFG0;
		if (TXByteCtr)                                // Check TX byte counter
		{
			UCB1TXBUF = TXData[TXByteCtr-1];            // Load TX buffer
			TXByteCtr--;
		}
		else
		{
			UCB1CTLW0 |= UCTXSTP;                     // I2C stop condition
			UCB1IFG &= ~UCTXIFG;                      // Clear USCI_B0 TX int flag
		}
	}
}
