#ifndef __NVS_STORAGE_H__
#define __NVS_STORAGE_H__

#include <stdint.h>
#include <stdbool.h>

// 初始化 NVS
void nvs_storage_init(void);

// 写入浮点数
bool nvs_save_float(const char* key, float value);

// 读取浮点数（如果不存在，返回默认值）
float nvs_load_float(const char* key, float default_val);

// 写入角度
void nvs_save_angle(float angle);

// 读取角度（默认值 0.0f）
float nvs_load_angle(void);

#endif
