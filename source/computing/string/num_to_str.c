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
    static char name[30] = "";
    snprintf(name, sizeof(name), "0x%08x", (unsigned int)qword);
    return name;
}

char* HexQWordRevToStr(uint64_t qword) {
    static char name[40] = "";
    uint64_t temp_qword = reverse_byte_order_uint64(qword);
    // snprintf(name, sizeof(name), "0x%llx",temp_qword);
    snprintf(name, sizeof(name), "0x%" PRIx64, temp_qword);
    return name;
}

char* HexQWordToStr(uint64_t qword) {
    static char name[40] = "";
    snprintf(name, sizeof(name), "0x%" PRIx64, qword);
    return name;
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
    static char name[100] = {0};
    double value_abs = fabs(value);
    double order_d = log10(value_abs);
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case -15:
    case -14:
    case -13:
        snprintf(name, sizeof(name), "%7.2ff", value * 1000000000000000.0);
        break;

    case -12:
    case -11:
    case -10:
        snprintf(name, sizeof(name), "%7.2fp", value * 1000000000000.0);
        break;

    case -9:
    case -8:
    case -7:
        snprintf(name, sizeof(name), "%7.2fn", value * 1000000000.0);
        break;

    case -6:
    case -5:
    case -4:
        snprintf(name, sizeof(name), "%7.2fu", value * 1000000.0);
        break;

    case -3:
        snprintf(name, sizeof(name), "%7.2fm", value * 1000.0);
        break;

    case -2:
        snprintf(name, sizeof(name), "%7.2fc", value * 100.0);
        break;

    case -1:
        snprintf(name, sizeof(name), "%7.2fd", value * 10.0);
        break;

    case 0:
    case 1:
    case 2:
        snprintf(name, sizeof(name), "%7.2f", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(name, sizeof(name), "%7.2fk", value / 1000.0);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(name, sizeof(name), "%7.2fM", value / 1000000.0);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(name, sizeof(name), "%7.2fG", value / 1000000000.0);
        break;

    default:
        snprintf(name, sizeof(name), "%7.2f", value);
        break;
    }

    str_del_char_inplace(name, ' ');
    LOG_DEBUG(LINE, "%f->[%s]", value, name);
    return name;
}

const char* uint32ToStr(uint32_t value) {
    static char name[100] = {0};
    double order_d = log10((double)value);
    int32_t order_i = (int32_t)order_d;
    switch(order_i) {

    case 0:
    case 1:
    case 2:
        snprintf(name, sizeof(name), "%u", value);
        break;

    case 3:
    case 4:
    case 5:
        snprintf(name, sizeof(name), "%uk", value / 1000);
        break;

    case 6:
    case 7:
    case 8:
        snprintf(name, sizeof(name), "%uM", value / 1000000);
        break;

    case 9:
    case 10:
    case 11:
        snprintf(name, sizeof(name), "%uG", value / 1000000000);
        break;

    default:
        snprintf(name, sizeof(name), "%u", value);
        break;
    }

    str_del_char_inplace(name, ' ');
    LOG_DEBUG(LINE, "%u->[%s]", value, name);
    return name;
}

const char* rx_dtoa(double d) {
    static char dtoa_str[(((MAX_INT64_STR_LEN_10 + MAX_PRECISION) + 1U) + 1U)] = {0};
#ifdef HAS_DOUBLE_TO_STR
    dtoa_(d, -1, dtoa_str);
#endif
    return dtoa_str;
}

const char* rx_ftoa(float float_v) {
    static char ftoa_str[(((MAX_INT64_STR_LEN_10 + MAX_PRECISION) + 1U) + 1U)] = {0};
#ifdef HAS_FLOAT_TO_STR
    ftoa_(float_v, -1, ftoa_str);
#endif
    return ftoa_str;
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
        LOG_ERROR(LINE, "BuffLen:%u Byte,ArraySize:%u Byte", buff_len, array_size);
    }
    return res;
}

