/*
 * utility.c
 *
 *  Created on: Sep 11, 2021
 *      Author: tocru
 */

#include "utility.h"


uint32_t millis(void)
{
  return HAL_GetTick();
}

uint32_t micros(void)
{
  return 0;
}

void delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}

void delay_us(uint32_t us)
{
}


