#ifndef __DRV_LED_H
#define __DRV_LED_H

#include "stdbool.h"
#include "stm32f1xx.h"

#define on GPIO_PIN_RESET
#define off GPIO_PIN_SET


void all_led_ctrl(GPIO_PinState sta);

void led_ctrl(uint8_t num, GPIO_PinState sta);
void led_ctrl_num(uint8_t num);
void displayBattery(void);

#endif

