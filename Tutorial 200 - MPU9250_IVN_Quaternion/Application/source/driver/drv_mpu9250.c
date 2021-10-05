/*
 * Reference GitHub Link : https://github.com/Tanba28/MPU9250-via-SPI
 */

#include "drv_mpu9250.h"
#include "mltypes.h"

extern I2C_HandleTypeDef hi2c1;

static struct
{
    I2C_HandleTypeDef       * I2Chnd;           ///< TWI configuration.
    void                      (*cb)(void);      ///< Callback. Invoked when a pin interrupt is caught by GPIOTE.
    bool                      initialized;      ///< Module initialized.
    bool                      int_registered;   ///<
    bool                      enabled;          ///< Driver enabled.
    uint32_t                  evt_sheduled;     ///< Number of scheduled events.
} m_mpu9250 = {.initialized = false, .int_registered = false};




uint32_t drv_mpu9250_init(drv_mpu9250_init_t * p_params)
{
  m_mpu9250.I2Chnd = &hi2c1;
  m_mpu9250.initialized = true;
  m_mpu9250.enabled     = false;
  m_mpu9250.evt_sheduled = 0;

  return HAL_OK;
}




/**@brief Function to init / allocate the TWI module
 */
static __inline uint32_t i2c_open(void)
{
  uint32_t err_code;

  err_code = HAL_I2C_Init(m_mpu9250.I2Chnd);
  if (err_code != HAL_OK)
  {
    printf("HAL_I2C_Init Error\n\r");
  }

  return err_code;
}


/**@brief Function to deinit the TWI module when this driver does not need to
 *        communicate on the TWI bus, so that other drivers can use the module.
 */
static __inline uint32_t i2c_close(void)
{
  uint32_t err_code;

  err_code = HAL_I2C_DeInit(m_mpu9250.I2Chnd);
  if (err_code != HAL_OK)
  {
    printf("HAL_I2C_DeInit Error\n\r");
  }

  return err_code;
}

int drv_mpu9250_write(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char const * p_data)
{
  uint32_t err_code;
  uint8_t buffer[length+1];
  buffer[0] = reg_addr;
  memcpy(&buffer[1], p_data, length);

//  err_code = HAL_I2C_Master_Transmit(m_mpu9250.I2Chnd, slave_addr, buffer, length+1, 100);
//  if (err_code != HAL_OK)
//  {
//    printf("drv_mpu9250_write Error\n\r");
//  }

  err_code = HAL_I2C_Master_Transmit(m_mpu9250.I2Chnd, (slave_addr<<1), buffer, length+1, 100);
  if (err_code != HAL_OK)
  {
    printf("drv_mpu9250_write Error\n\r");
  }

  return 0;
}


int drv_mpu9250_read(unsigned char slave_addr, unsigned char reg_addr, unsigned char length, unsigned char * data)
{
  uint32_t err_code;

//  err_code = HAL_I2C_Master_Transmit(m_mpu9250.I2Chnd, slave_addr, &reg_addr, 1, 100);
//  if (err_code != HAL_OK)
//  {
//    printf("drv_mpu9250_read Error\n\r");
//  }
//
//  err_code = HAL_I2C_Master_Receive(m_mpu9250.I2Chnd, slave_addr, data, length, 100);
//  if (err_code != HAL_OK)
//  {
//    printf("drv_mpu9250_read Error\n\r");
//  }

  err_code = HAL_I2C_Master_Transmit(m_mpu9250.I2Chnd, (slave_addr<<1), &reg_addr, 1, 100);
  if (err_code != HAL_OK)
  {
    printf("drv_mpu9250_read Error\n\r");
  }

  err_code = HAL_I2C_Master_Receive(m_mpu9250.I2Chnd, (slave_addr<<1), data, length, 100);
  if (err_code != HAL_OK)
  {
    printf("drv_mpu9250_read Error\n\r");
  }

  return 0;
}




