/**
  ******************************************************************************
  * @file   bq78350.h
  * @brief  
  ******************************************************************************
  */

#ifndef  _BQ78350_H_
#define  _BQ78350_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stm32f1xx_hal.h>
#include "stdbool.h"	
	
#define POWER_OUT_Pin GPIO_PIN_12
#define POWER_OUT_GPIO_Port GPIOB
	
#define   READ_TIMEOUT            20
#define 	BQ78350_ADDR					  0x16		//器件地址

/* SBS Commands Summary -----------------------------------------------------------*/
#define 	ManufacturerAccess		  0x00		//写入指定信息
#define 	RemainingCapacityAlarm	0x01		//容量警告值设置	R/W
#define 	RemainingTimeAlarm			0x02		//剩余运行时间警告值设置	R/W
#define 	BatteryMode							0x03		//选择电池运行模式	R/W
#define 	Temperature	  		      0x08		//温度最大值或平均值
#define 	Voltage									0x09		//总电压	R
#define 	Current									0x0A		//充放电电流	R 
#define   AverageCurrent          0x0B    //平均充放电电流	R 
#define 	MaxError								0x0C		//充电计算错误率
#define 	RelativeStateOfCharge		0x0D		//剩余电量百分比-相对	R
#define 	AbsoluteStateOfCharge		0x0E		//剩余电量百分比-绝对	R
#define 	RemainingCapacity				0x0F		//剩余电量	R
#define 	FullChargeCapacity			0x10		//满充预测容量
#define 	RunTimeToEmpty					0x11		//剩余运行时间 	R
#define   AverageTimeToEmpty      0x12    //剩余运行时间 R 
#define 	AverageTimeToFull				0x13		//剩余充电时间 	R
#define 	ChargingCurrent					0x14		//最大充电电流 	R
#define 	ChargingVoltage					0x15		//最大充电电压 	R
#define 	BatteryStatus						0x16		//电池状态 R
#define 	CycleCount							0x17		//循环次数 R r/w
#define 	DesignCapacity					0x18		//设计容量 R r/w
#define 	DesignVoltage						0x19 		//设计单体/整体电压 R r/w
#define 	SpecificationInfo				0x1A		//数据缩放 R
#define   ManufacturerData        0x54		//获得OperationStatus数据 R
#define 	HostFETControl					0x2B		//主机控制MOS管 R/W
#define 	VAUXVoltage							0x2E		//VAUX电压	R
#define 	CellVoltage1		        0x3F		//电池1电压地址 R
#define 	CellVoltage2		        0x3E		//电池2电压地址	R
#define 	CellVoltage3		        0x3D		//电池3电压地址	R
#define 	CellVoltage4		        0x3C		//电池4电压地址	R
#define 	CellVoltage5		        0x3B		//电池5电压地址	R
#define 	ManufacturerBlockAccess	0x44		//以块格式写入/读取指定信息
#define 	DynamicPower						0x4C		//运行功率  R
#define 	ExtAveCellVoltage				0x4D		//返回EDV参数	R
#define 	StateOfHealth						0x4F		//SOH - 容量和能量	R
#define 	SafetyAlert							0x50		//安全警报
#define 	SafetyStatus						0x51		//安全状态
#define 	PFAlert									0x52		//PF警报
#define 	PFStatus								0x53		//PF状态
#define 	OperationStatus					0x54		//Operation状态
#define 	ChargingStatus					0x55		//充电状态
#define 	GaugingStatus						0x56		//测量状态

																																									
/*设置 */
#define 	DeviceType 								0x0001	//设备类型
#define 	FirmwareVersion 					0x0002	//固件版本
#define 	HardwareVersion 					0x0003	//硬件版本
#define 	IFChecksum 								0x0004	//Flash签名
#define 	StaticDFSignature 				0x0005	//
#define 	ChemID 										0x0006
#define 	StaticChemDFSignature 		0x0008
#define   AllDFSignature						0x0009
#define 	ShutdownMode 							0x0010	//关机模式
#define 	SleepMode 								0x0011	//睡眠模式
#define 	DeviceReset 							0x0012	//设备复位
#define 	CellBalanceToggle 				0x001B 	//单元平衡切换
#define 	AFEDelayDisable 					0x001C	//AFE延迟禁用
#define 	SAFEToggle 								0x001D	
#define 	PrechargeFET 							0x001E	//打开/关闭Pre-CHG FET驱动功能
#define 	ChargeFET 								0x001F	//打开/关闭CHG FET驱动功能
#define 	DischargeFET 							0x0020 	//打开/关闭DSG FET驱动功能
#define 	Gauging 								 	0x0021	
#define 	FETControl 								0x0022	//禁用/启用固件对CHG，DSG和PCHG FET的控制
#define 	LifetimeDataCollection 		0x0023
#define 	PermanentFailure 					0x0024
#define 	BlackBoxRecorder 					0x0025
#define 	SAFE 											0x0026
#define 	LEDDisplayEnable 					0x0027
#define 	LifetimeDataReset 				0x0028
#define 	PermanentFailureDataReset 0x0029
#define 	BlackBoxRecorderReset 		0x002A
#define 	LED_Toggle 								0x002B
#define 	LEDDisplayPress 					0x002C
#define 	CalibrationMode 					0x002D
#define 	SealDevice 								0x0030
#define 	SecurityKeys 							0x0035
#define 	AuthenticationKey 				0x0037
#define 	Balancing_Configuration		0x460C		//电池均衡设置

