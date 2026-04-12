#include "byte_utils.h"

#include <stdint.h>
#include <string.h>

#include "data_utils.h"

uint8_t swap_nibbles(uint8_t const data) {
    uint8_t val = 0;
    val = ((LO_NIBBLE(data) << 4) | ((data & 0xF0) >> 4));
    return val;
}

uint64_t reverse_byte_order_uint64(const uint64_t in4byteVal) {
    uint64_t out_val = in4byteVal;
    out_val = (out_val & 0x00000000FFFFFFFF) << 32 | (out_val & 0xFFFFFFFF00000000) >> 32;
    out_val = (out_val & 0x0000FFFF0000FFFF) << 16 | (out_val & 0xFFFF0000FFFF0000) >> 16;
    out_val = (out_val & 0x00FF00FF00FF00FF) << 8 | (out_val & 0xFF00FF00FF00FF00) >> 8;
    return out_val;
}

uint32_t reverse_byte_order_uint32(const uint32_t in4byteVal) {
    uint32_t retval;
    retval = in4byteVal & 0xFF;
    retval = (retval << 8) | ((in4byteVal >> 8) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 16) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 24) & 0xFF);
    return retval;
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

uint16_t reverse_byte_order_uint16(const uint16_t in2byteVal) {
    uint16_t swapped = 0;
    swapped = (in2byteVal >> 8) | (in2byteVal << 8);
    return swapped;
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

uint16_t copy_and_rev16(const uint8_t* const array) {
    uint16_t value16b = 0;
    memcpy(&value16b, array, 2);
    value16b = reverse_byte_order_uint16(value16b);
    return value16b;
}

uint32_t copy_and_rev32(const uint8_t* const array) {
    uint32_t value32b = 0;
    memcpy(&value32b, array, 4);
    value32b = reverse_byte_order_uint32(value32b);
    return value32b;
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
