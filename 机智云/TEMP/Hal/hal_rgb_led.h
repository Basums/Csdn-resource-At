#ifndef _HAL_RGB_LED_H
#define _HAL_RGB_LED_H

#include <stdio.h>
#include <stm32f1xx.h>

#define  R_MAX  255
#define  G_MAX  255
#define  B_MAX  255

#define SCL_LOW 	HAL_GPIO_WritePin(RGBLED_CLK_GPIO_Port, RGBLED_CLK_Pin, GPIO_PIN_RESET)
#define SCL_HIGH 	HAL_GPIO_WritePin(RGBLED_CLK_GPIO_Port, RGBLED_CLK_Pin, GPIO_PIN_SET)

#define SDA_LOW		HAL_GPIO_WritePin(RGBLED_DIN_GPIO_Port, RGBLED_DIN_Pin, GPIO_PIN_RESET)
#define SDA_HIGH	HAL_GPIO_WritePin(RGBLED_DIN_GPIO_Port, RGBLED_DIN_Pin, GPIO_PIN_SET)

///*兼容V2.2及以上,RGB开关IO*/
#define RGB_Enable()		HAL_GPIO_WritePin(RGB_LED_EN_GPIO_Port, RGB_LED_EN_Pin, GPIO_PIN_SET)
#define RGB_Disable() 	HAL_GPIO_WritePin(RGB_LED_EN_GPIO_Port, RGB_LED_EN_Pin, GPIO_PIN_RESET)

void rgbLedInit(void);
void ledRgbControl(uint8_t R,uint8_t B,uint8_t G);


#endif /*_HAL_RGB_LED_H*/

