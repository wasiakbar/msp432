/*
 * uart.c
 *
 *  Created on: Apr 23, 2015
 *      Author: prachetverma
 */

#include "uart.h"

/*
 * 	 Initialise UART on port 1
 * 	 Use pins P1.3 (TX) and P1.2 (RX)
 * 	 Baud rate 9600
 */

void initUART(void) {
	// Configure UART pins
	P1SEL0 |= BIT2 | BIT3;                  // set 2-UART pin as second function

	NVIC_ISER0 = 1 << ((INT_EUSCIA0 - 16) & 31); // Enable eUSCIA0 interrupt in NVIC module

	// Configure UART
	UCA0CTLW0 |= UCSWRST;
	UCA0CTLW0 |= UCSSEL__ACLK;             // Put eUSCI in reset
	// Baud Rate set
	UCA0BR0 = 3;
	UCA0BR1 = 0x00;
	UCA0MCTLW = (0x92<<8);

	UCA0CTLW0 &= ~UCSWRST;                  // Initialize eUSCI
	UCA0IE |= UCRXIE;                       // Enable USCI_A0 RX interrupt

	strcpy(cmd,"");
	cmdPtr=0;


	/* Baud Rate calculation
	 * For future refernce. To be ignored since above uses ACLK at 32kHz
	 * fBR = SMCLK = 24e6
	 * Baudrate = 115200
	 * N = fBR/Baudrate = 24000000/115200 = 208.33
	 * Since N>16, OS16 = 1
	 * UCBR = int(N/16) = int (13.0208) = 13
	 * UCBRF = int( ((N/16) - int(N/16)) * 16 ) = int (0.33) = 0
	 * User's Guide Table 22-4: UCBRSx = 0x00
	 */

	if (DEBUG)
		sendStr(" UART initialisation complete.\n");
}

/*
 *   Wait for tx buffer to be freed
 * 	 Send single character to tx buffer
 */

void sendChar(char ch)
{
	while(!(UCA0IFG & UCTXIFG));
	UCA0TXBUF= ch;
}

/*
 *	Send a string by calling sendChar()
 *	multiple times
 */

void sendStr(char *p) {
	while (*p++!='\0')
		sendChar(*p);
}

/*
 * 	Convert int to string. Covers unsinged range.
 */

char* intToStr(uint32_t data) {
	unsigned char i=7;
	strcpy(str,"        \n");
	if (data==0) str[i]=48;
	else while (data>0) {
		str[i--]=(data%10)+48;
		data/=10;
	}
	return str;
}

/*
 * 	Execute command passed on serial
 */

void executeCmd() {
	cmd[cmdPtr]='\0';
	sendStr(" Here\n");
	cmdPtr=0;
}


/*
 * Interrupt Service Routine to read on UART
 * Note: Ensure entry in MSP432_startup_ccs.c Interrupt Vector Table
 */

void eUSCIA0IsrHandler(void)
{
    if (UCA0IFG & UCRXIFG)
    {
      while(!(UCA0IFG&UCTXIFG));
      UCA0TXBUF = UCA0RXBUF;
      __no_operation();
    }
}
		/*if (UCA0RXBUF != 'A')
			cmd[cmdPtr++]=UCA0RXBUF;
		else
			executeCmd();*/

