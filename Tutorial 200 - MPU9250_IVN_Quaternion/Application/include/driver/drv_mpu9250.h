/*
 * Reference GitHub Link : https://github.com/Tanba28/MPU9250-via-SPI
 */

#ifndef __MPU9250_H__
#define __MPU9250_H__

#include "bsp.h"


typedef struct
{
  I2C_HandleTypeDef       * I2Chnd
}drv_mpu9250_init_t;


uint32_t drv_mpu9250_init(drv_mpu9250_init_t * p_params);
int drv_mpu9250_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const * p_data);
int drv_mpu9250_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char * data);


#endif
