/*
 * uart.c
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#include "uart.h"
#include "app_config.h"
#include "qbuffer.h"


UART_HandleTypeDef huart1;
static bool is_open[UART_MAX_CH];
static qbuffer_t qbuffer;

static uint8_t rx_buf[256];
static uint8_t rx_data;

bool uartInit(void)
{
  bool ret = true;

  qbufferCreate(&qbuffer, &rx_buf[0], 256);

  for (int i = 0; i < UART_MAX_CH; i++)
  {
    is_open[i] = false;
  }

  if (HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data, 1) != HAL_OK)
  {
    ret = false;
  }

  return ret;
}

uint8_t uartAvailable(void)
{
  uint8_t ret;

  ret = (qbuffer.in - qbuffer.out) % qbuffer.len;

  return ret;
}


uint8_t uartRead(void)
{
  uint8_t ret;

  ret = rx_buf[qbuffer.out];

  if (qbuffer.out != qbuffer.in)
  {
    qbuffer.out = (qbuffer.out + 1) % qbuffer.len;
  }

  return ret;
}

void uartDataIn(uint8_t rx_data)
{

}

uint32_t  uartWrite(uint8_t *p_data, uint32_t length)
{
  uint32_t ret = 0;
  HAL_StatusTypeDef status;

  status = HAL_UART_Transmit(&huart1, p_data, length, 100);
  if (status == HAL_OK)
  {
    ret = length;
  }

  return ret;
}

uint32_t uartPrintf(char *fmt, ...)
{
  char buf[256];
  va_list args;
  int len;
  uint32_t ret;

  va_start(args, fmt);
  len = vsnprintf(buf, 256, fmt, args);

  ret = uartWrite((uint8_t *)buf, len);

  va_end(args);

  return ret;
}

uint32_t uartGetBaud(void)
{
  uint32_t ret = 0;

  return ret;
}



void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
  if (huart->Instance == USART1)
  {
    qbufferWrite(&qbuffer, &rx_data, 1);

    HAL_UART_Receive_IT(&huart1, (uint8_t *)&rx_data, 1);
  }
}


