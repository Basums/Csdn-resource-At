/*
		//OLED.h�ĵ�-------
		�����ˣ���־��
		����ʱ�䣺2019/12/21 ����
		�ĵ�˵�������ĵ��ṩ��ʾ��SPI��ʾ�Ķ��巽��

*/

#ifndef __OLED__H
#define __OLED__H
#include "main.h"
#include "stm32f1xx_hal.h"

//˵��:
//----------------------------------------------------------------
//GND  �ӵ�
//VCC  ��3.3V��Դ
//D0   (SPI1_SCK===>LCD_SCK) ����ʱ����
//D1   (SPI1_MOSI===>LCD_MOSI) ����������
//RES  Ӳ��λ OLED
//DC   ����/���ݱ�־(д0-����/д1-����)
//CS   OLEDƬѡ�ź�

//-----------------OLED�˿ڶ���---------------- 

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

#define OLED_CMD  0	//д����
#define OLED_DATA 1	//д����


//���������ֲ��ṩ��Ӧ�ĺ궨��
#define	    BRIGHTNESS	  0xCF			//����
#define     X_WIDTH       128				//���
#define     Y_WIDTH       64				//����
#define		  PAGE			    8					//ҳ��
#define			MAX_CHAR_POSX X_WIDTH-6 //�ַ������Ҫ-6
#define			MAX_CHAR_POSY Y_WIDTH-6 //�ַ�������Ҫ-6

//function-------------------------------------------
//OLED�ĳ�ʼ��
void OLED_Init(void);
//д����
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
//����OLED��ʾ---------------------------
void OLED_DisPlay_On(void);
//�ر�OLED���--------------------------------------� 
void OLED_DisPlay_Off(void);
//�����Դ浽OLED--------------------------------------	
void OLED_Refresh(void);
//��������-----------------------------------------
void OLED_Clear(void);
//����(����XY�ķ�Χ)
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y);
//���һ����(����XY�ķ�Χ)
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y);
//����
//x:0~127
//y:0~63
//x1,y1���������
//x2,y2���յ�����
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//x,y:Բ������
//r:Բ�İ뾶
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
//��ָ��λ����ʾһ���ַ�,���������ַ�
//x:0~127
//y:0~63
//size:ѡ������ 12/16/24
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
//��ʾ�ַ���
//x,y:�������  
//size1:�����С 
//*chr:�ַ�����ʼ��ַ 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);
//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n);
////��ʾ2������
////x,y :�������	 
////len :���ֵ�λ��
////size:�����С
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
//��ʾ����
//x,y:�������
//num:���ֶ�Ӧ�����
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);
//num ��ʾ���ֵĸ���
//space ÿһ����ʾ�ļ��
void OLED_ScrollDisplay(uint8_t num,uint8_t space);
//����д�����ݵ���ʼλ��
void OLED_WR_BP(uint8_t x,uint8_t y);
//x0,y0���������
//x1,y1���յ�����
//BMP[]��Ҫд���ͼƬ����
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);
//���Ժ���
void OLED_ColorTurn(uint8_t i);
//��Ļ��ת180��
void OLED_DisplayTurn(uint8_t i);

//����˵�������ģʽ��10s����ʾ�����Ӻ�δ���Ӹ���
//֮��ͨ��������ʾ

#endif //__OLED__H
