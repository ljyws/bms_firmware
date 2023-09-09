#include "systemState_task.h"
#include "cmsis_os.h"
#include "drv_key.h"
#include "drv_led.h"
#include "drv_bq78350.h"
#include "drv_rgb.h"
//#include "tim.h"

#define WAIT_LONGPRESS_TIME (200) //10*200 = 2s
SysState_e globalState = SYS_SLEEP;
FSM_EVENT_e fsm_evt;
uint16_t sta_count = 0;
uint16_t led_sta_count = 0;

//状态转移表
SysStateTransform_t SYS_SLEEP_StateTran[] = {
	{SYS_SLEEP, EVT_NULL,							SYS_SLEEP, 	 actionFun},    	//无事件
	{SYS_SLEEP, EVT_TIMEOUT,					SYS_SLEEP, 	 actionFun},    	//超时事件
	{SYS_SLEEP, EVT_KEY_SINGLECLICK, 	SYS_WAKE_UP, actionFun},			//短按事件
	{SYS_SLEEP, EVT_KEY_LONGPRESS,  	SYS_SLEEP, 	 actionFun},			//长按事件
};

SysStateTransform_t SYS_WAKE_UP_StateTran[] = {
	{SYS_WAKE_UP, EVT_NULL,							SYS_WAKE_UP, actionFun},    //无事件
	{SYS_WAKE_UP, EVT_TIMEOUT,					SYS_SLEEP, 	 actionFun},    //超时事件
	{SYS_WAKE_UP, EVT_KEY_SINGLECLICK, 	SYS_WAKE_UP, actionFun},		//短按事件
	{SYS_WAKE_UP, EVT_KEY_LONGPRESS,  	SYS_WORKING, actionFun},		//长按事件
};

SysStateTransform_t SYS_WORKING_StateTran[] = {
	{SYS_WORKING, EVT_NULL,							SYS_WORKING, 	  actionFun},  //无事件
	{SYS_WORKING, EVT_TIMEOUT,					SYS_WORKING, 		actionFun},  //超时事件
	{SYS_WORKING, EVT_KEY_SINGLECLICK, 	SYS_WAIT_SLEEP, actionFun},	 //短按事件
	{SYS_WORKING, EVT_KEY_LONGPRESS,  	SYS_WORKING, 		actionFun},	 //长按事件
};

SysStateTransform_t SYS_WAIT_SLEEP_StateTran[] = {
	{SYS_WAIT_SLEEP, EVT_NULL,						SYS_WAIT_SLEEP, actionFun},//无事件
	{SYS_WAIT_SLEEP, EVT_TIMEOUT,					SYS_WORKING,    actionFun},//超时事件
	{SYS_WAIT_SLEEP, EVT_KEY_SINGLECLICK, SYS_WAIT_SLEEP, actionFun},//短按事件
	{SYS_WAIT_SLEEP, EVT_KEY_LONGPRESS,  	SYS_SLEEP,      actionFun},//长按事件
};

void sysState_task(void *argument)
{
  for(;;)
  {
		eventTrigger();
		switch(globalState)
		{
			case SYS_SLEEP:
				do_action(&SYS_SLEEP_StateTran[fsm_evt]);
				break;
			case SYS_WAKE_UP:
				do_action(&SYS_WAKE_UP_StateTran[fsm_evt]);
				break;
			case SYS_WORKING:
				do_action(&SYS_WORKING_StateTran[fsm_evt]);
				break;
			case SYS_WAIT_SLEEP:
				do_action(&SYS_WAIT_SLEEP_StateTran[fsm_evt]);
				break;
			default:break;
		}
    osDelay(10);
  }

}

bool actionFun(void *arg)
{
	SysStateTransform_t *staTran = (SysStateTransform_t*)arg;
	if(staTran->current_state != staTran->next_state)
		sta_count = 0;
	switch(staTran->current_state)
	{
		case SYS_SLEEP:
			SYS_SLEEP_callback();
			break;
		case SYS_WAKE_UP:
			SYS_WAKE_UP_callback();
			break;
		case SYS_WORKING:
			SYS_WORKING_callback();
			break;
		case SYS_WAIT_SLEEP:
			SYS_WAIT_SLEEP_callback();
			break;
		default:break;
	}
	return true;
}

void do_action(SysStateTransform_t *staTran)
{
	if(staTran == NULL)
		return;
	globalState = staTran->next_state;
	if(staTran->actionFun != NULL)
		staTran->actionFun((void*)staTran);
	else
		return;
}

void eventTrigger()
{
	sta_count++;
	if(keyCfg.key_event)
		fsm_evt = ((int)keyCfg.key_event + 1);
	else if(sta_count <= WAIT_LONGPRESS_TIME)
		fsm_evt = EVT_NULL;
	else 
		fsm_evt = EVT_TIMEOUT;
}

void SYS_SLEEP_callback(void)
{
	//rgb_set(&htim1,0,0,0);
	bq78350.set_power_switch(off);
	all_led_ctrl(off);
}
void SYS_WAKE_UP_callback(void)
{
	
	if(keyCfg.key_action == PRESS)
	{
		led_sta_count++;
		sta_count = 0;
		//rgb_set(&htim1,250-(3.125*led_sta_count),(3.125*led_sta_count),0);
		switch(led_sta_count)
			{
				case 20:
					led_ctrl_num(1);
					break;
				case 40:
					led_ctrl_num(2);
					break;
				case 60:
					led_ctrl_num(3);
					break;
				case 80:
					led_ctrl_num(4);
					break;
				default:break;
			}
	}else
	{
		//rgb_set(&htim1,255,0,0);
		led_sta_count = 0;
		displayBattery();
	}
}
void SYS_WORKING_callback(void)
{
	//rgb_set(&htim1,0,255,0);
	bq78350.set_power_switch(on);
	displayBattery();
}
void SYS_WAIT_SLEEP_callback(void)
{
	if(keyCfg.key_action == PRESS)
	{
		led_sta_count++;
		sta_count = 0;
		//rgb_set(&htim1,(3.125*led_sta_count),250-(3.125*led_sta_count),0);
		switch(led_sta_count)
			{
				case 20:
					led_ctrl_num(4);
					break;
				case 40:
					led_ctrl_num(3);
					break;
				case 60:
					led_ctrl_num(2);
					break;
				case 80:
					led_ctrl_num(1);
					break;
				default:break;
			}
	}else
	{
		//rgb_set(&htim1,0,255,0);
		led_sta_count = 0;
		all_led_ctrl(on);
	}
}
