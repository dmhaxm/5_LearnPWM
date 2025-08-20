#ifndef _BSP_DRV8833_H
#define _BSP_DRV8833_H

#ifdef __cplusplus
extern "C" {
#endif

/*-Includes-(Header-Files)--------------------------------------------------*/
#include "main.h"
/*---------------------------------Config-----------------------------------*/
/*---------------------------------TypeDef----------------------------------*/
//衰减模式
typedef enum{
	SLOW_DECAY,  // 慢衰减
	FAST_DECAY   // 快速衰减
}enDecayMode_t;
/*---------------------------------Public-extern|define---------------------*/
/* Protocol defines */


/* BOOTLOADER states */


/*---------------------------------Public-macro/inline----------------------*/


/*---------------------------------Public-function--------------------------*/
void DRV8833_Init(void);
void DRV8833_SetDecayMode(enDecayMode_t enMode);
void DRV8833_Forward(uint8_t l_u8Speed);
void DRV8833_Backward(uint8_t l_u8Speed);
void DRV8833_Brake(void);
void DRV8833_Coast(void);

/*---------------------------------External-variables-----------------------*/

#ifdef __cplusplus
}
#endif
#endif
