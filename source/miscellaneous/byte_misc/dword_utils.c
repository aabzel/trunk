#include "dword_utils.h"

#include <string.h>

uint32_t reverse_byte_order_uint32(const uint32_t in4byteVal) {
    uint32_t retval;
    retval = in4byteVal & 0xFF;
    retval = (retval << 8) | ((in4byteVal >> 8) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 16) & 0xFF);
    retval = (retval << 8) | ((in4byteVal >> 24) & 0xFF);
    return retval;
}


bool fetch_big_endian_dword(const uint8_t* const data,
                            const uint32_t size,
                            uint32_t* const dword) {
    bool res = false;
    if(dword) {
        if(4 <= size) {
            uint32_t d_value = 0;
            memcpy(&d_value, data, 4);
            *dword = reverse_byte_order_uint32(d_value);
            res = true;
        }
    }
    return res;
}

uint32_t copy_and_rev32(const uint8_t* const array) {
    uint32_t value32b = 0;
    memcpy(&value32b, array, 4);
    value32b = reverse_byte_order_uint32(value32b);
    return value32b;
}
