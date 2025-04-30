#ifndef BASE16_H
#define BASE16_H

#include <stdbool.h>
#include <stdint.h>

#include "base16_types.h"

bool base16_is_allowed_char(char base16);
uint8_t base16_char_to_val(char hex_char);
bool is_base16(const uint8_t* const some_data, uint32_t data_size);
bool base16_decode(const char* const decode_str, uint32_t decode_str_len, uint8_t* const decode_data,
                   uint32_t* decode_data_size);

bool base16_encode(const uint8_t* const raw_data, uint32_t buff_len, char* const out_array);
#endif
