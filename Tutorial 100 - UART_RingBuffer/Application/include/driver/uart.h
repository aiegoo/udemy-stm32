/*
 * uart.h
 *
 *  Created on: Sep 12, 2021
 *      Author: tocru
 */

#ifndef INCLUDE_DRIVER_UART_H_
#define INCLUDE_DRIVER_UART_H_

#include "app_config.h"



bool uartInit(void);
bool uartOpen(uint8_t ch, uint32_t baud);
uint32_t uartAvailable(uint8_t ch);
uint8_t uartRead(uint8_t ch);
uint32_t uartWrite(uint8_t ch, uint8_t *p_data, uint32_t length);
uint32_t uartPrintf(uint8_t ch, char *fmt, ...);




#endif /* INCLUDE_DRIVER_UART_H_ */
