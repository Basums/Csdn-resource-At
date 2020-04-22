#include "ds18b20.h"

#include "delay.h"



/****************************************************************************
// 函 数 名:      DS18B20_Init()
// 函数功能描述:  温度传感器初始化引脚
// 参数描述:      无
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
void DS18B20_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct;
	DS18B20_GPIO_CLK_ENABLE();
	GPIO_InitStruct.Pin   = DS18B20_DQ_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  HAL_GPIO_Init(DS18B20_DQ_PORT, &GPIO_InitStruct);
	
	DS18B20_DQ_PIN_HIGH();
	//HAL_TIM_Base_Stop(&htim3);
}

/****************************************************************************
// 函 数 名:      DS18B20_Set_xxput()
// 函数功能描述:  温度传感器更改输入输出口
// 参数描述:      无
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
void DS18B20_Set_Input()
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    /*Configure GPIO pin : PE13 */
	DS18B20_GPIO_CLK_ENABLE();
	GPIO_InitStruct.Pin   = DS18B20_DQ_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_INPUT;
	HAL_GPIO_Init(DS18B20_DQ_PORT, &GPIO_InitStruct);
}

void DS18B20_Set_Output()
{
	GPIO_InitTypeDef GPIO_InitStruct;
    
    /*Configure GPIO pin : PE13 */
	DS18B20_GPIO_CLK_ENABLE();
	GPIO_InitStruct.Pin   = DS18B20_DQ_PIN;
	GPIO_InitStruct.Mode  = GPIO_MODE_OUTPUT_OD;
	GPIO_InitStruct.Pull  = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(DS18B20_DQ_PORT, &GPIO_InitStruct);
}


/****************************************************************************
// 函 数 名:      DS18B20_Reset()
// 函数功能描述:  温度传感器复位
// 参数描述:      无
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
void DS18B20_Reset()
{
	DS18B20_Set_Output();
	DS18B20_DQ_PIN_LOW();
	delay_us(750);
	DS18B20_DQ_PIN_HIGH();
	delay_us(15);
}

/****************************************************************************
// 函 数 名:      DS18B20_Presence()
// 函数功能描述:  温度传感器监测存在脉冲
// 参数描述:      无
// 返 回 值:      BOOL 是否存在
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
int DS18B20_Presence()
{
	uint8_t pulse_time = 0;
	DS18B20_Set_Input();
	
	// 时序图见 http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// 初始化时序：包括高电平的等待脉冲(15~60us)和低电平的存在脉冲(60~240us)
	while(GET_DS18B20_DQ_PIN() && pulse_time < 100)
	{
		pulse_time ++;
		delay_us(1);
	}
	if(pulse_time >= 100)
	{
		return 0;
	}
	else
	{
		pulse_time = 0;
	}
	while(!GET_DS18B20_DQ_PIN() && pulse_time < 240)
	{
		pulse_time ++;
		delay_us(1);
	}
	if(pulse_time >= 240)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/****************************************************************************
// 函 数 名:      DS18B20_WriteByte(uint8_t dat)
// 函数功能描述:  温度传感器写操作, LSB在先
// 参数描述:      dat: 要写的数据
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
void DS18B20_WriteByte(uint8_t dat)
{
	DS18B20_Set_Output();
	
	// 时序图见 http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// 写时序：写时序一开始先拉低总线，然后再写0和1，且持续时间至少为60us。从机看到低电平15us后接受数据
	for(uint8_t i = 0; i < 8; i++)
	{
		uint8_t LSB = dat & 0x01;
		dat = dat >> 1;
		if(LSB)
		{
			DS18B20_DQ_PIN_LOW();
			delay_us(10);
			DS18B20_DQ_PIN_HIGH();
			delay_us(65);   //...
		}
		else
		{
			DS18B20_DQ_PIN_LOW();
			delay_us(68);	//...
			DS18B20_DQ_PIN_HIGH();
			delay_us(2);
		}
	}
}

/****************************************************************************
// 函 数 名:      DS18B20_ReadBit()
// 函数功能描述:  温度传感器读位操作
// 参数描述:      无
// 返 回 值:      0或1
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
uint8_t DS18B20_ReadBit(void)
{
	uint8_t dat;
	
	// 时序图见 http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// 读时序：读时序一开始先拉低总线，然后再读0和1，且持续时间至少为45us。主机看到低电平15us后采样
	DS18B20_Set_Output();
	DS18B20_DQ_PIN_LOW();
//	Delay_us(10);
	
	DS18B20_Set_Input();
	if(GET_DS18B20_DQ_PIN())
	{
		dat = 1;
	}
	else
	{
		dat = 0;
	}
	delay_us(45);
	
	return dat;
}


/****************************************************************************
// 函 数 名:      DS18B20_ReadByte()
// 函数功能描述:  温度传感器读比特操作, LSB在先
// 参数描述:      无
// 返 回 值:      8位数据
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
uint8_t DS18B20_ReadByte()
{
	uint8_t dat = 0;
	
	for(uint8_t i = 0; i < 8;i ++)
	{
		uint8_t bit = DS18B20_ReadBit();
		dat = (dat)|(bit << i);
	}
	
	return dat;
}

/****************************************************************************
// 函 数 名:      DS18B20_Start()
// 函数功能描述:  温度传感器开始温度转换
// 参数描述:      无
// 返 回 值:      无
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
void DS18B20_Start()
{
	DS18B20_Reset();
	DS18B20_Presence();
	delay_us(400);
	DS18B20_WriteByte(0xcc); 	// 跳过ROM
	DS18B20_WriteByte(0x44); 	// 温度变换
}

/****************************************************************************
// 函 数 名:      DS18B20_Get_Temp()
// 函数功能描述:  温度传感器获得温度
// 参数描述:      无
// 返 回 值:      扩大十倍后的温度值(-550~1250)
// 返回值描述:    无
// 全局变量:      无
// 函数状态：     已经完成测试
// 函数层次：     软件应用层

// 创 建 人：     jlm
// 日期：         2019-4-5
// 修 改 人：                     
// 修改日期：     201x-xx-xx
****************************************************************************/
short DS18B20_Get_Temp()
{
	short Temp;
	int flag;
	
	DS18B20_Start();
	DS18B20_Reset();
	DS18B20_Presence();
	delay_us(400);
	DS18B20_WriteByte(0xcc); 	// 跳过ROM
	DS18B20_WriteByte(0xbe); 	// 读温度值


	uint8_t TempLSB = DS18B20_ReadByte();
	uint8_t TempMSB = DS18B20_ReadByte();
	
	if(TempMSB > 7)				// 如果是负温度，详情看寄存器
	{
		TempMSB = ~TempMSB;
		TempLSB = ~TempLSB;
		flag = 0;		// 负数
	}
	else
	{
		flag = 1;		// 正数
	}
	
	Temp = TempMSB;
	Temp <<= 8;
	Temp += TempLSB;
	Temp = (double)Temp * 0.625;	// 扩大十倍，原本应该0.0625
	
	if(flag)
	{
		return Temp;
	}
	else
	{
		return -Temp;
	}
}
