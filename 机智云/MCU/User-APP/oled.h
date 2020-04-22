/*
		//OLED.hÎÄµµ-------
		´´½¨ÈË£º°¬Ö¾Ææ
		´´½¨Ê±¼ä£º2019/12/21 ¶¬ÖÁ
		ÎÄµµËµÃ÷£º±¾ÎÄµµÌá¹©ÏÔÊ¾ÆÁSPIÏÔÊ¾µÄ¶¨Òå·½·¨

*/

#ifndef __OLED__H
#define __OLED__H
#include "main.h"
#include "stm32f1xx_hal.h"

//ËµÃ÷:
//----------------------------------------------------------------
//GND  ½ÓµØ
//VCC  ½Ó3.3VµçÔ´
//D0   (SPI1_SCK===>LCD_SCK) ´®ÐÐÊ±ÖÓÏß
//D1   (SPI1_MOSI===>LCD_MOSI) ´®ÐÐÊý¾ÝÏß
//RES  Ó²¸´Î» OLED
//DC   ÃüÁî/Êý¾Ý±êÖ¾(Ð´0-ÃüÁî/Ð´1-Êý¾Ý)
//CS   OLEDÆ¬Ñ¡ÐÅºÅ

//-----------------OLED¶Ë¿Ú¶¨Òå---------------- 

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

#define OLED_CMD  0	//Ð´ÃüÁî
#define OLED_DATA 1	//Ð´Êý¾Ý


//¸ù¾ÝÊý¾ÝÊÖ²áÌá¹©¶ÔÓ¦µÄºê¶¨Òå
#define	    BRIGHTNESS	  0xCF			//ÁÁ¶È
#define     X_WIDTH       128				//¿í¶È
#define     Y_WIDTH       64				//³¤¶È
#define		  PAGE			    8					//Ò³Êý
#define			MAX_CHAR_POSX X_WIDTH-6 //×Ö·û¿í¶ÈÐèÒª-6
#define			MAX_CHAR_POSY Y_WIDTH-6 //×Ö·û³¤¶ÈÐèÒª-6

//function-------------------------------------------
//OLEDµÄ³õÊ¼»¯
void OLED_Init(void);
//Ð´Êý¾Ý
void OLED_WR_Byte(uint8_t dat, uint8_t cmd);
//¿ªÆôOLEDÏÔÊ¾---------------------------
void OLED_DisPlay_On(void);
//¹Ø±ÕOLEDÏÔÊ--------------------------------------¾ 
void OLED_DisPlay_Off(void);
//¸üÐÂÏÔ´æµ½OLED--------------------------------------	
void OLED_Refresh(void);
//ÇåÆÁº¯Êý-----------------------------------------
void OLED_Clear(void);
//»­µã(½÷¼ÇXYµÄ·¶Î§)
//x:0~127
//y:0~63
void OLED_DrawPoint(uint8_t x,uint8_t y);
//Çå³ýÒ»¸öµã(½÷¼ÇXYµÄ·¶Î§)
//x:0~127
//y:0~63
void OLED_ClearPoint(uint8_t x,uint8_t y);
//»­Ïß
//x:0~127
//y:0~63
//x1,y1£ºÆðµã×ø±ê
//x2,y2£ºÖÕµã×ø±ê
void OLED_DrawLine(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2);
//x,y:Ô²ÐÄ×ø±ê
//r:Ô²µÄ°ë¾¶
void OLED_DrawCircle(uint8_t x,uint8_t y,uint8_t r);
//ÔÚÖ¸¶¨Î»ÖÃÏÔÊ¾Ò»¸ö×Ö·û,°üÀ¨²¿·Ö×Ö·û
//x:0~127
//y:0~63
//size:Ñ¡Ôñ×ÖÌå 12/16/24
void OLED_ShowChar(uint8_t x,uint8_t y,uint8_t chr,uint8_t size1);
//ÏÔÊ¾×Ö·û´®
//x,y:Æðµã×ø±ê  
//size1:×ÖÌå´óÐ¡ 
//*chr:×Ö·û´®ÆðÊ¼µØÖ· 
void OLED_ShowString(uint8_t x,uint8_t y,uint8_t *chr,uint8_t size1);
//m^n
uint32_t OLED_Pow(uint8_t m,uint8_t n);
////ÏÔÊ¾2¸öÊý×Ö
////x,y :Æðµã×ø±ê	 
////len :Êý×ÖµÄÎ»Êý
////size:×ÖÌå´óÐ¡
void OLED_ShowNum(uint8_t x,uint8_t y,uint32_t num,uint8_t len,uint8_t size1);
//ÏÔÊ¾ºº×Ö
//x,y:Æðµã×ø±ê
//num:ºº×Ö¶ÔÓ¦µÄÐòºÅ
void OLED_ShowChinese(uint8_t x,uint8_t y,uint8_t num,uint8_t size1);
//num ÏÔÊ¾ºº×ÖµÄ¸öÊý
//space Ã¿Ò»±éÏÔÊ¾µÄ¼ä¸ô
void OLED_ScrollDisplay(uint8_t num,uint8_t space);
//ÅäÖÃÐ´ÈëÊý¾ÝµÄÆðÊ¼Î»ÖÃ
void OLED_WR_BP(uint8_t x,uint8_t y);
//x0,y0£ºÆðµã×ø±ê
//x1,y1£ºÖÕµã×ø±ê
//BMP[]£ºÒªÐ´ÈëµÄÍ¼Æ¬Êý×é
void OLED_ShowPicture(uint8_t x0,uint8_t y0,uint8_t x1,uint8_t y1,uint8_t BMP[]);
//·´ÏÔº¯Êý
void OLED_ColorTurn(uint8_t i);
//ÆÁÄ»Ðý×ª180¶È
void OLED_DisplayTurn(uint8_t i);

//º¯ÊýËµÃ÷£º¼ì²âÄ£Ê½£¬10s£¬ÏÔÊ¾ÒÑÁ¬½ÓºÍÎ´Á¬½Ó¸ü»»
//Ö®ºóÍ¨¹ý´®¿ÚÏÔÊ¾

#endif //__OLED__H
