/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "adc.h"
#include "dma.h"
#include "rtc.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include "MFRC522.h"
#include <string.h>
#include <stdio.h>
#include "lcd16x2.h"
#include "seg7.h"
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

char* keyID;
_Bool ActiveLCD=false;
volatile uint16_t joystick[2];
uint8_t MenuPosition;
uint8_t MarkerPosition;
RTC_TimeTypeDef time;
RTC_DateTypeDef date;
int value = 0;

const char* jsos = "3\n";
const char* weather = "4\n";
const char* techno = "5\n";

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

int __io_putchar(int ch);
void DoItem(uint8_t Marker,uint8_t Menu);
void EditTime(void);
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);

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
  MX_USART2_UART_Init();
  MX_DMA_Init();
  MX_ADC1_Init();
  MX_SPI2_Init();
  MX_TIM6_Init();
  MX_RTC_Init();
  /* USER CODE BEGIN 2 */


   HAL_GPIO_WritePin(RC522_RST_GPIO_Port, RC522_RST_Pin, GPIO_PIN_SET);
   MFRC522_Init();

   HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);
   lcd16x2_init_4bits(RS_GPIO_Port, RS_Pin, E_Pin,D4_GPIO_Port, D4_Pin, D5_Pin, D6_Pin, D7_Pin);
   lcd16x2_printf("");
   lcd16x2_cursorShow(false);
   _ActiveLight=false;

   HAL_TIM_Base_Start_IT(&htim6);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
while (1){

	if(MFRC522_IsDetected()){
		keyID = MFRC522_ReturnHexKey();
	  	if( strcmp(keyID,RC522_Card)==0  && !ActiveLCD){
	  		ActiveLCD = true;
	  		HAL_GPIO_WritePin(LCD_ON_GPIO_Port, LCD_ON_Pin, GPIO_PIN_SET);
	  		HAL_ADC_Start_DMA(&hadc1, (uint32_t*)joystick , 2);
	  		lcd16x2_Animation();
	  		MenuPosition=0;
	  		MarkerPosition=0;
	  		lcd16x2_showMenu(MenuPosition);
	  		lcd16x2_shiftMarker(MarkerPosition);
	  	}
	  	else if ( strcmp(keyID, RC522_Pendant)==0){
	  		ActiveLCD = false;
	  		HAL_ADC_Stop_DMA(&hadc1);
	  		lcd16x2_clear();
	  		lcd16x2_Animation();
	  		lcd16x2_clear();
	  		HAL_GPIO_WritePin(LCD_ON_GPIO_Port, LCD_ON_Pin, GPIO_PIN_RESET);
	  	}
	}

if(ActiveLCD){
	if(joystick[0]>3000){
		if(MarkerPosition==1 && MenuPosition==MAXMENU){
			MarkerPosition=0;
			MenuPosition=0;
			lcd16x2_showMenu(MenuPosition);
			lcd16x2_shiftMarker(MarkerPosition);
			HAL_Delay(200);
		}
		else if(MarkerPosition==0){
			MarkerPosition=1;
			lcd16x2_shiftMarker(MarkerPosition);
			HAL_Delay(200);
		}
		else {
			MenuPosition+=1;
			lcd16x2_showMenu(MenuPosition);
			lcd16x2_shiftMarker(MarkerPosition);
			HAL_Delay(200);
		}
	}

	if(joystick[0]<1000){
			if(MarkerPosition==1){
				MarkerPosition=0;
				lcd16x2_shiftMarker(MarkerPosition);
				HAL_Delay(200);
			}
			else if(MenuPosition!=0){
				MenuPosition-=1;
				lcd16x2_showMenu(MenuPosition);
				lcd16x2_shiftMarker(MarkerPosition);
				HAL_Delay(200);
			}
		}
	if(HAL_GPIO_ReadPin(JOY_SW_GPIO_Port, JOY_SW_Pin)==GPIO_PIN_RESET){
		DoItem(MarkerPosition, MenuPosition);
		HAL_Delay(200);
	}
}

	HAL_Delay(50);


    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
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
  if (HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_LSI|RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.LSIState = RCC_LSI_ON;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_6;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_MSI;
  RCC_OscInitStruct.PLL.PLLM = 1;
  RCC_OscInitStruct.PLL.PLLN = 40;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV7;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV2;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */
int __io_putchar(int ch){
	if (ch == '\n'){
			__io_putchar('\r');
	}

			HAL_UART_Transmit(&huart2, (uint8_t*)&ch, 1, HAL_MAX_DELAY);

			return 1;
}


void DoItem(uint8_t Marker,uint8_t Menu){
	if(Marker==0){
		switch(Menu){
		case 0:
				if(_ActiveLight){
					HAL_GPIO_WritePin(Light_SW_GPIO_Port, Light_SW_Pin, GPIO_PIN_RESET);
					_ActiveLight=false;
					lcd16x2_showMenu(MenuPosition);
					lcd16x2_shiftMarker(MarkerPosition);
				}
				else{
					HAL_GPIO_WritePin(Light_SW_GPIO_Port, Light_SW_Pin, GPIO_PIN_SET);
					_ActiveLight=true;
					lcd16x2_showMenu(MenuPosition);
					lcd16x2_shiftMarker(MarkerPosition);
				}
				break;
		case 1:
				HAL_Delay(200);
				EditTime();
				break;
		case 2: printf(jsos);
				break;
		case 3: printf(weather);
				break;
		}
	} else {
		switch(Menu){
		case 0:
			HAL_Delay(200);
			EditTime();
			break;
		case 1:
			printf(jsos);
			break;
		case 2:
			printf(weather);
			break;
		case 3:
			printf(techno);
			HAL_Delay(5500);
			for(int i=0;i<30;i++){
				HAL_GPIO_WritePin(Light_SW_GPIO_Port, Light_SW_Pin, GPIO_PIN_SET);
				HAL_Delay(100);
				HAL_GPIO_WritePin(Light_SW_GPIO_Port, Light_SW_Pin, GPIO_PIN_RESET);
				HAL_Delay(100);
			}
			break;
		}
	}
}

void EditTime(void){
	_Bool HoursOK=false;

	while(HAL_GPIO_ReadPin(JOY_SW_GPIO_Port, JOY_SW_Pin)!=GPIO_PIN_RESET){

		while(HAL_GPIO_ReadPin(JOY_SW_GPIO_Port, JOY_SW_Pin)!=GPIO_PIN_RESET && !HoursOK){
			if(joystick[0]>3000){
				if(time.Hours!=23)
					time.Hours++;
				else time.Hours=0;
				HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
			//	HAL_Delay(150);
			}else if(joystick[0]<1000){
				if(time.Hours!=0)
					time.Hours--;
				else time.Hours=23;
				HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
			//	HAL_Delay(150);
			}
			HAL_Delay(150);
		}

		if(!HoursOK)
			HAL_Delay(200);
		HoursOK=true;

		if(joystick[0]>3000){
			if(time.Minutes!=59)
				time.Minutes++;
			else time.Minutes=0;
			HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
		}else if(joystick[0]<1000){
			if(time.Minutes!=0)
				time.Minutes--;
			else time.Minutes=59;
			HAL_RTC_SetTime(&hrtc, &time, RTC_FORMAT_BIN);
			//HAL_Delay(150);
		}
		HAL_Delay(150);
	}
	HAL_Delay(200);

}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim == &htim6) {
		HAL_RTC_GetTime(&hrtc, &time, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &date, RTC_FORMAT_BIN);
		seg7_show((uint32_t)seg7_TimeToInt());
		seg7_update();
	}
}





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

