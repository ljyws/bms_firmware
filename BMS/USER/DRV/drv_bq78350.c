/**
  ******************************************************************************
  * @file   bq78350.c
  * @brief  
  ******************************************************************************
  */
	
	
/* Includes ------------------------------------------------------------------*/
#include "drv_bq78350.h"
#include "stdbool.h"
#include "cmsis_os.h"

/* Private variables ---------------------------------------------------------*/
static I2C_HandleTypeDef* hi2cx;
BATTERY_t battery;


BQ78350_t bq78350 = {
	getVoltage,
	getCurrent,
	getTemperature,
	getResidualCapacity,
	getRelativeStateOfCharge,
	getAbsoluteStateOfCharge,
	getFullChargeCapacity,
	getRunTimeToEmpty,
	getAverageTimeToEmpty,
	getAverageTimeToFull,
	getChargingCurrent,
	getChargingVoltage,
	getBatteryStatus,
	getCycleCount,
	getDesignCapacity,
	getOperationStatus,
	getSafetyAlert,
	getSafetyStatus,
	getPFAlert,
	getPFStatus,
	getGaugingStatus,
	set_power_switch
};


/**
* @brief  IIC 初始化
* @param  hi2c : IIC句柄.
* @retval None
*/
void BQ78350_Init(I2C_HandleTypeDef* hi2c)
{
	hi2cx  = hi2c;
}

