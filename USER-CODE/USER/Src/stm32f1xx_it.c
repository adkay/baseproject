#include "stm32f1xx_it.h"


//用户中断函数

FUNC_POINT Tim2_IRQFunc;
FUNC_POINT Tim3_IRQFunc;
FUNC_POINT Tim4_IRQFunc;

void SetTimeIRQFunc(u8 timerNum,FUNC_POINT func)
{
	switch(timerNum)
	{
		case 2:
			Tim2_IRQFunc=func;
			break;
		case 3:
			Tim3_IRQFunc=func;
			break;
		case 4:
			Tim4_IRQFunc=func;
			break;
		
	}
	
}

void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001) //溢出中断
	{
		//LED0_T;
		Tim2_IRQFunc();
		
	} 
	TIM2->SR&=~(1<<0); //清除中断标志位
}


void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //溢出中断
	{
		//LED0_T;
		Tim3_IRQFunc();
	} 
	TIM3->SR&=~(1<<0); //清除中断标志位
}


void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001) //溢出中断
	{
		Tim4_IRQFunc();
	} 
	TIM4->SR&=~(1<<0); //清除中断标志位
}



