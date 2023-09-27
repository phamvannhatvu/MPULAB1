/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
enum TrafficLightState
{
	RED1_GREEN2,
	RED1_YELLOW2,
	GREEN1_RED2,
	YELLOW1_RED2
};

enum Led
{
	RED1,
	RED2,
	GREEN1,
	GREEN2,
	YELLOW1,
	YELLOW2
};
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void turnOnLight(enum Led);
void clearAllLed();

/* USER CODE BEGIN PFP */

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
  /* USER CODE BEGIN 2 */

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  turnOnLight(RED1);
  turnOnLight(GREEN1);
  uint8_t count = 3;
  uint8_t light = 5;
  uint8_t state = RED1_GREEN2;
  while (1)
  {
	switch (state)
	{
	case RED1_GREEN2:
		clearAllLed();
		turnOnLight(RED1);
		turnOnLight(GREEN2);
		--count;
		--light;
		if (count <= 0)
		{
			count = 2;
			state = RED1_YELLOW2;
		}
		break;
	case RED1_YELLOW2:
		clearAllLed();
		turnOnLight(RED1);
		turnOnLight(YELLOW2);
		--count;
		--light;
		if (count <= 0)
		{
			count = 3;
			light = 3;
			state = GREEN1_RED2;
		}
		break;
	case GREEN1_RED2:
		clearAllLed();
		turnOnLight(GREEN1);
		turnOnLight(RED2);
		--count;
		--light;
		if (count <= 0)
		{
			count = 2;
			light = 2;
			state = YELLOW1_RED2;
		}
		break;
	case YELLOW1_RED2:
		clearAllLed();
		turnOnLight(YELLOW1);
		turnOnLight(RED2);
		--count;
		--light;
		if (count <= 0)
		{
			count = 3;
			light = 5;
			state = RED1_GREEN2;
		}
		break;
	}
	HAL_Delay(1000);
  /* USER CODE END WHILE */

  /* USER CODE BEGIN 3 */
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
/* USER CODE BEGIN MX_GPIO_Init_1 */
/* USER CODE END MX_GPIO_Init_1 */

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOA_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOA, RED_LED1_Pin|YELLOW_LED1_Pin|GREEN_LED1_Pin|RED_LED2_Pin
                          |YELLOW_LED2_Pin|GREEN_LED2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pins : RED_LED1_Pin YELLOW_LED1_Pin GREEN_LED1_Pin RED_LED2_Pin
                           YELLOW_LED2_Pin GREEN_LED2_Pin */
  GPIO_InitStruct.Pin = RED_LED1_Pin|YELLOW_LED1_Pin|GREEN_LED1_Pin|RED_LED2_Pin
                          |YELLOW_LED2_Pin|GREEN_LED2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

/* USER CODE BEGIN MX_GPIO_Init_2 */
/* USER CODE END MX_GPIO_Init_2 */
}

/* USER CODE BEGIN 4 */
void clearAllLed()
{
    HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(RED_LED2_GPIO_Port, RED_LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin, GPIO_PIN_RESET);
    HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, GPIO_PIN_RESET);
}

void turnOnLight(enum Led led)
{
    switch (led)
    {
    case RED1:
        HAL_GPIO_WritePin(RED_LED1_GPIO_Port, RED_LED1_Pin, GPIO_PIN_SET);
        break;
    case GREEN1:
        HAL_GPIO_WritePin(GREEN_LED1_GPIO_Port, GREEN_LED1_Pin, GPIO_PIN_SET);
        break;
    case YELLOW1:
        HAL_GPIO_WritePin(YELLOW_LED1_GPIO_Port, YELLOW_LED1_Pin, GPIO_PIN_SET);
        break;
    case RED2:
        HAL_GPIO_WritePin(RED_LED2_GPIO_Port, RED_LED2_Pin, GPIO_PIN_SET);
        break;
    case GREEN2:
        HAL_GPIO_WritePin(GREEN_LED2_GPIO_Port, GREEN_LED2_Pin, GPIO_PIN_SET);
        break;
    case YELLOW2:
        HAL_GPIO_WritePin(YELLOW_LED2_GPIO_Port, YELLOW_LED2_Pin, GPIO_PIN_SET);
        break;
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
