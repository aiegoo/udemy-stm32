I2C_HandleTypeDef hi2c1;

int main(void)
{
  HAL_Init();
  
  SystemClock_Config();
  
  MX_GPIO_Init();
  MX_UART4_Init();
  MX_I2C1_Init();
  
  lcd16x2_i2c_init(&hi2c1);
  
  int count;
  while (1)
  {
    lcd16x2_i2c_1stLine();
	  lcd16x2_i2c_printf("COUNT : %d", count);
    count++;
  }
}
