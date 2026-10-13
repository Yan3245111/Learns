#ifndef __CMD_HANDLE_H__
#define __CMD_HANDLE_H__

#include "sdk.h"
#include "led.h"
#include "robot485.h"
#include "nvs_storage.h"


#define CMD_SET_REL_POS_CONTROL     0x01
#define CMD_SET_ABS_POS_CONTROL     0x02

#define CMD_GET_SING_ANGLE          0x03
#define CMD_GET_MULTI_ANGLE         0x04
#define CMD_SET_MOTOR_SAFE_CLOSE    0x05

#define CMD_SET_ENABLE              0x06
#define CMD_SET_DISABLE             0x07

#define CMD_SET_INIT_ANGLE          0x08
#define CMD_GET_INIT_ANGLE          0x09
#define CMD_GO_TO_INIT_ANGLE        0x0A  // 走到初始闭合位置



void cmd_handle_init(void);

void cmd_handle_task(void *pvParameters);

#endif
