#include "sdk.h"

#include <stdio.h>


// 发送 + 解析
static bool transceive(const uint8_t *tx_buf, size_t tx_len, rs485_rx_t *rx_buf, bool is_broadcast) {
    uint8_t buf[RS485_BUF_SIZE];
    memset(buf, 0, RS485_BUF_SIZE);
    buf[0] = is_broadcast == false ? HEAD : BROADCAST;
    buf[1] = DEVICE_ID;
    buf[2] = DATA_LEN;
    memcpy(buf + 3, tx_buf, tx_len);
    rs485_send_with_crc(buf, tx_len + 3);
    if (is_broadcast) { 
        return true;
    }
    return rs485_recv(rx_buf);
}

static bool check_pid_index(int func_index) {
    int pid_index[] = {0x01, 0x02, 0x04, 0x05, 0x07, 0x08, 0x09};
    for (int i = 0; i < (sizeof(pid_index) / sizeof(pid_index[0])); i++) {
        if (pid_index[i] == func_index) {
            return true;
        }
    }
    return false;
}

static bool parse_motion_response(rs485_rx_t *rx_buf, motor_motion_t *buf) {
    buf->temp = rx_buf->data[1];
    int16_t torque_cur;
    bytes_to_int16(rx_buf->data + 2, &torque_cur);
    buf->current = (float)torque_cur * 0.01f;
    bytes_to_int16(rx_buf->data + 4, &buf->speed);
    bytes_to_int16(rx_buf->data + 6, &buf->angle);
    return true;
}

/*---PID相关---*/
bool read_pid(int func_index, float *pid) {
    /*
     * 读取PID参数
     * @param func_index PID参数索引
     * @return PID参数值
     * func_index 
     * 0x01: 电流环Kp, 0x02: 电流环Ki, 
     * 0x04: 速度环Kp, 0x05: 速度环Ki, 
     * 0x07: 位置环Kp, 0x08: 位置环Ki, 0x09: 位置环Kd
    */
    if (!check_pid_index(func_index)) {
        return false;
    }
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_PID, func_index, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_float(rx_buf.data + 4, pid);
    return true;
}

bool write_pid_to_ram(int func_index, float pid) {
    if (!check_pid_index(func_index)) {
        return false;
    }
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_WRITE_RAM_PID, func_index, 0x00, 0x00};
    uint8_t pid_buf[4];
    float_to_bytes(pid, pid_buf);
    memcpy(tx_buf + 4, pid_buf, 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool write_pid_to_rom(int func_index, float pid) {
    if (!check_pid_index(func_index)) {
        return false;
    }
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_WRITE_ROM_PID, func_index, 0x00, 0x00};
    uint8_t pid_buf[4];
    float_to_bytes(pid, pid_buf);
    memcpy(tx_buf + 4, pid_buf, 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

/*---加速度相关---*/
bool read_acc(int func_index, int32_t *acc) {
    /*
     * 读取加速度
     * @param func_index 加速度索引
     * 0x00: 位置加速度, 0x01: 位置速度，0x02: 速度加速度，0x03: 速度速度
     * @return 加速度值
    */
    rs485_rx_t rx_buf;
    uint8_t acc_index[4] = {0x00, 0x01, 0x02, 0x03};
    uint8_t tx_buf[8] = {CMD_READ_ACC, func_index, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (int i = 0; i < (sizeof(acc_index) / sizeof(acc_index[0])); i++) {
        if (acc_index[i] == func_index) {
            bool ret = transceive(tx_buf, 8, &rx_buf, false);
            if (!ret) {
                return false;
            }
            bytes_to_int32(rx_buf.data + 4, acc);
            return true;
        }
    }
    return false;
}

bool write_acc(int func_index, int32_t acc) {
    if (acc < 100 || acc > 60000) {
        printf("acc out of range %ld, range: 100-60000\n", acc);
        return false;
    }
    rs485_rx_t rx_buf;
    uint8_t acc_buf[4];
    uint8_t tx_buf[8] = {CMD_WRITE_ACC, func_index, 0x00, 0x00};
    uint8_t acc_index[4] = {0x00, 0x01, 0x02, 0x03};
    int32_to_bytes(acc, acc_buf);
    memcpy(tx_buf + 4, acc_buf, 4);
    for (int i = 0; i < (sizeof(acc_index) / sizeof(acc_index[0])); i++) {
        if (acc_index[i] == func_index) {
            bool ret = transceive(tx_buf, 8, &rx_buf, false);
            return ret;
        }
    }
    return false;
}


/*---编码器位置角度相关---*/
bool read_multi_turn_encoder_pos(int32_t *pos) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MULTI_ENCODER_POS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_int32(rx_buf.data + 4, pos);
    return true;
}

bool read_multi_turn_encoder_ori_pos(int32_t *ori_pos) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MULTI_ENCODER_ORI_POS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_int32(rx_buf.data + 4, ori_pos);
    return true;
}

bool read_multi_turn_encoder_zero_offset_pos(int32_t *zero_offset_pos) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MULTI_ENCODER_ZERO_OFFSET_POS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_int32(rx_buf.data + 4, zero_offset_pos);
    return true;
}

