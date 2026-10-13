#include "pack_utils.h"


void float_to_bytes(float value, uint8_t *buf) {
    memcpy(buf, &value, sizeof(float));
}

void bytes_to_float(uint8_t *buf, float *value) {
    memcpy(value, buf, sizeof(float));
}

void int32_to_bytes(int32_t value, uint8_t *buf) {
    memcpy(buf, &value, sizeof(int32_t));
}

void bytes_to_int32(uint8_t *buf, int32_t *value) {
    memcpy(value, buf, sizeof(int32_t));
}

void uint32_to_bytes(uint32_t value, uint8_t *buf) {
    memcpy(buf, &value, sizeof(uint32_t));
}

void bytes_to_uint32(uint8_t *buf, uint32_t *value) {
    memcpy(value, buf, sizeof(uint32_t));
}

void int16_to_bytes(int16_t value, uint8_t *buf) {
    memcpy(buf, &value, sizeof(int16_t));
}

void bytes_to_int16(uint8_t *buf, int16_t *value) {
    memcpy(value, buf, sizeof(int16_t));
}

void uint16_to_bytes(uint16_t value, uint8_t *buf) {
    memcpy(buf, &value, sizeof(uint16_t));
}

void bytes_to_uint16(uint8_t *buf, uint16_t *value) {
    memcpy(value, buf, sizeof(uint16_t));
}
