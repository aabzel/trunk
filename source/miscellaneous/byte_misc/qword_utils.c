#include "qword_utils.h"

#include <string.h>

#include "word_utils.h"
#include "dword_utils.h"

#ifndef MAX
#define MAX(n, m) (((n) < (m)) ? (m) : (n))
#endif

#ifndef MIN
#define MIN(n, m) (((n) < (m)) ? (n) : (m))
#endif

uint64_t min64u(uint64_t min64u_x1, uint64_t min64u_x2) {
    return (((min64u_x1) < (min64u_x2)) ? (min64u_x1) : (min64u_x2));
}

uint64_t max64u(uint64_t max64u_x1, uint64_t max64u_x2) {
    return (((max64u_x1) > (max64u_x2)) ? (max64u_x1) : (max64u_x2));
}


uint64_t reverse_byte_order_uint64(const uint64_t in4byteVal) {
    uint64_t out_val = in4byteVal;
    out_val = (out_val & 0x00000000FFFFFFFF) << 32 | (out_val & 0xFFFFFFFF00000000) >> 32;
    out_val = (out_val & 0x0000FFFF0000FFFF) << 16 | (out_val & 0xFFFF0000FFFF0000) >> 16;
    out_val = (out_val & 0x00FF00FF00FF00FF) << 8 | (out_val & 0xFF00FF00FF00FF00) >> 8;
    return out_val;
}

uint64_t unsigned_big_endian_to_u64(const uint8_t* const memory, const uint32_t param_size) {
    uint64_t value_u64 = 0;
    if(memory) {
        switch (param_size) {
        case 1: {
            uint8_t byte = 0;
            memcpy(&byte, memory, 1);
            value_u64 = (uint64_t) byte;
        }
            break;

        case 2: {
            uint16_t word = 0;
            memcpy(&word, memory, 2);
            value_u64 = (uint64_t) reverse_byte_order_uint16(word);
        }
            break;

        case 4: {
            uint32_t dword = 0;
            memcpy(&dword, memory, 4);
            value_u64 = (uint64_t) reverse_byte_order_uint32(dword);
        }
            break;

        case 8: {
            uint64_t qword = 0;
            memcpy(&qword, memory, 8);
            value_u64 = (uint64_t) reverse_byte_order_uint64(qword);
        }
            break;
        default:
            break;
        }

    }
    return value_u64;
}


bool data_u64_init(U64Value_t* const Node) {
    bool res = false;
    if(Node) {
        Node->cur = 0;
        Node->max = 0;
        Node->min = 0xFFFFFFFFFFFFFFFF;
        res = true;
    }
    return res;
}


bool data_u64_update(U64Value_t* const Node, const uint64_t val) {
    bool res = false;
    if(Node) {
        Node->cur = val;
        Node->max = MAX(Node->max, val);
        Node->min = MIN(Node->min, val);
        res = true;
    }
    return res;
}

bool fetch_big_endian_qword(const uint8_t* const data,
                            const uint32_t size,
                            uint64_t* const qword) {
    bool res = false;
    if(qword) {
        if(8 <= size) {
            uint64_t q_value = 0;
            memcpy(&q_value, data, 8);
            *qword = reverse_byte_order_uint64(q_value);
            res = true;
        }
    }
    return res;
}
