/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "dma.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "bsp_printf.h"
#include "bsp_key.h"
#include "bsp_drv8833.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define DUTY_CYCLE_MAX 10
#define DUTY_CYCLE_MIN 200
//电机宏定义
#define MID_COUNTER 20
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */
uint8_t g_u8DutyCycle = 0;
uint32_t g_u32TimChannel[2] = {TIM_CHANNEL_1, TIM_CHANNEL_2};
uint8_t g_u8ChannelIndex = 0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
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
    SCB->VTOR = 0x08020000;
  	__enable_irq();
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
  MX_DMA_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM1_Init();
  MX_TIM2_Init();
  /* USER CODE BEGIN 2 */
  DRV8833_Init();  // 初始化电机驱动
	HAL_TIM_Encoder_Start(&htim1,TIM_CHANNEL_ALL);  // 启动编码器
  __HAL_TIM_SET_COUNTER(&htim1, MID_COUNTER);  
  //__HAL_TIM_SET_COMPARE(&htim3,g_u32TimChannel[g_u8ChannelIndex],g_u8DutyCycle);  // 设置PWM占空比
  //HAL_TIM_PWM_Start(&htim3,g_u32TimChannel[g_u8ChannelIndex]);
	//HAL_TIM_PWM_Start(&htim3,g_u32TimChannel[g_u8ChannelIndex]);  // 启动PWM
  DRV8833_SetDecayMode(SLOW_DECAY);
  DRV8833_Forward(80);  // 设置电机前进，速度为20
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (1)
  {
		HAL_Delay(3000);
		DRV8833_Coast();
    //1.按键控制PWM灯
      // if(KEY_Press(LED_PWM_GPIO_Port,LED_PWM_Pin))
      // {
      //   g_u8DutyCycle += 20;
      //   if(g_u8DutyCycle > 100)
      //     g_u8DutyCycle = 0;
      //     __HAL_TIM_SET_COMPARE(&htim3,g_u32TimChannel[g_u8ChannelIndex],g_u8DutyCycle);
      // }
    //2.编码器控制PWM灯
      // g_u8DutyCycle = __HAL_TIM_GET_COUNTER(&htim1);  // 获取编码器计数值
      // if(g_u8DutyCycle > 100)
      // {
      //   g_u8DutyCycle = 0;
      //   __HAL_TIM_SET_COUNTER(&htim1, 0);
      // }
      // __HAL_TIM_SET_COMPARE(&htim3,g_u32TimChannel[g_u8ChannelIndex],g_u8DutyCycle);  // 设置PWM占空比  
			// qDebug("TIM_Chinnal:%d,g_u8DutyCycle:%d",g_u8ChannelIndex,g_u8DutyCycle);
      // if(KEY_Press(LED_Change_GPIO_Port,LED_Change_Pin))
      // {
      //   g_u8DutyCycle = 0;
      //   HAL_TIM_PWM_Stop(&htim3,g_u32TimChannel[g_u8ChannelIndex]);  // 停止PWM
      //   g_u8ChannelIndex = (g_u8ChannelIndex + 1) % 2;
      //   __HAL_TIM_SET_COMPARE(&htim3,g_u32TimChannel[g_u8ChannelIndex],g_u8DutyCycle);
      //   HAL_TIM_PWM_Start(&htim3,g_u32TimChannel[g_u8ChannelIndex]);  // 启动新的PWM
      // }
			// HAL_Delay(100);
    //3.PWM呼吸灯
      // for(int i = 0;i < 100;i++)
      // {
      //     __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);
      //     HAL_Delay(10);
      // }
      // for(int i = 99;i > 0;i--)
      // {
      //     __HAL_TIM_SET_COMPARE(&htim3,TIM_CHANNEL_1,i);
      //     HAL_Delay(10);
      // }
    //4.编码器控制舵机
      //此处更改了频率为舵机需要的50HZ，对应的一圈20个脉冲，2个引脚记数应该为40，
      //但是我预分频器为2-1，所以一圈还是20，即0~360°为0~20，则要0~180°对应0~10
//      g_u8DutyCycle = __HAL_TIM_GET_COUNTER(&htim1);  // 获取编码器计数值
//      if(g_u8DutyCycle > DUTY_CYCLE_MIN)    //这里要先判断最大的，因为程序是从上往下执行的
//      {
//        g_u8DutyCycle = 0;
//        __HAL_TIM_SET_COUNTER(&htim1, g_u8DutyCycle);
//      }
//      else if(g_u8DutyCycle > DUTY_CYCLE_MAX)      
//      {
//        g_u8DutyCycle = DUTY_CYCLE_MAX;
//        __HAL_TIM_SET_COUNTER(&htim1, DUTY_CYCLE_MAX);
//      }
//      
//      qDebug("TIM_Chinnal:%d,g_u8DutyCycle:%d",g_u8ChannelIndex,g_u8DutyCycle);
//      g_u8DutyCycle = g_u8DutyCycle * 20 + 50; 
//      __HAL_TIM_SET_COMPARE(&htim3,g_u32TimChannel[g_u8ChannelIndex],g_u8DutyCycle);  // 设置PWM占空比
//      qDebug("g_u8DutyCycle:%.2f%%",(float)g_u8DutyCycle / 2000 * 100); //这里记得转换成浮点数
//      HAL_Delay(10);
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
  __HAL_RCC_PWR_CLK_ENABLE();
  __HAL_PWR_VOLTAGESCALING_CONFIG(PWR_REGULATOR_VOLTAGE_SCALE1);

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_ON;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLM = 4;
  RCC_OscInitStruct.PLL.PLLN = 168;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = 4;
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
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV4;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_5) != HAL_OK)
  {
    Error_Handler();
  }
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