/**
* @brief  获得电池总电压
* @param  void
* @retval 电压 单位：mV
*/
uint16_t getVoltage(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,Voltage,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;		
}
/**
* @brief  获得电池电流
* @param  void
* @retval 电流 单位：mA
*/
uint16_t getCurrent(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,Current,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;	
}
/**
* @brief  获得电池电流
* @param  void
* @retval 电流 单位：mA
*/
uint16_t getTemperature(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,Current,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;	
}
/**
* @brief  获得电池剩余电量
* @param  void
* @retval 剩余电量 
*         当BatteryMode()[CAPM] = 0 单位为mAh
*         当BatteryMode()[CAPM] = 1 单位为10mWh
*/
uint16_t getResidualCapacity(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,RemainingCapacity,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;	
}
/**
* @brief  获得电池电量相对于FullChargeCapacity()电量的百分比
* @param  void
* @retval 电量百分比
*/
uint16_t getRelativeStateOfCharge(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,RelativeStateOfCharge,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;	
}
/**
* @brief  获得电池电量相对于DesignCapacity()电量的百分比
* @param  void
* @retval 电量百分比
*/
uint16_t getAbsoluteStateOfCharge(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,AbsoluteStateOfCharge,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  获得电池满充容量
* @param  void
* @retval 电量 
*         当BatteryMode()[CAPM] = 0 数据为mAh
*         当BatteryMode()[CAPM] = 1 数据为10mWh
*/
uint16_t getFullChargeCapacity(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,FullChargeCapacity,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  以放电速率获得电池剩余运行时间
* @param  void
* @retval 分钟 min
*/
uint16_t getRunTimeToEmpty(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,RunTimeToEmpty,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  以平均电流计算获得电池剩余运行时间
* @param  void
* @retval 分钟 min
*/
uint16_t getAverageTimeToEmpty(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,AverageTimeToEmpty,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  以平均电流计算获得电池剩余充电时间
* @param  void
* @retval 分钟 min
*/
uint16_t getAverageTimeToFull(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,AverageTimeToFull,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  充电电流
* @param  void
* @retval 电流 单位：mA
*/
uint16_t getChargingCurrent(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,ChargingCurrent,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}

/**
* @brief  充电电压
* @param  void
* @retval 电压 单位：mV
*/
uint16_t getChargingVoltage(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,ChargingVoltage,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  获得电池状态
* @param  void
* @retval BatteryStatus_t
*/
BatteryStatus_t getBatteryStatus(void)
{
	uint8_t rxbuf[2];
	BatteryStatus_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,BatteryStatus,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
	{
		sta._OverChargedAlarm 				= (rxbuf[1] >> 7) & 0x01;
		sta._TerminateChargeAlarm 		= (rxbuf[1] >> 6) & 0x01;
		sta._OverTemperatureAlarm 		= (rxbuf[1] >> 4) & 0x01;
		sta._TerminateDischargeAlarm 	= (rxbuf[1] >> 3) & 0x01;
		sta._RemainingCapacityAlarm 	= (rxbuf[1] >> 1) & 0x01;
		sta._RemainingTimeAlarm 			= (rxbuf[1]) 			& 0x01;
		sta._isInitialization					= (rxbuf[0] >> 7) & 0x01;
		sta._isDischargingOrRest			= (rxbuf[0] >> 6) & 0x01;
		sta._isFullyCharged						= (rxbuf[0] >> 5) & 0x01;
		sta._isFullyDischarged				= (rxbuf[0] >> 4) & 0x01;
		sta._err_code									= (rxbuf[0])			& 0x0F;      
	}
	return sta;
}
/**
* @brief  获得电池循环次数
* @param  void
* @retval 单位：cycles
*/
uint16_t getCycleCount(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,CycleCount,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  获得电池设计容量
* @param  void
* @retval 电量
*         当BatteryMode()[CAPM] = 0 数据为mAh
*         当BatteryMode()[CAPM] = 1 数据为10mWh
*/
uint16_t getDesignCapacity(void)
{
	uint8_t rxbuf[2];
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,DesignCapacity,I2C_MEMADD_SIZE_8BIT,rxbuf,2,READ_TIMEOUT) == HAL_OK)
		return rxbuf[1]<<8|rxbuf[0];
	else
		return 0;
}
/**
* @brief  获得Operation状态
* @param  void
* @retval OperationStatus_t
*/
OperationStatus_t getOperationStatus()
{
	uint8_t rxbuf[5];
	OperationStatus_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,OperationStatus,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._KEYIN 									= (rxbuf[4] >> 7) & 0x01;
		sta._isCellBalancingStatus 	= (rxbuf[4] >> 4) & 0x01;
		sta._isCCMeasInSleepMode 	 	= (rxbuf[4] >> 3) & 0x01;
		sta._isADCMeasInSleepMode 	= (rxbuf[4] >> 2) & 0x01;
		sta._isInitAfterFullReset 	= (rxbuf[4]) 			& 0x01;
		sta._SleepM 								= (rxbuf[3] >> 7) & 0x01;
		sta._is400KHzSBSMode 				= (rxbuf[3] >> 6) & 0x01;
		sta._CaliOffset 						= (rxbuf[3] >> 5) & 0x01;
		sta._CaliOutput 						= (rxbuf[3] >> 4) & 0x01;
		sta._AUTH 									= (rxbuf[3] >> 2) & 0x01;
		sta._isLedON 								= (rxbuf[3] >> 1) & 0x01;
		sta._SDM 										= (rxbuf[3]) 			& 0x01;
		sta._Sleep 									= (rxbuf[2] >> 7) & 0x01;
		sta._isCHGDisabled 					= (rxbuf[2] >> 6) & 0x01;
		sta._isDSGDisabled 					= (rxbuf[2] >> 5) & 0x01;
		sta._PF 										= (rxbuf[2] >> 4) & 0x01;
		sta._SafeytyModeStatus 			= (rxbuf[2] >> 3) & 0x01;
		sta._SDV 										= (rxbuf[2] >> 2) & 0x01;
		sta._security_mode 					= (rxbuf[2]) 			& 0x03;
		sta._SAFE 									= (rxbuf[1] >> 5) & 0x01;
		sta._HCFET 									= (rxbuf[1] >> 4) & 0x01;
		sta._PCHG 									= (rxbuf[1] >> 3) & 0x01;
		sta._DSG 										=	(rxbuf[1] >> 2) & 0x01;
		sta._CHG 										= (rxbuf[1] >> 1) & 0x01;
		sta._PRES 									= (rxbuf[1]) 			& 0x01;
	}
	return sta;
}

/**
* @brief  获得SafetyAlert
* @param  void
* @retval OperationStatus_t
*/
SafetyAlert_t getSafetyAlert(void)
{
	uint8_t rxbuf[5];
	SafetyAlert_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,SafetyAlert,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._OverCharge 					= (rxbuf[3] >> 4) & 0x01;
		sta._ChargeTimeoutSuspend = (rxbuf[3] >> 3) & 0x01;
		sta._preCHGTimeoutSuspend = (rxbuf[3] >> 1) & 0x01;
		sta._OCDL 								= (rxbuf[2] >> 6) & 0x01;
		sta._OverTemperatureFault = (rxbuf[2] >> 5) & 0x01;
		sta._AFE_OVRD 						= (rxbuf[2] >> 4) & 0x01;
		sta._UTD									= (rxbuf[2] >> 3) & 0x01;
		sta._UTC 									= (rxbuf[2] >> 2) & 0x01;
		sta._OTD 									= (rxbuf[2] >> 1) & 0x01;
		sta._OTC 									= (rxbuf[2]) 			& 0x01;
		sta._ASCDL 								= (rxbuf[1] >> 7) & 0x01;
		sta._ASCD 								= (rxbuf[1] >> 6) & 0x01;
		sta._AOLDL 								= (rxbuf[1] >> 5) & 0x01;
		sta._AOLD 								= (rxbuf[1] >> 4) & 0x01;
		sta._OCD 									= (rxbuf[1] >> 3) & 0x01;
		sta._OCC 									= (rxbuf[1] >> 2) & 0x01;
		sta._COV 									= (rxbuf[1] >> 1) & 0x01;
		sta._CUV 									= (rxbuf[1]) 			& 0x01;
	}
	return sta;
}

/**
* @brief  获得SafetyStatus
* @param  void
* @retval SafetyStatus_t
*/
SafetyStatus_t getSafetyStatus(void)
{
	uint8_t rxbuf[5];
	SafetyStatus_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,SafetyStatus,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._OverCharge 					= (rxbuf[3] >> 4) & 0x01;
		sta._ChargeTimeout 				= (rxbuf[3] >> 2) & 0x01;
		sta._PreCHGTimeout 				= (rxbuf[3]) 			& 0x01;
		sta._OCDL 								= (rxbuf[2] >> 6) & 0x01;
		sta._OverTemperatureFault = (rxbuf[2] >> 5) & 0x01;
		sta._AFE_OVRD 						= (rxbuf[2] >> 4) & 0x01;
		sta._UTD									= (rxbuf[2] >> 3) & 0x01;
		sta._UTC 									= (rxbuf[2] >> 2) & 0x01;
		sta._OTD 									= (rxbuf[2] >> 1) & 0x01;
		sta._OTC 									= (rxbuf[2]) 			& 0x01;
		sta._ASCDL 								= (rxbuf[1] >> 7) & 0x01;
		sta._ASCD 								= (rxbuf[1] >> 6) & 0x01;
		sta._AOLDL 								= (rxbuf[1] >> 5) & 0x01;
		sta._AOLD 								= (rxbuf[1] >> 4) & 0x01;
		sta._OCD 									= (rxbuf[1] >> 3) & 0x01;
		sta._OCC 									= (rxbuf[1] >> 2) & 0x01;
		sta._COV 									= (rxbuf[1] >> 1) & 0x01;
		sta._CUV 									= (rxbuf[1]) 			& 0x01;
	}
	return sta;
}

/**
* @brief  获得PFAlert
* @param  void
* @retval PFAlert_t
*/
PFAlert_t getPFAlert(void)
{
	uint8_t rxbuf[3];
	PFAlert_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,PFAlert,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._SOTF 		= (rxbuf[2] >> 7) & 0x01;
		sta._TS3 			= (rxbuf[2] >> 6) & 0x01;
		sta._TS2 			= (rxbuf[2] >> 5) & 0x01;
		sta._TS1			= (rxbuf[2] >> 4) & 0x01;
		sta._AFE_XRDY = (rxbuf[2] >> 3) & 0x01;
		sta._AFE_OVRD = (rxbuf[2] >> 2) & 0x01;
		sta._AFEC 		= (rxbuf[2] >> 1) & 0x01;
		sta._AFER 		= (rxbuf[2]) 			& 0x01;
		sta._DFETF 		= (rxbuf[1] >> 7) & 0x01;
		sta._CFETF 		= (rxbuf[1] >> 6) & 0x01;
		sta._VIMR 		= (rxbuf[1] >> 5) & 0x01;
		sta._SOT 			= (rxbuf[1] >> 4) & 0x01;
		sta._SOCD 		= (rxbuf[1] >> 3) & 0x01;
		sta._SOCC			= (rxbuf[1] >> 2) & 0x01;
		sta._SOV   		= (rxbuf[1] >> 1) & 0x01;
		sta._SUV			= (rxbuf[1]) 			& 0x01;	
	}
	return sta;
}

/**
* @brief  获得PFAlert
* @param  void
* @retval PFAlert_t
*/
PFStatus_t getPFStatus(void)
{
	uint8_t rxbuf[5];
	PFStatus_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,PFStatus,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._DFW      = (rxbuf[3] >> 1) & 0x01;
		sta._IFC      = (rxbuf[3])			& 0x01;	
		sta._SOTF 		= (rxbuf[2] >> 7) & 0x01;
		sta._TS3 			= (rxbuf[2] >> 6) & 0x01;
		sta._TS2 			= (rxbuf[2] >> 5) & 0x01;
		sta._TS1			= (rxbuf[2] >> 4) & 0x01;
		sta._AFE_XRDY = (rxbuf[2] >> 3) & 0x01;
		sta._AFE_OVRD = (rxbuf[2] >> 2) & 0x01;
		sta._AFEC 		= (rxbuf[2] >> 1) & 0x01;
		sta._AFER 		= (rxbuf[2]) 			& 0x01;
		sta._DFETF 		= (rxbuf[1] >> 7) & 0x01;
		sta._CFETF 		= (rxbuf[1] >> 6) & 0x01;
		sta._VIMR 		= (rxbuf[1] >> 5) & 0x01;
		sta._SOT 			= (rxbuf[1] >> 4) & 0x01;
		sta._SOCD 		= (rxbuf[1] >> 3) & 0x01;
		sta._SOCC			= (rxbuf[1] >> 2) & 0x01;
		sta._SOV   		= (rxbuf[1] >> 1) & 0x01;
		sta._SUV			= (rxbuf[1]) 			& 0x01;	
	}
	return sta;
}


