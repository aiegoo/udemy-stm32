/*
 * led.h
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#ifndef INCLUDE_DRIVERS_LED_H_
#define INCLUDE_DRIVERS_LED_H_

#include "app_config.h"
#include "bsp.h"


#ifdef USE_HW_LED

#define LED_MAX_CH      HW_LED_MAX_CH

bool ledInit(void);
void ledOn(uint8_t ch);
void ledOff(uint8_t ch);
void ledToggle(uint32_t ch);

#endif


#endif /* INCLUDE_DRIVERS_LED_H_ */
