#ifndef BASE64_H
#define BASE64_H

#include <stdbool.h>
#include <stdint.h>

#include "base64_types.h"

bool is_base64(const uint8_t* const encode_data, uint32_t data_size);
bool base64_decode(const char* const decode_str, int32_t decode_str_len, uint8_t decode_data[],
                   uint32_t* decode_data_size);
uint32_t base64_encode(const uint8_t encode_data[], uint32_t encode_data_size, char encode_result[]);

#endif
