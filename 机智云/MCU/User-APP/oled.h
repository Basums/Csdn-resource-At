/*
		//OLED.h文档-------
		创建人：艾志奇
		创建时间：2019/12/21 冬至
		文档说明：本文档提供显示屏SPI显示的定义方法

*/

#ifndef __OLED__H
#define __OLED__H
#include "main.h"
#include "stm32f1xx_hal.h"

//说明:
//----------------------------------------------------------------
//GND  接地
//VCC  接3.3V电源
//D0   (SPI1_SCK===>LCD_SCK) 串行时钟线
//D1   (SPI1_MOSI===>LCD_MOSI) 串行数据线
//RES  硬复位 OLED
//DC   命令/数据标志(写0-命令/写1-数据)
//CS   OLED片选信号

//-----------------OLED端口定义---------------- 

#define OLED_SCLK_Clr() 	HAL_GPIO_WritePin(GPIOA, OLED_SCL_Pin, GPIO_PIN_RESET)//SCL
#define OLED_SCLK_Set() 	HAL_GPIO_WritePin(GPIOA, OLED_SCL_Pin, GPIO_PIN_SET)

#define OLED_SDIN_Clr() 	HAL_GPIO_WritePin(GPIOA, OLED_SDA_Pin, GPIO_PIN_RESET)//SDA
#define OLED_SDIN_Set() 	HAL_GPIO_WritePin(GPIOA, OLED_SDA_Pin, GPIO_PIN_SET)

#define OLED_RST_Clr() 		HAL_GPIO_WritePin(GPIOA, OLED_RES_Pin, GPIO_PIN_RESET)//RES
#define OLED_RST_Set() 		HAL_GPIO_WritePin(GPIOA, OLED_RES_Pin, GPIO_PIN_SET)

#define OLED_DC_Clr() 		HAL_GPIO_WritePin(GPIOA, OLED_DC_Pin, GPIO_PIN_RESET)//DC
#define OLED_DC_Set() 		HAL_GPIO_WritePin(GPIOA, OLED_DC_Pin, GPIO_PIN_SET)
 		     
#define OLED_CS_Clr()  		HAL_GPIO_WritePin(GPIOB, OLED_CS_Pin, GPIO_PIN_RESET)//CS
#define OLED_CS_Set()  		HAL_GPIO_WritePin(GPIOB, OLED_CS_Pin, GPIO_PIN_SET)

#define OLED_CMD  0	//写命令
#define OLED_DATA 1	//写数据


//根据数据手册提供对应的宏定义
#define	    BRIGHTNESS	  0xCF			//亮度
#define     X_WIDTH       128				//宽度
#define     Y_WIDTH       64				//长度
#define		  PAGE			    8					//页数
#define			MAX_CHAR_POSX X_WIDTH-6 //字符宽度需要-6
#define			MAX_CHAR_POSY Y_WIDTH-6 //字符长度需要-6

//function-------------------------------------------
//OLED的初始化
void OLED_Init(void);
//写数据
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
//开启OLED显示---------------------------
void OLED_DisPlay_On(void);
//关闭OLED显�--------------------------------------� 
void OLED_DisPlay_Off(void);
//更新显存到OLED--------------------------------------	
void OLED_Refresh(void);
//清屏函数-----------------------------------------
void OLED_Clear(void);
//画点(谨记XY的范围)
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y);
//清除一个点(谨记XY的范围)
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y);
//画线
//x:0~127
//y:0~63
//x1,y1：起点坐标
//x2,y2：终点坐标
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//x,y:圆心坐标
//r:圆的半径
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
//在指定位置显示一个字符,包括部分字符
//x:0~127
//y:0~63
//size:选择字体 12/16/24
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
//显示字符串
//x,y:起点坐标  
//size1:字体大小 
//*chr:字符串起始地址 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);
//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n);
////显示2个数字
////x,y :起点坐标	 
////len :数字的位数
////size:字体大小
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
//显示汉字
//x,y:起点坐标
//num:汉字对应的序号
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);
//num 显示汉字的个数
//space 每一遍显示的间隔
void OLED_ScrollDisplay(uint8_t num,uint8_t space);
//配置写入数据的起始位置
void OLED_WR_BP(uint8_t x,uint8_t y);
//x0,y0：起点坐标
//x1,y1：终点坐标
//BMP[]：要写入的图片数组
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);
//反显函数
void OLED_ColorTurn(uint8_t i);
//屏幕旋转180度
void OLED_DisplayTurn(uint8_t i);

//函数说明：检测模式，10s，显示已连接和未连接更换
//之后通过串口显示

#endif //__OLED__H
