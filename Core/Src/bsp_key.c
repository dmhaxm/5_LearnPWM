/**-#####################################
**--File---Name--:--bsp_key
**--Description--:--BSP key driver
--------------------------------------------

--Dev.-PlatForm:-vscode-&-Keil5.42

Created-By---:--DongMinghang
Created-Date-:--2025-07-28-
Version-----:--V1.0.0

Modified-Info-:--none
**-######################################*/

/*-------------------------Includes-(Header-Files)-----------------------------*/
#include "bsp_key.h"
#include "gpio.h"
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

uint8_t KEY_Press(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
	if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
	{
		HAL_Delay(10);
		if(HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET)
		{
			while((HAL_GPIO_ReadPin(GPIOx, GPIO_Pin) == GPIO_PIN_RESET));
		}
		return 1;
	}
	return 0;
}
