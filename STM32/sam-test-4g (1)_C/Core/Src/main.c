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
//#include "gps_parcer.h"


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
uint8_t rxData[40];
uint8_t n=0;
uint8_t i=0;
uint8_t rxindex=0;
uint8_t newmesure=1;
uint8_t rxBuffer[40];
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
UART_HandleTypeDef huart1;
UART_HandleTypeDef huart2;
UART_HandleTypeDef huart4;

/* USER CODE BEGIN PV */







/*void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
// if (huart->Instance = USART1){
	 HAL_UART_Receive_IT(&huart1,(uint8_t)(rxData+n),1);
	 n=n+1;
	 if (n>=10){
		 n=0;
	 }


//	}
}
*/

/*
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){

	if (rxData[0]==13){ // || rxData[0]=='\r\n'
			rxindex=0;
			newmesure=1;
	}
	else{
		rxBuffer[rxindex]=rxData[0];
		rxindex++;
		if (rxindex>20)
			rxindex=0;
	 }
	 HAL_UART_Receive_IT(&huart1,(uint8_t)(rxData+n),1);
}

*/

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
for (i=0 ; i < 20 ; i = i + 1) {
	rxBuffer[rxindex]=rxData[i];
		rxindex++;
	HAL_UART_Receive_IT(&huart1,(uint8_t)(rxData+n),1);

}
}
/*






/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART1_UART_Init(void);
static void MX_USART4_UART_Init(void);
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

			/*code d'un projet git récuperation données GPS (NMEA)*/

	/**
	 * @brief  Retrieving specific part of the string
	 * @param  Pointer to input string
	 * @param  Start position of the required part of the string
	 * @param  Length of the required part of the string
	 * @retval Constant pointer to a resulting string
	 */

/*	const char* subString(const char* in_str, int8_t offset, int8_t len) {
	    int8_t instr_length = strlen(in_str);
	    if (offset + len > instr_length) {
	        return NULL;
	    }
	    char *outstr = malloc((sizeof(in_str)+1));
	    strncpy(outstr, in_str + offset, len);
	    strcat(outstr, "\0");
	    return outstr;
	}

	/**
	 * @brief  Truncate the income string by delimeter
	 * @param  Input array of chars (array of chars as a string required by strtok)
	 * @param  Output array of strings
	 * @param  char Delimeter
	 * @retval Number of elements in result array
	 */
	/*int32_t truncateStr(char instr[], char *outstr[], const char delimeter) {
	    char *tempBuff;
	    int32_t numberOfRawsOutArray = 0;
	    tempBuff = strtok(instr, &delimeter);
	    while (tempBuff != NULL) {
	        strcpy(outstr[numberOfRawsOutArray], tempBuff);//(outstr[numberOfRawsOutArray], tempBuff);
	        strcat(outstr[numberOfRawsOutArray], "\0");
	        numberOfRawsOutArray++;
	        tempBuff = strtok(NULL, &delimeter);
	    }
	    return numberOfRawsOutArray;
	}

	/**
	 * @brief  Parsing truncated array as a GGA NMEA message to a struct
	 * @param  Input array of chars (array of chars as a string required by strtok)
	 * @param  Number of rows in input array of truncated array
	 * @retval Struct with parsed GGA NMEA message
	 */
/*	GPGGA_Message parseGPGGA(char* inStrMessage[], int32_t numb_of_raws){
		GPGGA_Message gpggam_data;
	    gpggam_data.utc_time[0] = atoi(subString(inStrMessage[1],0,2));
	    gpggam_data.utc_time[1] = atoi(subString(inStrMessage[1],2,2));
	    gpggam_data.utc_time[2] = atoi(subString(inStrMessage[1],4,2));

	    gpggam_data.latitude = atof(subString(inStrMessage[2],0,8));
	    gpggam_data.lat_direction = *subString(inStrMessage[3],0,1);
	    gpggam_data.longitude = atof(subString(inStrMessage[4],0,8));
	    gpggam_data.lon_direction = *subString(inStrMessage[5],0,1);
	    gpggam_data.fix_quality = atoi(subString(inStrMessage[6],0,1));
	    gpggam_data.num_sattelites = atoi(subString(inStrMessage[7],0,2));
	    gpggam_data.h_duration = atof(subString(inStrMessage[8],0,3));
	    gpggam_data.altitude = atof(subString(inStrMessage[9],0,5));
	    gpggam_data.altitude_unit = *subString(inStrMessage[10],0,1);
	    gpggam_data.height_of_geoid = atof(subString(inStrMessage[11],0,4));
	    gpggam_data.hog_unit = *subString(inStrMessage[12],0,1);
	    gpggam_data.checksum = strtoul(subString(inStrMessage[13],1,2), NULL, 16);
	    return gpggam_data;
	}

	/**
	 * @brief  Printing GGA NMEA message back to UART
	 * @param  Structure with parsed GGA NMEA data
	 * @retval None
	 */
