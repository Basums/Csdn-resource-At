 #include "led.h"
 
  /*LED�ĳ�ʼ������*/
 void LED_GPIO_Init(void)
{
		GPIO_InitTypeDef GPIO_InitStruct;
	  
		GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	 
		// LED���ų�ʼ��
	  HAL_RCC_LED_GPIOX_CLK_EN(); 
	  GPIO_InitStruct.Pin = LED_PIN_Pin;
	  HAL_GPIO_Init(LED_PIN_GPIO_Port, &GPIO_InitStruct);
}

