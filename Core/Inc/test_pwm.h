#ifndef _TEST_PWM_H
#define _TEST_PWM_H

#ifdef __cplusplus
extern "C" {
#endif

/*-Includes-(Header-Files)--------------------------------------------------*/
#include "main.h"
/*---------------------------------Config-----------------------------------*/
/*---------------------------------TypeDef----------------------------------*/

/*---------------------------------Public-extern|define---------------------*/
#define IN_TIM &htim8
#define IN_CH1 TIM_CHANNEL_1
#define IN_CH2 TIM_CHANNEL_2

/* BOOTLOADER states */


/*---------------------------------Public-macro/inline----------------------*/


/*---------------------------------Public-function--------------------------*/
void TEST_PWM_Init(void);
void HAL_TIM_IC_CaptureCallback(TIM_HandleTypeDef *htim);
void TEST_PWM_Get(uint32_t* l_pu32Frequence, uint8_t* l_pu8DutyCycle);

/*---------------------------------External-variables-----------------------*/

#ifdef __cplusplus
}
#endif
#endif
