#include "drv_key.h"
#include "main.h"

static KeyPinLevel_e keyReadPin(void);   // 按键读取按键的电平函数
static void KEY_GetAction_PressOrRelease(void); // 获取按键是按下还是释放，保存到结构体

KeyConfig_t keyCfg = {
	0,
	RELEASE,
	KEY_IDLE,
	KEY_NULL,
	keyReadPin
};

static KeyPinLevel_e keyReadPin(void)
{
	return (KeyPinLevel_e) HAL_GPIO_ReadPin(KEY_GPIO_Port,KEY_Pin);
}

static void KEY_GetAction_PressOrRelease(void)
{
	if(keyCfg.KEY_ReadPin_Fcn() == KEY_PRESSD_LEVEL)
		keyCfg.key_action = PRESS;
	else
		keyCfg.key_action = RELEASE;
}


void keyStateMachine(void)
{
	KEY_GetAction_PressOrRelease(); //读按键动作
	
	switch(keyCfg.key_state)
	{
		case KEY_IDLE:   	//未按下是空闲状态
		{
			if(keyCfg.key_action == PRESS) //如果按下
			{
				keyCfg.key_state = KEY_DEBOUNCE;	//状态机转为消抖
				keyCfg.key_event = KEY_NULL;			//无事件
			}else
			{
				keyCfg.key_state = KEY_IDLE;			//未按下保持空闲
				keyCfg.key_event = KEY_NULL;			//无事件
			}
			break;
		}
		case KEY_DEBOUNCE:										//进入消抖
		{
			if(keyCfg.key_action == PRESS)			//如果依旧按下
			{
				keyCfg.key_state = KEY_CONFIRM_PRESS;	//说明确认按下 状态切到确认按下
				keyCfg.key_event = KEY_NULL;			//无事件
			}
			else
			{
				keyCfg.key_state = KEY_IDLE;			//与上一周期不同，说明由于抖动，重新进入空闲
				keyCfg.key_event = KEY_NULL;			//无事件
			}
			break;
		}
		case KEY_CONFIRM_PRESS:								//确认按下状态
		{
			if((keyCfg.key_action == PRESS) && (keyCfg.count >= KEY_LONG_PRESS_TIME)) //如果确实按下了并且按下时间大于长按判断时间
			{	
				keyCfg.key_state = KEY_CONFIRM_LONGPRESS;				//说明是长按，状态切到长按
				keyCfg.key_event = KEY_NULL;										//无事件
				keyCfg.count = 0;																//计数清零
			}
			else if((keyCfg.key_action == PRESS) && (keyCfg.count < KEY_LONG_PRESS_TIME)) //如果依旧按下并按下的计数小于长按判断时间
			{
				keyCfg.count++;													//计数++
				keyCfg.key_state = KEY_CONFIRM_PRESS;		//状态切到确认按下
				keyCfg.key_event = KEY_NULL;
			}else
			{
				keyCfg.count = 0;
				keyCfg.key_state = KEY_CONFIRM_SINGLE_CLICK;
				keyCfg.key_event = KEY_NULL;
			}
			break;
		}
		case KEY_CONFIRM_SINGLE_CLICK:
		{
				keyCfg.count = 0;
				keyCfg.key_state = KEY_IDLE;  
				keyCfg.key_event = KEY_SINGLE_CLICK;// 响应单击
			break;
		}
		case KEY_CONFIRM_LONGPRESS:
		{
			if(keyCfg.key_action == PRESS) 
			{   
				keyCfg.key_state = KEY_CONFIRM_LONGPRESS;
				keyCfg.key_event = KEY_LONG_PRESS;
				keyCfg.count = 0;
			}
			else
			{
				keyCfg.key_state = KEY_IDLE;
				keyCfg.key_event = KEY_LONG_PRESS;
				keyCfg.count = 0;
			}
			break;	
		}


		default:break;
	}
}



