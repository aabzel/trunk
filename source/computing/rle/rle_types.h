#ifndef RLE_TYPES_H
#define RLE_TYPES_H

#include <stdint.h>

#include "rle_const.h"

typedef struct {
    char prev;
    uint32_t cnt;
    uint32_t in_size;
    char* mem_start;
    char temp_str[100];
    uint32_t out_idx;
} RleEncodeFsm_t;

typedef struct {
    uint32_t d;
    uint32_t i;
    char prev_letter;
    char prev_symbol;
    char cur_char;
    RleDecoderState_t state;
    RleDecoderInput_t input;
    uint32_t out_idx;
}RleDecodeFsm_t;

#endif
