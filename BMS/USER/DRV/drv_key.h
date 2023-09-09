#ifndef __DRV_KEY_H_
#define __DRV_KEY_H_

#include "stm32f1xx.h"

#define KEY_LONG_PRESS_TIME (105)  //TIME = �������� x KEY_LONG_PRESS_TIME  eg��10ms * 200 = 2s
#define KEY_PRESSD_LEVEL (0)

//�����¼�
typedef enum
{
	KEY_IDLE = 0,						 //����
	KEY_DEBOUNCE,						 //����
	KEY_CONFIRM_PRESS,			 //ȷ�ϰ���
	KEY_CONFIRM_SINGLE_CLICK,//ȷ�϶̰�
	KEY_CONFIRM_LONGPRESS,	 //ȷ�ϳ���
} KeyState_e;

//�����¼�
typedef enum
{
	KEY_NULL 				 = 0x00,  //�޶���
	KEY_SINGLE_CLICK = 0x01,	//����
	KEY_LONG_PRESS 	 = 0x02		//����
} KeyEvent_e;

//��������
typedef enum
{
	PRESS = 0,
	RELEASE 
} KeyAction_e;

// �������ŵĵ�ƽ
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
	
void keyStateMachine(void);  //����״̬��

#endif

