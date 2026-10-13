#include "cmd_handle.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"


static void send_feedback_to_robot(uint8_t cmd_id, void *buf, uint8_t data_len) {
    uint8_t tx_buf[RS485_BUF_SIZE];
    tx_buf[0] = ROBOT485_HEAD;
    tx_buf[1] = cmd_id;
    tx_buf[2] = data_len;
    memcpy(tx_buf + 3, buf, data_len);
    tx_buf[data_len + 3] = ROBOT485_TAIL;
    robot485_send((uint8_t*)tx_buf, data_len + 4);
}


static void process_cmd(robot485_rx_t *rx_buf) {
    uint8_t cmd_id = rx_buf->cmd_id;
    float angle;
    motor_motion_t buf;
    switch (cmd_id) {
        case CMD_SET_REL_POS_CONTROL:
            bytes_to_float(rx_buf->data, &angle);
            printf("rel pos control angle: %f\n", angle);
            rel_pos_control(angle, 500, &buf);
            send_feedback_to_robot(cmd_id, &buf, sizeof(motor_motion_t) - 2);
            break;
        case CMD_SET_ABS_POS_CONTROL:
            bytes_to_float(rx_buf->data, &angle);
            printf("abs pos control angle: %f\n", angle);
            abs_pos_control(angle, 500, &buf);
            send_feedback_to_robot(cmd_id, &buf, sizeof(motor_motion_t) - 2);
            break;
        case CMD_GET_SING_ANGLE:
            read_single_turn_encoder_angle(&angle);
            printf("single turn angle: %f\n", angle);
            send_feedback_to_robot(cmd_id, &angle, sizeof(angle));
            break;
        case CMD_GET_MULTI_ANGLE:
            read_multi_turn_encoder_angle(&angle);
            printf("multi turn angle: %f\n", angle);
            send_feedback_to_robot(cmd_id, &angle, sizeof(angle));
            break;
        case CMD_SET_MOTOR_SAFE_CLOSE:
            printf("safe close motor\n");
            safe_close_motor();
            break;
        case CMD_SET_ENABLE:
            printf("enable motor\n");
            led_set_all(0, 255, 0);
            enable();
            break;
        case CMD_SET_DISABLE:
            printf("disable motor\n");
            led_set_all(255, 0, 0);
            disable();
            break;
         case CMD_SET_INIT_ANGLE:
            read_multi_turn_encoder_angle(&angle);
            printf("read multi turn angle: %f\n", angle);
            nvs_save_angle(angle);
            break;
        case CMD_GET_INIT_ANGLE:
            angle = nvs_load_angle();
            printf("init angle: %f\n", angle);
            send_feedback_to_robot(cmd_id, &angle, sizeof(angle));
            break;
        case CMD_GO_TO_INIT_ANGLE:
            angle = nvs_load_angle();
            printf("go to init angle: %f\n", angle);
            if (angle != 0.0f) {
                abs_pos_control(angle, 500, &buf);
                send_feedback_to_robot(cmd_id, &buf, sizeof(motor_motion_t) - 2);
            }
            break;
        default:
            break;
    }
}

void cmd_handle_init(void) {
    rs485_init();
    robot485_init();
    nvs_storage_init();
    led_init();
}

void cmd_handle_task(void *pvParameters) {
    robot485_rx_t rx_buf;
     while (1) {
        if (robot485_recv(&rx_buf)) {
            process_cmd(&rx_buf);
        }
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}
