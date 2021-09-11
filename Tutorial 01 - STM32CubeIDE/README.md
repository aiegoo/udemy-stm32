# STM32CubeIDE Project Basic form

## 1. uart 1 for printf

```c
int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 10);
  return len;
}
```

## 2. uart 1 interrupt callback function

```c
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    HAL_UART_Receive_IT(&huart1, &rxData, 1);
    HAL_UART_Transmit(&huart1, &rxData, 1, 10);
  }
}

```

## 3. uart 1 start RX interrut

```c
HAL_UART_Receive_IT(&huart1, &rxData, 1);
```

## 4. use float value in printf

- project > properties > C/C++ Build > Settings > MCU GCC Linker > Miscellaneous
  
  - "-u_printf_float"

