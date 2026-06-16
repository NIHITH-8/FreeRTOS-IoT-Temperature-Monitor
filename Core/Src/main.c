  
  
  
  
#include "main.h"
#include "cmsis_os.h"
#include "lcd.h"
#include "lm35.h"
#include <stdio.h>
#include "esp8266.h"

float temp;
int decimal;
  

  
  

  

  
  

  

  
ADC_HandleTypeDef hadc1;

UART_HandleTypeDef huart6;

  
osThreadId_t SensorTaskHandle;
const osThreadAttr_t SensorTask_attributes = {
  .name = "SensorTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
  
osThreadId_t LCDTaskHandle;
const osThreadAttr_t LCDTask_attributes = {
  .name = "LCDTask",
  .stack_size = 256 * 4,
  .priority = (osPriority_t) osPriorityBelowNormal,
};
  
osThreadId_t ESPTaskHandle;
const osThreadAttr_t ESPTask_attributes = {
  .name = "ESPTask",
  .stack_size = 512 * 4,
  .priority = (osPriority_t) osPriorityNormal,
};
  
osMessageQueueId_t TemperatureQueueHandle;
const osMessageQueueAttr_t TemperatureQueue_attributes = {
  .name = "TemperatureQueue"
};
  

  

  
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_ADC1_Init(void);
static void MX_USART6_UART_Init(void);
void StartDefaultTask(void *argument);
void StartTask02(void *argument);
void StartTask03(void *argument);

  

  

  
  

  
  
int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();
  lcd_init();
  MX_ADC1_Init();
  MX_USART6_UART_Init();

    
 /*
  osKernelInitialize();
  TemperatureQueueHandle = osMessageQueueNew (5, 4, &TemperatureQueue_attributes);
  SensorTaskHandle = osThreadNew(StartDefaultTask, NULL, &SensorTask_attributes);
  LCDTaskHandle = osThreadNew(StartTask02, NULL, &LCDTask_attributes);
  ESPTaskHandle = osThreadNew(StartTask03, NULL, &ESPTask_attributes);
  osKernelStart();
*/


   char buf[20];

   int whole;


   while(1)
   {
       temp = LM35_ReadTemp();

       whole = (int)temp;

       decimal = (int)((temp - whole) * 10);

       sprintf(buf,"T=%d.%d C",whole,decimal);

       scmd(0x01);

       string(buf);

       HAL_Delay(1000);
       AT_configs();

}
}

  
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

    
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE2);

    
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_NONE;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

    
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

  
static void MX_ADC1_Init(void)
{

    

    

  ADC_ChannelConfTypeDef sConfig = {0};

    

    

    
  hadc1.Instance = ADC1;
  hadc1.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
  hadc1.Init.Resolution = ADC_RESOLUTION_12B;
  hadc1.Init.ScanConvMode = ENABLE;
  hadc1.Init.ContinuousConvMode = ENABLE;
  hadc1.Init.DiscontinuousConvMode = DISABLE;
  hadc1.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
  hadc1.Init.ExternalTrigConv = ADC_SOFTWARE_START;
  hadc1.Init.DataAlign = ADC_DATAALIGN_RIGHT;
  hadc1.Init.NbrOfConversion = 2;
  hadc1.Init.DMAContinuousRequests = DISABLE;
  hadc1.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
  if (HAL_ADC_Init(&hadc1) != HAL_OK)
  {
    Error_Handler();
  }

    
  sConfig.Channel = ADC_CHANNEL_10;
  sConfig.Rank = 1;
  sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }

    
  sConfig.Channel = ADC_CHANNEL_11;
  sConfig.Rank = 2;
  if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
  {
    Error_Handler();
  }
    

    

}

  
static void MX_USART6_UART_Init(void)
{

    

    

    

    
  huart6.Instance = USART6;
  huart6.Init.BaudRate = 115200;
  huart6.Init.WordLength = UART_WORDLENGTH_8B;
  huart6.Init.StopBits = UART_STOPBITS_1;
  huart6.Init.Parity = UART_PARITY_NONE;
  huart6.Init.Mode = UART_MODE_TX_RX;
  huart6.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  huart6.Init.OverSampling = UART_OVERSAMPLING_16;
  if (HAL_UART_Init(&huart6) != HAL_OK)
  {
    Error_Handler();
  }
    

    

}

  
static void MX_GPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
    

    

    
  __HAL_RCC_GPIOC_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

    
  HAL_GPIO_WritePin(GPIOB, LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin, GPIO_PIN_RESET);

    
  GPIO_InitStruct.Pin = LCD_D4_Pin|LCD_D5_Pin|LCD_D6_Pin|LCD_D7_Pin
                          |LCD_RS_Pin|LCD_RW_Pin|LCD_EN_Pin;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    

    
}

  

  

  
  
  
void StartDefaultTask(void *argument)
{
    
    
  for(;;)
  {
    osDelay(1);
  }
    
}

  
  
  
void StartTask02(void *argument)
{
    
    
  for(;;)
  {
    osDelay(1);
  }
    
}

  
  
  
void StartTask03(void *argument)
{
    
    
  for(;;)
  {
    osDelay(1);
  }
    
}

  
void Error_Handler(void)
{
    
    
  __disable_irq();
  while (1)
  {
  }
    
}
#ifdef USE_FULL_ASSERT
  
void assert_failed(uint8_t *file, uint32_t line)
{
    
    
    
}
#endif   
