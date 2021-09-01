# LED Project

- Add Custom project into Basic project structure

#### 1. Create STM32CubeMX project

- STM32CubeMX project and save into <b>project>src>lib</b> folder

#### 2. Exclude Core folder from Build process

- Project folder > src > lib > Cube_STM32H750 > Core : Mouse right click
- Resource Configurations > Exclude from Build...

#### 3. Add include path

<img src="../images/led_include_path.png"></img>

#### 4. Add MCU type into preprocess

- MCU Type is in the stm32h7xx.h header file list

<img src="../images/preprocessor.png"></img>

### 5. Some file copy to my project folder

- lib > Cube_STM32H750 > Core > Inc
    - stm32h7xx_hal-conf.h
    - stm32h7xx_it.h

- lib > Cube_STM32H750 > Core > Src
    - stm32h7xx_hal_msp.c
    - stm32h7xx_it.c
    - system_stm32h7xx.c

<img src="../images/file_copy_to_myproject.png"></img>



