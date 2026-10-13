#ifndef __PACK_UTILS_H__
#define __PACK_UTILS_H__

#include <stdint.h>
#include <stddef.h>
#include <string.h>


void float_to_bytes(float value, uint8_t *buf);

void bytes_to_float(uint8_t *buf, float *value);

void int32_to_bytes(int32_t value, uint8_t *buf);

void bytes_to_int32(uint8_t *buf, int32_t *value);

void uint32_to_bytes(uint32_t value, uint8_t *buf);

void bytes_to_uint32(uint8_t *buf, uint32_t *value);

void int16_to_bytes(int16_t value, uint8_t *buf);

void bytes_to_int16(uint8_t *buf, int16_t *value);

void uint16_to_bytes(uint16_t value, uint8_t *buf);

void bytes_to_uint16(uint8_t *buf, uint16_t *value);


#endif  