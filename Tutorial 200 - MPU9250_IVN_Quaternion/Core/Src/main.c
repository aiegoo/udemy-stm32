/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2021 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under BSD 3-Clause license,
  * the "License"; You may not use this file except in compliance with the
  * License. You may obtain a copy of the License at:
  *                        opensource.org/licenses/BSD-3-Clause
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
//#include "m_motion.h"
//#include "mltypes.h"

#include "drv_mpu9250.h"


#include "inv_mpu.h"
#include "inv_mpu_dmp_motion_driver.h"
#include "invensense.h"
#include "invensense_adv.h"
#include "eMPL_outputs.h"
#include "mltypes.h"
#include "mpu.h"
#include "log.h"
#include "packet.h"



/* Data read from MPL. */
#define PRINT_ACCEL     (0x01)
#define PRINT_GYRO      (0x02)
#define PRINT_QUAT      (0x04)
#define PRINT_COMPASS   (0x08)
#define PRINT_EULER     (0x10)
#define PRINT_ROT_MAT   (0x20)
#define PRINT_HEADING   (0x40)
#define PRINT_PEDO      (0x80)
#define PRINT_LINEAR_ACCEL (0x100)
#define PRINT_GRAVITY_VECTOR (0x200)

#define ACCEL_ON        (0x01)
#define GYRO_ON         (0x02)
#define COMPASS_ON      (0x04)

#define MOTION          (0)
#define NO_MOTION       (1)

/* Starting sampling rate. */
#define DEFAULT_MPU_HZ  (20)

#define FLASH_SIZE      (512)
#define FLASH_MEM_START ((void*)0x1800)

#define PEDO_READ_MS    (1000)
#define TEMP_READ_MS    (500)
#define COMPASS_READ_MS (100)
struct rx_s {
    unsigned char header[3];
    unsigned char cmd;
};
struct hal_s {
    unsigned char lp_accel_mode;
    unsigned char sensors;
    unsigned char dmp_on;
    unsigned char wait_for_tap;
    volatile unsigned char new_gyro;
    unsigned char motion_int_mode;
    unsigned long no_dmp_hz;
    unsigned long next_pedo_ms;
    unsigned long next_temp_ms;
    unsigned long next_compass_ms;
    unsigned int report;
    unsigned short dmp_features;
    struct rx_s rx;
};
static struct hal_s hal = {0};

/* USB RX binary semaphore. Actually, it's just a flag. Not included in struct
 * because it's declared extern elsewhere.
 */
volatile unsigned char rx_new;

unsigned char *mpl_key = (unsigned char*)"eMPL 5.1";

/* Platform-specific information. Kinda like a boardfile. */
struct platform_data_s {
    signed char orientation[9];
};

/* The sensors can be mounted onto the board in any orientation. The mounting
 * matrix seen below tells the MPL how to rotate the raw data from the
 * driver(s).
 * TODO: The following matrices refer to the configuration on internal test
 * boards at Invensense. If needed, please modify the matrices to match the
 * chip-to-body matrix for your particular set up.
 */
static struct platform_data_s gyro_pdata = {
    .orientation = { 1, 0, 0,
                     0, 1, 0,
                     0, 0, 1}
};

#if defined MPU9150 || defined MPU9250
static struct platform_data_s compass_pdata = {
    .orientation = { 0, 1, 0,
                     1, 0, 0,
                     0, 0,-1}
};
#define COMPASS_ENABLED 1
#elif defined AK8975_SECONDARY
static struct platform_data_s compass_pdata = {
    .orientation = {-1, 0, 0,
                     0, 1, 0,
                     0, 0,-1}
};
#define COMPASS_ENABLED 1
#elif defined AK8963_SECONDARY
static struct platform_data_s compass_pdata = {
    .orientation = {-1, 0, 0,
                     0,-1, 0,
                     0, 0, 1}
};
#define COMPASS_ENABLED 1
#endif



/* Get data from MPL.
 * TODO: Add return values to the inv_get_sensor_type_xxx APIs to differentiate
 * between new and stale data.
 */
