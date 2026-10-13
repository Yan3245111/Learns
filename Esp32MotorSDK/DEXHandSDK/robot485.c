#include "robot485.h"

#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"


static bool is_init = false;
static SemaphoreHandle_t robot485_mutex = NULL;

static bool unpack_robot485_recv_data(const uint8_t *rx_buf, robot485_rx_t *out_buf) {
     if (rx_buf[0] != ROBOT485_HEAD || rx_buf[7] != ROBOT485_TAIL) {
        return false;
    }
    out_buf->head = rx_buf[0];
    out_buf->cmd_id = rx_buf[1];
    out_buf->data_len = rx_buf[2];
    memcpy(out_buf->data, rx_buf + 3, out_buf->data_len);
    out_buf->tail = rx_buf[3 + out_buf->data_len];
    if (out_buf->data_len <= 0) {
        return false;
    };
    return true;
}

void robot485_init(void) { 
    if (is_init) {
        return;
    }
    // 初始化互斥锁
    robot485_mutex = xSemaphoreCreateMutex();
    if (robot485_mutex == NULL) {
        return;
    }
    // 配置 UART
    uart_config_t uart_config = {
        .baud_rate = ROBOT485_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // 安装串口驱动
    uart_driver_install(ROBOT485_UART_NUM, 256, 256, 0, NULL, 0);
    uart_param_config(ROBOT485_UART_NUM, &uart_config);
    uart_set_pin(ROBOT485_UART_NUM, ROBOT485_TX_PIN, ROBOT485_RX_PIN, ROBOT485_DIR_PIN, UART_PIN_NO_CHANGE);
    uart_set_mode(ROBOT485_UART_NUM, UART_MODE_RS485_HALF_DUPLEX);  // 自动切换方向
    is_init = true;
}

void robot485_send(const uint8_t *data, uint16_t len) {
    if (!is_init || data == NULL || len <= 0) {
        return;
    }
    // 加锁
    xSemaphoreTake(robot485_mutex, portMAX_DELAY);
    // 发送数据
    uart_write_bytes(ROBOT485_UART_NUM, data, len);
    // 解锁
    xSemaphoreGive(robot485_mutex);
}

bool robot485_recv(robot485_rx_t *out_buf) {
    if (!is_init || out_buf == NULL) {
            return false;
    }
    // 接收数据 加锁 获取锁超时1000ms 读取超时100ms
    if (xSemaphoreTake(robot485_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return false;
    }
    uint8_t rx_buf[ROBOT485_BUF_SIZE];
    int len = uart_read_bytes(ROBOT485_UART_NUM, rx_buf, ROBOT485_BUF_SIZE, pdMS_TO_TICKS(100));
    // 解锁
    xSemaphoreGive(robot485_mutex);
    if (len <= 0) {
        return false;
    }
    // for (int i = 0; i < len; i++) {
    //     printf("%02X ", rx_buf[i]);
    // }
    // printf("\n");
    return unpack_robot485_recv_data(rx_buf, out_buf);
}
