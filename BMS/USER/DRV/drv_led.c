#include "drv_led.h"
#include "main.h"
#include "drv_bq78350.h"

uint32_t led_count = 0;

void all_led_ctrl(GPIO_PinState sta)
{
	HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,sta);
	HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,sta);
	HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,sta);
	HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,sta);
}

void led_ctrl(uint8_t num, GPIO_PinState sta)
{
	switch(num)
	{
		case 1:
			HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,sta);
		break;
		case 2:
			HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,sta);
		break;
		case 3:
			HAL_GPIO_WritePin(LED3_GPIO_Port,LED3_Pin,sta);
		break;
		case 4:
			HAL_GPIO_WritePin(LED4_GPIO_Port,LED4_Pin,sta);
		break;
		default:break;
	}
}

void led_ctrl_num(uint8_t num)
{
	switch(num)
	{
		case 1:
			led_ctrl(1,on);
			led_ctrl(2,off);
			led_ctrl(3,off);
			led_ctrl(4,off);
			break;

		case 2:
			led_ctrl(1,on);
			led_ctrl(2,on);
			led_ctrl(3,off);
			led_ctrl(4,off);
			break;
		case 3:
			led_ctrl(1,on);
			led_ctrl(2,on);
			led_ctrl(3,on);
			led_ctrl(4,off);
			break;
		case 4:
			led_ctrl(1,on);
			led_ctrl(2,on);
			led_ctrl(3,on);
			led_ctrl(4,on);
			break;
		default:break;
	}
}

static inline void vol_7_8(void)
{
	all_led_ctrl(on);
}


static inline void vol_6_7()
{
	led_ctrl(1,on);
	led_ctrl(2,on);
	led_ctrl(3,on);
	if(led_count == 20)
		{
			led_count = 0;
			HAL_GPIO_TogglePin(LED4_GPIO_Port,LED4_Pin);
		}
}

static inline void vol_5_6()
{
	led_ctrl(1,on);
	led_ctrl(2,on);
	led_ctrl(3,on);
	led_ctrl(4,off);
}

static inline void vol_4_5()
{

	led_ctrl(1,on);
	led_ctrl(2,on);
	if(led_count == 20)
		{
			led_count = 0;
			HAL_GPIO_TogglePin(LED3_GPIO_Port,LED3_Pin);
		}
	led_ctrl(4,off);
}

static inline void vol_3_4()
{
	led_ctrl(1,on);
	led_ctrl(2,on);
	led_ctrl(3,off);
	led_ctrl(4,off);
}

static inline void vol_2_3()
{
	led_ctrl(1,on);
	if(led_count == 20)
		{
			led_count = 0;
			HAL_GPIO_TogglePin(LED2_GPIO_Port,LED2_Pin);
		}
	led_ctrl(3,off);
	led_ctrl(4,off);
}

static inline void vol_1_2()
{
	led_ctrl(1,on);
	led_ctrl(2,off);
	led_ctrl(3,off);
	led_ctrl(4,off);
}

static inline void vol_0_1()
{
	led_ctrl(3,off);
	if(led_count == 20)
		{
			led_count = 0;
			HAL_GPIO_TogglePin(LED1_GPIO_Port,LED1_Pin);
		}
	led_ctrl(3,off);
	led_ctrl(4,off);
}

void displayBattery(void)
{
	led_count++;
	if(battery.voltage > 12225)
		vol_7_8();
	else if(battery.voltage > 11850)
		vol_6_7();
	else if(battery.voltage > 11475)
		vol_5_6();
	else if(battery.voltage > 11100)
		vol_4_5();
	else if(battery.voltage > 10725)
		vol_3_4();
	else if(battery.voltage > 10350)
		vol_2_3();
	else if(battery.voltage > 9975)
		vol_1_2();
	else if(battery.voltage > 9600)
		vol_0_1();
	

}
