/*
 * uart.c
 *
 *  Created on: Sep 12, 2021
 *      Author: tocru
 */

#include "uart.h"
#include "usart.h"
#include "qbuffer.h"

static bool is_open[UART_MAX_CH];

//UART_HandleTypeDef huart1;
//UART_HandleTypeDef huart2;

static qbuffer_t qbuffer[UART_MAX_CH];
static uint8_t rx_data[UART_MAX_CH];

static uint8_t rx_buf1[UART_RINGBUFFER_LENGTH];
static uint8_t rx_buf2[UART_RINGBUFFER_LENGTH];


bool uartInit(void)
{
  for (int i = 0; i < UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  return true;
}

bool uartOpen(uint8_t ch, uint32_t baud)
{
  bool ret = false;

  switch (ch)
  {
    case DEF_UART1:
      qbufferCreate(&qbuffer[ch], &rx_buf1[0], 256);

      is_open[ch] = true;
      ret = true;

//      if (HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data[ch], 1) != HAL_OK)
      if (HAL_UART_Receive_DMA(&huart1, (uint8_t *)&rx_buf1[0], 256) != HAL_OK)
      {
        ret = false;
      }

      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
      qbuffer[ch].out = qbuffer[ch].in;
      break;

    case DEF_UART2:
      qbufferCreate(&qbuffer[ch], &rx_buf2[0], 256);

      is_open[ch] = true;
      ret = true;

//      if (HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_data[ch], 1) != HAL_OK)
      if (HAL_UART_Receive_DMA(&huart2, (uint8_t *)&rx_buf2[0], 256) != HAL_OK)
      {
        ret = false;
      }

      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
      qbuffer[ch].out = qbuffer[ch].in;
      break;
  }

  return ret;
}

uint32_t uartAvailable(uint8_t ch)
{
  uint32_t ret = 0;

  switch (ch)
  {
    case DEF_UART1:
      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;

    case DEF_UART2:
      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;
  }

  return ret;
}


uint8_t uartRead(uint8_t ch)
{
  uint8_t ret = 0;

  switch (ch)
  {
    case DEF_UART1:
//      ret = qbufferRead(&qbuffer[DEF_UART1], &ret, 1); // uart polling rx interrupt
      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart1.hdmarx);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;

    case DEF_UART2:
//      ret = qbufferRead(&qbuffer[DEF_UART2], &ret, 1); // uart polling rx interrupt
      qbuffer[ch].in = qbuffer[ch].len - __HAL_DMA_GET_COUNTER(huart2.hdmarx);
      ret = qbufferAvailable(&qbuffer[ch]);
      break;
  }

  return ret;
}

uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  HAL_StatusTypeDef status;

  switch (ch)
  {
    case DEF_UART1:
      status = HAL_UART_Transmit(&huart1, p_data, length, 100);
      if (status == HAL_OK)
      {
        ret = length;
      }
      break;

    case DEF_UART2:
      status = HAL_UART_Transmit(&huart2, p_data, length, 100);
      if (status == HAL_OK)
      {
        ret = length;
      }
      break;
  }

  return ret;
}


uint32_t uartPrintf(uint8_t ch, char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite(ch, (uint8_t *)buf, len);

  va_end(args);

  return ret;
}


uint32_t uartGetBaud(uint8_t ch)
{
  uint32_t ret = 0;

  switch (ch)
  {
    case DEF_UART1:
      ret = huart1.Init.BaudRate;
      break;

    case DEF_UART2:
      ret = huart2.Init.BaudRate;
      break;
  }

  return ret;
}

// uart polling interrupt rx -> tx -----------------------
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    qbufferWrite(&qbuffer[DEF_UART1], &rx_data[DEF_UART1], 1);

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data[DEF_UART1], 1);
    HAL_UART_Transmit(&huart1, (uint8_t *)&rx_data[DEF_UART1], 1, 0xffff);

    // print received data count number-----------------
    printf("Rx data in : %d\n\r", qbuffer[DEF_UART1].in);
  }
  if (huart->Instance == USART2)
  {
    qbufferWrite(&qbuffer[DEF_UART2], &rx_data[DEF_UART2], 1);

    HAL_UART_Receive_IT(&huart2, (uint8_t *)&rx_data[DEF_UART2], 1);
  }
}


