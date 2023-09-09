#include "bqRead_task.h"
#include "cmsis_os.h"
#include "main.h"
#include "drv_bq78350.h"
#include "drv_key.h"

void bqRead_task(void *argument)
{

  for(;;)
  {
		battery.voltage 							= bq78350.getVoltage();
		battery.current 							= bq78350.getCurrent();
		battery.temperature           = bq78350.getTemperature();
		battery.residualCapacity 			= bq78350.getResidualCapacity();
		battery.relativeStateOfCharge = bq78350.getRelativeStateOfCharge();
		battery.absoluteStateOfCharge = bq78350.getAbsoluteStateOfCharge();
		battery.fullChargeCapacity    = bq78350.getFullChargeCapacity();
		battery.runTimeToEmpty 				= bq78350.getRunTimeToEmpty();
		battery.averageTimeToEmpty    = bq78350.getAverageTimeToEmpty();
		battery.averageTimeToFull     = bq78350.getAverageTimeToFull();
		battery.chargingVoltage       = bq78350.getChargingVoltage();
		battery.chargingCurrent       = bq78350.getChargingCurrent();
		battery.batteryStatus 				= bq78350.getBatteryStatus();
		battery.cycleCount            = bq78350.getCycleCount();
		battery.designCapacity        = bq78350.getDesignCapacity();
		battery.operationStatus 			= bq78350.getOperationStatus();
		battery.pFAlert 							= bq78350.getPFAlert();
		battery.pFStatus 							= bq78350.getPFStatus();
		battery.safetyAlert 					= bq78350.getSafetyAlert();
		battery.safetyStatus 					= bq78350.getSafetyStatus();
		battery.gaugingStatus					= bq78350.getGaugingStatus();
		
		osDelay(50);
		
  }

}