/*	void uart_print_gpgga_message(const GPGGA_Message *gpgga_data){
		printf("\r\nTime: %d:%d:%d UTC\r\n",gpgga_data->utc_time[0],gpgga_data->utc_time[1],gpgga_data->utc_time[2]);
		printf("Latitude: %.3f", 1234.1234);
	    printf(" %c \r\n", gpgga_data->lat_direction);
	    printf("Longitude: %f ", gpgga_data->longitude);
	    printf(" %c \r\n", gpgga_data->lon_direction);
	    printf("Fix quality: %d \r\n", gpgga_data->fix_quality);
	    printf("Number of satellites: %d \r\n", gpgga_data->num_sattelites);
	    printf("Horizontal dilution: %f \r\n", gpgga_data->h_duration);
	    printf("Altitude: %f", gpgga_data->altitude);
	    printf(" %c \r\n", gpgga_data->altitude_unit);
	    printf("Height of geoid: %f", gpgga_data->height_of_geoid);
	    printf(" %c \r\n", gpgga_data->hog_unit);
	    printf("Checksum: %lu ~\r\n", gpgga_data->checksum);
	}




*/

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
  MX_USART1_UART_Init();
  MX_USART4_UART_Init();
  /* USER CODE BEGIN 2 */
  HAL_UART_Receive_IT(&huart1,rxData,1);
  /* USER CODE END 2 */
/*  HAL_StatusTypeDef HAL_UART_Transmit(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  HAL_StatusTypeDef HAL_UART_Receive(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size, uint32_t Timeout);
  HAL_StatusTypeDef HAL_UART_Transmit_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
  HAL_StatusTypeDef HAL_UART_Receive_IT(UART_HandleTypeDef *huart, uint8_t *pData, uint16_t Size);
 */
  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  	 //HAL_UART_Transmit_IT(&huart1,"AT+CGPS=1\r\n",11);
  	 //HAL_UART_Transmit_IT(&huart1,"AT+CPIN=1234\r\n",14);
 	 HAL_UART_Transmit_IT(&huart1,"AT+CGPSINFO\r\n",13);
 	 //HAL_UART_Transmit_IT(&huart1,"AT+cmgr=1\r\n",11);
    //HAL_UART_Transmit_IT(&huart1,"\r\n\x1A",3);


 	 /* test d'envoie d'un message (fonctionne OK)
 	HAL_UART_Transmit_IT(&huart1,"AT+cmgs=\"+33631360334\"\r\n",23);
 	HAL_Delay(1000);
 	HAL_UART_Transmit_IT(&huart1,"kiwi du mardi\x1A",14);
 	
*/

 	 //HAL_UART_Transmit_IT(&huart1,"AT+cmgr=1\r\n",11);
 	 //HAL_UART_Transmit_IT(&huart1,"AT+cmgr=1\r\n",11);


 	 HAL_UART_Receive_IT(&huart1,rxData,1);


 while (1)
  {
    /* USER CODE END WHILE */
    /* USER CODE BEGIN 3 */


	 //printf("Kiwi du Lundi");
	 //Avec la carte Kiwi tu paies moitié prix
	 HAL_Delay(3000);
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
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Configure the main internal regulator output voltage
  */
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_MSI;
  RCC_OscInitStruct.MSIState = RCC_MSI_ON;
  RCC_OscInitStruct.MSICalibrationValue = 0;
  RCC_OscInitStruct.MSIClockRange = RCC_MSIRANGE_5;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_MSI;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_0) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_USART2;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.Usart2ClockSelection = RCC_USART2CLKSOURCE_PCLK1;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief USART1 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART1_UART_Init(void)
{

  /* USER CODE BEGIN USART1_Init 0 */

  /* USER CODE END USART1_Init 0 */

  /* USER CODE BEGIN USART1_Init 1 */

  /* USER CODE END USART1_Init 1 */
  huart1.Instance = USART1;
  huart1.Init.BaudRate = 115200;
  huart1.Init.WordLength = UART_WORDLENGTH_8B;
  huart1.Init.StopBits = UART_STOPBITS_1;
  huart1.Init.Parity = UART_PARITY_NONE;
  huart1.Init.Mode = UART_MODE_TX_RX;
  huart1.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart1.Init.OverSampling = UART_OVERSAMPLING_16;
  huart1.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart1.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART1_Init 2 */

  /* USER CODE END USART1_Init 2 */

}

/**
  * @brief USART2 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART2_UART_Init(void)
{

  /* USER CODE BEGIN USART2_Init 0 */

  /* USER CODE END USART2_Init 0 */

  /* USER CODE BEGIN USART2_Init 1 */

  /* USER CODE END USART2_Init 1 */
  huart2.Instance = USART2;
  huart2.Init.BaudRate = 115200;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */

  /* USER CODE END USART2_Init 2 */

}

/**
  * @brief USART4 Initialization Function
  * @param None
  * @retval None
  */
static void MX_USART4_UART_Init(void)
{

  /* USER CODE BEGIN USART4_Init 0 */

  /* USER CODE END USART4_Init 0 */

  /* USER CODE BEGIN USART4_Init 1 */

  /* USER CODE END USART4_Init 1 */
  huart4.Instance = USART4;
  huart4.Init.BaudRate = 115200;
  huart4.Init.WordLength = UART_WORDLENGTH_8B;
  huart4.Init.StopBits = UART_STOPBITS_1;
  huart4.Init.Parity = UART_PARITY_NONE;
  huart4.Init.Mode = UART_MODE_TX_RX;
  huart4.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart4.Init.OverSampling = UART_OVERSAMPLING_16;
  huart4.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
  huart4.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
  if (HAL_UART_Init(&huart4) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART4_Init 2 */

  /* USER CODE END USART4_Init 2 */

}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOH_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pins : PB6 PB8 PB9 */
  GPIO_InitStruct.Pin = GPIO_PIN_6|GPIO_PIN_8|GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

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