//static void read_from_mpl(void)
//{
//    long msg, data[9];
//    int8_t accuracy;
//    unsigned long timestamp;
//    float float_data[3] = {0};
//
//    if (inv_get_sensor_type_quat(data, &accuracy, (inv_time_t*)&timestamp)) {
//       /* Sends a quaternion packet to the PC. Since this is used by the Python
//        * test app to visually represent a 3D quaternion, it's sent each time
//        * the MPL has new data.
//        */
//        eMPL_send_quat(data);
//
//        /* Specific data packets can be sent or suppressed using USB commands. */
//        if (hal.report & PRINT_QUAT)
//            eMPL_send_data(PACKET_DATA_QUAT, data);
//    }
//
//    if (hal.report & PRINT_ACCEL) {
//        if (inv_get_sensor_type_accel(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_ACCEL, data);
//    }
//    if (hal.report & PRINT_GYRO) {
//        if (inv_get_sensor_type_gyro(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_GYRO, data);
//    }
//#ifdef COMPASS_ENABLED
//    if (hal.report & PRINT_COMPASS) {
//        if (inv_get_sensor_type_compass(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_COMPASS, data);
//    }
//#endif
//    if (hal.report & PRINT_EULER) {
//        if (inv_get_sensor_type_euler(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_EULER, data);
//    }
//    if (hal.report & PRINT_ROT_MAT) {
//        if (inv_get_sensor_type_rot_mat(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_ROT, data);
//    }
//    if (hal.report & PRINT_HEADING) {
//        if (inv_get_sensor_type_heading(data, &accuracy,
//            (inv_time_t*)&timestamp))
//            eMPL_send_data(PACKET_DATA_HEADING, data);
//    }
//    if (hal.report & PRINT_LINEAR_ACCEL) {
//        if (inv_get_sensor_type_linear_acceleration(float_data, &accuracy, (inv_time_t*)&timestamp)) {
//          MPL_LOGI("Linear Accel: %7.5f %7.5f %7.5f\r\n",
//              float_data[0], float_data[1], float_data[2]);
//         }
//    }
//    if (hal.report & PRINT_GRAVITY_VECTOR) {
//            if (inv_get_sensor_type_gravity(float_data, &accuracy,
//                (inv_time_t*)&timestamp))
//              MPL_LOGI("Gravity Vector: %7.5f %7.5f %7.5f\r\n",
//                  float_data[0], float_data[1], float_data[2]);
//    }
//    if (hal.report & PRINT_PEDO) {
//        unsigned long timestamp;
//        msp430_get_clock_ms(&timestamp);
//        if (timestamp > hal.next_pedo_ms) {
//            hal.next_pedo_ms = timestamp + PEDO_READ_MS;
//            unsigned long step_count, walk_time;
//            dmp_get_pedometer_step_count(&step_count);
//            dmp_get_pedometer_walk_time(&walk_time);
//            MPL_LOGI("Walked %ld steps over %ld milliseconds..\n", step_count,
//            walk_time);
//        }
//    }
//
//    /* Whenever the MPL detects a change in motion state, the application can
//     * be notified. For this example, we use an LED to represent the current
//     * motion state.
//     */
//    msg = inv_get_message_level_0(INV_MSG_MOTION_EVENT |
//            INV_MSG_NO_MOTION_EVENT);
//    if (msg) {
//        if (msg & INV_MSG_MOTION_EVENT) {
//            MPL_LOGI("Motion!\n");
//        } else if (msg & INV_MSG_NO_MOTION_EVENT) {
//            MPL_LOGI("No motion!\n");
//        }
//    }
//}

//#ifdef COMPASS_ENABLED
//void send_status_compass() {
//  long data[3] = { 0 };
//  int8_t accuracy = { 0 };
//  unsigned long timestamp;
//  inv_get_compass_set(data, &accuracy, (inv_time_t*) &timestamp);
//  MPL_LOGI("Compass: %7.4f %7.4f %7.4f ",
//      data[0]/65536.f, data[1]/65536.f, data[2]/65536.f);
//  MPL_LOGI("Accuracy= %d\r\n", accuracy);
//
//}
//#endif

/* Handle sensor on/off combinations. */
//static void setup_gyro(void)
//{
//    unsigned char mask = 0, lp_accel_was_on = 0;
//    if (hal.sensors & ACCEL_ON)
//        mask |= INV_XYZ_ACCEL;
//    if (hal.sensors & GYRO_ON) {
//        mask |= INV_XYZ_GYRO;
//        lp_accel_was_on |= hal.lp_accel_mode;
//    }
//#ifdef COMPASS_ENABLED
//    if (hal.sensors & COMPASS_ON) {
//        mask |= INV_XYZ_COMPASS;
//        lp_accel_was_on |= hal.lp_accel_mode;
//    }
//#endif
//    /* If you need a power transition, this function should be called with a
//     * mask of the sensors still enabled. The driver turns off any sensors
//     * excluded from this mask.
//     */
//    mpu_set_sensors(mask);
//    mpu_configure_fifo(mask);
//    if (lp_accel_was_on) {
//        unsigned short rate;
//        hal.lp_accel_mode = 0;
//        /* Switching out of LP accel, notify MPL of new accel sampling rate. */
//        mpu_get_sample_rate(&rate);
//        inv_set_accel_sample_rate(1000000L / rate);
//    }
//}

