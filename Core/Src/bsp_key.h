#ifndef _KEY_H
#define _KEY_H

#ifdef __cplusplus
extern "C" {
#endif

/*-Includes-(Header-Files)--------------------------------------------------*/
#include "main.h"
/*---------------------------------Config-----------------------------------*/

/*---------------------------------Public-extern|define---------------------*/
/* Protocol defines */

/*---------------------------------TypeDef----------------------------------*/
/* BOOTLOADER states */


/*---------------------------------Public-macro/inline----------------------*/


/*---------------------------------Public-function--------------------------*/
uint8_t KEY_Press(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);


/*---------------------------------External-variables-----------------------*/

#ifdef __cplusplus
}
#endif
#endif
