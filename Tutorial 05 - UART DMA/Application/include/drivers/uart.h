/*
 * uart.h
 *
 *  Created on: Sep 5, 2021
 *      Author: tocru
 */

#ifndef INCLUDE_DRIVERS_UART_H_
#define INCLUDE_DRIVERS_UART_H_


#include "bsp.h"

#ifdef USE_HW_UART

bool      uartInit(void);
uint8_t   uartRead(void);
void      uartDataIn(uint8_t rx_data);
uint32_t  uartWrite(uint8_t *p_data, uint32_t length);
uint32_t  uartGetBaud(void);
uint8_t  uartAvailable(void);

#endif




#endif /* INCLUDE_DRIVERS_UART_H_ */
