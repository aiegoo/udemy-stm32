/*
 * app_config.h
 *
 *  Created on: Sep 11, 2021
 *      Author: tocru
 */

#ifndef CONFIG_APP_CONFIG_H_
#define CONFIG_APP_CONFIG_H_

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#include "stm32f4xx_hal.h"



#define UART_MAX_CH       2

#define DEF_UART1         0
#define DEF_UART2         1

#define UART_RINGBUFFER_LENGTH    256



#endif /* CONFIG_APP_CONFIG_H_ */
