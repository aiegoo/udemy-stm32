/*
 * utility.h
 *
 *  Created on: Sep 11, 2021
 *      Author: tocru
 */

#ifndef INCLUDE_UTILITY_UTILITY_H_
#define INCLUDE_UTILITY_UTILITY_H_

#include "app_config.h"
#include "stm32f4xx_hal.h"



uint32_t millis(void);
uint32_t micros(void);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);


#endif /* INCLUDE_UTILITY_UTILITY_H_ */
