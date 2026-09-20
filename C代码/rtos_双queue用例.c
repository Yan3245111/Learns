#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/queue.h"
#include "stdint.h"

// 请求报文结构体，把要发送的数据、长度、超时封装
typedef struct
{
    uint8_t data[64];
    uint16_t len;
    uint16_t timeout_ms;   // 本次一问一答总超时
} rs485_req_t;

// 两个全局队列句柄
static QueueHandle_t tx_queue_high;
static QueueHandle_t tx_queue_normal;

// 底层已经存在的硬件互斥锁（你原有代码）
extern SemaphoreHandle_t rs485_mutex;

/**
 * @brief 真正执行一次完整事务：发送 + 等待应答，带超时
 * 内部会使用你原来的 rs485_mutex 硬件锁
 */
static int rs485_do_transaction(const rs485_req_t *req)
{
    if(xSemaphoreTake(rs485_mutex, pdMS_TO_TICKS(10)) != pdTRUE)
    {
        return -1; // 获取硬件发送锁失败
    }

    // -------- 你的原有485发送代码 --------
    // rs485_send_bytes(req->data, req->len);
    // 等待应答，超时时间 req->timeout_ms
    // ret = rs485_wait_response(resp_buf, req->timeout_ms);
    // -----------------------------------

    xSemaphoreGive(rs485_mutex);
    return 0;
}

/**
 * @brief 底层485收发任务：优先高优先级队列
 */
static void rs485_worker_task(void *arg)
{
    rs485_req_t req;
    for(;;)
    {
        BaseType_t got_high = xQueueReceive(tx_queue_high, &req, 0);
        if(got_high == pdTRUE)
        {
            // 处理控制指令，高优先级
            rs485_do_transaction(&req);
            continue;
        }

        // 高队列为空，阻塞等待普通轮询报文
        BaseType_t got_normal = xQueueReceive(tx_queue_normal, &req, portMAX_DELAY);
        if(got_normal == pdTRUE)
        {
            rs485_do_transaction(&req);
        }
    }
}

/**
 * @brief 电机状态轮询任务：100ms，避免压满队列
 * 规则：普通队列还有未处理消息，则跳过本次轮询，不生产新请求
 */
static void motor_poll_task(void *arg)
{
    rs485_req_t poll_req = {0};

    // 填充你的读电机状态查询帧
    poll_req.len = 8;
    poll_req.timeout_ms = 80;
    // memcpy(poll_req.data, your_query_frame, 8);

    for(;;)
    {
        vTaskDelay(pdMS_TO_TICKS(100));

        // 如果普通队列还有待处理轮询包 → 直接跳过这一轮，防止堆积
        UBaseType_t pending = uxQueueMessagesWaiting(tx_queue_normal);
        if(pending > 0)
        {
            continue;
        }

        // 压入普通队列，0超时：队列满直接丢弃这条轮询请求
        xQueueSend(tx_queue_normal, &poll_req, 0);
    }
}

/**
 * @brief 串口指令任务示例：收到上位机运动指令，压入高优先级队列
 */
static void uart_cmd_task(void *arg)
{
    rs485_req_t ctrl_req = {0};

    for(;;)
    {
        // 等待串口收到控制指令，填充 ctrl_req
        // ctrl_req.len = xxx;
        // memcpy(ctrl_req.data, cmd_buf, len);
        ctrl_req.timeout_ms = 80;

        // 控制指令压高优先级队列，队列满这里可以做处理，比如返回"总线忙"
        if(xQueueSend(tx_queue_high, &ctrl_req, pdMS_TO_TICKS(5)) != pdPASS)
        {
            // 队列满，向上位机回复：通信繁忙
        }
    }
}

/**
 * @brief 初始化：创建队列、启动任务，放在app_main
 */
void rs485_comm_init(void)
{
    // 高优先级队列：运动指令，深度4足够
    tx_queue_high = xQueueCreate(4, sizeof(rs485_req_t));
    // 普通队列：轮询查询，深度4
    tx_queue_normal = xQueueCreate(4, sizeof(rs485_req_t));

    xTaskCreate(rs485_worker_task, "rs485_worker", 3072, NULL, 5, NULL);
    xTaskCreate(motor_poll_task, "motor_poll", 2048, NULL, 3, NULL);
    xTaskCreate(uart_cmd_task, "uart_cmd", 2048, NULL, 3, NULL);
}
