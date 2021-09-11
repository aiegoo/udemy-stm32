# Tutorial 07 - EXTI

## 1. GPIO PIN Configuration

- GPIO mode : Rising edge / Falling edge Trigger
- GPIO Pull-up/Pull-down
- NVIC interrupt Enable

## 2. EXTI Callback function

```c
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
  if (GPIO_Pin == GPIO_PIN_0)
  {
    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
  }
}
```
