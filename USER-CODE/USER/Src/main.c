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

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

//任务优先级
#define task1_TASK_PRIO		2
//任务堆栈大小	
#define task1_STK_SIZE 		50  
//任务句柄
TaskHandle_t task1Task_Handler;
//任务函数
void task1_task(void *pvParameters);

//任务优先级
#define task2_TASK_PRIO		3
//任务堆栈大小	
#define task2_STK_SIZE 		50  
//任务句柄
TaskHandle_t task2Task_Handler;
//任务函数
void task2_task(void *pvParameters);


int main(void)
{	
	
	u8 i=0;
	Stm32_Clock_Init(9);
	delay_init(72);	    //延时函数初始化	  
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
	    taskENTER_CRITICAL();           //进入临界区
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
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
	
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










