/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx.h"

//MCAL
#include "BIT_MATH.h"
#include "GPIO_config.h"
#include "GPIO_interface.h"
#include "UART_config.h"
#include "UART_interface.h"
#include "EXTI_config.h"
#include "EXTI_interface.h"
#include "I2C_config.h"
#include "I2C_interface.h"
#include "AdvancedTIM_config.h"
#include "AdvancedTIM_interface.h"
#include "ADC_config.h"
#include "ADC_interface.h"

//HAL
#include"DCmotor_interface.h"
#include "MPU6050_config.h"
#include "MPU6050_interface.h"
#include "ENCODER_config.h"
#include "ENCODER_interface.h"
#include "PCA9685_config.h"
#include "PCA9685_interface.h"

//Controllers
#include"PID_interface.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
