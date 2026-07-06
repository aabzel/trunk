#include "num_to_str.h"

#include <inttypes.h>
#include <math.h>
#include <stddef.h>
#include <stdio.h>

#include "byte_utils.h"
#include "convert.h"
#include "log.h"
#include "str_utils.h"

static char lText[200] = {0};

static const char symbols[] = "FEDCBA9876543210123456789ABCDEF";

char* HexQWord2Str(uint32_t qword) {
    snprintf(lText, sizeof(lText), "0x%08x", (unsigned int)qword);
    return lText;
}

char* HexQWordRevToStr(uint64_t qword) {
    uint64_t temp_qword = reverse_byte_order_uint64(qword);
    // snprintf(lText, sizeof(lText), "0x%llx",temp_qword);
    snprintf(lText, sizeof(lText), "0x%llx", temp_qword);
    return lText;
}

char* HexQWordToStr(uint64_t qword) {
    snprintf(lText, sizeof(lText), "0x%llx", qword);
    return lText;
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
        snprintf(lText, sizeof(lText), "%7.3ff", value * 1000000000000000.0);
        break;

    case -12:
    case -11:
    case -10:
        snprintf(lText, sizeof(lText), "%7.3fp", value * 1000000000000.0);
        break;

    case -9:
    case -8:
    case -7:
        snprintf(lText, sizeof(lText), "%7.3fn", value * 1000000000.0);
        break;

    case -6:
    case -5:
    case -4:
        snprintf(lText, sizeof(lText), "%7.3fu", value * 1000000.0);
        break;

    case -1:
        // snprintf(lText, sizeof(lText), "%7.2fd", value * 10.0);
        // break;
    case -2:
        // snprintf(lText, sizeof(lText), "%7.2fc", value * 100.0);
        // break;
    case -3:
        snprintf(lText, sizeof(lText), "%7.3fm", value * 1000.0);
        break;

    case 0:
    case 1:
    case 2:
        snprintf(lText, sizeof(lText), "%7.3f", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(lText, sizeof(lText), "%7.3fk", value / 1000.0);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(lText, sizeof(lText), "%7.3fM", value / 1000000.0);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(lText, sizeof(lText), "%7.3fG", value / 1000000000.0);
        break;

    default:
        snprintf(lText, sizeof(lText), "%7.3f", value);
        break;
    }

    str_del_char_inplace(lText, ' ');
    LOG_DEBUG(STR_LG, "%f->[%s]", value, lText);
    return lText;
}

const char* uint32ToStr(uint32_t value) {
    double order_d = log10((double)value);
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case 0:
    case 1:
    case 2:
        snprintf(lText, sizeof(lText), "%u", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(lText, sizeof(lText), "%uk", value / 1000);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(lText, sizeof(lText), "%uM", value / 1000000);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(lText, sizeof(lText), "%uG", value / 1000000000);
        break;

    default:
        snprintf(lText, sizeof(lText), "%u", value);
        break;
    }

    str_del_char_inplace(lText, ' ');
    LOG_DEBUG(STR_LG, "%u->[%s]", value, lText);
    return lText;
}

const char* rx_dtoa(double d) {
#ifdef HAS_DOUBLE_TO_STR
    dtoa_(d, -1, lText);
#endif
    return lText;
}

const char* rx_ftoa(float float_v) {
#ifdef HAS_FLOAT_TO_STR
    ftoa_(float_v, -1, lText);
#endif
    return lText;
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
    if(buff) {
        if(out_array) {
            uint32_t i = 0;
            uint32_t j = 0;
            memset(out_array, 0, array_size);
            if((2 * buff_len) <= array_size) {
            } else {
                array_size = 2 * buff_len;
                LOG_DEBUG(STR_LG, "OutSizeTooSmall,Text:[%s],BuffLen:%u,Byte,ArraySize:%uByte", buff, buff_len,
                          array_size);
            }

            res = true;
            for(i = 0; i < buff_len; i++, j += 2) {
                out_array[j] = Nibble2Char[HI_NIBBLE(buff[i])];
                out_array[j + 1] = Nibble2Char[LO_NIBBLE(buff[i])];
            }
        }
    }
    return res;
}

