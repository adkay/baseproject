#include "sys.h"
#include "stm32f1xx_it.h"


//�û��жϺ���

void TIM2_IRQHandler(void)
{
	if(TIM2->SR&0X0001) //����ж�
	{
		//LED0_T;

		
	} 
	TIM2->SR&=~(1<<0); //����жϱ�־λ
}


void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0X0001) //����ж�
	{
		//LED0_T;
		
	} 
	TIM3->SR&=~(1<<0); //����жϱ�־λ
}


void TIM4_IRQHandler(void)
{
	if(TIM4->SR&0X0001) //����ж�
	{
		
	} 
	TIM4->SR&=~(1<<0); //����жϱ�־λ
}



