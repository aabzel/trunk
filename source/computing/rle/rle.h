#ifndef RLE_H
#define RLE_H

#include <stdbool.h>
#include <stdint.h>

#include "rle_types.h"

bool rle_encode(const char* const encode_data, uint32_t in_size, char* const encode_result, uint32_t* const out_size);
uint32_t rle_encode_in_place(char* chars, uint32_t chars_size);
bool rle_decode(const char* const decode_str, uint32_t in_size, char* const decode_data, uint32_t* const out_size);
int rle_encode_v2(char* chars, int charsSize);

#endif