#ifdef HAS_BIN_2_STR
const char* utoa_bin8(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    memset(lText, 0, sizeof(lText));
    strncpy(lText, "0000_0000", sizeof(lText));
    while(0 != mask8) {
        if(lText[cell8] == '_') {
            cell8++;
        }
        if(0u != (u8_bin_data & mask8)) {
            lText[cell8] = '1';
        } else {
            lText[cell8] = '0';
        }
        mask8 >>= 1U;
        cell8++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

#endif

#ifdef HAS_BIN_2_STR
const char* utoa_bin8_plain(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    memset(lText, 0, sizeof(lText));
    while(0 != mask8) {
        if(0u != (u8_bin_data & mask8)) {
            lText[cell8] = '1';
        } else {
            lText[cell8] = '0';
        }
        mask8 >>= 1U;
        cell8++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

const char* utoa_bin16(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    memset(lText, 0, sizeof(lText));
    strncpy(lText, "0000_0000_0000_0000", sizeof(lText));
    while(mask16 != 0U) {
        if(lText[cell16] == '_') {
            cell16++;
        }
        if(0u != (u16_bin_data & mask16)) {
            lText[cell16] = '1';
        } else {
            lText[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

const char* utoa_bin16_plain(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    memset(lText, 0, sizeof(lText));
    while(mask16 != 0U) {
        if(0u != (u16_bin_data & mask16)) {
            lText[cell16] = '1';
        } else {
            lText[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

const char* utoa_bin24_plain(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = (((uint32_t)1) << 23);
    memset(lText, 0, sizeof(lText));
    while(mask24 != 0U) {
        if(0u != (u32_bin_data & mask24)) {
            lText[cell24] = 'X';
        } else {
            lText[cell24] = '.';
        }
        mask24 >>= 1U;
        cell24++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

const char* utoa_bin64(uint64_t u64_bin_data) {
    /*TODO: Implement later*/
    memset(lText, 0, sizeof(lText));
    return lText;
}

const char* utoa_bin24(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = 0x00800000U;
    memset(lText, 0, sizeof(lText));
    strcpy(lText, "0000_0000_0000_0000_0000_0000");
    while(mask24 != 0U) {
        if(lText[cell24] == '_') {
            cell24++;
        }
        if(0u != (u32_bin_data & mask24)) {
            lText[cell24] = '1';
        } else {
            lText[cell24] = '0';
        }
        mask24 >>= 1U;
        cell24++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

const char* utoa_bin(const uint32_t u32_bin_data) {
    static char buffer[42]; //
    char* ptr = buffer;
    uint32_t data = u32_bin_data;
    int32_t msb = -1; //
    int32_t i;

    // Find the most significant bit (from 31 to 0)
    for(i = 31; i >= 0; i--) {
        if((data >> i) & 1) {
            msb = i;
            break;
        }
    }

    if(msb == -1) {
        buffer[0] = '0';
        buffer[1] = '\0';
    } else {
        for(i = msb; i >= 0; i--) {
            // Insert a separator before the bit that is on the group boundary
            // (position i is a multiple of 4, counting from the least significant bit), but not before
            // the very first bit
            if(i % 4 == 3 && i != msb) {
                *ptr++ = '_';
            }
            *ptr++ = ((data >> i) & 1) ? '1' : '0';
        }
        *ptr = '\0';
    }

    return buffer;
}

const char* utoa_bin32(uint32_t u32_bin_data) {
    uint8_t cell32 = 0u;
    uint32_t mask32 = 0x80000000U;
    memset(lText, 0, sizeof(lText));
    strcpy(lText, "0000_0000|0000_0000|0000_0000|0000_0000");
    while(mask32 != 0U) {
        if((lText[cell32] == '_') || (lText[cell32] == '|')) {
            cell32++;
        }
        if(0u != (u32_bin_data & mask32)) {
            lText[cell32] = '1';
        } else {
            lText[cell32] = '0';
        }
        mask32 >>= 1U;
        cell32++;
    }
    lText[sizeof(lText) - 1u] = '\0';
    return lText;
}

#endif

const char* rx_ltoa32(int32_t ltoa32_data) {
    memset(lText, 0, sizeof(lText));
    return ltoa32_(ltoa32_data, lText, 10U, NULL);
}

const char* rx_ltoa64(int64_t ltoa64_data) {
    memset(lText, 0, sizeof(lText));
    return ltoa64_(ltoa64_data, lText, 10U, NULL);
}

const char* rx_utoa32(uint32_t utoa32_data) {
    memset(lText, 0, sizeof(lText));
    return utoa32_(utoa32_data, lText, 10U, NULL);
}

const char* rx_utoa64(uint64_t utoa64_data) {
    memset(lText, 0, sizeof(lText));
    return utoa64_(utoa64_data, lText, 10U, NULL);
}

const char* utoa_hex32(uint32_t u32_hex_data) {
    memset(lText, 0, sizeof(lText));
    return utoa32_(u32_hex_data, lText, 16U, NULL);
}

const char* utoa_hex64(uint64_t u64_hex_data) {
    memset(lText, 0, sizeof(lText));
    return utoa64_(u64_hex_data, lText, 16U, NULL);
}

const char* ltoa_hex32(int32_t s32_hex_data) {
    memset(lText, 0, sizeof(lText));
    return ltoa32_(s32_hex_data, lText, 16U, NULL);
}

const char* ltoa_hex64(int64_t s64_hex_data) {
    memset(lText, 0, sizeof(lText));
    return ltoa64_(s64_hex_data, lText, 16U, NULL);
}
