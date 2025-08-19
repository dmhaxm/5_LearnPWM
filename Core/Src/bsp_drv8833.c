/**-#####################################
**--File---Name--:--bsp_drv8833
**--Description--:--Driver for the DRV8833 motor driver
--------------------------------------------

--Dev.-PlatForm:-vscode-&-Keil5.42

Created-By---:--DongMinghang
Created-Date-:--2025-08-19-
Version-----:--V1.0.0

Modified-Info-:--none
**-######################################*/

/*-------------------------Includes-(Header-Files)-----------------------------*/
#include "bsp_drv8833.h"

/*-------------------------Private-typedef|define|macro(Private-in-.c-file,Public-in-.h-file)--------*/


/*-------------------------Private-variables-|-function-prototypes-(static)--------------------------*/

/*-------------------------Private-function(static)-------------------------*/


/*
**=============================================================================
**-Function-name:--KEY_Press
**-Descriptions-:--Handles key press events, toggling an LED when the specified key is pressed.
**
**-Input--Para--:--GPIO_TypeDef* GPIOx: Pointer to the GPIO port where the key is connected.
**-Output-Para--:--uint16_t GPIO_Pin: The specific GPIO pin number for the key.
**-Return-Value-:--void
**
**=============================================================================
*/


/*-------------------------Public--function-(defined-in-header-file)--------------------------*/
void COMM_Init(void)
{
	// Initialize the communication interface, if needed
	// This could include setting up UART, GPIO, etc.
	HAL_UARTEx_ReceiveToIdle_DMA(&huart1,g_u8RxData,sizeof(g_u8RxData));  //UART空闲中断，采用DMA形式
	__HAL_DMA_DISABLE_IT(&hdma_usart1_rx,DMA_IT_HT);   //因为数组长度过半DMA也会触发中断函数，但是过半中断的调用的另一个回调函数HAL_UART_RxHalfCpltCallback里并没有处理什么，所以在接收的数据依旧完整，这里关闭只是节省资源
}
