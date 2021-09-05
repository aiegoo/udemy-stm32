/*
 * bsp.c
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#include "bsp.h"



void delay(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}