#ifdef HAS_BIN_2_STR
const char* utoa_bin8(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    static char outBitStr8[11U] = "";
    memset(outBitStr8, 0, sizeof(outBitStr8));
    strncpy(outBitStr8, "0000_0000", sizeof(outBitStr8));
    while(0 != mask8) {
        if(outBitStr8[cell8] == '_') {
            cell8++;
        }
        if(0u != (u8_bin_data & mask8)) {
            outBitStr8[cell8] = '1';
        } else {
            outBitStr8[cell8] = '0';
        }
        mask8 >>= 1U;
        cell8++;
    }
    outBitStr8[sizeof(outBitStr8) - 1u] = '\0';
    return outBitStr8;
}

#endif

#ifdef HAS_BIN_2_STR
const char* utoa_bin8_plain(uint8_t u8_bin_data) {
    uint8_t cell8 = 0u;
    uint8_t mask8 = 0x80U;
    static char outBitStr8[11U] = "";
    memset(outBitStr8, 0, sizeof(outBitStr8));
    strncpy(outBitStr8, "00000000", sizeof(outBitStr8));
    while(0 != mask8) {
        if(0u != (u8_bin_data & mask8)) {
            outBitStr8[cell8] = 'X';
        } else {
            outBitStr8[cell8] = '.';
        }
        mask8 >>= 1U;
        cell8++;
    }
    outBitStr8[sizeof(outBitStr8) - 1u] = '\0';
    return outBitStr8;
}

