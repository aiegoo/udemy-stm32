/*
 * bsp.h
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#ifndef INCLUDE_UTIL_BSP_H_
#define INCLUDE_UTIL_BSP_H_


#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdarg.h>

#include "stm32f4xx_hal.h"





void delay(uint32_t ms);
uint32_t millis(void);


#endif /* INCLUDE_UTIL_BSP_H_ */