//static void tap_cb(unsigned char direction, unsigned char count)
//{
//    switch (direction) {
//    case TAP_X_UP:
//        MPL_LOGI("Tap X+ ");
//        break;
//    case TAP_X_DOWN:
//        MPL_LOGI("Tap X- ");
//        break;
//    case TAP_Y_UP:
//        MPL_LOGI("Tap Y+ ");
//        break;
//    case TAP_Y_DOWN:
//        MPL_LOGI("Tap Y- ");
//        break;
//    case TAP_Z_UP:
//        MPL_LOGI("Tap Z+ ");
//        break;
//    case TAP_Z_DOWN:
//        MPL_LOGI("Tap Z- ");
//        break;
//    default:
//        return;
//    }
//    MPL_LOGI("x%d\n", count);
//    return;
//}

//static void android_orient_cb(unsigned char orientation)
//{
//  switch (orientation) {
//  case ANDROID_ORIENT_PORTRAIT:
//        MPL_LOGI("Portrait\n");
//        break;
//  case ANDROID_ORIENT_LANDSCAPE:
//        MPL_LOGI("Landscape\n");
//        break;
//  case ANDROID_ORIENT_REVERSE_PORTRAIT:
//        MPL_LOGI("Reverse Portrait\n");
//        break;
//  case ANDROID_ORIENT_REVERSE_LANDSCAPE:
//        MPL_LOGI("Reverse Landscape\n");
//        break;
//  default:
//    return;
//  }
//}

//static inline void msp430_reset(void)
//{
//    PMMCTL0 |= PMMSWPOR;
//}


//static inline void run_self_test(void)
//{
//    int result;
//    long gyro[3], accel[3];
//
//#if defined (MPU6500) || defined (MPU9250)
//    result = mpu_run_6500_self_test(gyro, accel, 0);
//#elif defined (MPU6050) || defined (MPU9150)
//    result = mpu_run_self_test(gyro, accel);
//#endif
//    if (result == 0x7) {
//    MPL_LOGI("Passed!\n");
//        MPL_LOGI("accel: %7.4f %7.4f %7.4f\n",
//                    accel[0]/65536.f,
//                    accel[1]/65536.f,
//                    accel[2]/65536.f);
//        MPL_LOGI("gyro: %7.4f %7.4f %7.4f\n",
//                    gyro[0]/65536.f,
//                    gyro[1]/65536.f,
//                    gyro[2]/65536.f);
//        /* Test passed. We can trust the gyro data here, so now we need to update calibrated data*/
//
//#ifdef USE_CAL_HW_REGISTERS
//        /*
//         * This portion of the code uses the HW offset registers that are in the MPUxxxx devices
//         * instead of pushing the cal data to the MPL software library
//         */
//        unsigned char i = 0;
//
//        for(i = 0; i<3; i++) {
//          gyro[i] = (long)(gyro[i] * 32.8f); //convert to +-1000dps
//          accel[i] *=  2048.f; //convert to +-16G (bug fix from +-8G)
//          accel[i] = accel[i] >> 16;
//          gyro[i] = (long)(gyro[i] >> 16);
//        }
//
//        mpu_set_gyro_bias_reg(gyro);
//
//#if defined (MPU6500) || defined (MPU9250)
//        mpu_set_accel_bias_6500_reg(accel);
//#elif defined (MPU6050) || defined (MPU9150)
//        mpu_set_accel_bias_6050_reg(accel);
//#endif
//#else
//        /* Push the calibrated data to the MPL library.
//         *
//         * MPL expects biases in hardware units << 16, but self test returns
//     * biases in g's << 16.
//     */
//      unsigned short accel_sens;
//      float gyro_sens;
//
//    mpu_get_accel_sens(&accel_sens);
//    accel[0] *= accel_sens;
//    accel[1] *= accel_sens;
//    accel[2] *= accel_sens;
//    inv_set_accel_bias(accel, 3);
//    mpu_get_gyro_sens(&gyro_sens);
//    gyro[0] = (long) (gyro[0] * gyro_sens);
//    gyro[1] = (long) (gyro[1] * gyro_sens);
//    gyro[2] = (long) (gyro[2] * gyro_sens);
//    inv_set_gyro_bias(gyro, 3);
//#endif
//    }
//    else {
//            if (!(result & 0x1))
//                MPL_LOGE("Gyro failed.\n");
//            if (!(result & 0x2))
//                MPL_LOGE("Accel failed.\n");
//            if (!(result & 0x4))
//                MPL_LOGE("Compass failed.\n");
//     }
//
//}


