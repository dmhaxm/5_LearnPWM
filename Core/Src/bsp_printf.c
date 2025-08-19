/**-#####################################
**--File---Name--:--bsp_printf
**--Description--:--BSP printf functions for debugging and communication
--------------------------------------------

--Dev.-PlatForm:-vscode-&-Keil5.42

Created-By---:--DongMinghang
Created-Date-:--2025-08-14--
Version-----:--V1.0.0

Modified-Info-:--none
**-######################################*/

/*-------------------------Includes-(Header-Files)-----------------------------*/
#include "bsp_printf.h"
#include "usart.h"
#include "stdio.h"
#include <stdarg.h>
#include <string.h>

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
//法二：新的重定向函数（DMA方式）
uint8_t _dbg_TXBuff[1000];

// 串口1 DMA打印函数（基础功能）
void uart1_printf(const char* format, ...)
{
    uint32_t length;
    uint32_t l_u32SendTimer = 0;
    va_list args;

    // 等待串口就绪（带超时保护）
    while (huart1.gState != HAL_UART_STATE_READY)
    {
        l_u32SendTimer++;
        if(l_u32SendTimer > 300000)  // 超时阈值
        {
            break;
        }
    }

    // 解析可变参数并格式化字符串
    va_start(args, format);
    length = vsnprintf((char*)_dbg_TXBuff, sizeof(_dbg_TXBuff), (char*)format, args);
    va_end(args);

    // 确保不超过缓冲区大小
    length = (length > sizeof(_dbg_TXBuff)) ? sizeof(_dbg_TXBuff) : length;

    // 使用DMA发送数据
    HAL_UART_Transmit_DMA(&huart1, _dbg_TXBuff, length);
    
    // 添加短暂延时，确保DMA真正启动
    HAL_Delay(1);
}

/**
 * @brief 将uint8_t数组转换为"0xHH 0xHH ..."格式的字符串并发送
 * @param hexArray: 要转换的十六进制数组
 * @param len: 数组有效长度
 */
uint8_t _hex_TXBuff[1000];  // 独立的十六进制缓冲区
void uart1_printfhex(uint8_t* hexArray, uint16_t len)
{
    if (hexArray == NULL || len == 0)
    {
        uart1_printf("Error: 空数组或长度为0");
        return;
    }

    // 计算转换后字符串所需长度：每个字节对应"0xHH "（5个字符），最后加换行
    uint32_t str_len = len * 5 + 2;  // +2 预留换行符和字符串结束符
    if (str_len > sizeof(_hex_TXBuff))  // 注意：这里应该检查_hex_TXBuff的大小
    {
        uart1_printf("Error: 数组过长，超过缓冲区大小");
        return;
    }
    
    // 等待串口空闲
    uint32_t l_u32SendTimer = 0;
    while (huart1.gState != HAL_UART_STATE_READY)
    {
        l_u32SendTimer++;
        if(l_u32SendTimer > 300000)
        {
            break;
        }
    }
    
    char* p = (char*)_hex_TXBuff;
    *p = '\0';  // 初始化空字符串

    // 循环转换每个字节为"0xHH "格式
    for (uint16_t i = 0; i < len; i++)
    {
        // 拼接单个字节的十六进制字符串（如0x66 ）
        sprintf(p, "0x%02X ", hexArray[i]);
        p += 5;  // 移动指针到下一个位置（"0xHH "占5个字符）
    }

    // 替换最后一个空格为换行符（可选，优化显示）
    if (len > 0)
    {
        sprintf(p - 1, "\r\n");
    }

    // 直接DMA发送，不要调用uart1_printf
    uint32_t actual_len = strlen((char*)_hex_TXBuff);
    HAL_UART_Transmit_DMA(&huart1, _hex_TXBuff, actual_len);
    
    // 添加短暂延时，确保DMA真正启动
    HAL_Delay(1);
}
