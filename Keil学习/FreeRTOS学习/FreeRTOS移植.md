# FreeRTOS下载  下载链接：https://www.freertos.org/a00104.html
* 教程链接：https://blog.csdn.net/qq_61672347/article/details/125748646
* 创建任务：
```c语言
#define START_TASK_PRIO 1
//任务堆栈大小
#define START_STK_SIZE 128
//任务句柄
TaskHandle_t StartTask_Handler;
//任务函数
void start_task(void *pvParameters);

int main(void) 
{
	NVIC_PriorityGroupConfig( NVIC_PriorityGroup_4);
	   /* 创建 AppTaskCreate 任务 */
	xTaskCreate((TaskFunction_t)start_task,			 //任务函数
			(const char *)"start_task",			 //任务名称
			(uint16_t)START_STK_SIZE,			 //任务堆栈大小
			(void *)NULL,						 //传递给任务函数的参数
			(UBaseType_t)START_TASK_PRIO,		 //任务优先级
			(TaskHandle_t *)&StartTask_Handler); //任务句柄

	vTaskStartScheduler(); //开启任务调度 
															
	while (1) {
	
	}
	return 0;
}

void start_task(void *pvParameters)
{
	while (1) {
		int LED_ON = 1;
	}
}
```

