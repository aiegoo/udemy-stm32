# PWM & Output Compare

## 1. PWM Generation

- Timer PWM start

```c
HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
```

## 2. Output Compare

- Timer Output Compare start

```c
HAL_TIM_Base_Start_IT(&htim4);
HAL_TIM_PWM_Start_IT(&htim4, TIM_CHANNEL_1);
```

## 3. Timer interrupt callback function

```c
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_SET);
  }
}

void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
  if (htim->Instance == TIM4)
  {
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)
          HAL_GPIO_WritePin(GPIOG, GPIO_PIN_14, GPIO_PIN_RESET);
    if(htim->Channel == HAL_TIM_ACTIVE_CHANNEL_2)
          HAL_GPIO_WritePin(GPIOG, GPIO_PIN_13, GPIO_PIN_RESET);
  }
}
```

