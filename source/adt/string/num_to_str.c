#include "num_to_str.h"

#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "byte_utils.h"
#include "convert.h"
#include "log.h"
#include "str_utils.h"

static const char symbols[] = "FEDCBA9876543210123456789ABCDEF";

char* HexQWord2Str(uint32_t qword) {
    snprintf(text, sizeof(text), "0x%08x", (unsigned int)qword);
    return text;
}

char* HexQWordRevToStr(uint64_t qword) {
    uint64_t temp_qword = reverse_byte_order_uint64(qword);
    // snprintf(text, sizeof(text), "0x%llx",temp_qword);
    snprintf(text, sizeof(text), "0x%" PRIx64, temp_qword);
    return text;
}

char* HexQWordToStr(uint64_t qword) {
    snprintf(text, sizeof(text), "0x%" PRIx64, qword);
    return text;
}

const char* bool2test_status(bool val) {
    const char* name = "undef";
    if(true == val) {
        name = "+";
    }
    if(false == val) {
        name = "fail";
    }
    return name;
}

const char* bool2name(bool val) {
    const char* name = "undef";
    if(true == val) {
        name = "on";
    }
    if(false == val) {
        name = "off";
    }
    return name;
}

const char* DoubleToStr(double value) {
    double value_abs = fabs(value);
    double order_d = log10(value_abs);
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case -15:
    case -14:
    case -13:
        snprintf(text, sizeof(text), "%7.3ff", value * 1000000000000000.0);
        break;

    case -12:
    case -11:
    case -10:
        snprintf(text, sizeof(text), "%7.3fp", value * 1000000000000.0);
        break;

    case -9:
    case -8:
    case -7:
        snprintf(text, sizeof(text), "%7.3fn", value * 1000000000.0);
        break;

    case -6:
    case -5:
    case -4:
        snprintf(text, sizeof(text), "%7.3fu", value * 1000000.0);
        break;

    case -1:
        // snprintf(text, sizeof(text), "%7.2fd", value * 10.0);
        // break;
    case -2:
        // snprintf(text, sizeof(text), "%7.2fc", value * 100.0);
        // break;
    case -3:
        snprintf(text, sizeof(text), "%7.3fm", value * 1000.0);
        break;

    case 0:
    case 1:
    case 2:
        snprintf(text, sizeof(text), "%7.3f", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(text, sizeof(text), "%7.3fk", value / 1000.0);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(text, sizeof(text), "%7.3fM", value / 1000000.0);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(text, sizeof(text), "%7.3fG", value / 1000000000.0);
        break;

    default:
        snprintf(text, sizeof(text), "%7.3f", value);
        break;
    }

    str_del_char_inplace(text, ' ');
    LOG_DEBUG(LINE, "%f->[%s]", value, text);
    return text;
}

const char* uint32ToStr(uint32_t value) {
    double order_d = log10((double)value);
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case 0:
    case 1:
    case 2:
        snprintf(text, sizeof(text), "%u", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(text, sizeof(text), "%uk", value / 1000);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(text, sizeof(text), "%uM", value / 1000000);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(text, sizeof(text), "%uG", value / 1000000000);
        break;

    default:
        snprintf(text, sizeof(text), "%u", value);
        break;
    }

    str_del_char_inplace(text, ' ');
    LOG_DEBUG(LINE, "%u->[%s]", value, text);
    return text;
}

const char* rx_dtoa(double d) {
#ifdef HAS_DOUBLE_TO_STR
    dtoa_(d, -1, text);
#endif
    return text;
}

const char* rx_ftoa(float float_v) {
#ifdef HAS_FLOAT_TO_STR
    ftoa_(float_v, -1, text);
#endif
    return text;
}

const char* utoa64_(uint64_t u64_data, char u64_stringified[], uint8_t u64_base, uint32_t* u64_len) {
    char u64_reverse_str[MAX_INT64_STR_LEN_10 + 1U];
    uint32_t u64_reverse_str_index = 0U;
    uint32_t u64_result_str_index = 0U;
    uint32_t u64_result_str_len = 0U;
    uint64_t u64_symbol_index = 0U;
    uint64_t u64_temp_value = 0U;
    uint64_t u64_d = u64_data;

    do {
        u64_temp_value = u64_d;
        u64_d = u64_d / (uint64_t)u64_base;
        u64_symbol_index = 15U + (u64_temp_value - (u64_d * (uint64_t)u64_base));
        u64_reverse_str[u64_reverse_str_index] = symbols[u64_symbol_index];
        u64_reverse_str_index++;
    } while(u64_d != 0U);

    u64_result_str_len = u64_reverse_str_index;

    if(u64_len != NULL) {
        *u64_len = u64_result_str_len;
    }

    u64_reverse_str[u64_reverse_str_index] = '\0';
    u64_reverse_str_index--;

    for(u64_result_str_index = 0U; u64_result_str_index < u64_result_str_len; u64_result_str_index++) {
        u64_stringified[u64_result_str_index] = u64_reverse_str[u64_reverse_str_index];
        u64_reverse_str_index--;
    }

    u64_stringified[u64_result_str_index] = '\0';

    return u64_stringified;
}