/* Every time new gyro data is available, this function is called in an
 * ISR context. In this example, it sets a flag protecting the FIFO read
 * function.
 */
static void gyro_data_ready_cb(void)
{
    hal.new_gyro = 1;
}









/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
#define MPU9250_ADDRESS     (0x68 << 1)

uint8_t data[2] = {0,};
uint8_t recvData[1] = {0,};
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
int _write(int file, char *ptr, int len)
{
  HAL_UART_Transmit(&huart1, (uint8_t *)ptr, len, 10);
  return len;
}
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_USART1_UART_Init();
  MX_SPI1_Init();
  MX_TIM3_Init();
  MX_I2C1_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */






  printf("Application Start ---------------------------\n\r");

  drv_mpu9250_init_t mpu_param;
  mpu_param.I2Chnd = &hi2c1;
  drv_mpu9250_init(&mpu_param);



  inv_error_t result;
  unsigned char accel_fsr,  new_temp = 0;
  unsigned short gyro_rate, gyro_fsr;
  unsigned long timestamp;
  struct int_param_s int_param;

  #ifdef COMPASS_ENABLED
      unsigned char new_compass = 0;
      unsigned short compass_fsr;
  #endif

  int_param.cb = gyro_data_ready_cb;
  result = mpu_init(&int_param);
  if (result) {
      MPL_LOGE("Could not initialize gyro.\n");
//      msp430_reset();
  }

  result = inv_init_mpl();
  if (result) {
      MPL_LOGE("Could not initialize MPL.\n");
//      msp430_reset();
  }

  /* Compute 6-axis and 9-axis quaternions. */
  inv_enable_quaternion();
  inv_enable_9x_sensor_fusion();

  inv_enable_fast_nomot();
  inv_enable_gyro_tc();

#ifdef COMPASS_ENABLED
    /* Compass calibration algorithms. */
    inv_enable_vector_compass_cal();
    inv_enable_magnetic_disturbance();
#endif

    /* Allows use of the MPL APIs in read_from_mpl. */
    inv_enable_eMPL_outputs();

    result = inv_start_mpl();
    if (result == INV_ERROR_NOT_AUTHORIZED) {
        while (1) {
            MPL_LOGE("Not authorized.\n");
            delay_ms(5000);
        }
    }
    if (result) {
        MPL_LOGE("Could not start the MPL.\n");
//        msp430_reset();
    }


    /* Get/set hardware configuration. Start gyro. */
        /* Wake up all sensors. */
    #ifdef COMPASS_ENABLED
        mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL | INV_XYZ_COMPASS);
    #else
        mpu_set_sensors(INV_XYZ_GYRO | INV_XYZ_ACCEL);
    #endif
        /* Push both gyro and accel data into the FIFO. */
        mpu_configure_fifo(INV_XYZ_GYRO | INV_XYZ_ACCEL);
        mpu_set_sample_rate(DEFAULT_MPU_HZ);
    #ifdef COMPASS_ENABLED
        /* The compass sampling rate can be less than the gyro/accel sampling rate.
         * Use this function for proper power management.
         */
        mpu_set_compass_sample_rate(1000 / COMPASS_READ_MS);
    #endif
        /* Read back configuration in case it was set improperly. */
        mpu_get_sample_rate(&gyro_rate);
        mpu_get_gyro_fsr(&gyro_fsr);
        mpu_get_accel_fsr(&accel_fsr);
    #ifdef COMPASS_ENABLED
        mpu_get_compass_fsr(&compass_fsr);
    #endif
        /* Sync driver configuration with MPL. */
        /* Sample rate expected in microseconds. */
        inv_set_gyro_sample_rate(1000000L / gyro_rate);
        inv_set_accel_sample_rate(1000000L / gyro_rate);
    #ifdef COMPASS_ENABLED
        /* The compass rate is independent of the gyro and accel rates. As long as
         * inv_set_compass_sample_rate is called with the correct value, the 9-axis
         * fusion algorithm's compass correction gain will work properly.
         */
        inv_set_compass_sample_rate(COMPASS_READ_MS * 1000L);
    #endif
        /* Set chip-to-body orientation matrix.
         * Set hardware units to dps/g's/degrees scaling factor.
         */
        inv_set_gyro_orientation_and_scale(
                inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
                (long)gyro_fsr<<15);
        inv_set_accel_orientation_and_scale(
                inv_orientation_matrix_to_scalar(gyro_pdata.orientation),
                (long)accel_fsr<<15);
    #ifdef COMPASS_ENABLED
        inv_set_compass_orientation_and_scale(
                inv_orientation_matrix_to_scalar(compass_pdata.orientation),
                (long)compass_fsr<<15);
    #endif
        /* Initialize HAL state variables. */
    #ifdef COMPASS_ENABLED
        hal.sensors = ACCEL_ON | GYRO_ON | COMPASS_ON;
    #else
        hal.sensors = ACCEL_ON | GYRO_ON;
    #endif
        hal.dmp_on = 0;
        hal.report = 0;
        hal.rx.cmd = 0;
        hal.next_pedo_ms = 0;
        hal.next_compass_ms = 0;
        hal.next_temp_ms = 0;

        /* Compass reads are handled by scheduler. */
        get_tick_count(&timestamp);


    if (dmp_load_motion_driver_firmware()) {
            MPL_LOGE("Could not download DMP.\n");
//            msp430_reset();
    }
    dmp_set_orientation(
        inv_orientation_matrix_to_scalar(gyro_pdata.orientation));
