/* USER CODE BEGIN Header */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <string.h>
#include <stdarg.h>
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
 CAN_HandleTypeDef hcan;

UART_HandleTypeDef huart2;

/* USER CODE BEGIN PV */
volatile uint8_t recvFlag = 0;
volatile uint8_t recvUart = 0;
uint16_t ODBfilterID = 0;
uint16_t ODBfilterMaskID = 0xFFFF;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_CAN_Init(void);
/* USER CODE BEGIN PFP */
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

CAN_TxHeaderTypeDef TxHeader;
CAN_RxHeaderTypeDef RxHeader;

uint32_t TxMailbox;
uint8_t TxData[8];
uint8_t RxData[8];

uint8_t count = 0;

uint8_t ramka_uart[11];
uint8_t ramka_config[7];

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
	recvUart = 1;
	HAL_UART_Receive_IT(&huart2, ramka_config, 7); // Ponowne włączenie nasłuchiwania
}

void myprintf(const char *fmt, ...) {
	static char buffer[40];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buffer, sizeof(buffer), fmt, args);
	va_end(args);
	int len = strlen(buffer);

	HAL_UART_Transmit(&huart2, (uint8_t*) buffer, len, -1);

}

void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan) {
	HAL_CAN_GetRxMessage(hcan, CAN_RX_FIFO0, &RxHeader, RxData);
	recvFlag = 1;
}

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
  MX_CAN_Init();
  /* USER CODE BEGIN 2 */

	HAL_CAN_Start(&hcan);

	HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING);

	TxHeader.DLC = 1;
	TxHeader.ExtId = 0;
	TxHeader.IDE = CAN_ID_STD;
	TxHeader.RTR = CAN_RTR_DATA;
	TxHeader.StdId = 0x103;
	TxHeader.TransmitGlobalTime = DISABLE;

	TxData[0] = 0xf3;

	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);

  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
	while (1) {

		HAL_UART_Receive_IT(&huart2, ramka_config, 7);

		if(recvUart == 1){
			recvUart = 0;
			HAL_CAN_Stop(&hcan);

			  hcan.Instance = CAN1;
			  hcan.Init.Prescaler = ramka_config[0];
			  hcan.Init.Mode = CAN_MODE_NORMAL;
			  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;

			  switch(ramka_config[1]){
			  case 1:
				hcan.Init.TimeSeg1 = CAN_BS1_1TQ;
				break;
			  case 2:
			  	hcan.Init.TimeSeg1 = CAN_BS1_2TQ;
			  	break;
			  case 3:
			  	hcan.Init.TimeSeg1 = CAN_BS1_3TQ;
			  	break;
			  case 4:
			  	hcan.Init.TimeSeg1 = CAN_BS1_4TQ;
			  	break;
			  case 5:
			  	hcan.Init.TimeSeg1 = CAN_BS1_5TQ;
			  	break;
			  case 6:
			  	hcan.Init.TimeSeg1 = CAN_BS1_6TQ;
			  	break;
			  case 7:
			  	hcan.Init.TimeSeg1 = CAN_BS1_7TQ;
			  	break;
			  case 8:
			  	hcan.Init.TimeSeg1 = CAN_BS1_8TQ;
			  	break;
			  case 9:
				hcan.Init.TimeSeg1 = CAN_BS1_9TQ;
				break;
			  case 10:
			  	hcan.Init.TimeSeg1 = CAN_BS1_10TQ;
			  	break;
			  case 11:
			  	hcan.Init.TimeSeg1 = CAN_BS1_11TQ;
			  	break;
			  case 12:
			  	hcan.Init.TimeSeg1 = CAN_BS1_12TQ;
			  	break;
			  case 13:
			  	hcan.Init.TimeSeg1 = CAN_BS1_13TQ;
			  	break;
			  case 14:
			  	hcan.Init.TimeSeg1 = CAN_BS1_14TQ;
			  	break;
			  case 15:
			  	hcan.Init.TimeSeg1 = CAN_BS1_15TQ;
			  	break;
			  case 16:
			  	hcan.Init.TimeSeg1 = CAN_BS1_16TQ;
			  	break;
			  }

			  switch(ramka_config[2]){
			  case 1:
				hcan.Init.TimeSeg2 = CAN_BS2_1TQ;
				break;
			  case 2:
			  	hcan.Init.TimeSeg2 = CAN_BS2_2TQ;
			  	break;
			  case 3:
			  	hcan.Init.TimeSeg2 = CAN_BS2_3TQ;
			  	break;
			  case 4:
			  	hcan.Init.TimeSeg2 = CAN_BS2_4TQ;
			  	break;
			  case 5:
			  	hcan.Init.TimeSeg2 = CAN_BS2_5TQ;
			  	break;
			  case 6:
			  	hcan.Init.TimeSeg2 = CAN_BS2_6TQ;
			  	break;
			  case 7:
			  	hcan.Init.TimeSeg2 = CAN_BS2_7TQ;
			  	break;
			  case 8:
			  	hcan.Init.TimeSeg2 = CAN_BS2_8TQ;
			  	break;

			  }
			  hcan.Init.TimeTriggeredMode = DISABLE;
			  hcan.Init.AutoBusOff = DISABLE;
			  hcan.Init.AutoWakeUp = DISABLE;
			  hcan.Init.AutoRetransmission = DISABLE;
			  hcan.Init.ReceiveFifoLocked = DISABLE;
			  hcan.Init.TransmitFifoPriority = DISABLE;
			  if (HAL_CAN_Init(&hcan) != HAL_OK)
			  {
			    Error_Handler();
			  }

			  ODBfilterID = (ramka_config[3]<<8) + ramka_config[4];
			  ODBfilterMaskID = (ramka_config[5]<<8) + ramka_config[6];

			CAN_FilterTypeDef canfilterconfig;

			canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
			canfilterconfig.FilterBank = 8; // which filter bank to use from the assigned ones
			canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
			canfilterconfig.FilterIdHigh = 0x0000;
			canfilterconfig.FilterIdLow = ODBfilterID;
			canfilterconfig.FilterMaskIdHigh = 0x0000;
			canfilterconfig.FilterMaskIdLow = ODBfilterMaskID;
			canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
			canfilterconfig.FilterScale = CAN_FILTERSCALE_16BIT;
			canfilterconfig.SlaveStartFilterBank = 10; // how many filters to assign to the CAN1 (master can)

			HAL_CAN_ConfigFilter(&hcan, &canfilterconfig);

			HAL_CAN_Start(&hcan);
		}

		if (recvFlag == 1) {							//if wykonywany gdy nastąpiło przerwanie od CAN i ustawiona została flaga recvFlag
			recvFlag = 0;								//zerowanie flagi

			ramka_uart[0] = (RxHeader.StdId >> 3);		//pierwszy bajt i pierwsze 8 bit adresu
			ramka_uart[1] = (RxHeader.StdId << 5) + (RxHeader.RTR << 4) + (RxHeader.IDE << 3) + RxHeader.DLC; //reszta adresu + RTR + IDE + DLC
			for(int i = 0; i<RxHeader.DLC ; i++){   	//wpisywanie danych do tablicy
				ramka_uart[2+i] = RxData[i];
			}
			ramka_uart[RxHeader.DLC+2] = 0x0a; 			// Wyslanie kodu nowej linii "\n" dla latwiejszego rozdzielania ramek przez aplikacje
			if(RxHeader.DLC<8){							//wykonaj tylko jeżeli nie wykorzystujemy wszystkich bajtów tablicy
				for(int i = RxHeader.DLC; i<10; i++){	//nieuzywane bajty = 0 (nie trzeba tal ale łatwiej debugować i czytać)
					ramka_uart[3+i] = 0;
				}
			}
			HAL_UART_Transmit(&huart2, (uint8_t*) ramka_uart, 3+RxHeader.DLC, -1);	//wysylanie po uarcie potrzebnej ilosci bajtow, timeout=inf
		}

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

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL9;
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
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_2) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief CAN Initialization Function
  * @param None
  * @retval None
  */
