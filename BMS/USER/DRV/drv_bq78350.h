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
#define 	BQ78350_ADDR					  0x16		//������ַ

/* SBS Commands Summary -----------------------------------------------------------*/
#define 	ManufacturerAccess		  0x00		//д��ָ����Ϣ
#define 	RemainingCapacityAlarm	0x01		//��������ֵ����	R/W
#define 	RemainingTimeAlarm			0x02		//ʣ������ʱ�侯��ֵ����	R/W
#define 	BatteryMode							0x03		//ѡ��������ģʽ	R/W
#define 	Temperature	  		      0x08		//�¶����ֵ��ƽ��ֵ
#define 	Voltage									0x09		//�ܵ�ѹ	R
#define 	Current									0x0A		//��ŵ����	R 
#define   AverageCurrent          0x0B    //ƽ����ŵ����	R 
#define 	MaxError								0x0C		//�����������
#define 	RelativeStateOfCharge		0x0D		//ʣ������ٷֱ�-���	R
#define 	AbsoluteStateOfCharge		0x0E		//ʣ������ٷֱ�-����	R
#define 	RemainingCapacity				0x0F		//ʣ�����	R
#define 	FullChargeCapacity			0x10		//����Ԥ������
#define 	RunTimeToEmpty					0x11		//ʣ������ʱ�� 	R
#define   AverageTimeToEmpty      0x12    //ʣ������ʱ�� R 
#define 	AverageTimeToFull				0x13		//ʣ����ʱ�� 	R
#define 	ChargingCurrent					0x14		//�������� 	R
#define 	ChargingVoltage					0x15		//������ѹ 	R
#define 	BatteryStatus						0x16		//���״̬ R
#define 	CycleCount							0x17		//ѭ������ R r/w
#define 	DesignCapacity					0x18		//������� R r/w
#define 	DesignVoltage						0x19 		//��Ƶ���/�����ѹ R r/w
#define 	SpecificationInfo				0x1A		//�������� R
#define   ManufacturerData        0x54		//���OperationStatus���� R
#define 	HostFETControl					0x2B		//��������MOS�� R/W
#define 	VAUXVoltage							0x2E		//VAUX��ѹ	R
#define 	CellVoltage1		        0x3F		//���1��ѹ��ַ R
#define 	CellVoltage2		        0x3E		//���2��ѹ��ַ	R
#define 	CellVoltage3		        0x3D		//���3��ѹ��ַ	R
#define 	CellVoltage4		        0x3C		//���4��ѹ��ַ	R
#define 	CellVoltage5		        0x3B		//���5��ѹ��ַ	R
#define 	ManufacturerBlockAccess	0x44		//�Կ��ʽд��/��ȡָ����Ϣ
#define 	DynamicPower						0x4C		//���й���  R
#define 	ExtAveCellVoltage				0x4D		//����EDV����	R
#define 	StateOfHealth						0x4F		//SOH - ����������	R
#define 	SafetyAlert							0x50		//��ȫ����
#define 	SafetyStatus						0x51		//��ȫ״̬
#define 	PFAlert									0x52		//PF����
#define 	PFStatus								0x53		//PF״̬
#define 	OperationStatus					0x54		//Operation״̬
#define 	ChargingStatus					0x55		//���״̬
#define 	GaugingStatus						0x56		//����״̬

																																									
/*���� */
#define 	DeviceType 								0x0001	//�豸����
#define 	FirmwareVersion 					0x0002	//�̼��汾
#define 	HardwareVersion 					0x0003	//Ӳ���汾
#define 	IFChecksum 								0x0004	//Flashǩ��
#define 	StaticDFSignature 				0x0005	//
#define 	ChemID 										0x0006
#define 	StaticChemDFSignature 		0x0008
#define   AllDFSignature						0x0009
#define 	ShutdownMode 							0x0010	//�ػ�ģʽ
#define 	SleepMode 								0x0011	//˯��ģʽ
#define 	DeviceReset 							0x0012	//�豸��λ
#define 	CellBalanceToggle 				0x001B 	//��Ԫƽ���л�
#define 	AFEDelayDisable 					0x001C	//AFE�ӳٽ���
#define 	SAFEToggle 								0x001D	
#define 	PrechargeFET 							0x001E	//��/�ر�Pre-CHG FET��������
#define 	ChargeFET 								0x001F	//��/�ر�CHG FET��������
#define 	DischargeFET 							0x0020 	//��/�ر�DSG FET��������
#define 	Gauging 								 	0x0021	
#define 	FETControl 								0x0022	//����/���ù̼���CHG��DSG��PCHG FET�Ŀ���
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
#define 	Balancing_Configuration		0x460C		//��ؾ�������

/* Private type --------------------------------------------------------------*/

//BatteryStatus����
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

//OperationStatus����
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


//SafetyAlert����
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

//SafetyStatus����
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


//PFAlert����

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


//PFStatus����
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

//GaugingStatus����
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


//�����Ϣ
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


