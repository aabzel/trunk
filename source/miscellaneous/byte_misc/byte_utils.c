#include "byte_utils.h"

#include <stdint.h>
#include <string.h>

#include "data_utils.h"

uint8_t swap_nibbles(uint8_t const data) {
    uint8_t val = 0;
    val = ((LO_NIBBLE(data) << 4) | ((data & 0xF0) >> 4));
    return val;
}

uint32_t reverse_byte_order_uint24(const uint32_t in3byteVal) {
    Type32Union_t u32val_in = {0}, u32val_out = {0};

    u32val_in.u32 = in3byteVal;

    u32val_out.u8[0] = u32val_in.u8[2];
    u32val_out.u8[1] = u32val_in.u8[1];
    u32val_out.u8[2] = u32val_in.u8[0];
    u32val_out.u8[3] = 0x00;

    return u32val_out.u32;
}

int32_t reverse_byte_order_int24(const int32_t in3byteVal) {
    Type32Union_t u32val_in, u32val_out;

    u32val_in.s32 = in3byteVal;

    u32val_out.u8[0] = u32val_in.u8[2];
    u32val_out.u8[1] = u32val_in.u8[1];
    u32val_out.u8[2] = u32val_in.u8[0];
    u32val_out.u8[3] = 0;
    return u32val_out.s32;
}

bool reverse_byte_order_array(uint8_t* const in_out_array, uint32_t len) {
    bool res = false;
    if(in_out_array) {
        if(len) {
            res = true;
            uint32_t i = 0;
            for(i = 0; i < (len / 2); i++) {
                res = swap8(&in_out_array[i], &in_out_array[len - i - 1]) && res;
            }
        }
    }

    return res;
}

uint64_t copy_and_rev64(const uint8_t* const array) {
    uint64_t value64b = 0;
    memcpy(&value64b, array, 8);
    value64b = reverse_byte_order_uint64(value64b);
    return value64b;
}

uint32_t reverse_half_word_order_uint32(const uint32_t word) {
    Type32Union_t un32_out;
    Type32Union_t un32_in;
    un32_out.u32 = 0;
    un32_in.u32 = word;
    un32_out.u16[0] = un32_in.u16[1];
    un32_out.u16[1] = un32_in.u16[0];
    return un32_out.u32;
}

#if 0
const char* ByteNameToStr(const uint8_t code, const char* token) {
    char* name = "_";
    if(code) {
        name = token;
    }
    return name;
}
#endif

bool fetch_big_endian_word(const uint8_t* const data, const uint32_t size, uint16_t* const word) {
    bool res = false;
    if(word) {
        if(2 <= size) {
            uint16_t w_value = 0;
            memcpy(&w_value, data, 2);
            *word = reverse_byte_order_uint16(w_value);
            res = true;
        }
    }
    return res;
}

bool is_byte_in_range(const uint8_t min_val, const uint8_t cur, const uint8_t max_val) {
    bool res = false;
    if(min_val <= cur) {
        if(cur <= max_val) {
            res = true;
        }
    }
    return res;
}

/*
 is val : 1 3 5 7 9
 */
bool is_byte_odd(const uint8_t val) {
    bool res = false;
    res = (1 == (1 & val));
    return res;
}