static void MX_CAN_Init(void)
{

  /* USER CODE BEGIN CAN_Init 0 */
  /* USER CODE END CAN_Init 0 */

  /* USER CODE BEGIN CAN_Init 1 */
  /* USER CODE END CAN_Init 1 */
  hcan.Instance = CAN1;
  hcan.Init.Prescaler = 18;
  hcan.Init.Mode = CAN_MODE_NORMAL;
  hcan.Init.SyncJumpWidth = CAN_SJW_1TQ;
  hcan.Init.TimeSeg1 = CAN_BS1_7TQ;
  hcan.Init.TimeSeg2 = CAN_BS2_8TQ;
  hcan.Init.TimeTriggeredMode = DISABLE;
  hcan.Init.AutoBusOff = DISABLE;
  hcan.Init.AutoWakeUp = DISABLE;
  hcan.Init.AutoRetransmission = DISABLE;
  hcan.Init.ReceiveFifoLocked = DISABLE;
  hcan.Init.TransmitFifoPriority = DISABLE;
  if (HAL_CAN_Init(&hcan) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN CAN_Init 2 */

	CAN_FilterTypeDef canfilterconfig;

	canfilterconfig.FilterActivation = CAN_FILTER_ENABLE;
	canfilterconfig.FilterBank = 8; // which filter bank to use from the assigned ones
	canfilterconfig.FilterFIFOAssignment = CAN_RX_FIFO0;
	canfilterconfig.FilterIdHigh = 0x0000;
	canfilterconfig.FilterIdLow = 0x0000;
	canfilterconfig.FilterMaskIdHigh = 0x0000;
	canfilterconfig.FilterMaskIdLow = 0xffff;
	canfilterconfig.FilterMode = CAN_FILTERMODE_IDMASK;
	canfilterconfig.FilterScale = CAN_FILTERSCALE_16BIT;
	canfilterconfig.SlaveStartFilterBank = 10; // how many filters to assign to the CAN1 (master can)

	HAL_CAN_ConfigFilter(&hcan, &canfilterconfig);
  /* USER CODE END CAN_Init 2 */

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
  huart2.Init.BaudRate = 9600;
  huart2.Init.WordLength = UART_WORDLENGTH_8B;
  huart2.Init.StopBits = UART_STOPBITS_1;
  huart2.Init.Parity = UART_PARITY_NONE;
  huart2.Init.Mode = UART_MODE_TX_RX;
  huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart2.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart2) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN USART2_Init 2 */
  /* USER CODE END USART2_Init 2 */

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
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
  HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin : B1_Pin */
  GPIO_InitStruct.Pin = B1_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

  /*Configure GPIO pin : LD2_Pin */
  GPIO_InitStruct.Pin = LD2_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

  /* EXTI interrupt init*/
  HAL_NVIC_SetPriority(EXTI15_10_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI15_10_IRQn);

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
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
