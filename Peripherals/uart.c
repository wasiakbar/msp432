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

char* intToStr(int32_t data) {
	uint8_t i=7;
	uint8_t negFlag=0;
	if (data<0) {
		negFlag=1;
		data*=-1;
	}
	strcpy(str,"        \n");
	if (data==0) str[i]=48;
	else while (data>0) {
		str[i--]=(data%10)+48;
		data/=10;
	}
	if (negFlag)
		str[i]='-';
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
	initialise=0;
	reader=0;
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
	else if (!(strcmp(argv[0],"START"))) {
		setLED();
		if (first==1) {
			initialise=1;
			first=0;
		}
		else
			recording=1;
	}
	else if (!(strcmp(argv[0],"auto"))) {
		if (strToInt(argv[1])) {
			automatic=1;
			sendStr(" Auto mode.\n");
			initialise=1;
		}
		else {
			automatic=0;
			sendStr(" Manual mode.\n");
		}
	}
	else if (!(strcmp(argv[0],"setcycles"))) {
		if (automatic)
			sendStr(" Auto mode. Cannot edit.\n");
		else {
			setCycles(strToInt(argv[1]), strToInt(argv[2]));
		}
	}
	else if (!(strcmp(argv[0],"correlate"))) {
		if (automatic)
			sendStr(" Please switch to manual mode.\n");
		else
			correlate();
	}
	else if (!(strcmp(argv[0],"record"))) {
		if (automatic)
			sendStr(" Please switch to manual mode.\n");
		else
			recording=1;
	}
	else if (!(strcmp(argv[0],"measure"))) {
		if (automatic)
			reader=1;
		else
			sendStr(intToStr(getDistance()));
	}
	else if (!(strcmp(argv[0],"setcntl"))) {
		if (automatic)
			sendStr(" Auto mode. Cannot edit.\n");
		else
			setCntl((strToInt(argv[1]))/10.0);
	}
	else if (!(strcmp(argv[0],"setclmp"))) {
		if (automatic)
			sendStr(" Auto mode. Cannot edit.\n");
		else
			setClmp((strToInt(argv[1]))/10.0);
	}
	else if (!(strcmp(argv[0],"setignore"))) {
		if (automatic)
			sendStr(" Auto mode. Cannot edit.\n");
		else
			ignore=(float)strToInt(argv[1])/0.085;
	}
	else if (!(strcmp(argv[0],"help")));
	else
		sendStr(" Invalid command.\n");

	flag=0;
}


void pushData(void) {
	uint16_t i;
	sendChar('$');
	for (i=0; i<BANK; ++i) {
		sendStr(intToStr(data[i]));
	}
	sendChar('$');
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

