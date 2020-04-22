#ifndef  __usart_H__
#define  __usart_H__
#include "stm32f1xx_hal.h"

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

void MX_USART1_UART_Init(void);
void MX_USART2_UART_Init(void);

#endif
