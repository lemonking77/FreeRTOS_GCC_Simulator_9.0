/*
 * @file: 
 * @brief: 
 * @author: Deven
 * @date: Do not edit
 * @email: 862215606@qq.com
 * @copyright: 
 * @company: 
 */


#include "FreeRTOS.h"
#include "task.h"

#include "config.h"

//任务优先级
#define START_TASK_PRIO		1
//任务堆栈大小	
#define START_STK_SIZE 		128  
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);


#define LED0_TASK_PIRO      5	/* LED0任务先级  0是最低的 */
#define LED0_TASK_SIZE      50
void vLED0_Task(void *pvParamenters);
TaskHandle_t LED0Task_Handler;

#define LED1_TASK_PRIO      3
#define LED1_TASK_SIZE      50
void vLED1_Task(void *pvParamenters);
TaskHandle_t LED1Task_Handler;

void vPre_Init(void)
{
  printf("pre init\r\n");
}

void vLED0_Task(void *pvParamenters)
{
	while(1)
	{
        printf("led0 tast runing\r\n");
        vTaskDelay(7000);
	}
}

void vLED1_Task(void *pvParamenters)
{
	while(1)
	{
		printf("led1 tast runing\r\n");
		vTaskDelay(3000);	/* 调用FreeRTOS的vTaskDelay()函数会切换任务，先去执行别的任务*/
	}
}


int main(void)
{
    vPre_Init();
    xTaskCreate((TaskFunction_t )start_task,            //任务函数
                (const char*    )"start_task",          //任务名称
                (uint16_t       )START_STK_SIZE,        //任务堆栈大小
                (void*          )NULL,                  //传递给任务函数的参数
                (UBaseType_t    )START_TASK_PRIO,       //任务优先级
                (TaskHandle_t*  )&StartTask_Handler);   //任务句柄              
    vTaskStartScheduler();          //开启任务调度
}


//开始任务任务函数
void start_task(void *pvParameters)
{
    taskENTER_CRITICAL();           //进入临界区
    
    //动态创建任务
    xTaskCreate( ( TaskFunction_t ) vLED0_Task,		/* 函数名 */
          ( const char *   ) "vLED0_Task",	/* 任务名 */
          ( uint16_t 	  ) LED0_TASK_SIZE,	/* 任务堆栈大小 */
          ( void *		  ) NULL,			/* 任务参数 */
          ( UBaseType_t    ) LED0_TASK_PIRO,	/* 任务优先级 */
          ( TaskHandle_t   ) LED0Task_Handler/* 任务句柄 */		 
          );	
    xTaskCreate( ( TaskFunction_t ) vLED1_Task,		/* 函数名 */
          ( const char *   ) "vLED1_Task",	/* 任务名 */
          ( uint16_t    	  ) LED1_TASK_SIZE, /* 任务堆栈大小 */
          ( void *		  ) NULL,			/* 任务参数 */
          ( UBaseType_t	  ) LED1_TASK_PRIO, /* 任务优先级 */
          (TaskHandle_t    ) LED1Task_Handler/* 任务句柄 */
          );	
                 
    vTaskDelete(StartTask_Handler); //删除开始任务
    taskEXIT_CRITICAL();            //退出临界区
}



