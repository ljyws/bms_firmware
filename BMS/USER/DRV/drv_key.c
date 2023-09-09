#include "drv_key.h"
#include "main.h"

static KeyPinLevel_e keyReadPin(void);   // ������ȡ�����ĵ�ƽ����
static void KEY_GetAction_PressOrRelease(void); // ��ȡ�����ǰ��»����ͷţ����浽�ṹ��

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
	KEY_GetAction_PressOrRelease(); //����������
	
	switch(keyCfg.key_state)
	{
		case KEY_IDLE:   	//δ�����ǿ���״̬
		{
			if(keyCfg.key_action == PRESS) //�������
			{
				keyCfg.key_state = KEY_DEBOUNCE;	//״̬��תΪ����
				keyCfg.key_event = KEY_NULL;			//���¼�
			}else
			{
				keyCfg.key_state = KEY_IDLE;			//δ���±��ֿ���
				keyCfg.key_event = KEY_NULL;			//���¼�
			}
			break;
		}
		case KEY_DEBOUNCE:										//��������
		{
			if(keyCfg.key_action == PRESS)			//������ɰ���
			{
				keyCfg.key_state = KEY_CONFIRM_PRESS;	//˵��ȷ�ϰ��� ״̬�е�ȷ�ϰ���
				keyCfg.key_event = KEY_NULL;			//���¼�
			}
			else
			{
				keyCfg.key_state = KEY_IDLE;			//����һ���ڲ�ͬ��˵�����ڶ��������½������
				keyCfg.key_event = KEY_NULL;			//���¼�
			}
			break;
		}
		case KEY_CONFIRM_PRESS:								//ȷ�ϰ���״̬
		{
			if((keyCfg.key_action == PRESS) && (keyCfg.count >= KEY_LONG_PRESS_TIME)) //���ȷʵ�����˲��Ұ���ʱ����ڳ����ж�ʱ��
			{	
				keyCfg.key_state = KEY_CONFIRM_LONGPRESS;				//˵���ǳ�����״̬�е�����
				keyCfg.key_event = KEY_NULL;										//���¼�
				keyCfg.count = 0;																//��������
			}
			else if((keyCfg.key_action == PRESS) && (keyCfg.count < KEY_LONG_PRESS_TIME)) //������ɰ��²����µļ���С�ڳ����ж�ʱ��
			{
				keyCfg.count++;													//����++
				keyCfg.key_state = KEY_CONFIRM_PRESS;		//״̬�е�ȷ�ϰ���
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
				keyCfg.key_event = KEY_SINGLE_CLICK;// ��Ӧ����
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



