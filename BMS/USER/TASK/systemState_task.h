#ifndef __SYSTEM_STATE_TASK_H_
#define __SYSTEM_STATE_TASK_H_

#include "stm32f1xx.h"
#include "stdbool.h"

typedef enum
{
	SYS_SLEEP = 0,
	SYS_WAKE_UP,
	SYS_WORKING,
	SYS_WAIT_SLEEP
}SysState_e;

typedef enum
{
	EVT_NULL = 0,
	EVT_TIMEOUT,
	EVT_KEY_SINGLECLICK,
	EVT_KEY_LONGPRESS
}FSM_EVENT_e;


typedef struct
{
	SysState_e current_state;
	FSM_EVENT_e evt;
	SysState_e next_state;
	bool (*actionFun)(void *arg);
}SysStateTransform_t;



bool actionFun(void *arg);
void SYS_IDLE_callback(void);
void SYS_SLEEP_callback(void);
void SYS_WAKE_UP_callback(void);
void SYS_WORKING_callback(void);
void SYS_WAIT_SLEEP_callback(void);
void eventTrigger(void);
void do_action(SysStateTransform_t *staTran);
#endif
