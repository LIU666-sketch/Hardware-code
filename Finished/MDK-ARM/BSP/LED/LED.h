
#ifndef __LED_H__
#define __LED_H__
#include "gpio.h"

#define LED1_ON() HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_RESET)
#define LED1_OFF() HAL_GPIO_WritePin(LED1_GPIO_Port,LED1_Pin,GPIO_PIN_SET)
#define LED2_ON() HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_RESET)
#define LED2_OFF() HAL_GPIO_WritePin(LED2_GPIO_Port,LED2_Pin,GPIO_PIN_SET)

void LED_ALL_ON(void);
void LED_ALL_OFF(void);
void LED_green_ON(void);
void LED_red_ON(void);
#endif