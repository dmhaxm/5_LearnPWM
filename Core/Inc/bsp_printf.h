#ifndef _BSP_PRINTF_H
#define _BSP_PRINTF_H

#ifdef __cplusplus
extern "C" {
#endif

/*-Includes-(Header-Files)--------------------------------------------------*/
#include "main.h"
/*---------------------------------Config-----------------------------------*/

/*---------------------------------Public-extern|define---------------------*/
//调试宏定义
#define _DEBUG  // 注释此行关闭所有调试输出

#ifdef _DEBUG
// 调试模式：启用打印和十六进制发送
#define qDebug(format, ...) uart1_printf(format "\r\n", ##__VA_ARGS__)
#define qDebugHex(hexArray, len) uart1_printfhex(hexArray, len)
#else
// 非调试模式：宏展开为空（不执行任何操作）
#define qDebug(format, ...)
#define qDebugHex(hexArray, len)
#endif

/*---------------------------------TypeDef----------------------------------*/



/*---------------------------------Public-macro/inline----------------------*/


/*---------------------------------Public-function--------------------------*/
void uart1_printf(const char* format, ...);
void uart1_printfhex(uint8_t* hexArray, uint16_t len);


/*---------------------------------External-variables-----------------------*/

#ifdef __cplusplus
}
#endif
#endif