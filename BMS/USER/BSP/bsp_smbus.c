/**
  ******************************************************************************
  * @file   drv_smbus.c
  * @brief  SMBUSЭ�飬��HAL��Ļ����Ͻ��з�װ��
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_smbus.h"


/* Private function declarations ---------------------------------------------*/
static void Error_Handler(void);

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef* hi2cx;


/**
* @brief  IIC ��ʼ��
* @param  hi2c : IIC���.
* @retval None
*/
void SMBUS_Init(I2C_HandleTypeDef* hi2c,uint16_t I2C_ADDRESS,uint8_t *Rxbuffer,uint32_t length)
{
	hi2cx = hi2c;
	if(HAL_I2C_Master_Receive_IT(hi2c, (uint16_t)I2C_ADDRESS, (uint8_t *)Rxbuffer, length) != HAL_OK)
    {
      /* Error_Handler() function is called in case of error. */
			Error_Handler();
    }
}


/**
* @brief  ��I2C�豸�ļĴ���д�����ݣ��෢һ���Ĵ�����ַ��
* @param  DevAddress  : �ӻ���ַ
* @param  MemAddress  : �Ĵ�����ַ
* @param     Data     : ������ʼ��ַ
* @param     Size     : ���ݴ�С
* @refer  �ӻ��Ĵ�����ַĬ��Ϊ8Bit
* @retval HAL_StatusTypeDef : ״̬ 
*/
uint8_t IIC_Write_Mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* Data, uint16_t Size)
{
  return HAL_I2C_Mem_Write(hi2cx, DevAddress, MemAddress, I2C_MEMADD_SIZE_8BIT, Data, Size, 100);
}


/**
* @brief  ��I2C���豸��������
* @param  DevAddress  : �ӻ���ַ
* @param     Data     : ������ʼ��ַ
* @param     Size     : ���ݴ�С
* @retval HAL_StatusTypeDef : ״̬
*/
uint8_t I2C_Master_Transmit(uint16_t DevAddress, uint8_t* Data, uint16_t Size)
{
  return HAL_I2C_Master_Transmit(hi2cx,DevAddress,Data,Size,100);
}


/**
 * @brief  ����������
 * @param  None
 * @retval None
 */ 
static void Error_Handler(void)
{
  /* Nromally the program would never run here. */
  while(1){}
}

