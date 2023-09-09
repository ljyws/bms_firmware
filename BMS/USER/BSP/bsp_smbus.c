/**
  ******************************************************************************
  * @file   drv_smbus.c
  * @brief  SMBUS协议，在HAL库的基础上进行封装。
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "bsp_smbus.h"


/* Private function declarations ---------------------------------------------*/
static void Error_Handler(void);

/* Private variables ---------------------------------------------------------*/
I2C_HandleTypeDef* hi2cx;


/**
* @brief  IIC 初始化
* @param  hi2c : IIC句柄.
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
* @brief  向I2C设备的寄存器写入数据（多发一个寄存器地址）
* @param  DevAddress  : 从机地址
* @param  MemAddress  : 寄存器地址
* @param     Data     : 数据起始地址
* @param     Size     : 数据大小
* @refer  从机寄存器地址默认为8Bit
* @retval HAL_StatusTypeDef : 状态 
*/
uint8_t IIC_Write_Mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* Data, uint16_t Size)
{
  return HAL_I2C_Mem_Write(hi2cx, DevAddress, MemAddress, I2C_MEMADD_SIZE_8BIT, Data, Size, 100);
}


/**
* @brief  向I2C从设备发送数据
* @param  DevAddress  : 从机地址
* @param     Data     : 数据起始地址
* @param     Size     : 数据大小
* @retval HAL_StatusTypeDef : 状态
*/
uint8_t I2C_Master_Transmit(uint16_t DevAddress, uint8_t* Data, uint16_t Size)
{
  return HAL_I2C_Master_Transmit(hi2cx,DevAddress,Data,Size,100);
}


/**
 * @brief  错误发生函数
 * @param  None
 * @retval None
 */ 
static void Error_Handler(void)
{
  /* Nromally the program would never run here. */
  while(1){}
}

