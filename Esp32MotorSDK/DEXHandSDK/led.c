#include "led.h"

#include "led_strip.h"
#include "esp_err.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>

static led_strip_handle_t strip = NULL;


void led_init(void) {
    led_strip_config_t strip_config = {
        .strip_gpio_num = LED_PIN,
        .max_leds = LED_NUMBERS,
        .led_model = LED_MODEL_WS2812,
        .color_component_format = LED_STRIP_COLOR_COMPONENT_FMT_GRB,
        .flags.invert_out = false,
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT,
        .resolution_hz = 10 * 1000 * 1000,
        .flags.with_dma = false,
    };

    esp_err_t ret = led_strip_new_rmt_device(&strip_config, &rmt_config, &strip);
    if (ret != ESP_OK) {
        strip = NULL;
        return;
    }
    led_strip_clear(strip);
}

void led_set_pixel(int index, uint8_t r, uint8_t g, uint8_t b) {
    if (strip == NULL || index < 0 || index >= LED_NUMBERS) return;
    led_strip_set_pixel(strip, index, r, g, b);
}

void led_set_all(uint8_t r, uint8_t g, uint8_t b) {
    if (strip == NULL) return;
    for (int i = 0; i < LED_NUMBERS; i++) {
        led_strip_set_pixel(strip, i, r, g, b);
    }
    led_refresh();
}

void led_refresh(void) {
    if (strip == NULL) return;
    led_strip_refresh(strip);
}

void led_clear(void) {
    if (strip == NULL) return;
    led_strip_clear(strip);
}
