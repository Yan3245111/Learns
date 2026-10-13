#ifndef __MODEL485_H__
#define __MODEL485_H__

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

// 接收数据结构体
#pragma pack(push, 1)
typedef struct {
    uint8_t head;
    uint8_t device_id;
    uint8_t data_len;
    uint8_t data[8];
} rs485_rx_t;
#pragma pack(pop)


// 485硬件配置
#define RS485_UART_NUM   UART_NUM_2
#define RS485_TX_PIN     GPIO_NUM_11
#define RS485_RX_PIN     GPIO_NUM_10
#define RS485_DIR_PIN    GPIO_NUM_12

#define RS485_BAUDRATE   115200
#define RS485_BUF_SIZE   13
#define RS485_TIMEOUT_MS 100


void rs485_init(void);

void rs485_send(const uint8_t *data, size_t len);

void rs485_send_with_crc(const uint8_t *data, size_t len);

bool rs485_recv(rs485_rx_t *out_buf);

#endif
