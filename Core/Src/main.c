/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32f4xx_hal.h"
/* USER CODE END Includes */

/* Private variables ---------------------------------------------------------*/
osThreadId_t FlashGreenLEDTaskHandle;
osThreadId_t FlashRedLEDTaskHandle;

const osThreadAttr_t FlashGreenLEDTask_attributes = {
  .name = "FlashGreenLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
const osThreadAttr_t FlashRedLEDTask_attributes = {
  .name = "FlashRedLEDTask",
  .stack_size = 128 * 4,
  .priority = (osPriority_t) osPriorityAboveNormal,
};

/* USER CODE BEGIN PV */
volatile int start_flag = 1;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
void FlashGreenLED(void *argument);
void FlashRedLED(void *argument);
void AccessSharedData(void);

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  osKernelInitialize();
  FlashGreenLEDTaskHandle = osThreadNew(FlashGreenLED, NULL, &FlashGreenLEDTask_attributes);
  FlashRedLEDTaskHandle = osThreadNew(FlashRedLED, NULL, &FlashRedLEDTask_attributes);
  osKernelStart();

  while (1)
  {
    // Main loop
  }
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  /* Configure clock as needed */
}

/**
  * @brief GPIO Initialization Function
  * @param None
  * @retval None
  */
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* Enable GPIO Ports Clock */
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /* Configure GPIO pin for Green LED (PA5) */
  GPIO_InitStruct.Pin = GPIO_PIN_5;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /* Configure GPIO pin for Red LED (PB0) and Blue LED (PB7) */
  GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_7;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}

/**
  * @brief Function implementing the FlashGreenLED task.
  * @param argument: Not used
  * @retval None
  */
void FlashGreenLED(void *argument)
{
 for(;;)
  {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_SET);
    AccessSharedData();
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_5, GPIO_PIN_RESET);
    osDelay(500);
  }
}

/**
  * @brief Function implementing the FlashRedLED task.
  * @param argument: Not used
  * @retval None
  */
void FlashRedLED(void *argument)
{
  for(;;)
  {
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_SET);
    AccessSharedData();
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, GPIO_PIN_RESET);
    osDelay(100);
  }
}

/**
  * @brief Access shared data and check for collisions.
  * @retval None
  */
void AccessSharedData(void)
{
    if (start_flag == 1)
    {
        start_flag = 0;
    }
    else
    {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_SET);
    }

    osDelay(500);

    start_flag = 1;

    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_7, GPIO_PIN_RESET);
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */
/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void) {
  __disable_irq();
  while (1) {
  }
}

#ifdef  USE_FULL_ASSERT
void assert_failed(uint8_t *file, uint32_t line) {
}
#endif /* USE_FULL_ASSERT */
