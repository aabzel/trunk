#include "dword_utils.h"

#include <string.h>

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_MATH
#include "utils_math.h"
#endif

bool is_range_uint32(const uint32_t in_val, const uint32_t min, const uint32_t max) {
    bool res = false;
    if(min <= in_val) {
        if(in_val <= max) {
            res = true;
        }
    }
    return res;
}

/* 1 - 1
 * 12 - 2
 * 123 - 3*/
uint32_t rank_dec(const uint32_t de) {
    uint32_t r = 0;
    uint32_t t = de;
    while(t) {
        t /= 10;
        r++;
    }
    return r;
}

uint32_t u32_decimal_rank(const uint32_t value) {
    uint32_t in_value = value;
    uint32_t rank = 1;

    while(1) {
        in_value = in_value / 10;
        if(in_value) {
            rank++;
        } else {
            break;
        }
    }
    return rank;
}

bool swap_u32_xor(uint32_t* const a, uint32_t* const b) {
    bool res = false;
    if(a != b) {
        *a = *a ^ *b; /* a = a XOR b = c            */
        *b = *a ^ *b; /* b = (a XOR b) XOR b = a    */
        *a = *a ^ *b; /* a = (a XOR b) XOR a = b    */
        res = true;
    }
    return res;
}

/*
  invert decimal digits in a number
  1234 -> 4321
  1222 -> 2221
  1234567899 -> 9987654321
  */
uint64_t invert_dec(const uint32_t value) {
    uint64_t inv = 0;
#ifdef HAS_LOG
    LOG_INFO(SYS, "InvertDec:0x%08X=%u", value, value);
#endif
    uint32_t i = 0;
    uint32_t t = value;
    uint32_t rank = rank_dec(value);
    while(t) {
        uint32_t digit = t % 10;
        t /= 10;
        uint32_t exp = rank - i - 1;
        uint64_t scale = ((uint64_t)digit) * ipow(10, exp);
        inv += (uint64_t)scale;
        i++;
    }
#ifdef HAS_LOG
    LOG_INFO(SYS, "InvertedDec:%llu", inv);
#endif
    return inv;
}

int32_t max32(int32_t max32_x1, int32_t max32_x2) { return (((max32_x1) > (max32_x2)) ? (max32_x1) : (max32_x2)); }

int32_t min32(int32_t min32_x1, int32_t min32_x2) { return (((min32_x1) < (min32_x2)) ? (min32_x1) : (min32_x2)); }

bool data_u32_init(U32Value_t* const Node) {
    bool res = false;
    if(Node) {
        Node->cur = 0;
        Node->max = 0;
        Node->min = 0xFFFFFFFF;
        res = true;
    }
    return res;
}

/*from right to left from decimal*/
uint8_t extract_digit(uint32_t in_num, uint8_t digit_index) {
    uint8_t i = 0;
    uint8_t digit = 0;
    uint8_t out_digit = 0;
    uint32_t num = in_num;
    while(0 < num) {
        digit = num % 10;
        if(digit_index == i) {
            out_digit = digit;
            break;
        }
        num = num / 10;
        i++;
    }
    return out_digit;
}

uint32_t max32u(uint32_t max32u_x1, uint32_t max32u_x2) {
    return (((max32u_x1) > (max32u_x2)) ? (max32u_x1) : (max32u_x2));
}

uint32_t min32u(uint32_t min32u_x1, uint32_t min32u_x2) {
    return (((min32u_x1) < (min32u_x2)) ? (min32u_x1) : (min32u_x2));
}

int32_t int32_range_limiter(const int32_t in_val, const int32_t min, const int32_t max) {
    int32_t out_val = in_val;
    if(in_val < min) {
        out_val = min;
    } else if(max < in_val) {
        out_val = max;
    } else {
        out_val = in_val;
    }
    return out_val;
}

/*100, 7 -> 7*/
/*5, 7 -> 5*/
uint32_t uint32_limiter(const uint32_t in_val, const uint32_t max) {
    uint32_t out_val = in_val;
    if(max < in_val) {
        out_val = max;
    } else {
        out_val = in_val;
    }
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

bool fetch_big_endian_dword(const uint8_t* const data, const uint32_t size, uint32_t* const dword) {
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

uint32_t binary_coded_decimal_to_u32(const uint8_t* const data, const uint32_t nimble_cnt) {
    uint32_t result = 0;
    int32_t n_i = 0;
    for(n_i = nimble_cnt; 0 < n_i; n_i--) {
        uint8_t byte_index = (n_i - 1) / 2;
        uint8_t nibble = 0;
        if(0x1 & n_i) {
            nibble = data[byte_index] & 0x0F;
        } else {
            nibble = data[byte_index] >> 4;
        }
        result = result * 10 + nibble;
    }
    return result;
}

bool u32_to_binary_coded_decimal(const uint32_t value, uint8_t* const data, uint32_t* const nimble_cnt) {
    bool res = false;
    if(data) {
        if(nimble_cnt) {
            uint32_t c_ind = 0;
            uint32_t rank = u32_decimal_rank(value);
            *nimble_cnt = rank;
            uint32_t cur = value;
            while(1) {
                uint32_t nimble_i = 0x1 & c_ind;
                uint32_t byte_i = c_ind / 2;
                uint32_t digit = cur % 10;
                cur = cur / 10;

                if(nimble_i) {
                    data[byte_i] |= digit << 4;
                } else {
                    data[byte_i] = 0x00;
                    data[byte_i] = 0x0F & digit;
                }
#ifdef HAS_LOG
                LOG_DEBUG(SYS, "i:%u,nimble_i:%u,digit:%d,byte_i:%u,Data:0x%02x", c_ind, nimble_i, digit, byte_i,
                          data[byte_i]);
#endif

                if(0 == cur) {
                    res = true;
                    break;
                }
                c_ind++;
            }
        }
    }
    return res;
}
