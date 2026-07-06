/*freertos */
/* 同时读写使用互斥量 */
#include "FreeRTOS.h"


/* 声明互斥量句柄 */
SemaphoreHandle_t xMutex;

/* 创建互斥量 */
xMutex = xSemaphoreCreateMutex();

/* 写操作 */
void write_task(void *pvParameters) {
    while(1) {
        /* 获取互斥量，无限等待 */
        xSemaphoreTake(xMutex, portMAX_DELAY);
        
        /* 执行写操作 - 临界区开始 */
        /* ... 修改共享数据 ... */
        
        /* 释放互斥量 */
        xSemaphoreGive(xMutex);
    }
} 

/* 读操作 - 同样需要互斥保护 */
void read_task(void *pvParameters) {
    while(1) {
        xSemaphoreTake(xMutex, portMAX_DELAY);
        
        /* 执行读操作 - 临界区开始 */
        /* ... 读取共享数据 ... */
        
        xSemaphoreGive(xMutex);
    }
}

/* 
互斥的底层机制
1.队列机制 take一个被占用的互斥量时，放到队列里等待，give的时候唤醒一个等待的任务
2.优先级继承机制 高优先级take一个低优先级的任务持有的互斥量时，会暂时提升低优先级任务的优先级，这样低优先级任务就可以尽快完成任务
释放互斥量，避免优先级反转问题
3.所有权管理 互斥量只能被持有它的任务释放，防止其他任务误释放导致数据不一致

*/