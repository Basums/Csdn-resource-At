#ifndef  __LED_H__
#define  __LED_H__
#include "stm32f1xx_hal.h"
#include "main.h"

//LED
#define  HAL_RCC_LED_GPIOX_CLK_EN()	__HAL_RCC_GPIOA_CLK_ENABLE()
#define  LED_ON()										HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_RESET)
#define  LED_OFF()									HAL_GPIO_WritePin(LED_PIN_GPIO_Port, LED_PIN_Pin, GPIO_PIN_SET)
#define  LED_TOGGLE() 							HAL_GPIO_TogglePin(LED_PIN_GPIO_Port, LED_PIN_Pin)
#define  LED_Read()   							HAL_GPIO_ReadPin(LED_PIN_GPIO_Port, LED_PIN_Pin)

void  LED_GPIO_Init(void);
#endif
