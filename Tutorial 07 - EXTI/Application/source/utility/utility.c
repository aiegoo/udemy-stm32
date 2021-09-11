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

void delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}