/**
* @brief  获得GaugingStatus
* @param  void
* @retval GaugingStatus_t
*/
GaugingStatus_t getGaugingStatus(void)
{
	uint8_t rxbuf[3];
	GaugingStatus_t sta;
	if(HAL_I2C_Mem_Read(hi2cx,BQ78350_ADDR,GaugingStatus,I2C_MEMADD_SIZE_8BIT,rxbuf,5,READ_TIMEOUT) == HAL_OK)
	{
		sta._VDQ 		= (rxbuf[2] >> 7) & 0x01;
		sta._EDV2 	= (rxbuf[2] >> 6) & 0x01;
		sta._EDV1 	= (rxbuf[2] >> 5) & 0x01;
		sta._FCCX 	= (rxbuf[2] >> 2) & 0x01;
		sta._OCVFR 	= (rxbuf[2] >> 1) & 0x01;
		sta._REST 	= (rxbuf[2]) 			& 0x01;
		sta._CF 		= (rxbuf[1] >> 7) & 0x01;
		sta._DSG 		= (rxbuf[1] >> 6) & 0x01;
		sta._EDV0 	= (rxbuf[1] >> 5) & 0x01;
		sta._BAL_OK = (rxbuf[1] >> 4) & 0x01;
		sta._TC 		= (rxbuf[1] >> 3) & 0x01;
		sta._TD			= (rxbuf[1] >> 2) & 0x01;
		sta._FC   	= (rxbuf[1] >> 1) & 0x01;
		sta._FD			= (rxbuf[1]) 			& 0x01;	
	}
	return sta;
}

bool set_power_switch(GPIO_PinState sta)
{
	HAL_GPIO_WritePin(POWER_OUT_GPIO_Port,POWER_OUT_Pin,sta);
	return battery.operationStatus._KEYIN;
}





