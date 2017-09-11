#include "stepmotor_dev.h"
#include "stepmotor_core.h"


void ctrlGPIO_Init(void)
{
	RCC->APB2ENR|=1<<2;  //PA
	GPIOA->CRL&=0xF0F0FFFF;  //PA4 PA6
	GPIOA->CRL|=0X03030000;

	GPIOA->CRH&=0xFFFF0FFF;  //PA11
	GPIOA->CRH|=0X00003000;
}

void timer_init(void)
{
	// TIMER2  
	RCC->APB1ENR|=1<<0;		//TIMER2
	RCC->APB2ENR|=1<<2;  //PA
	GPIOA->CRL&=0xFFFFFF0F;  //PA1
	GPIOA->CRL|=0X000000B0;
	TIM2->CR1|=1<<2;
	TIM2->DIER|=1<<0;
	TIM2->CCMR1&=~(3<<8);
	TIM2->CCMR1|=7<<12;
	TIM2->CCER|=1<<4;
	TIM2->ARR=TIME2_ARR-1;
	
	TIM2->CCR2=5;
	MY_NVIC_Init(1,2,TIM2_IRQn,2);
	
	
	//TIMER3
	RCC->APB1ENR|=1<<1;
	RCC->APB2ENR|=1<<2; 
	GPIOA->CRL&=0x0FFFFFFF;
	GPIOA->CRL|=0xB0000000; //PA7
	TIM3->CR1|=1<<2;
	TIM3->DIER|=1<<0;
	TIM3->CCMR1&=~(3<<8);
	TIM3->CCMR1|=7<<12;
	TIM3->CCER|=1<<4;
	TIM3->ARR=TIME2_ARR-1;
	
	TIM3->CCR2=5;
	MY_NVIC_Init(1,3,TIM3_IRQn,2);
	
	//TIMER4
	RCC->APB1ENR|=1<<2;
	RCC->APB2ENR|=1<<3; 
	GPIOB->CRL&=0x0FFFFFFF;
	GPIOB->CRL|=0xB0000000; //PB7
	TIM4->CR1|=1<<2;
	TIM4->DIER|=1<<0;
	TIM4->CCMR1&=~(3<<8);
	TIM4->CCMR1|=7<<12;
	TIM4->CCER|=1<<4;
	TIM4->ARR=TIME2_ARR-1;
	
	TIM4->CCR2=5;
	MY_NVIC_Init(1,4,TIM4_IRQn,2);
	
}
void change_Timer(u8 n,u8 f)
{
	switch(n)
	{
		case 2:
			if(f)TIM2->CR1|=0x01;
			else TIM2->CR1&=~0X01;
			break;
		case 3:
			if(f)TIM3->CR1|=0x01;
			else TIM3->CR1&=~0X01;
			break;
		case 4:
			if(f)TIM4->CR1|=0x01;
			else TIM4->CR1&=~0X01;
			break;
	}
}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001) //溢出中断
	{
		tim2_irq_callback();
	} 
	TIM2->SR&=~(1<<0); //清除中断标志位
}

void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //溢出中断
	{
		tim3_irq_callback();
	} 
	TIM3->SR&=~(1<<0); //清除中断标志位
}

void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001) //溢出中断
	{
		tim4_irq_callback();
	} 
	TIM4->SR&=~(1<<0); //清除中断标志位
}



