#include "data_utils.h"

#include <float.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_ARRAY
#include "array.h"
#endif

#ifdef HAS_DATA_UTILS_EXT
uint8_t uint16_to_uint8_limiter(uint16_t in_val) {
    uint8_t out_val = 0xFF;
    if(in_val < 0xFF) {
        out_val = in_val;
    }
    return out_val;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
uint32_t ceil4byte(uint32_t val) {
    uint32_t out_val = val;
    while((out_val & 3) != 0) {
        out_val++;
    }
    return out_val;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
uint8_t uint8_limiter(uint8_t in_val, uint8_t up_val) {
    uint8_t out_val = up_val;
    if(in_val <= up_val) {
        out_val = in_val;
    }
    return out_val;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
int8_t int8_limiter(int32_t in_val) {
    int32_t out_val = in_val;
    if(in_val < -127) {
        out_val = -127;
    }
    if(127 < in_val) {
        out_val = 127;
    }
    return out_val;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
/*TODO test it*/
double limit_value_double(double min_val, double max_val, double in_value) {
    double out_value = in_value;
    if(in_value < min_val) {
        out_value = min_val;
    }
    if(max_val < in_value) {
        out_value = max_val;
    }
    return out_value;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
/*100, 7 -> 7*/
/*5, 7 -> 5*/
uint32_t uint32_limiter(uint32_t in_val, uint32_t max) {
    uint32_t out_val = in_val;
    if(max < in_val) {
        out_val = max;
    } else {
        out_val = in_val;
    }
    return out_val;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
int32_t int32_range_limiter(int32_t in_val, int32_t min, int32_t max) {
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
#endif

#ifdef HAS_DATA_UTILS_EXT
uint8_t max8u(uint8_t max8u_x1, uint8_t max8u_x2) { return (((max8u_x1) > (max8u_x2)) ? (max8u_x1) : (max8u_x2)); }

uint8_t min8u(uint8_t min8u_x1, uint8_t min8u_x2) { return (((min8u_x1) < (min8u_x2)) ? (min8u_x1) : (min8u_x2)); }

uint16_t max16u(uint16_t max16u_x1, uint16_t max16u_x2) {
    return (((max16u_x1) > (max16u_x2)) ? (max16u_x1) : (max16u_x2));
}

uint16_t min16u(uint16_t min16u_x1, uint16_t min16u_x2) {
    return (((min16u_x1) < (min16u_x2)) ? (min16u_x1) : (min16u_x2));
}

uint32_t max32u(uint32_t max32u_x1, uint32_t max32u_x2) {
    return (((max32u_x1) > (max32u_x2)) ? (max32u_x1) : (max32u_x2));
}

uint64_t max64u(uint64_t max64u_x1, uint64_t max64u_x2) {
    return (((max64u_x1) > (max64u_x2)) ? (max64u_x1) : (max64u_x2));
}

uint32_t min32u(uint32_t min32u_x1, uint32_t min32u_x2) {
    return (((min32u_x1) < (min32u_x2)) ? (min32u_x1) : (min32u_x2));
}

uint64_t min64u(uint64_t min64u_x1, uint64_t min64u_x2) {
    return (((min64u_x1) < (min64u_x2)) ? (min64u_x1) : (min64u_x2));
}

int8_t max8(int8_t max8_x1, int8_t max8_x2) { return (((max8_x1) > (max8_x2)) ? (max8_x1) : (max8_x2)); }

int8_t min8(int8_t min8_x1, int8_t min8_x2) { return (((min8_x1) < (min8_x2)) ? (min8_x1) : (min8_x2)); }

int16_t max16(int16_t max16_x1, int16_t max16_x2) { return (((max16_x1) > (max16_x2)) ? (max16_x1) : (max16_x2)); }

int16_t min16(int16_t min16_x1, int16_t min16_x2) { return (((min16_x1) < (min16_x2)) ? (min16_x1) : (min16_x2)); }

int32_t max32(int32_t max32_x1, int32_t max32_x2) { return (((max32_x1) > (max32_x2)) ? (max32_x1) : (max32_x2)); }

int32_t min32(int32_t min32_x1, int32_t min32_x2) { return (((min32_x1) < (min32_x2)) ? (min32_x1) : (min32_x2)); }
#endif

#ifdef HAS_DATA_UTILS_EXT
uint32_t swap32(uint32_t u32_num) {
    return ((((u32_num) >> 24) & 0xffU) | (((u32_num) << 8) & 0xff0000U) | (((u32_num) >> 8) & 0xff00U) |
            (((u32_num) << 24) & 0xff000000U));
}
#endif

#ifdef HAS_DATA_UTILS_EXT
uint16_t swap16(uint16_t u16_num) {
    return (((uint16_t)((u16_num) >> 8) & 0xffU) | ((uint16_t)((u16_num) << 8) & 0xff00U));
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool swap8(uint8_t* const u8_x, uint8_t* const u8_y) {
    bool res = false;
    if(u8_x && u8_y) {
        uint8_t temp = *u8_x;
        *u8_x = *u8_y;
        *u8_y = temp;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool swap_f(float* const u8_x, float* const u8_y) {
    bool res = false;
    if(u8_x && u8_y) {
        float temp = *u8_x;
        *u8_x = *u8_y;
        *u8_y = temp;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool swap_16(uint16_t* u16_x, uint16_t* u16_y) {
    bool res = false;
    if(u16_x && u16_y) {
        uint16_t temp = *u16_x;
        *u16_x = *u16_y;
        *u16_y = temp;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
#define TEN_SPACES "          "
const char* get_spaces_str(uint32_t spaces_length) {
    static char szSpaces[101] =
        TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES TEN_SPACES;
    uint32_t last_index = sizeof(szSpaces) - 1U;
    if(spaces_length > last_index) {
        last_index = 0U;
    } else {
        last_index -= spaces_length;
    }
    return &szSpaces[last_index];
}
#endif

#ifdef HAS_DATA_UTILS_EXT
float ms2Hz(uint16_t ms) {
    float hz = (1.0f * 1000.0f) / ((float)ms);
    return hz;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
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
#endif

#if 0
bool try_alloc_on_stack(int n, uint8_t pat, uint16_t* real_size) {
    // uint8_t array[n];
    bool res = false;
    uint8_t array[n]; // actually on heap
    *real_size = sizeof(array);

    memset(array, pat, n);
    if(is_arr_pat(array, n, pat)) {
        res = true;
    }

    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool mem_scan(uint8_t* base, uint32_t size, float* usage_pec, uint32_t* spare, uint32_t* busy) {
    bool res = false;
    if(usage_pec && spare && busy) {
        res = true;
        *spare = 0;
        *busy = 0;
        uint8_t* addr = base;
        uint32_t cnt = 0;
        for(addr = base, cnt = 0; addr < (base + size); addr++, cnt++) {
            if(0xFF == (*addr)) {
                (*spare)++;
            } else {
                (*busy)++;
            }
            if(!(cnt % 1000)) {
                // wait_in_loop_ms(5);
            }
        }
        *usage_pec = (float)(((float)(100U * (*busy))) / ((float)size));
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
uint8_t Bits2Bytes(uint8_t bits_cnt) {
    uint8_t bytes_cnt = 0;
    bytes_cnt = bits_cnt / 8;
    if(0 < bits_cnt % 8) {
        bytes_cnt++;
    }
    return bytes_cnt;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool is_around_int_val(int32_t center, int32_t value, uint32_t delta) {
    bool res = false;
    if(value < (center + ((int32_t)delta))) {
        if((center - ((int32_t)delta)) < value) {
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool toggle_bool(bool on_off_in) {
    bool on_off_out = false;
    switch((uint8_t)on_off_in) {
    case true:
        on_off_out = false;
        break;
    case false:
        on_off_out = true;
        break;
    }
    return on_off_out;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool double_val_reset(DoubleValue_t* const Node) {
    bool res = false;
    if(Node) {
        Node->cur = 0.0;
        Node->max = DBL_MIN;
        Node->min = DBL_MAX;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool float_val_reset(FloatValue_t* const Node) {
    bool res = false;
    if(Node) {
        Node->cur = 0.0;
        Node->max = FLT_MIN;
        Node->min = FLT_MAX;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
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
#endif

#ifdef HAS_DATA_UTILS_EXT
bool data_u64_init(U64Value_t* const Node) {
    bool res = false;
    if(Node) {
        Node->cur = 0;
        Node->max = 0;
        Node->min = 0xFFFFFFFFFFFFffff;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool data_u64_update(U64Value_t* const Node, uint64_t val) {
    bool res = false;
    if(Node) {
        Node->cur = val;
        Node->max = MAX(Node->max, val);
        Node->min = MIN(Node->min, val);
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_DATA_UTILS_EXT
bool swap_u32_xor(uint32_t* const a, uint32_t* const b) {
    bool res = false;
    if(a != b) {
        *a = *a ^ *b; // a = a XOR b = c
        *b = *a ^ *b; // b = (a XOR b) XOR b = a
        *a = *a ^ *b; // a = (a XOR b) XOR a = b
        res = true;
    }
    return res;
}
#endif