const char* utoa_bin16(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    static char outBitStr16[20U] = "0000_0000_0000_0000";
    while(mask16 != 0U) {
        if(outBitStr16[cell16] == '_') {
            cell16++;
        }
        if(0u != (u16_bin_data & mask16)) {
            outBitStr16[cell16] = '1';
        } else {
            outBitStr16[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    outBitStr16[sizeof(outBitStr16) - 1u] = '\0';
    return outBitStr16;
}

const char* utoa_bin16_plain(uint16_t u16_bin_data) {
    uint8_t cell16 = 0u;
    uint16_t mask16 = 0x8000U;
    static char outBitStr16[20U] = "0000000000000000";
    while(mask16 != 0U) {
        if(0u != (u16_bin_data & mask16)) {
            outBitStr16[cell16] = '1';
        } else {
            outBitStr16[cell16] = '0';
        }
        mask16 >>= 1U;
        cell16++;
    }
    outBitStr16[sizeof(outBitStr16) - 1u] = '\0';
    return outBitStr16;
}

const char* utoa_bin24_plain(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = (((uint32_t)1) << 23);
    static char outBitStr24[25U] = "000000000000000000000000";
    while(mask24 != 0U) {
        if(0u != (u32_bin_data & mask24)) {
            outBitStr24[cell24] = 'X';
        } else {
            outBitStr24[cell24] = '.';
        }
        mask24 >>= 1U;
        cell24++;
    }
    outBitStr24[sizeof(outBitStr24) - 1u] = '\0';
    return outBitStr24;
}

const char* utoa_bin64(uint64_t u64_bin_data) {
    static char outBitStr16[] = "none";
    /*TODO: Implement later*/
    return outBitStr16;
}

const char* utoa_bin24(uint32_t u32_bin_data) {
    uint8_t cell24 = 0u;
    uint32_t mask24 = 0x00800000U;
    static char outBitStr24[sizeof("0000_0000_0000_0000_0000_0000") + 1U] = "0000_0000_0000_0000_0000_0000";
    while(mask24 != 0U) {
        if(outBitStr24[cell24] == '_') {
            cell24++;
        }
        if(0u != (u32_bin_data & mask24)) {
            outBitStr24[cell24] = '1';
        } else {
            outBitStr24[cell24] = '0';
        }
        mask24 >>= 1U;
        cell24++;
    }
    outBitStr24[sizeof(outBitStr24) - 1u] = '\0';
    return outBitStr24;
}

bool PrintReg32(uint32_t value) {
    int32_t b = 0;
    bool res = true;
    static const table_col_t cols[32] = {
        {3, "31"}, {3, "30"}, {3, "29"}, {3, "28"}, {3, "27"}, {3, "26"}, {3, "25"}, {3, "24"},
        {3, "23"}, {3, "22"}, {3, "21"}, {3, "20"}, {3, "19"}, {3, "18"}, {3, "17"}, {3, "16"},
        {3, "15"}, {3, "14"}, {3, "13"}, {3, "12"}, {3, "11"}, {3, "10"}, {3, "9"},  {3, "8"},
        {3, "7"},  {3, "6"},  {3, "5"},  {3, "4"},  {3, "3"},  {3, "2"},  {3, "1"},  {3, "0"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(TSEP);
    for(b = 31; 0 <= b; b--) {
        cli_printf(" %1u " TSEP, CHECK_BIT_NUM(value, b));
    }
    cli_printf(CRLF);
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cli_printf(" %s ", CRLF);
    return res;
}

const char* utoa_bin32(uint32_t u32_bin_data) {
    uint8_t cell32 = 0u;
    uint32_t mask32 = 0x80000000U;
    static char outBitStr32[sizeof("0000_0000_0000_0000_0000_0000_0000_0000") + 1U] =
        "0000_0000_0000_0000_0000_0000_0000_0000";
    while(mask32 != 0U) {
        if(outBitStr32[cell32] == '_') {
            cell32++;
        }
        if(0u != (u32_bin_data & mask32)) {
            outBitStr32[cell32] = '1';
        } else {
            outBitStr32[cell32] = '0';
        }
        mask32 >>= 1U;
        cell32++;
    }
    outBitStr32[sizeof(outBitStr32) - 1u] = '\0';
    return outBitStr32;
}

#endif

const char* rx_ltoa32(int32_t ltoa32_data) {
    static char ltoa32_str[(MAX_INT32_STR_LEN_10 + 1U)];
    return ltoa32_(ltoa32_data, ltoa32_str, 10U, NULL);
}

const char* rx_ltoa64(int64_t ltoa64_data) {
    static char ltoa64_str[(MAX_INT64_STR_LEN_10 + 1U)];
    return ltoa64_(ltoa64_data, ltoa64_str, 10U, NULL);
}

const char* rx_utoa32(uint32_t utoa32_data) {
    static char utoa32_str[(MAX_INT32_STR_LEN_10 + 1U)];
    return utoa32_(utoa32_data, utoa32_str, 10U, NULL);
}

const char* rx_utoa64(uint64_t utoa64_data) {
    static char utoa64_str[(MAX_INT64_STR_LEN_10 + 1U)];
    return utoa64_(utoa64_data, utoa64_str, 10U, NULL);
}

const char* utoa_hex32(uint32_t u32_hex_data) {
    static char utoa_hex32_str[(MAX_INT32_STR_LEN_16 + 1U)];
    return utoa32_(u32_hex_data, utoa_hex32_str, 16U, NULL);
}

const char* utoa_hex64(uint64_t u64_hex_data) {
    static char utoa_hex64_str[(MAX_INT64_STR_LEN_16 + 1U)];
    return utoa64_(u64_hex_data, utoa_hex64_str, 16U, NULL);
}

const char* ltoa_hex32(int32_t s32_hex_data) {
    static char ltoa_hex32_str[(MAX_INT32_STR_LEN_16 + 1U)];
    return ltoa32_(s32_hex_data, ltoa_hex32_str, 16U, NULL);
}

const char* ltoa_hex64(int64_t s64_hex_data) {
    static char ltoa_hex64_str[(MAX_INT64_STR_LEN_16 + 1U)];
    return ltoa64_(s64_hex_data, ltoa_hex64_str, 16U, NULL);
}
