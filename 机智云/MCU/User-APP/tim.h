#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f1xx_hal.h"
#include "main.h" 
	 
	 
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim2;
extern TIM_HandleTypeDef htim3;
	 
void MX_TIM2_Init(void);
void MX_TIM1_Init(void);
void MX_TIM3_Init(void);
	 
#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */
