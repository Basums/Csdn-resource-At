#ifndef  __ds18b20_H__
#define  __ds18b20_H__
#include "stm32f1xx_hal.h"
#include "main.h"
//#include "sys.h"

////IO方向设置
//#define DS18B20_IO_IN()  {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=8<<0;}
//#define DS18B20_IO_OUT() {GPIOB->CRL&=0XFFFFFFF0;GPIOB->CRL|=3<<0;}

//////IO操作函数											   
//#define	DS18B20_DQ_OUT PBout(3) //数据端口	PB3
//#define	DS18B20_DQ_IN  PBin(3)  //数据端口	PB3 


//void DS18B20_Rst(void);
//uint8_t DS18B20_Check(void);
//void DS18B20_Write_Byte(uint8_t dat);
//uint8_t DS18B20_Read_Bit(void);
//uint8_t DS18B20_Read_Byte(void);
//void DS18B20_Start(void);
//short DS18B20_Get_Temp(void);
//uint8_t DS18B20_Init(void);


#define		DS18B20_GPIO_CLK_ENABLE()		__HAL_RCC_GPIOE_CLK_ENABLE()
#define		DS18B20_DQ_PIN							DS18B20_PIN_Pin
#define		DS18B20_DQ_PORT							DS18B20_PIN_GPIO_Port

#define		DS18B20_DQ_PIN_HIGH()				HAL_GPIO_WritePin(DS18B20_DQ_PORT, DS18B20_DQ_PIN, GPIO_PIN_SET)
#define		DS18B20_DQ_PIN_LOW()				HAL_GPIO_WritePin(DS18B20_DQ_PORT, DS18B20_DQ_PIN, GPIO_PIN_RESET)
#define		GET_DS18B20_DQ_PIN()				HAL_GPIO_ReadPin(DS18B20_DQ_PORT, DS18B20_DQ_PIN)

void	DS18B20_Init(void);
void 	DS18B20_Set_Input(void);
void 	DS18B20_Set_Output(void);
void 	DS18B20_Reset(void);
int 	DS18B20_Presence(void);
void 	DS18B20_WriteByte(uint8_t);
uint8_t	DS18B20_ReadBit(void);
uint8_t DS18B20_ReadByte(void);

void	DS18B20_Start(void);
short 	DS18B20_Get_Temp(void);



#endif

