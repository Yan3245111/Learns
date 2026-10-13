#include "model485.h"

#include "driver/uart.h"
#include "driver/gpio.h"
#include "freertos/semphr.h"


static bool is_init = false;
static SemaphoreHandle_t rs485_mutex = NULL;


// CRC16计算函数
static uint16_t calculate_crc(const uint8_t *data, size_t len) {
    uint16_t crc = 0xFFFF;
    for (size_t i = 0; i < len; i++) {
        crc ^= data[i];
        for (size_t j = 0; j < 8; j++) {
            if (crc & 1) {
                crc = (crc >> 1) ^ 0xA001;
            }
            else {
                crc >>= 1;
            }
        }
    }
    return crc & 0xFFFF;
}

// 接收数据解包
static bool unpack_rs485_recv_data(const uint8_t *rx_buf, rs485_rx_t *out_buf) {
    out_buf->head = rx_buf[0];
    out_buf->device_id = rx_buf[1];
    out_buf->data_len = rx_buf[2];
    if (out_buf->data_len != 8) {
        return false;
    }
    // 检查crc 不包含末尾2字节 低字节在前
    uint16_t crc = calculate_crc(rx_buf, out_buf->data_len + 3);
    if (crc != (uint16_t)((rx_buf[out_buf->data_len + 3]) | rx_buf[out_buf->data_len + 4] << 8)) {
        return false;
    }
    memcpy(out_buf->data, rx_buf + 3, out_buf->data_len);
    return true;
}

// 485初始化
void rs485_init(void) { 
    if (is_init) {
        return;
    }
    // 初始化互斥锁
    rs485_mutex = xSemaphoreCreateMutex();
    if (rs485_mutex == NULL) {
        return;
    }
    // 配置 UART
    uart_config_t uart_config = {
        .baud_rate = RS485_BAUDRATE,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    // 安装串口驱动
    uart_driver_install(RS485_UART_NUM, RS485_BUF_SIZE * 20, RS485_BUF_SIZE * 10, 0, NULL, 0);
    uart_param_config(RS485_UART_NUM, &uart_config);
    uart_set_pin(RS485_UART_NUM, RS485_TX_PIN, RS485_RX_PIN, RS485_DIR_PIN, UART_PIN_NO_CHANGE);
    uart_set_mode(RS485_UART_NUM, UART_MODE_RS485_HALF_DUPLEX);  // 自动切换方向
    is_init = true;
}

void rs485_send(const uint8_t *data, size_t len) {
    if (!is_init || data == NULL || len == 0) {
        return;
    }
    // 发送数据 加锁
    if (xSemaphoreTake(rs485_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return;
    }
    // 发送数据
    int write_len = uart_write_bytes(RS485_UART_NUM, (const char*)data, len);
    if (write_len != len) {
        printf("rs485_send error: write_len %d, len %d\n", write_len, len);
    }
    uart_wait_tx_done(RS485_UART_NUM, pdMS_TO_TICKS(RS485_TIMEOUT_MS));
    // 解锁
    xSemaphoreGive(rs485_mutex);
}

void rs485_send_with_crc(const uint8_t *data, size_t len) {
    if (!is_init || data == NULL || len == 0) {
        return;
    }
    uint16_t crc = calculate_crc(data, len);
    uint8_t tx_buf[RS485_BUF_SIZE];
    memcpy(tx_buf, data, len);
    tx_buf[len] = crc & 0xFF;
    tx_buf[len + 1] = (crc >> 8) & 0xFF;
    rs485_send(tx_buf, len + 2);
}

bool rs485_recv(rs485_rx_t *out_buf) {
    if (!is_init || out_buf == NULL) {
            return false;
    }
    // 接收数据 加锁 获取锁超时1000ms 读取超时100ms
    if (xSemaphoreTake(rs485_mutex, pdMS_TO_TICKS(1000)) != pdTRUE) {
        return false;
    }
    uint8_t rx_buf[RS485_BUF_SIZE];
    int len = uart_read_bytes(RS485_UART_NUM, rx_buf, RS485_BUF_SIZE, pdMS_TO_TICKS(RS485_TIMEOUT_MS));
    // 解锁
    xSemaphoreGive(rs485_mutex);
    if (len < RS485_BUF_SIZE) {
        return false;
    }
    return unpack_rs485_recv_data(rx_buf, out_buf);
}