/* Private type --------------------------------------------------------------*/

//BatteryStatus数据
typedef enum
{
	OK = 0,
	BUSY,
	RESERVED_COMMAND,
	UNSUPPORTED_COMMAND,
	ACCESS_DENIED,
	OVERFLOW_OR_UNDERFLOW,
	BADSIZE,
	UNKNOWN
}BatSta_Err_e;
typedef struct 
{
	bool _OverChargedAlarm;
	bool _TerminateChargeAlarm;
	bool _OverTemperatureAlarm;
	bool _TerminateDischargeAlarm;
	bool _RemainingCapacityAlarm;
	bool _RemainingTimeAlarm;
	bool _isInitialization;
	bool _isDischargingOrRest;
	bool _isFullyCharged;
	bool _isFullyDischarged;
	BatSta_Err_e _err_code;
} BatteryStatus_t;

//OperationStatus数据
typedef enum 
{
	Reserved = 0,
	FullAccess,
	Unsealed,
	Sealed
}SECURITY_MODE_e;
typedef struct 
{
	bool _KEYIN;
	bool _isCellBalancingStatus;
	bool _isCCMeasInSleepMode;
	bool _isADCMeasInSleepMode;
	bool _isInitAfterFullReset;
	bool _SleepM;
	bool _is400KHzSBSMode;
	bool _CaliOffset;
	bool _CaliOutput;
	bool _AUTH;
	bool _isLedON;
	bool _SDM;
	bool _Sleep;
	bool _isCHGDisabled;
	bool _isDSGDisabled;
	bool _PF;
	bool _SafeytyModeStatus;
	bool _SDV;	
  SECURITY_MODE_e _security_mode;
	bool _SAFE;
	bool _HCFET;
	bool _PCHG;
	bool _DSG;
	bool _CHG;
	bool _PRES;
}OperationStatus_t;


//SafetyAlert数据
typedef struct
{
	bool _OverCharge;
	bool _ChargeTimeoutSuspend;
	bool _preCHGTimeoutSuspend;
	bool _OCDL;
	bool _OverTemperatureFault;
	bool _AFE_OVRD;
	bool _UTD;
	bool _UTC;
	bool _OTD;
	bool _OTC;
	bool _ASCDL;
	bool _ASCD;
	bool _AOLDL;
	bool _AOLD;
	bool _OCD;
	bool _OCC;
	bool _COV;
	bool _CUV;
}SafetyAlert_t;

//SafetyStatus数据
typedef struct
{
	bool _OverCharge;
	bool _ChargeTimeout;
	bool _PreCHGTimeout;
	bool _OCDL;
	bool _OverTemperatureFault;
	bool _AFE_OVRD;
	bool _UTD;
	bool _UTC;
	bool _OTD;
	bool _OTC;
	bool _ASCDL;
	bool _ASCD;
	bool _AOLDL;
	bool _AOLD;
	bool _OCD;
	bool _OCC;
	bool _COV;
	bool _CUV;
}SafetyStatus_t;


//PFAlert数据

typedef struct
{
	bool _SOTF;
	bool _TS3;
	bool _TS2;
	bool _TS1;
	bool _AFE_XRDY;
	bool _AFE_OVRD;
	bool _AFEC;
	bool _AFER;
	bool _DFETF;
	bool _CFETF;
	bool _VIMR;
	bool _SOT;
	bool _SOCD;
	bool _SOCC;
	bool _SOV;
	bool _SUV;
}PFAlert_t;


