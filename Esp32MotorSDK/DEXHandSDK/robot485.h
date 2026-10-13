#ifndef __ROBOT485_H__
#define __ROBOT485_H__

#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct {
    uint8_t head;
    uint8_t cmd_id;
    uint8_t data_len;
    uint8_t data[4];
    uint8_t tail;
} robot485_rx_t;
#pragma pack(pop)


// 485硬件配置
#define ROBOT485_UART_NUM   UART_NUM_1
#define ROBOT485_TX_PIN     GPIO_NUM_17
#define ROBOT485_RX_PIN     GPIO_NUM_18
#define ROBOT485_DIR_PIN    GPIO_NUM_14

#define ROBOT485_BAUDRATE   115200
#define ROBOT485_BUF_SIZE   120

#define ROBOT485_HEAD       0xAA
#define ROBOT485_TAIL       0x55

void robot485_init(void);

void robot485_send(const uint8_t *data, uint16_t len);

bool robot485_recv(robot485_rx_t *out_buf);

#endif
