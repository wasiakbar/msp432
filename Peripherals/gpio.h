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

/*
 * Hardcoding set and unset for
 * GPIO pins
 */
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

#endif /* PERIPHERALS_GPIO_H_ */