//    dmp_register_tap_cb(tap_cb);
//    dmp_register_android_orient_cb(android_orient_cb);
    /*
     * Known Bug -
     * DMP when enabled will sample sensor data at 200Hz and output to FIFO at the rate
     * specified in the dmp_set_fifo_rate API. The DMP will then sent an interrupt once
     * a sample has been put into the FIFO. Therefore if the dmp_set_fifo_rate is at 25Hz
     * there will be a 25Hz interrupt from the MPU device.
     *
     * There is a known issue in which if you do not enable DMP_FEATURE_TAP
     * then the interrupts will be at 200Hz even if fifo rate
     * is set at a different rate. To avoid this issue include the DMP_FEATURE_TAP
     *
     * DMP sensor fusion works only with gyro at +-2000dps and accel +-2G
     */
    hal.dmp_features = DMP_FEATURE_6X_LP_QUAT | DMP_FEATURE_TAP |
        DMP_FEATURE_ANDROID_ORIENT | DMP_FEATURE_SEND_RAW_ACCEL | DMP_FEATURE_SEND_CAL_GYRO |
        DMP_FEATURE_GYRO_CAL;
    dmp_enable_feature(hal.dmp_features);
    dmp_set_fifo_rate(DEFAULT_MPU_HZ);
    inv_set_quat_sample_rate(1000000L / DEFAULT_MPU_HZ);
    mpu_set_dmp_state(1);
    hal.dmp_on = 1;







  /* USER CODE END 2 */


  while (1)
  {
    HAL_GPIO_TogglePin(GPIOG, GPIO_PIN_13);
//    HAL_Delay(100);

    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */


    unsigned long sensor_timestamp;
    int new_data = 0;

#ifdef COMPASS_ENABLED
    /* We're not using a data ready interrupt for the compass, so we'll
     * make our compass reads timer-based instead.
     */
    if ((timestamp > hal.next_compass_ms) && !hal.lp_accel_mode &&
        hal.new_gyro && (hal.sensors & COMPASS_ON)) {
        hal.next_compass_ms = timestamp + COMPASS_READ_MS;
        new_compass = 1;
    }
#endif

//    short accel_short[3];
//    long accel[3];
//    mpu_get_accel_reg(accel_short, &sensor_timestamp);
//    accel[0] = (long)accel_short[0];
//    accel[1] = (long)accel_short[1];
//    accel[2] = (long)accel_short[2];
//    inv_build_accel(accel, 0, sensor_timestamp);
//    printf("Acc: %d, %d, %d\n\r", accel[0], accel[1], accel[2]);


    short gyro[3], accel_short[3], sensors;
    unsigned char more;
    long accel[3], quat[4], temperature;

    dmp_read_fifo(gyro, accel_short, quat, &sensor_timestamp, &sensors, &more);
    inv_build_quat(quat, 0, sensor_timestamp);

    printf("quat: %d, %d, %d, %d\n\r", quat[0], quat[1], quat[2], quat[3]);


  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE3);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 64;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* USART1_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(USART1_IRQn);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
