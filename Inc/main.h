/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include "stm32l4xx_hal.h"

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
#define JOY_SW_Pin GPIO_PIN_2
#define JOY_SW_GPIO_Port GPIOC
#define D4_Pin GPIO_PIN_4
#define D4_GPIO_Port GPIOA
#define D5_Pin GPIO_PIN_5
#define D5_GPIO_Port GPIOA
#define D6_Pin GPIO_PIN_6
#define D6_GPIO_Port GPIOA
#define D7_Pin GPIO_PIN_7
#define D7_GPIO_Port GPIOA
#define SPI2_CS_Pin GPIO_PIN_12
#define SPI2_CS_GPIO_Port GPIOB
#define RC522_RST_Pin GPIO_PIN_6
#define RC522_RST_GPIO_Port GPIOC
#define Light_SW_Pin GPIO_PIN_8
#define Light_SW_GPIO_Port GPIOC
#define LCD_ON_Pin GPIO_PIN_9
#define LCD_ON_GPIO_Port GPIOC
#define DP_Pin GPIO_PIN_8
#define DP_GPIO_Port GPIOA
#define DIG1_Pin GPIO_PIN_9
#define DIG1_GPIO_Port GPIOA
#define DIG2_Pin GPIO_PIN_10
#define DIG2_GPIO_Port GPIOA
#define DIG3_Pin GPIO_PIN_11
#define DIG3_GPIO_Port GPIOA
#define DIG4_Pin GPIO_PIN_12
#define DIG4_GPIO_Port GPIOA
#define RS_Pin GPIO_PIN_10
#define RS_GPIO_Port GPIOC
#define E_Pin GPIO_PIN_11
#define E_GPIO_Port GPIOC
#define SEG_A_Pin GPIO_PIN_3
#define SEG_A_GPIO_Port GPIOB
#define SEG_B_Pin GPIO_PIN_4
#define SEG_B_GPIO_Port GPIOB
#define SEG_C_Pin GPIO_PIN_5
#define SEG_C_GPIO_Port GPIOB
#define SEG_D_Pin GPIO_PIN_6
#define SEG_D_GPIO_Port GPIOB
#define SEG_E_Pin GPIO_PIN_7
#define SEG_E_GPIO_Port GPIOB
#define SEG_F_Pin GPIO_PIN_8
#define SEG_F_GPIO_Port GPIOB
#define SEG_G_Pin GPIO_PIN_9
#define SEG_G_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
