#include "sys.h"
#include "delay.h"
//#include "stdio.h"
#include "led.h"
#include "key.h"
#include "usart.h"
//#include "timer.h"
#include "FreeRTOS.h"
#include "task.h"
//#include "stepmotor_core.h"

//�������ȼ�
#define START_TASK_PRIO		1
//�����ջ��С	
#define START_STK_SIZE 		128  
//������
TaskHandle_t StartTask_Handler;
//������
void start_task(void *pvParameters);

//�������ȼ�
#define task1_TASK_PRIO		2
//�����ջ��С	
#define task1_STK_SIZE 		50  
//������
TaskHandle_t task1Task_Handler;
//������
void task1_task(void *pvParameters);

//�������ȼ�
#define task2_TASK_PRIO		3
//�����ջ��С	
#define task2_STK_SIZE 		50  
//������
TaskHandle_t task2Task_Handler;
//������
void task2_task(void *pvParameters);


int main(void)
{	
	
	u8 i=0;
	Stm32_Clock_Init(9);
	delay_init(72);	    //��ʱ������ʼ��	  
	led_Init();
	key_Init();
	uart_init(72,115200);
	//stepMotorInit();
	
	
	xTaskCreate((TaskFunction_t)	start_task,
							(const char* 	 )	"start_task",
							(uint16_t			 )	START_STK_SIZE,
							(void*				 )	NULL,
							(UBaseType_t	 )	START_TASK_PRIO,
							(TaskHandle_t* )	&StartTask_Handler);
	vTaskStartScheduler();

}
 
void start_task(void *pvParameters)
{
	    taskENTER_CRITICAL();           //�����ٽ���
    xTaskCreate((TaskFunction_t )task1_task,     	
                (const char*    )"task1_task",   	
                (uint16_t       )task1_STK_SIZE, 
                (void*          )NULL,				
                (UBaseType_t    )task1_TASK_PRIO,	
                (TaskHandle_t*  )&task1Task_Handler);   
    xTaskCreate((TaskFunction_t )task2_task,     
                (const char*    )"task2_task",   
                (uint16_t       )task2_STK_SIZE, 
                (void*          )NULL,
                (UBaseType_t    )task2_TASK_PRIO,
                (TaskHandle_t*  )&task2Task_Handler);         
    vTaskDelete(StartTask_Handler); //ɾ����ʼ����
    taskEXIT_CRITICAL();            //�˳��ٽ���
	
}

void task1_task(void *pyParameters)
{
	u16 i;
	while(1)
	{
		//keyRead();
		i>100?i=0:i++;
		if (i==100)
		{
			
			//stepMotorRun();
		}
		LED0_T;
		vTaskDelay(500);
	
	}
}
void task2_task(void *pyParameters)
{
	while(1)
	{
		
		
		vTaskDelay(500);
	}
}










