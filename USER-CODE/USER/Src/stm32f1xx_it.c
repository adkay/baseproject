#include "sys.h"
#include "stm32f1xx_it.h"


//用户中断函数

void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001) //溢出中断
	{
		//LED0_T;

		
	} 
	TIM2->SR&=~(1<<0); //清除中断标志位
}


void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //溢出中断
	{
		//LED0_T;
		
	} 
	TIM3->SR&=~(1<<0); //清除中断标志位
}


void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001) //溢出中断
	{
		
	} 
	TIM4->SR&=~(1<<0); //清除中断标志位
}