const char* utoa32_(uint32_t u32_data, char u32_stringified[], uint8_t u32_base, uint32_t* u32_len) {
    char u32_reverse_str[MAX_INT32_STR_LEN_10 + 1U];
    uint32_t u32_reverse_str_index = 0U;
    uint32_t u32_result_str_index = 0U;
    uint32_t u32_result_str_len = 0U;
    uint32_t u32_symbol_index = 0U;
    uint32_t u32_temp_value = 0U;
    uint32_t u32_d = u32_data;

    do {
        u32_temp_value = u32_d;
        u32_d = u32_d / (uint32_t)u32_base;
        u32_symbol_index = 15U + (u32_temp_value - (u32_d * (uint32_t)u32_base));
        u32_reverse_str[u32_reverse_str_index] = symbols[u32_symbol_index];
        u32_reverse_str_index++;
    } while(u32_d != 0U);

    u32_result_str_len = u32_reverse_str_index;

    if(u32_len != NULL) {
        *u32_len = u32_result_str_len;
    }

    u32_reverse_str[u32_reverse_str_index] = '\0';
    u32_reverse_str_index--;

    for(u32_result_str_index = 0U; u32_result_str_index < u32_result_str_len; u32_result_str_index++) {
        u32_stringified[u32_result_str_index] = u32_reverse_str[u32_reverse_str_index];
        u32_reverse_str_index--;
    }

    u32_stringified[u32_result_str_index] = '\0';

    return u32_stringified;
}

const char* ltoa64_(int64_t s64_data, char s64_stringified[], uint8_t s64_base, uint32_t* s64_len) {
    char s64_reverse_str[MAX_INT64_STR_LEN_10 + 1U];
    uint32_t s64_reverse_str_index = 0U;
    uint32_t s64_result_str_index = 0U;
    uint32_t s64_result_str_len = 0U;
    int64_t s64_temp_value = 0;
    int64_t s64_symbol_index = 0;
    int64_t s64_d = s64_data;

    do {
        s64_temp_value = s64_d;
        s64_d = s64_d / (int64_t)s64_base;
        s64_symbol_index = 15 + (s64_temp_value - (s64_d * (int64_t)s64_base));
        s64_reverse_str[s64_reverse_str_index] = symbols[s64_symbol_index];
        s64_reverse_str_index++;
    } while(s64_d != 0);

    /* Apply negative sign */
    if(s64_temp_value < 0) {
        s64_reverse_str[s64_reverse_str_index] = '-';
        s64_reverse_str_index++;
    }

    s64_result_str_len = s64_reverse_str_index;

    if(s64_len != NULL) {
        *s64_len = s64_result_str_len;
    }

    s64_reverse_str[s64_reverse_str_index] = '\0';
    s64_reverse_str_index--;

    for(s64_result_str_index = 0U; s64_result_str_index < s64_result_str_len; s64_result_str_index++) {
        s64_stringified[s64_result_str_index] = s64_reverse_str[s64_reverse_str_index];
        s64_reverse_str_index--;
    }

    s64_stringified[s64_result_str_index] = '\0';

    return s64_stringified;
}

const char* ltoa32_(int32_t s32_data, char s32_stringified[], uint8_t s32_base, uint32_t* s32_len) {
    char s32_reverse_str[MAX_INT32_STR_LEN_10 + 1U];
    uint32_t s32_reverse_str_index = 0U;
    uint32_t s32_result_str_index = 0U;
    uint32_t s32_result_str_len = 0U;
    int32_t s32_symbol_index = 0;
    int32_t s32_temp_value = 0;
    int32_t s32_d = s32_data;

    do {
        s32_temp_value = s32_d;
        s32_d = s32_d / (int32_t)s32_base;
        s32_symbol_index = 15 + (s32_temp_value - (s32_d * (int32_t)s32_base));
        s32_reverse_str[s32_reverse_str_index] = symbols[s32_symbol_index];
        s32_reverse_str_index++;
    } while(s32_d != 0);

    /* Apply negative sign */
    if(s32_temp_value < 0) {
        s32_reverse_str[s32_reverse_str_index] = '-';
        s32_reverse_str_index++;
    }

    s32_result_str_len = s32_reverse_str_index;

    if(s32_len != NULL) {
        *s32_len = s32_result_str_len;
    }

    s32_reverse_str[s32_reverse_str_index] = '\0';
    s32_reverse_str_index--;

    for(s32_result_str_index = 0U; s32_result_str_index < s32_result_str_len; s32_result_str_index++) {
        s32_stringified[s32_result_str_index] = s32_reverse_str[s32_reverse_str_index];
        s32_reverse_str_index--;
    }

    s32_stringified[s32_result_str_index] = '\0';

    return s32_stringified;
}

