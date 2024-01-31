/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

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
#define LED_Pin GPIO_PIN_2
#define LED_GPIO_Port GPIOA

#define SW6_Pin GPIO_PIN_3
#define SW6_GPIO_Port GPIOA

#define SW5_Pin GPIO_PIN_4
#define SW5_GPIO_Port GPIOA

#define SW4_Pin GPIO_PIN_5
#define SW4_GPIO_Port GPIOA

#define NHOME1_Pin GPIO_PIN_6
#define NHOME1_GPIO_Port GPIOA
#define TIM3_CH2_STEPOUT1_Pin GPIO_PIN_7
#define TIM3_CH2_STEPOUT1_GPIO_Port GPIOA
#define ENABLE1_Pin GPIO_PIN_0
#define ENABLE1_GPIO_Port GPIOB
#define DIR_OUT1_Pin GPIO_PIN_1
#define DIR_OUT1_GPIO_Port GPIOB
#define DECAY1_Pin GPIO_PIN_2
#define DECAY1_GPIO_Port GPIOB
#define READ_FAULT1_Pin GPIO_PIN_10
#define READ_FAULT1_GPIO_Port GPIOB
#define NSLEEP1_Pin GPIO_PIN_12
#define NSLEEP1_GPIO_Port GPIOB
#define NRESET1_Pin GPIO_PIN_13
#define NRESET1_GPIO_Port GPIOB
#define ACS_CURRENT_Pin GPIO_PIN_8
#define ACS_CURRENT_GPIO_Port GPIOA
#define NHOME2_Pin GPIO_PIN_15
#define NHOME2_GPIO_Port GPIOA
#define TIM2_CH2_STEPOUT2_Pin GPIO_PIN_3
#define TIM2_CH2_STEPOUT2_GPIO_Port GPIOB
#define ENABLE2_Pin GPIO_PIN_4
#define ENABLE2_GPIO_Port GPIOB
#define DIR_OUT2_Pin GPIO_PIN_5
#define DIR_OUT2_GPIO_Port GPIOB
#define DECAY2_Pin GPIO_PIN_6
#define DECAY2_GPIO_Port GPIOB
#define READ_FAULT2_Pin GPIO_PIN_7
#define READ_FAULT2_GPIO_Port GPIOB
#define NSLEEP2_Pin GPIO_PIN_8
#define NSLEEP2_GPIO_Port GPIOB
#define NRESET2_Pin GPIO_PIN_9
#define NRESET2_GPIO_Port GPIOB
/* USER CODE BEGIN Private defines */

#define SET_DIR_1(x)   (x ? (HAL_GPIO_WritePin(DIR_OUT1_GPIO_Port,DIR_OUT1_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(DIR_OUT1_GPIO_Port,DIR_OUT1_Pin,GPIO_PIN_RESET)))
#define SET_DIR_2(x)   (x ? (HAL_GPIO_WritePin(DIR_OUT2_GPIO_Port,DIR_OUT2_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(DIR_OUT2_GPIO_Port,DIR_OUT2_Pin,GPIO_PIN_RESET)))


#define ENABLE_M_1(x)   (x ? (HAL_GPIO_WritePin(ENABLE1_GPIO_Port,ENABLE1_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(ENABLE1_GPIO_Port,ENABLE1_Pin,GPIO_PIN_RESET)))
#define ENABLE_M_2(x)   (x ? (HAL_GPIO_WritePin(ENABLE2_GPIO_Port,ENABLE2_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(ENABLE2_GPIO_Port,ENABLE2_Pin,GPIO_PIN_RESET)))

#define SLEEP_1(x)   (x ? (HAL_GPIO_WritePin(NSLEEP1_GPIO_Port,NSLEEP1_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(NSLEEP1_GPIO_Port,NSLEEP1_Pin,GPIO_PIN_RESET)))
#define SLEEP_2(x)   (x ? (HAL_GPIO_WritePin(NSLEEP2_GPIO_Port,NSLEEP2_Pin,GPIO_PIN_SET)):(HAL_GPIO_WritePin(NSLEEP2_GPIO_Port,NSLEEP2_Pin,GPIO_PIN_RESET)))




#define READ_SW1  HAL_GPIO_ReadPin( SW4_GPIO_Port , SW4_Pin )
#define READ_SW2  HAL_GPIO_ReadPin( SW5_GPIO_Port , SW5_Pin )
#define READ_SW3  HAL_GPIO_ReadPin( SW6_GPIO_Port , SW6_Pin )


#define LED_TGL HAL_GPIO_TogglePin(LED_GPIO_Port , LED_Pin)

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
