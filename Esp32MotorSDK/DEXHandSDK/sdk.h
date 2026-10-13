#ifndef __SDK_H__
#define __SDK_H__

#include "model485.h"
#include "pack_utils.h"

#define HEAD      0x3E
#define BROADCAST 0xCD
#define ENC_PPR   65536
#define MAX_SPEED 500
#define DEVICE_ID 0x01
#define DATA_LEN  8

// 指令码
#define CMD_READ_PID         0x30
#define CMD_WRITE_RAM_PID    0x31
#define CMD_WRITE_ROM_PID    0x32

#define CMD_READ_ACC         0x42
#define CMD_WRITE_ACC        0x43

#define CMD_READ_MULTI_ENCODER_POS                  0x60
#define CMD_READ_MULTI_ENCODER_ORI_POS              0x61
#define CMD_READ_MULTI_ENCODER_ZERO_OFFSET_POS      0x62
#define CMD_WRITE_MULTI_ENCODER_POS_AS_ZERO         0x63
#define CMD_WRITE_MULTI_ENCODER_CURRENT_POS_AS_ZERO 0x64

#define CMD_READ_SINGLE_ENCODER_POS                 0x90
#define CMD_READ_MULTI_ENCODER_ANGLE                0x92
#define CMD_READ_SINGLE_ENCODER_ANGLE               0x94

#define CMD_READ_MOTOR_STATUS1     0x9A
#define CMD_READ_MOTOR_STATUS2     0x9C
#define CMD_READ_MOTOR_STATUS3     0x9D

#define CMD_CLOSE_MOTOR         0x80
#define CMD_STOP_MOTOR          0x81

#define CMD_TORQUE_CONTROL     0xA1
#define CMD_SPEED_CONTROL      0xA2
#define CMD_ABS_POS_CONTROL    0xA4
#define CMD_SINGLE_POS_CONTROL 0xA6
#define CMD_REL_POS_CONTROL    0xA8

#define CMD_READ_RUN_MODE     0x70
#define CMD_RESET             0x76
#define CMD_ENABLE            0x77
#define CMD_DISABLE           0x78
#define CMD_RW_MOTOR_ID       0x79

#define CMD_READ_RUN_TIME       0xB1
#define CMD_READ_VERSION_DATE   0xB2
#define CMD_SET_INTER_TIMEOUT   0xB3
#define CMD_SET_BAUDRATE        0xB4
#define CMD_READ_MOTOR_MODEL    0xB5

#define CMD_FUNC_CONTROL        0x20

// 字节对齐 要发数据到机器人
#pragma pack(push, 1)
// 单圈编码器位置
typedef struct {
    uint16_t pos;
    uint16_t raw_pos;
    uint16_t offset_pos;
} encoder_pos_t;

// 电机状态1
typedef struct {
    int8_t temp;
    uint8_t brake;
    float voltage;
    uint16_t error;
} motor_status_t1;

// 电机状态2
typedef struct {
    int8_t temp;
    float torque_cur;
    int16_t speed;
    int16_t angle;
} motor_status_t2;

// 电机状态3
typedef struct {
    int8_t temp;
    float current_a;
    float current_b;
    float current_c;
} motor_status_t3;

// 电机运动控制
typedef struct {
    int8_t temp;      // 1字节
    float current;    // 4字节
    int16_t speed;    // 2字节
    int16_t angle;    // 2字节
    uint16_t pos;     // 2字节
} motor_motion_t;
#pragma pack(pop)

// PID 读取/写入
bool read_pid(int func_index, float *pid);

bool write_pid_to_ram(int func_index, float pid);

bool write_pid_to_rom(int func_index, float pid);

// 加速度读写
bool read_acc(int func_index, int32_t *acc);

bool write_acc(int func_index, int32_t acc);

// 编码器位置角度读写
bool read_multi_turn_encoder_pos(int32_t *pos);

bool read_multi_turn_encoder_ori_pos(int32_t *pos);

bool read_multi_turn_encoder_zero_offset_pos(int32_t *pos);

bool write_multi_turn_encoder_pos_as_zero(int32_t value);

bool write_multi_turn_encoder_current_pos_as_zero(int32_t value);

bool read_single_turn_encoder_pos(encoder_pos_t *buf);

bool read_multi_turn_encoder_angle(float *angle);

bool read_single_turn_encoder_angle(float *angle);

bool read_motor_status1(motor_status_t1 *buf);

bool read_motor_status2(motor_status_t2 *buf);

bool read_motor_status3(motor_status_t3 *buf);

// 电机关闭 停止
bool close_motor();

bool stop_motor();

// 电机运动控制
// 转矩闭环控制
bool torque_control(float current, motor_motion_t *buf);

// 速度闭环控制
bool speed_control(float speed, motor_motion_t *buf);

// 绝对位置闭环控制
bool abs_pos_control(float angle, int16_t max_speed, motor_motion_t *buf);

// 相对位置闭环控制
bool rel_pos_control(float angle, int16_t max_speed, motor_motion_t *buf);

// 单圈位置闭环控制
bool single_pos_control(float angle, int16_t max_speed, int8_t is_positive, motor_motion_t *buf);

// 抱闸
bool enable();

bool disable();

// 系统相关
bool reset();

bool set_baudrate(uint8_t baud_idx);

bool set_comm_interrupt_timeout(uint32_t timeout);

bool set_motor_id(uint8_t new_id);

bool read_motor_id(uint8_t *id);

// 读取运行模式
bool read_run_mode(uint8_t *mode);

bool read_system_run_time(uint32_t *time);

bool read_software_version_date(uint32_t *date);

bool read_motor_model(char *buf);

bool function_control(uint8_t func_index, int32_t value);

// 安全停止电机
bool safe_close_motor();

#endif
