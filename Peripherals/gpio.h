/*
 * gpio.h
 *
 *  Created on: Apr 26, 2015
 *      Author: prachetverma
 */

#ifndef PERIPHERALS_GPIO_H_
#define PERIPHERALS_GPIO_H_

#include "../essential.h"

//Initialisation
void initGPIO(void);

//Usage
void ultraTX(uint8_t);

/*
 * Hardcoding set and unset for
 * GPIO pins
 */

//For sensor board
#define setLED() P1OUT |= BIT0
#define setG1() P4OUT |= BIT0
#define setG2() P4OUT |= BIT1
#define setOE() P4OUT |= BIT2
#define setTX() P4OUT |= BIT4

#define unsetLED() P1OUT &= ~BIT0
#define unsetG1() P4OUT &= ~BIT0
#define unsetG2() P4OUT &= ~BIT1
#define unsetOE() P4OUT &= ~BIT2
#define unsetTX() P4OUT &= ~BIT4

#define toggleLED() P1OUT ^= BIT0
#define toggleG1() P4OUT ^= BIT0
#define toggleTX() P4OUT ^= BIT4

//For power board
#define enablePower() P5OUT &= ~BIT2
#define disablePower() P5OUT |= BIT2

#define disableBoost() P5OUT &= ~BIT4
#define enableBoost() P5OUT |= BIT4

#define disableBuck() P5OUT &= ~BIT6
#define enableBuck() P5OUT |= BIT6

#define enableLDO() P5OUT &= ~BIT7
#define disableLDO() P5OUT |= BIT7

#endif /* PERIPHERALS_GPIO_H_ */
