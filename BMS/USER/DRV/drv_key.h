#ifndef __DRV_KEY_H_
#define __DRV_KEY_H_

#include "stm32f1xx.h"

#define KEY_LONG_PRESS_TIME (105)  //TIME = 运行周期 x KEY_LONG_PRESS_TIME  eg：10ms * 200 = 2s
#define KEY_PRESSD_LEVEL (0)

//按键事件
typedef enum
{
	KEY_IDLE = 0,						 //空闲
	KEY_DEBOUNCE,						 //消抖
	KEY_CONFIRM_PRESS,			 //确认按下
	KEY_CONFIRM_SINGLE_CLICK,//确认短按
	KEY_CONFIRM_LONGPRESS,	 //确认长按
} KeyState_e;

//按键事件
typedef enum
{
	KEY_NULL 				 = 0x00,  //无动作
	KEY_SINGLE_CLICK = 0x01,	//单击
	KEY_LONG_PRESS 	 = 0x02		//长按
} KeyEvent_e;

//按键动作
typedef enum
{
	PRESS = 0,
	RELEASE 
} KeyAction_e;

// 按键引脚的电平
typedef enum
{ 
	KKEY_PinLevel_Low = 0,
	KEY_PinLevel_High
}KeyPinLevel_e;


typedef struct
{
	uint16_t count;
	KeyAction_e key_action;
	KeyState_e  key_state;
	KeyEvent_e  key_event;
	KeyPinLevel_e (*KEY_ReadPin_Fcn)(void);
} KeyConfig_t;

extern KeyConfig_t keyCfg;
	
void keyStateMachine(void);  //按键状态机

#endif

