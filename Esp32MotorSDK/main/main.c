#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "cmd_handle.h"


void app_main(void)
{
    cmd_handle_init();
    xTaskCreate(cmd_handle_task, "cmd_handle_task", 2048, NULL, 5, NULL);
    while (1) {
        vTaskDelay(pdMS_TO_TICKS(100));
    }
}
