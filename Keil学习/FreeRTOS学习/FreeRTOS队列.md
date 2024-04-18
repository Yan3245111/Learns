* 缓冲机制：先进先出，出队可以选择阻塞机制，栈是先进后出
* 出队/入队阻塞机制：1：无阻塞 2：有延时阻塞 3：无延时阻塞 
* 临界区：taskENTER_CRITICAL(); //进入临界区    taskEXIT_CRITICAL(); //退出临界区 
  * 指必须完整执行不能被打断的任务，比如队列初始化的时候使用
```c代码讲解演示
QueueHandle_t Queue_uart;  // 队列实例
xQueueCreate((UBaseType_t)50, (UBaseType_t)100);  // 队列包个数，每个包的长度
xQueueReceive(Queue_uart, &receive_data, 0); // 队列实例，接收数据（结构体/buf/数据指针），接收延时
xQueueSend(Queue_uart, &send_data, 0);  // 队列实例，发送数据（结构体/buf/数据指针），发送延时
```
