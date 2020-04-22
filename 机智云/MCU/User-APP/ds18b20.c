#include "ds18b20.h"

#include "delay.h"



/****************************************************************************
// �� �� ��:      DS18B20_Init()
// ������������:  �¶ȴ�������ʼ������
// ��������:      ��
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      DS18B20_Set_xxput()
// ������������:  �¶ȴ������������������
// ��������:      ��
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      DS18B20_Reset()
// ������������:  �¶ȴ�������λ
// ��������:      ��
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      DS18B20_Presence()
// ������������:  �¶ȴ���������������
// ��������:      ��
// �� �� ֵ:      BOOL �Ƿ����
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
int DS18B20_Presence()
{
	uint8_t pulse_time = 0;
	DS18B20_Set_Input();
	
	// ʱ��ͼ�� http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// ��ʼ��ʱ�򣺰����ߵ�ƽ�ĵȴ�����(15~60us)�͵͵�ƽ�Ĵ�������(60~240us)
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
// �� �� ��:      DS18B20_WriteByte(uint8_t dat)
// ������������:  �¶ȴ�����д����, LSB����
// ��������:      dat: Ҫд������
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void DS18B20_WriteByte(uint8_t dat)
{
	DS18B20_Set_Output();
	
	// ʱ��ͼ�� http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// дʱ��дʱ��һ��ʼ���������ߣ�Ȼ����д0��1���ҳ���ʱ������Ϊ60us���ӻ������͵�ƽ15us���������
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
// �� �� ��:      DS18B20_ReadBit()
// ������������:  �¶ȴ�������λ����
// ��������:      ��
// �� �� ֵ:      0��1
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
uint8_t DS18B20_ReadBit(void)
{
	uint8_t dat;
	
	// ʱ��ͼ�� http://www.21ic.com/jichuzhishi/datasheet/DS18B20/data/187578.html
	// ��ʱ�򣺶�ʱ��һ��ʼ���������ߣ�Ȼ���ٶ�0��1���ҳ���ʱ������Ϊ45us�����������͵�ƽ15us�����
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
// �� �� ��:      DS18B20_ReadByte()
// ������������:  �¶ȴ����������ز���, LSB����
// ��������:      ��
// �� �� ֵ:      8λ����
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
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
// �� �� ��:      DS18B20_Start()
// ������������:  �¶ȴ�������ʼ�¶�ת��
// ��������:      ��
// �� �� ֵ:      ��
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
void DS18B20_Start()
{
	DS18B20_Reset();
	DS18B20_Presence();
	delay_us(400);
	DS18B20_WriteByte(0xcc); 	// ����ROM
	DS18B20_WriteByte(0x44); 	// �¶ȱ任
}

/****************************************************************************
// �� �� ��:      DS18B20_Get_Temp()
// ������������:  �¶ȴ���������¶�
// ��������:      ��
// �� �� ֵ:      ����ʮ������¶�ֵ(-550~1250)
// ����ֵ����:    ��
// ȫ�ֱ���:      ��
// ����״̬��     �Ѿ���ɲ���
// ������Σ�     ���Ӧ�ò�

// �� �� �ˣ�     jlm
// ���ڣ�         2019-4-5
// �� �� �ˣ�                     
// �޸����ڣ�     201x-xx-xx
****************************************************************************/
short DS18B20_Get_Temp()
{
	short Temp;
	int flag;
	
	DS18B20_Start();
	DS18B20_Reset();
	DS18B20_Presence();
	delay_us(400);
	DS18B20_WriteByte(0xcc); 	// ����ROM
	DS18B20_WriteByte(0xbe); 	// ���¶�ֵ


	uint8_t TempLSB = DS18B20_ReadByte();
	uint8_t TempMSB = DS18B20_ReadByte();
	
	if(TempMSB > 7)				// ����Ǹ��¶ȣ����鿴�Ĵ���
	{
		TempMSB = ~TempMSB;
		TempLSB = ~TempLSB;
		flag = 0;		// ����
	}
	else
	{
		flag = 1;		// ����
	}
	
	Temp = TempMSB;
	Temp <<= 8;
	Temp += TempLSB;
	Temp = (double)Temp * 0.625;	// ����ʮ����ԭ��Ӧ��0.0625
	
	if(flag)
	{
		return Temp;
	}
	else
	{
		return -Temp;
	}
}