static const unsigned char Nibble2Char[] = "0123456789ABCDEF";
bool array2str(const uint8_t* const buff, uint32_t buff_len, char* const out_array, uint16_t array_size) {
    bool res = false;
    uint32_t i = 0;
    uint32_t j = 0;
    memset(out_array, 0, array_size);
    if((2 * buff_len) <= array_size) {
        res = true;
        for(i = 0; i < buff_len; i++, j += 2) {
            out_array[j] = Nibble2Char[HI_NIBBLE(buff[i])];
            out_array[j + 1] = Nibble2Char[LO_NIBBLE(buff[i])];
        }
    } else {
        LOG_ERROR(LINE, "BuffLen:%u,Byte,ArraySize:%uByte", buff_len, array_size);
    }
    return res;
}

#ifdef HAS_BIN_2_STR
const char* utoa_bin8(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    memset(text, 0, sizeof(text));
    strncpy(text, "0000_0000", sizeof(text));
    while(0 != mask8) {
        if(text[cell8] == '_') {
            cell8++;
        }
        if(0u != (u8_bin_data & mask8)) {
            text[cell8] = '1';
        } else {
            text[cell8] = '0';
        }
        mask8 >>= 1U;
        cell8++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

#endif

#ifdef HAS_BIN_2_STR
const char* utoa_bin8_plain(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(0 != mask8) {
        if(0u != (u8_bin_data & mask8)) {
            text[cell8] = 'X';
        } else {
            text[cell8] = '.';
        }
        mask8 >>= 1U;
        cell8++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

const char* utoa_bin16(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(mask16 != 0U) {
        if(text[cell16] == '_') {
            cell16++;
        }
        if(0u != (u16_bin_data & mask16)) {
            text[cell16] = '1';
        } else {
            text[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

const char* utoa_bin16_plain(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(mask16 != 0U) {
        if(0u != (u16_bin_data & mask16)) {
            text[cell16] = '1';
        } else {
            text[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

const char* utoa_bin24_plain(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = (((uint32_t)1) << 23);
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(mask24 != 0U) {
        if(0u != (u32_bin_data & mask24)) {
            text[cell24] = 'X';
        } else {
            text[cell24] = '.';
        }
        mask24 >>= 1U;
        cell24++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

const char* utoa_bin64(uint64_t u64_bin_data) {
    /*TODO: Implement later*/
    memset(text, 0, SHARED_ARRAY_SIZE);
    return text;
}

const char* utoa_bin24(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = 0x00800000U;
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(mask24 != 0U) {
        if(text[cell24] == '_') {
            cell24++;
        }
        if(0u != (u32_bin_data & mask24)) {
            text[cell24] = '1';
        } else {
            text[cell24] = '0';
        }
        mask24 >>= 1U;
        cell24++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

const char* utoa_bin32(uint32_t u32_bin_data) {
    uint8_t cell32 = 0u;
    uint32_t mask32 = 0x80000000U;
    memset(text, 0, SHARED_ARRAY_SIZE);
    while(mask32 != 0U) {
        if(text[cell32] == '_') {
            cell32++;
        }
        if(0u != (u32_bin_data & mask32)) {
            text[cell32] = '1';
        } else {
            text[cell32] = '0';
        }
        mask32 >>= 1U;
        cell32++;
    }
    text[sizeof(text) - 1u] = '\0';
    return text;
}

#endif

const char* rx_ltoa32(int32_t ltoa32_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return ltoa32_(ltoa32_data, text, 10U, NULL);
}

const char* rx_ltoa64(int64_t ltoa64_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return ltoa64_(ltoa64_data, text, 10U, NULL);
}

const char* rx_utoa32(uint32_t utoa32_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return utoa32_(utoa32_data, text, 10U, NULL);
}

const char* rx_utoa64(uint64_t utoa64_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return utoa64_(utoa64_data, text, 10U, NULL);
}

const char* utoa_hex32(uint32_t u32_hex_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return utoa32_(u32_hex_data, text, 16U, NULL);
}

const char* utoa_hex64(uint64_t u64_hex_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return utoa64_(u64_hex_data, text, 16U, NULL);
}

const char* ltoa_hex32(int32_t s32_hex_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return ltoa32_(s32_hex_data, text, 16U, NULL);
}

const char* ltoa_hex64(int64_t s64_hex_data) {
    memset(text, 0, SHARED_ARRAY_SIZE);
    return ltoa64_(s64_hex_data, text, 16U, NULL);
}
