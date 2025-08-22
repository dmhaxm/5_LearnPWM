/**-#####################################
**--File---Name--:--test_pwm.c
**--Description--:--PWM testing functions
--------------------------------------------

--Dev.-PlatForm:-vscode-&-Keil5.42

Created-By---:--DongMinghang
Created-Date-:--2025-08-22-
Version-----:--V1.0.0

Modified-Info-:--none
**-######################################*/

/*-------------------------Includes-(Header-Files)-----------------------------*/
#include "test_pwm.h"
#include "tim.h"
/*-------------------------Private-typedef|define|macro(Private-in-.c-file,Public-in-.h-file)--------*/


/*-------------------------Private-variables-|-function-prototypes-(static)--------------------------*/
uint32_t volatile r_u32IC1Value = 0;  // Input Capture value for Channel 1
uint32_t volatile r_u32IC2Value = 0;  // Input Capture value for Channel 2
uint32_t volatile r_u32Frequence = 0;
uint8_t volatile r_u8DutyCycle = 0;
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
/*
**=============================================================================
**-Function-name:--TEST_PWM_Init
**-Descriptions-:--Initializes the PWM input capture functionality.
**-Input--Para--:--None
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

void TEST_PWM_Init(void)
{
	HAL_TIM_IC_Start_IT(IN_TIM, IN_CH1);  // Start Input Capture on TIM2 Channel 1
    HAL_TIM_IC_Start_IT(IN_TIM, IN_CH2);  // Start Input Capture on TIM2 Channel 2
}
/*
**=============================================================================
**-Function-name:--HAL_TIM_IC_CaptureCallback
**-Descriptions-:--Handles the input capture callback for the specified timer.
**-Input--Para--:--TIM_HandleTypeDef *htim
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim)
{
    if (htim == IN_TIM)  // Check if the interrupt is from TIM2
    {
        if (htim->Channel == HAL_TIM_ACTIVE_CHANNEL_1)  // Check if it's Channel 1
        {
            r_u32IC1Value = HAL_TIM_ReadCapturedValue(htim, IN_CH1);
            r_u32IC2Value = HAL_TIM_ReadCapturedValue(htim, IN_CH2);
            if(r_u32IC1Value)
            {
                r_u32Frequence = 168000000 / 168 / (r_u32IC1Value + 1);
                r_u8DutyCycle = (r_u32IC2Value + 1) * 100 / (r_u32IC1Value + 1);
                // Process capture value for Channel 1
            }
            else
            {
                r_u32Frequence = 0;
                r_u8DutyCycle = 0;
            }
        }
    }
}
/// @brief Retrieves the current PWM frequency and duty cycle values.
/// @param l_pu16Frequence Pointer to store the frequency value.
/// @param l_pu8DutyCycle Pointer to store the duty cycle value.

void TEST_PWM_Get(uint32_t* l_pu32Frequence, uint8_t* l_pu8DutyCycle)
{
    *l_pu32Frequence = r_u32Frequence;
    *l_pu8DutyCycle = r_u8DutyCycle;
}