#include "sys.h"
#include "delay.h"
#include "gpio.h"
#include "stdio.h"
#include "led.h"
#include "key.h"
#include "usart.h"
#include "timer.h"


int main(void)
{	
	
	u8 i=0;
	Stm32_Clock_Init(9);
	delay_init(72);	    //延时函数初始化	  
	GPIO_Init();
	uart_init(72,115200);
	
	while(1)
	{
		keyRead();
		i>100?i=0:i++;
		if (i==100)
		{
			LED0_T;
		}
		delay_ms(1);
	}
}
 





