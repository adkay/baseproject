#include "led.h"


void led_Init(void)
{
	RCC->APB2ENR|=1<<3;    	//PORTB
	GPIOB->CRH&=0XFFFFFF0F; 
	GPIOB->CRH|=0X00000030;	 
  GPIOB->ODR|=1<<9;      
	
	RCC->APB2ENR|=1<<8;    	//PORTG
	GPIOG->CRH&=0X0FFFFFFF; 
	GPIOG->CRH|=0X30000000;  	 
  GPIOG->ODR|=1<<15; 
}




