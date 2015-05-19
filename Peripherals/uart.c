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
	UCA0CTLW0 |= UCSSEL__SMCLK;             // Put eUSCI in reset
	// Baud Rate set
	UCA0BR0 = 13;                           // 12000000/16/9600
	UCA0BR1 = 0x00;
	UCA0MCTLW = (0x25<<8) | UCOS16;

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
 * 	Convert string to int. Covers unsinged range for 32-bit.
 */

uint32_t strToInt(char *p) {
	uint8_t i;
	uint32_t r=0;
	for (i=0; p[i]; ++i) {
		r*=10;
		r+=p[i]-48;
	}
	return r;
}

/*
 * 	Execute command passed on serial
 */

void executeCmd() {
	uint8_t j=0, argc=0;
	uint32_t i;
	char argv[3][20];
	cmd[cmdPtr]='\0';
	cmdPtr=0;
	recording=0;
	for (i=0; cmd[i]!='\0'; i++) {
		if (cmd[i]==' ') {
			argv[argc][j]='\0';
			argc++;
			j=0;
		}
		else
			argv[argc][j++]=cmd[i];
	}
	argv[argc][j]='\0';

	if (!(strcmp(argv[0],"pull"))) {
		pushData();
	}
	else if (!(strcmp(argv[0],"setcycles"))) {
		cycles=strToInt(argv[1]);
		i=strToInt(argv[2]);
		nPat=0;
		totCyc=0;
		while (i>0) {
			pattern[nPat]=i%10;
			totCyc+=pattern[nPat++];
			i/=10;
		}
	}
	else if (!(strcmp(argv[0],"correlate"))) {
		correlate();
	}
	else if (!(strcmp(argv[0],"record"))) {
		recording=1;
	}
	else if (!(strcmp(argv[0],"measure"))) {
		sendStr(intToStr(getDistance()));
	}
	else if (!(strcmp(argv[0],"setcntl"))) {
		setCntl((strToInt(argv[1]))/10.0);
	}
	else if (!(strcmp(argv[0],"setclmp"))) {
		setClmp((strToInt(argv[1]))/10.0);
	}
	else if (!(strcmp(argv[0],"help")));
	else
		sendStr(" Invalid command.\n");

	flag=0;
}


void pushData(void) {
	uint16_t i;
	sendStr(" $$$\n");
	for (i=0; i<BANK; ++i) {
		sendStr(intToStr(data[i]));
	}
	sendStr(" $$$\n");
	sendStr(" Data transfer successful.\n");
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
		if (UCA0RXBUF != '\n')
			cmd[cmdPtr++]=UCA0RXBUF;
		else
			executeCmd();
	}
}

