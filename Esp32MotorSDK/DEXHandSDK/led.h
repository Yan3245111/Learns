#ifndef __LED_H__
#define __LED_H__

#include <stdint.h>
#include <stdbool.h>

#define LED_PIN         GPIO_NUM_35

#define LED_NUMBERS     3

#define BREATH_STEPS    100

void led_init(void);

void led_set_pixel(int index, uint8_t r, uint8_t g, uint8_t b);

void led_set_all(uint8_t r, uint8_t g, uint8_t b);

void led_refresh(void);

void led_clear(void);

#endif
