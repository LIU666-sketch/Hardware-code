#ifndef __KEY_H__
#define __KEY_H__
#include "gpio.h"

#define KEY1 HAL_GPIO_ReadPin(KEY1_GPIO_Port,KEY1_Pin)
#define KEY2 HAL_GPIO_ReadPin(KEY2_GPIO_Port,KEY2_Pin)
#define KEY3 HAL_GPIO_ReadPin(KEY3_GPIO_Port,KEY3_Pin)

#define KEY1_PRES 1
#define KEY2_PRES 2
#define KEY3_PRES 3

unsigned char KEY_Scan(void);
#endif