bool write_multi_turn_encoder_pos_as_zero(int32_t value) {
    rs485_rx_t rx_buf;
    uint8_t pos_buf[4];
    uint8_t tx_buf[8] = {CMD_WRITE_MULTI_ENCODER_POS_AS_ZERO, 0x00, 0x00, 0x00};
    int32_to_bytes(value, pos_buf);
    memcpy(tx_buf + 4, pos_buf, 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool write_multi_turn_encoder_current_pos_as_zero(int32_t value) {
    rs485_rx_t rx_buf;
    uint8_t pos_buf[4];
    uint8_t tx_buf[8] = {CMD_WRITE_MULTI_ENCODER_CURRENT_POS_AS_ZERO, 0x00, 0x00, 0x00};
    int32_to_bytes(value, pos_buf);
    memcpy(tx_buf + 4, pos_buf, 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool read_single_turn_encoder_pos(encoder_pos_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_SINGLE_ENCODER_POS, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_uint16(rx_buf.data + 2, &buf->pos);
    bytes_to_uint16(rx_buf.data + 4, &buf->raw_pos);
    bytes_to_uint16(rx_buf.data + 6, &buf->offset_pos);
    return true;
}

bool read_multi_turn_encoder_angle(float *angle) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MULTI_ENCODER_ANGLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    int32_t angle_int;
    bytes_to_int32(rx_buf.data + 4, &angle_int);
    *angle = (float)angle_int * 0.01f;
    return true;
}

bool read_single_turn_encoder_angle(float *angle) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_SINGLE_ENCODER_ANGLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    uint16_t angle_int;
    bytes_to_uint16(rx_buf.data + 6, &angle_int);
    *angle = (float)angle_int * 0.01f;
    return true;
}

/*---电机状态相关---*/
bool read_motor_status1(motor_status_t1 *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MOTOR_STATUS1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    uint16_t voltage;
    buf->temp = rx_buf.data[1];
    buf->brake = rx_buf.data[3];
    bytes_to_uint16(rx_buf.data + 4, &voltage);
    buf->voltage = (float)voltage * 0.1f;
    bytes_to_uint16(rx_buf.data + 6, &buf->error);
    return true;
}

bool read_motor_status2(motor_status_t2 *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MOTOR_STATUS2, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    buf->temp = rx_buf.data[1];
    int16_t torque_cur;
    bytes_to_int16(rx_buf.data + 2, &torque_cur);
    buf->torque_cur = (float)torque_cur * 0.01f;
    bytes_to_int16(rx_buf.data + 4, &buf->speed);
    bytes_to_int16(rx_buf.data + 6, &buf->angle);
    return true;
}

bool read_motor_status3(motor_status_t3 *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MOTOR_STATUS3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    int16_t current_a;
    int16_t current_b;
    int16_t current_c;
    buf->temp = rx_buf.data[1];
    bytes_to_int16(rx_buf.data + 2, &current_a);
    bytes_to_int16(rx_buf.data + 4, &current_b);
    bytes_to_int16(rx_buf.data + 6, &current_c);
    buf->current_a = (float)current_a * 0.01f;
    buf->current_b = (float)current_b * 0.01f;
    buf->current_c = (float)current_c * 0.01f;
    return true;
}

/*---电机运动相关---*/
bool close_motor() {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_CLOSE_MOTOR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool stop_motor() {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_STOP_MOTOR, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

/*---电机运动控制相关---*/
bool torque_control(float current, motor_motion_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8];
    memset(tx_buf, 0, sizeof(tx_buf));  // 先全部写0x00
    tx_buf[0] = CMD_TORQUE_CONTROL;
    int16_t torque_cur = (int16_t)(current * 100.0f);
    int16_to_bytes(torque_cur, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    parse_motion_response(&rx_buf, buf);
    return true;
}

bool speed_control(float speed, motor_motion_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_SPEED_CONTROL, 0x00, 0x00, 0x00};
    int16_t speed_cur = (int16_t)(speed * 100.0f);
    int16_to_bytes(speed_cur, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    parse_motion_response(&rx_buf, buf);
    return true;
}

bool abs_pos_control(float angle, int16_t max_speed, motor_motion_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_ABS_POS_CONTROL, 0x00};
    int16_to_bytes(max_speed, tx_buf + 2);
    int32_t angle_cur = (int32_t)(angle * 100.0f);
    int32_to_bytes(angle_cur, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    parse_motion_response(&rx_buf, buf);
    return true;
}

bool rel_pos_control(float angle, int16_t max_speed, motor_motion_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_REL_POS_CONTROL, 0x00};
    int16_to_bytes(max_speed, tx_buf + 2);
    int32_t angle_cur = (int32_t)(angle * 100.0f);
    int32_to_bytes(angle_cur, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    parse_motion_response(&rx_buf, buf);
    return true;
}

bool single_pos_control(float angle, int16_t max_speed, int8_t is_positive, motor_motion_t *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_REL_POS_CONTROL, is_positive};
    int16_to_bytes(max_speed, tx_buf + 2);
    int32_t angle_cur = (int32_t)(angle * 100.0f);
    int32_to_bytes(angle_cur, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    buf->temp = rx_buf.data[1];
    int16_t torque_cur;
    bytes_to_int16(rx_buf.data + 2, &torque_cur);
    buf->current = (float)torque_cur * 0.01f;
    bytes_to_int16(rx_buf.data + 4, &buf->speed);
    bytes_to_uint16(rx_buf.data + 6, &buf->pos);
    return true;
}

/*---刹车相关---*/
bool enable() {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_ENABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool disable() {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_DISABLE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool reset() {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_RESET, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool set_baudrate(uint8_t baud_idx) {
    /*
     设置波特率 默认115200
     baud_idx: 波特率索引
     0: 115200
     1: 500kbps
     2: 1Mbps
    */
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_SET_BAUDRATE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, baud_idx};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool set_comm_interrupt_timeout(uint32_t timeout) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_SET_INTER_TIMEOUT, 0x00, 0x00, 0x00};
    uint32_to_bytes(timeout, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool set_motor_id(uint8_t new_id) {
    rs485_rx_t rx_buf;
    // 1-32 电机ID
    if (new_id < 1 || new_id > 32) {
        return false;
    }
    uint8_t tx_buf[8] = {CMD_RW_MOTOR_ID, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, new_id};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

bool read_motor_id(uint8_t *motor_id) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_RW_MOTOR_ID, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (ret) {
        *motor_id = rx_buf.data[7];
        return true;
    }
    return false;
}

bool read_run_mode(uint8_t *mode) {
    /*
     读取电机模式
     0x01: 电流环
     0x02: 速度环
     0x03: 位置环
    */
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_RUN_MODE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    *mode = rx_buf.data[7];
    return true;
}

bool read_system_run_time(uint32_t *system_run_time) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_RUN_TIME, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_uint32(rx_buf.data + 4, system_run_time);
    return true;
}

bool read_software_version_date(uint32_t *vesion_date) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_VERSION_DATE, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    bytes_to_uint32(rx_buf.data + 4, vesion_date);
    return true;
}

bool read_motor_model(char *buf) {
    rs485_rx_t rx_buf;
    uint8_t tx_buf[8] = {CMD_READ_MOTOR_MODEL, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    if (!ret) {
        return false;
    }
    memcpy(buf, rx_buf.data + 1, 7);
    buf[7] = '\0';
    return true;
}

bool function_control(uint8_t func_index, int32_t value) {
    /*
    func_index: 功能索引
    0x01: 清除多圈值
    0x02: CANID滤波器使能
    0x03: 错误状态发送使能
    0x04: 多圈值掉电时保存使能
    0x05: 设置CANID
    0x06: 设置位置运行最大正角度
    0x07: 设置位置运行最大负角度
    */
    rs485_rx_t rx_buf;
    if (func_index < 0x01 || func_index > 0x07) {
        return false;
    }
    uint8_t tx_buf[8];
    memset(tx_buf, 0x00, sizeof(tx_buf));
    tx_buf[0] = CMD_FUNC_CONTROL;
    tx_buf[1] = func_index;
    int32_to_bytes(value, tx_buf + 4);
    bool ret = transceive(tx_buf, 8, &rx_buf, false);
    return ret;
}

// 安全停止电机
bool safe_close_motor() {
    bool ret = true;
    ret &= stop_motor();
    ret &= close_motor();
    return ret;
}
