#include "LED.h"
void LED_ALL_ON(void)
{
	LED1_ON();
	LED2_ON();
	
}
void LED_ALL_OFF(void)
{
	LED1_OFF();
	LED2_OFF();
	
}
void LED_red_ON(void)
{
	LED1_ON();
	LED2_OFF();
	
}
void LED_green_ON(void)
{
	LED1_OFF();
	LED2_ON();
	
}