//PFStatus数据
typedef struct
{
	bool _DFW;
	bool _IFC;
	bool _SOTF;
	bool _TS3;
	bool _TS2;
	bool _TS1;
	bool _AFE_XRDY;
	bool _AFE_OVRD;
	bool _AFEC;
	bool _AFER;
	bool _DFETF;
	bool _CFETF;
	bool _VIMR;
	bool _SOT;
	bool _SOCD;
	bool _SOCC;
	bool _SOV;
	bool _SUV;
}PFStatus_t;

//GaugingStatus数据
typedef struct
{
	bool _VDQ;
	bool _EDV2;
	bool _EDV1;
	bool _FCCX;
	bool _OCVFR;
	bool _REST;
	bool _CF;
	bool _DSG;
	bool _EDV0;
	bool _BAL_OK;
	bool _TC;
	bool _TD;
	bool _FC;
	bool _FD;
}GaugingStatus_t;


//电池信息
typedef struct
{
	uint16_t voltage;
	uint16_t current;
	uint16_t temperature; 
	uint16_t residualCapacity;
	uint16_t relativeStateOfCharge;
	uint16_t absoluteStateOfCharge;
	uint16_t remainingCapacity;
	uint16_t fullChargeCapacity;
	uint16_t runTimeToEmpty;
	uint16_t averageTimeToEmpty;
	uint16_t averageTimeToFull;
	uint16_t chargingCurrent;
	uint16_t chargingVoltage;
	BatteryStatus_t batteryStatus; 
	uint16_t cycleCount;
	uint16_t designCapacity;
	OperationStatus_t operationStatus;
	SafetyAlert_t safetyAlert;
	SafetyStatus_t safetyStatus;
	PFAlert_t pFAlert;
	PFStatus_t pFStatus;
	GaugingStatus_t gaugingStatus;
	
}BATTERY_t;
extern BATTERY_t battery;


typedef struct
{
	uint16_t (*getVoltage)(void);
	uint16_t (*getCurrent)(void);
	uint16_t (*getTemperature)(void);
	uint16_t (*getResidualCapacity)(void);
	uint16_t (*getRelativeStateOfCharge)(void);
	uint16_t (*getAbsoluteStateOfCharge)(void);
	uint16_t (*getFullChargeCapacity)(void);
	uint16_t (*getRunTimeToEmpty)(void);
	uint16_t (*getAverageTimeToEmpty)(void);
	uint16_t (*getAverageTimeToFull)(void);
	uint16_t (*getChargingCurrent)(void);
	uint16_t (*getChargingVoltage)(void);
	BatteryStatus_t (*getBatteryStatus)(void);
	uint16_t (*getCycleCount)(void);
	uint16_t (*getDesignCapacity)(void);
	OperationStatus_t (*getOperationStatus)(void);
	SafetyAlert_t (*getSafetyAlert)(void);
	SafetyStatus_t (*getSafetyStatus)(void);
	PFAlert_t (*getPFAlert)(void);
	PFStatus_t (*getPFStatus)(void);
	GaugingStatus_t (*getGaugingStatus)(void);
	bool (*set_power_switch)(GPIO_PinState sta);
}BQ78350_t;

extern BQ78350_t bq78350;
/* Exported function declarations --------------------------------------------*/
void BQ78350_Init(I2C_HandleTypeDef* hi2c);
extern uint16_t getVoltage(void);
extern uint16_t getCurrent(void);
extern uint16_t getTemperature(void);
extern uint16_t getResidualCapacity(void);
extern uint16_t getRelativeStateOfCharge(void);
extern uint16_t getAbsoluteStateOfCharge(void);
extern uint16_t getFullChargeCapacity(void);
extern uint16_t getRunTimeToEmpty(void);
extern uint16_t getAverageTimeToEmpty(void);
extern uint16_t getAverageTimeToFull(void);
extern uint16_t getChargingCurrent(void);
extern uint16_t getChargingVoltage(void);
extern BatteryStatus_t getBatteryStatus(void);
extern uint16_t getCycleCount(void);
extern uint16_t getDesignCapacity(void);
extern OperationStatus_t getOperationStatus(void);
extern SafetyAlert_t getSafetyAlert(void);
extern SafetyStatus_t getSafetyStatus(void);
extern PFAlert_t getPFAlert(void);
extern PFStatus_t getPFStatus(void);
extern GaugingStatus_t getGaugingStatus(void);

extern bool set_power_switch(GPIO_PinState sta);
#ifdef __cplusplus
}
#endif
#endif


