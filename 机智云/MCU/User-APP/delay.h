#ifndef __delay_H
#define __delay_H
#ifdef __cplusplus
 extern "C" {
#endif

/*includes---------------------*/
#include "stm32f1xx_hal.h"
#include "main.h" 

void delay_us(uint32_t nus);
void delay_ms(uint16_t nms);
	 	

#ifdef __cplusplus
}
#endif
#endif /*__delay_H */

