/**
  ******************************************************************************
  * @file   drv_smbus.h
  * @brief  SMBUS
  ******************************************************************************
  */

#ifndef __DRV_SMBUS_H__
#define __DRV_SMBUS_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32f1xx_hal.h>
	
/* Exported function declarations --------------------------------------------*/
void SMBUS_Init(I2C_HandleTypeDef* hi2c,uint16_t I2C_ADDRESS,uint8_t *Rxbuffer,uint32_t length);
uint8_t IIC_Write_Mem(uint16_t DevAddress, uint16_t MemAddress, uint8_t* Data,  uint16_t Size);
uint8_t I2C_Master_Transmit(uint16_t DevAddress, uint8_t* Data, uint16_t Size);


uint16_t getVoltage(void);


	#ifdef __cplusplus
}
#endif
#endif

