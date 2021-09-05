/*
 * blinking.c
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#include "blinking.h"
#include "tim.h"




void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM14)
      ledToggle(0);
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM14)
    ledToggle(0);
}

void led_Init(void)
{
  HAL_TIM_Base_Start_IT(&htim14);

  htim14.Instance->ARR = 5000;

}
