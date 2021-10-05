/*
 * bsp.c
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#include "bsp.h"



void delay_ms(uint32_t ms)
{
  HAL_Delay(ms);
}

uint32_t millis(void)
{
  return HAL_GetTick();
}


uint32_t drv_mpu9250_ms_get(uint32_t *millis)
{
  *millis = HAL_GetTick();
  return millis;
}


uint32_t get_tick_count(uint32_t *timestamp)
{
  timestamp = HAL_GetTick();
  return timestamp;
}
