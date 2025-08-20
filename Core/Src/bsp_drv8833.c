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
#include "tim.h"
/*-------------------------Private-typedef|define|macro(Private-in-.c-file,Public-in-.h-file)--------*/
//电机使用引脚的定时器
#define IN1_TIM &htim2
#define IN2_TIM &htim2

//电机使用引脚的PWM通道
#define IN1_CH TIM_CHANNEL_1
#define IN2_CH TIM_CHANNEL_2

//电机最大速度
#define MAX_SPEED 100



/*-------------------------Private-variables-|-function-prototypes-(static)--------------------------*/
enDecayMode_t g_enDecayMode = SLOW_DECAY; // 默认使用慢衰减模式
/*-------------------------Private-function(static)-------------------------*/
/*
**=============================================================================
**-Function-name:--__SetIn1PWM
**-Descriptions-:--Sets the PWM duty cycle for the IN1 pin.
**-Input--Para--:--uint8_t l_u8Speed
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

static inline void __SetIn1PWM(uint8_t l_u8Speed)
{
	// 设置IN1引脚的PWM占空比
	__HAL_TIM_SET_COMPARE(IN1_TIM, IN1_CH, l_u8Speed);
}
/*-------------------------Private-function(static)-------------------------*/
/*
**=============================================================================
**-Function-name:--__SetIn2PWM
**-Descriptions-:--Sets the PWM duty cycle for the IN2 pin.
**-Input--Para--:--uint8_t l_u8Speed
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

static inline void __SetIn2PWM(uint8_t l_u8Speed)
{
	// 设置IN2引脚的PWM占空比
	__HAL_TIM_SET_COMPARE(IN2_TIM, IN2_CH, l_u8Speed);
}

/*-------------------------Public--function-(defined-in-header-file)--------------------------*/
/*
**=============================================================================
**-Function-name:--DRV8833_Init
**-Descriptions-:--Initializes the DRV8833 motor driver.
**
**-Input--Para--:--None
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

void DRV8833_Init(void)
{
	// Initialize the PWM channels for the motor driver
	HAL_TIM_PWM_Start(IN1_TIM, IN1_CH);
	HAL_TIM_PWM_Start(IN2_TIM, IN2_CH);
}
/*
**=============================================================================
**-Function-name:--DRV8833_SetDecayMode
**-Descriptions-:--Sets the decay mode for the DRV8833 motor driver.
**
**-Input--Para--:--enDecayMode_t enMode
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

//设置电机模式
void DRV8833_SetDecayMode(enDecayMode_t enMode)
{
	g_enDecayMode = enMode;
}
/*
**=============================================================================
**-Function-name:--DRV8833_Forward
**-Descriptions-:--Sets the motor direction to forward.
**
**-Input--Para--:--uint8_t l_u8Speed: The speed of the motor (0-100).
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

void DRV8833_Forward(uint8_t l_u8Speed)
{
	if(l_u8Speed > MAX_SPEED) 
		l_u8Speed = MAX_SPEED;
	if(g_enDecayMode == FAST_DECAY)
	{
		__SetIn1PWM(l_u8Speed);
		__SetIn2PWM(0);
	}
	else{
		__SetIn1PWM(MAX_SPEED);
		__SetIn2PWM(MAX_SPEED - l_u8Speed);
	}
}
/*
**=============================================================================
**-Function-name:--DRV8833_Backward
**-Descriptions-:--Sets the motor direction to backward.
**
**-Input--Para--:--uint8_t l_u8Speed: The speed of the motor (0-100).
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

void DRV8833_Backward(uint8_t l_u8Speed)
{
	if(l_u8Speed > MAX_SPEED) 
		l_u8Speed = MAX_SPEED;
	if(g_enDecayMode == FAST_DECAY)
	{
		__SetIn1PWM(0);
		__SetIn2PWM(l_u8Speed);
	}
	else{
		__SetIn1PWM(MAX_SPEED - l_u8Speed);
		__SetIn2PWM(MAX_SPEED);
	}
}
/*
**=============================================================================
**-Function-name:--DRV8833_Brake
**-Descriptions-:--Sets the motor to brake mode.
**
**-Input--Para--:--void
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

//刹车
void DRV8833_Brake(void)
{
	__SetIn1PWM(MAX_SPEED);
	__SetIn2PWM(MAX_SPEED);
}
/*
**=============================================================================
**-Function-name:--DRV8833_Coast
**-Descriptions-:--Sets the motor to coast mode.
**
**-Input--Para--:--void
**-Output-Para--:--None
**-Return-Value-:--None
**
**=============================================================================
*/

//滑行
void DRV8833_Coast(void)
{
	__SetIn1PWM(0);
	__SetIn2PWM(0);
}