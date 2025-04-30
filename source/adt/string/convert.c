#include "convert.h"

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_CONVERT_DEBUG
#include <stdio.h>
#endif

//#include "byte_utils.h"
#include "convert_diag.h"
#include "convert_types.h"
#include "log.h"
#include "storage_diag.h"

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

#ifndef MAX_INT64_STR_LEN_16
#define MAX_INT64_STR_LEN_16 (sizeof(uint64_t) * 2U)
#endif

static bool try_dec_char_to_u8(uint8_t dec_char, uint8_t* dec_char_to_u8_value);
static bool is_signed(const char first_str_char, int32_t* first_digit_index);
static bool get_str_len(const char char_str[], int32_t* str_len);
// static bool proc_strtod(const char str[], const char** endptr, double* result);
static bool is_true(const char* true_str_to_check);
static bool is_false(const char* false_str_to_check);
// static void dtoa_normal(double double_data, int32_t double_precision, char double_stringified[]);
// static void ftoa_normal(float float_data, int32_t float_precision, char float_stringified[]);

#ifdef HAS_STR2_FLOAT
static const float rounders[(MAX_PRECISION + 1U)] = {
    0.5f,          /* 0 */
    0.05f,         /* 1 */
    0.005f,        /* 2 */
    0.0005f,       /* 3 */
    0.00005f,      /* 4 */
    0.000005f,     /* 5 */
    0.0000005f,    /* 6 */
    0.00000005f,   /* 7 */
    0.000000005f,  /* 8 */
    0.0000000005f, /* 9 */
    0.00000000005f /* 10 */
};
#endif

/* STRING TO 64 BIT
 * ****************************************************************************
 */

bool try_str2uint64(const char u64_str[], uint64_t* u64_value) {
    bool res = false;
    if(NULL != u64_str) {
        if(NULL != u64_value) {
            int32_t u64_str_len = (int32_t)strlen(u64_str);
            res = try_strl2uint64(u64_str, u64_str_len, u64_value);
        }
    }
    return res;
}

bool try_str2int64(const char s64_str[], int64_t* s64_value) {
    bool res = false;
    if(NULL != s64_str) {
        if(NULL != s64_value) {
            int32_t s64_str_len = (int32_t)strlen(s64_str);
            res = try_strl2int64(s64_str, s64_str_len, s64_value);
        }
    }
    return res;
}

bool is_hex_str(const char str_to_check[], int32_t str_to_check_len, uint8_t* const out_shift) {
    bool is_hex_str_result = false;
    int32_t validHexCnt = 0;
    uint8_t out_shift_loc = 0U;
    if(str_to_check && out_shift) {
        bool is_dec_str_res = is_dec_str(str_to_check, str_to_check_len);
        if(false == is_dec_str_res) {
            bool len_check_passed = (str_to_check_len > 2);
            if(len_check_passed) {
                if(((char)'0' == str_to_check[0]) &&
                   (((char)'x' == str_to_check[1]) || ((char)'X' == str_to_check[1]))) {
                    out_shift_loc = 2U;
                } else {
                    out_shift_loc = 0U;
                }

                int32_t i = 0;
                for(i = ((int32_t)out_shift_loc); i < str_to_check_len; i++) {
                    if(is_hex_digit(str_to_check[i])) {
                        validHexCnt++;
                    } else {
                        LOG_DEBUG(LINE, "NotHexCh[%u]=[%c]Err ", i, str_to_check[i]);
                        break;
                    }
                }
                if((str_to_check_len - ((int32_t)out_shift_loc)) == validHexCnt) {
                    (*out_shift) = out_shift_loc;
                    is_hex_str_result = true;
                }
            }
        } else {
            is_hex_str_result = true;
        }
    }
    return is_hex_str_result;
}

bool try_strl2uint64(const char u64l_str[], int32_t u64l_str_len, uint64_t* u64l_value) {
    bool u64l_success = true;
    bool u64l_str_not_empty = true;
    int32_t u64l_len = u64l_str_len;
    if(NULL != u64l_str) {
        if(NULL != u64l_value) {
            *u64l_value = 0U;
            u64l_str_not_empty = get_str_len(u64l_str, &u64l_len);
            if(u64l_str_not_empty == false) {
                u64l_success = false;
            }

            if(u64l_success) {
                uint8_t num_shift = 0U;
                bool res = is_dec_str(u64l_str, u64l_len);
                if(res) {
                    u64l_success = try_strl2uint64_dec(u64l_str, u64l_len, u64l_value);
                } else {
                    res = is_hex_str(u64l_str, u64l_len, &num_shift);
                    if(res) {
                        u64l_success =
                            try_strl2uint64_hex(&u64l_str[num_shift], u64l_len - ((int32_t)num_shift), u64l_value);
                    } else {
                        LOG_ERROR(LINE, "UndefFormat[%s]", u64l_str);
                        u64l_success = false;
                    }
                }
            }
        }
    } else {
        u64l_success = false;
    }

    return u64l_success;
}

bool try_strl2int64(const char s64l_str[], int32_t s64l_str_len, int64_t* s64l_value) {
    bool s64l_success = true;
    bool s64l_str_not_empty = true;
    int32_t s64l_len = s64l_str_len;
    if(NULL != s64l_str) {
        if(NULL != s64l_value) {
            *s64l_value = 0;
            s64l_str_not_empty = get_str_len(s64l_str, &s64l_len);
            if(s64l_str_not_empty == false) {
                s64l_success = false;
            }

            if(s64l_success) {
                uint8_t num_shift = 0U;
                bool res = is_dec_str(s64l_str, s64l_len);
                if(res) {
                    s64l_success = try_strl2int64_dec(s64l_str, s64l_len, s64l_value);
                } else {
                    res = is_hex_str(s64l_str, s64l_len, &num_shift);
                    if(res) {
                        s64l_success =
                            try_strl2int64_hex(&s64l_str[num_shift], s64l_len - ((int32_t)num_shift), s64l_value);
                    } else {
                        s64l_success = false;
                    }
                }
            }
        } else {
            s64l_success = false;
        }
    } else {
        s64l_success = false;
    }

    return s64l_success;
}

bool try_strl2uint64_hex(const char u64_hex_str[], int32_t u64_hex_str_len, uint64_t* u64_hex_value) {
    bool u64_hex_success = true;
    bool u64_str_not_empty = true;
    uint64_t u64_hex_result = 0U;
    int32_t u64_hex_str_index;
    int32_t u64_hex_len = u64_hex_str_len;
    if((NULL != u64_hex_str) && (NULL != u64_hex_value)) {
        u64_str_not_empty = get_str_len(u64_hex_str, &u64_hex_len);
        if(u64_str_not_empty == false) {
            u64_hex_success = false;
        }

        if(u64_hex_len > (int32_t)MAX_INT64_STR_LEN_16) {
            u64_hex_success = false;
        }

        if(u64_hex_success) {
            for(u64_hex_str_index = 0; u64_hex_str_index < u64_hex_len; u64_hex_str_index++) {
                uint8_t u64_hex_str_char = (uint8_t)u64_hex_str[u64_hex_str_index];
                uint8_t u64_hex_str_number = 0U;

                if(try_hex_char_to_u8(u64_hex_str_char, &u64_hex_str_number)) {
                    u64_hex_result = (u64_hex_result * 16U) + u64_hex_str_number;
                } else {
                    u64_hex_success = false;
                    u64_hex_result = 0U;
                    break;
                }
            }
        }

        *u64_hex_value = u64_hex_result;
    } else {
        u64_hex_success = false;
    }
    return u64_hex_success;
}

bool try_strl2int64_hex(const char s64_hex_str[], int32_t s64_hex_str_len, int64_t* s64_hex_value) {
    bool s64_hex_success = true;
    bool s64_str_not_empty = true;
    int64_t s64_hex_result = 0;
    int32_t s64_hex_str_index;
    int32_t s64_hex_len = s64_hex_str_len;
    if((NULL != s64_hex_str) && (NULL != s64_hex_value)) {
        s64_str_not_empty = get_str_len(s64_hex_str, &s64_hex_len);
        if(s64_str_not_empty == false) {
            s64_hex_success = false;
        }

        if(s64_hex_len > (int32_t)MAX_INT64_STR_LEN_16) {
            s64_hex_success = false;
        }

        if(s64_hex_success) {
            for(s64_hex_str_index = 0; s64_hex_str_index < s64_hex_len; s64_hex_str_index++) {
                uint8_t s64_hex_str_char = (uint8_t)s64_hex_str[s64_hex_str_index];
                uint8_t s64_hex_str_number = 0U;
                s64_hex_success = try_hex_char_to_u8(s64_hex_str_char, &s64_hex_str_number);

                if(s64_hex_success) {
                    s64_hex_result = (s64_hex_result * 16) + (int64_t)s64_hex_str_number;
                    if(s64_hex_result > (INT64_MAX / 16)) {
                        s64_hex_success = false;
                    }
                }

                if(s64_hex_success == false) {
                    s64_hex_result = 0;
                    break;
                }
            }
        }

        *s64_hex_value = s64_hex_result;
    } else {
        s64_hex_success = false;
    }
    return s64_hex_success;
}

bool try_strl2uint64_dec(const char u64_dec_str[], int32_t u64_dec_str_len, uint64_t* u64_dec_value) {
    bool u64l_dec_success = true;
    uint64_t u64l_dec_result = 0U;
    int32_t u64l_dec_str_index = 0;

    if(is_signed(u64_dec_str[0], &u64l_dec_str_index)) {
        u64l_dec_success = false;
    } else {
        for(; u64l_dec_str_index < u64_dec_str_len; u64l_dec_str_index++) {
            uint8_t u64l_dec_str_char = (uint8_t)u64_dec_str[u64l_dec_str_index];
            uint8_t u64l_dec_str_number = 0U;
            uint64_t u64l_dec_temp_value = 0U;

            u64l_dec_success = try_dec_char_to_u8(u64l_dec_str_char, &u64l_dec_str_number);
            if(u64l_dec_success) {
                u64l_dec_temp_value = (u64l_dec_result * 10U) + u64l_dec_str_number;
                if(u64l_dec_temp_value < u64l_dec_result) {
                    u64l_dec_success = false;
                }
            }
            if(false == u64l_dec_success) {
                u64l_dec_result = 0U;
                break;
            }
            u64l_dec_result = u64l_dec_temp_value;
        }
    }

    *u64_dec_value = u64l_dec_result;
    return u64l_dec_success;
}

bool try_strl2int64_dec(const char s64_dec_str[], int32_t s64_dec_str_len, int64_t* s64_dec_value) {
    bool s64l_dec_success = true;
    bool s64l_dec_signed = false;
    int64_t s64l_dec_result = 0;
    int32_t s64l_dec_str_index = 0;
    if((NULL != s64_dec_str) && (NULL != s64_dec_value)) {
        s64l_dec_signed = is_signed(s64_dec_str[0], &s64l_dec_str_index);
        if((s64l_dec_signed) && (s64_dec_str_len < 2)) {
            s64l_dec_success = false;
        }

        if(s64l_dec_success) {
            for(; s64l_dec_str_index < s64_dec_str_len; s64l_dec_str_index++) {
                uint8_t s64_dec_str_char = (uint8_t)s64_dec_str[s64l_dec_str_index];
                uint8_t s64_dec_str_number = 0U;
                int64_t s64_dec_temp_value = 0;

                s64l_dec_success = try_dec_char_to_u8(s64_dec_str_char, &s64_dec_str_number);
                if(s64l_dec_success) {
                    s64_dec_temp_value = (s64l_dec_result * 10) + (int64_t)s64_dec_str_number;
                    if(s64_dec_temp_value < s64l_dec_result) {
                        s64l_dec_success = false;
                    }
                }

                if(s64l_dec_success == false) {
                    s64l_dec_result = 0;
                    break;
                }

                s64l_dec_result = s64_dec_temp_value;
            }
        }

        if(s64l_dec_signed) {
            *s64_dec_value = -s64l_dec_result;
        } else {
            *s64_dec_value = s64l_dec_result;
        }
    } else {
        s64l_dec_success = false;
    }
    return s64l_dec_success;
}

/* STRING TO 32 BIT
 */
bool try_str2uint32(const char u32_str[], uint32_t* u32_value) {
    bool res = false;
    if(u32_str) {
        if(u32_value) {
            int32_t u32_str_len = (int32_t)strlen(u32_str);
            res = try_strl2uint32(u32_str, u32_str_len, u32_value);
        }
    }
    return res;
}

bool try_str2int32(const char s32_str[], int32_t* s32_value) {
    bool res = false;
    if((NULL != s32_str) && (NULL != s32_value)) {
        int32_t s32_str_len = (int32_t)strlen(s32_str);
        res = try_strl2int32(s32_str, s32_str_len, s32_value);
    }
    return res;
}

bool try_strl2uint32(const char u32l_str[], int32_t u32l_str_len, uint32_t* u32l_value) {
    bool u32l_success = true;
    LOG_DEBUG(LINE, "strl2uint32 [%s] Len:%u", u32l_str, u32l_str_len);
    bool u32l_str_not_empty = true;
    int32_t u32l_len = u32l_str_len;
    if((NULL != u32l_str) && (NULL != u32l_value)) {
        (*u32l_value) = 0U;
        u32l_str_not_empty = get_str_len(u32l_str, &u32l_len);
        if(u32l_str_not_empty == false) {
            u32l_success = false;
        } else {
            uint8_t num_shift = 0U;
            u32l_success = false;
            if(is_dec_str(u32l_str, u32l_len)) {
                u32l_success = try_strl2uint32_dec(u32l_str, u32l_len, u32l_value);
            } else {
                if(is_hex_str(u32l_str, u32l_len, &num_shift)) {
                    u32l_success =
                        try_strl2uint32_hex(&u32l_str[num_shift], u32l_len - ((int32_t)num_shift), u32l_value);
                }
            }
        }
    } else {
        u32l_success = false;
    }
    return u32l_success;
}

static bool skip_prefix_spaces(const char str[], uint32_t len, uint32_t* start_index) {
    bool res = false;
    if(str && (0 < len) && start_index) {
        uint32_t shift = 0;
        while((' ' == str[0]) && (shift < len)) {
            shift++;
            str++;
        }
        *start_index = shift;
        res = true;
    }
    return res;
}

#ifdef HAS_STR2_MONTH
bool try_strl2month(const char str[], int32_t* mon_value) {
    bool res = true;
    if(strstr(str, "Dec")) {
        *mon_value = 11;
    } else if(strstr(str, "Jan")) {
        *mon_value = 0;
    } else if(strstr(str, "Feb")) {
        *mon_value = 1;
    } else if(strstr(str, "Mar")) {
        *mon_value = 2;
    } else if(strstr(str, "Apr")) {
        *mon_value = 3;
    } else if(strstr(str, "May")) {
        *mon_value = 4;
    } else if(strstr(str, "Jun")) {
        *mon_value = 5;
    } else if(strstr(str, "Jul")) {
        *mon_value = 6;
    } else if(strstr(str, "Aug")) {
        *mon_value = 7;
    } else if(strstr(str, "Sep")) {
        *mon_value = 8;
    } else if(strstr(str, "Oct")) {
        *mon_value = 9;
    } else if(strstr(str, "Nov")) {
        *mon_value = 10;
    } else {
        res = false;
    }
    return res;
}
#endif

bool try_strl2int32(const char s32l_str[], int32_t s32l_str_len, int32_t* s32l_value) {
    LOG_DEBUG(LINE, "%s() index %u len %u status %u", __FUNCTION__, s32l_str, s32l_str_len);
    bool s32l_success = true;
    bool s32l_str_not_empty = true;
    int32_t s32l_len = s32l_str_len;
    if(NULL != s32l_value) {
        *s32l_value = 0;
    }
    uint32_t start_index = 0;
    bool res = skip_prefix_spaces(s32l_str, s32l_str_len, &start_index);
    if(res) {
        s32l_len -= (int32_t)start_index;
    }
    s32l_str_not_empty = get_str_len(&s32l_str[start_index], &s32l_len);
    if(s32l_str_not_empty == false) {
        s32l_success = false;
    }

    if(s32l_success) {
        uint8_t out_shift = 0U;
        res = is_dec_str(&s32l_str[start_index], s32l_len);
        if(res) {
            s32l_success = try_strl2int32_dec(&s32l_str[start_index], s32l_len, s32l_value);
        } else {
            LOG_DEBUG(LINE, "NotDec [%s]", &s32l_str[start_index]);
            if(is_hex_str(&s32l_str[start_index], s32l_len, &out_shift)) {
                s32l_success =
                    try_strl2int32_hex(&s32l_str[out_shift + start_index], s32l_len - ((int32_t)out_shift), s32l_value);
            } else {
                s32l_success = false;
            }
        }
    }

    return s32l_success;
}

bool try_str2uint32_hex(const char u32_hex_str[], uint32_t* u32_hex_value) {
    bool res = false;
    if((NULL != u32_hex_str) && (NULL != u32_hex_value)) {
        int32_t u32_hex_str_len = (int32_t)strlen(u32_hex_str);
        res = try_strl2uint32_hex(u32_hex_str, u32_hex_str_len, u32_hex_value);
    }
    return res;
}

bool try_strl2uint32_hex(const char u32l_hex_str[], int32_t u32l_hex_str_len, uint32_t* u32l_hex_value) {
    uint64_t u32l_hex_result = 0U;
    bool u32l_hex_success = try_strl2uint64_hex(u32l_hex_str, u32l_hex_str_len, &u32l_hex_result);

    if((u32l_hex_success) && (u32l_hex_result <= (uint64_t)UINT32_MAX)) {
        *u32l_hex_value = (uint32_t)u32l_hex_result;
    } else {
        u32l_hex_success = false;
        *u32l_hex_value = 0U;
    }

    return u32l_hex_success;
}

bool try_strl2int32_hex(const char s32l_hex_str[], int32_t s32l_hex_str_len, int32_t* s32l_hex_value) {
    int64_t s32l_hex_result = 0;
    bool s32l_hex_success = try_strl2int64_hex(s32l_hex_str, s32l_hex_str_len, &s32l_hex_result);

    if((s32l_hex_success) && (s32l_hex_result <= INT32_MAX) && (s32l_hex_result >= INT32_MIN)) {
        *s32l_hex_value = (int32_t)s32l_hex_result;
    } else {
        s32l_hex_success = false;
        *s32l_hex_value = 0;
    }

    return s32l_hex_success;
}

bool try_strl2uint32_dec(const char u32_dec_str[], int32_t u32_dec_str_len, uint32_t* u32_dec_value) {
    uint64_t u32l_dec_result = 0U;
    bool u32l_dec_success = try_strl2uint64_dec(u32_dec_str, u32_dec_str_len, &u32l_dec_result);

    if((u32l_dec_success) && (u32l_dec_result <= UINT32_MAX)) {
        *u32_dec_value = (uint32_t)u32l_dec_result;
    } else {
        u32l_dec_success = false;
        *u32_dec_value = 0U;
    }

    return u32l_dec_success;
}

bool try_strl2int32_dec(const char s32_dec_str[], int32_t s32_dec_str_len, int32_t* s32_dec_value) {
    int64_t s32l_dec_result = 0;
#ifdef HAS_CONVERT_DEBUG
    printf("\n%s() str:[%s] len [%u]", __FUNCTION__, s32_dec_str, s32_dec_str_len);
#endif
    bool s32l_dec_success = try_strl2int64_dec(s32_dec_str, s32_dec_str_len, &s32l_dec_result);

    if(s32l_dec_success && (s32l_dec_result <= INT32_MAX) && (s32l_dec_result >= INT32_MIN)) {
        *s32_dec_value = (int32_t)s32l_dec_result;
    } else {
        s32l_dec_success = false;
        *s32_dec_value = 0;
    }

    return s32l_dec_success;
}

/* STRING TO 16 BIT
 * ****************************************************************************
 */

bool try_str2uint16(const char u16_str[], uint16_t* u16_value) {
    bool res = false;
    if((NULL != u16_str) && (NULL != u16_value)) {
        int32_t u16_str_len = (int32_t)strlen(u16_str);
        res = try_strl2uint16(u16_str, u16_str_len, u16_value);
    }
    return res;
}

bool try_str2int16(const char s16_str[], int16_t* s16_value) {
    int32_t s16_str_len = (int32_t)strlen(s16_str);
    return try_strl2int16(s16_str, s16_str_len, s16_value);
}

bool try_strl2uint16(const char u16l_str[], int32_t u16l_str_len, uint16_t* u16l_value) {
    uint32_t u16l_result = 0U;
    bool u16l_success = try_strl2uint32(u16l_str, u16l_str_len, &u16l_result);

    if((u16l_success) && (u16l_result <= (uint32_t)UINT16_MAX)) {
        *u16l_value = (uint16_t)u16l_result;
    } else {
        u16l_success = false;
        *u16l_value = 0U;
    }

    return u16l_success;
}

bool try_strl2int16(const char s16l_str[], int32_t s16l_str_len, int16_t* s16l_value) {
    int32_t s16l_result = 0;
    bool s16l_success = try_strl2int32(s16l_str, s16l_str_len, &s16l_result);

    if((s16l_success) && (s16l_result <= INT16_MAX) && (s16l_result >= INT16_MIN)) {
        *s16l_value = (int16_t)s16l_result;
    } else {
        s16l_success = false;
        *s16l_value = 0;
    }

    return s16l_success;
}

/* STRING TO 8 BIT
 * *****************************************************************************
 */
#ifdef HAS_PARSE_8BIT_TYPES
bool try_str2uint8(const char u8_str[], uint8_t* u8_value) {
    bool res = false;
    if((NULL != u8_str) && (NULL != u8_value)) {
        int32_t u8_str_len = (int32_t)strlen(u8_str);
        res = try_strl2uint8(u8_str, u8_str_len, u8_value);
    } /*Otherwise reboot will occur*/
    return res;
}

bool try_str2int8(const char s8_str[], int8_t* s8_value) {
    int32_t s8_str_len = (int32_t)strlen(s8_str);
    return try_strl2int8(s8_str, s8_str_len, s8_value);
}

bool try_strl2uint8(const char u8l_str[], int32_t u8l_str_len, uint8_t* u8l_value) {
    bool u8l_success = false;
    if(u8l_str) {
        uint32_t u8l_result = 0U;
        u8l_success = try_strl2uint32(u8l_str, u8l_str_len, &u8l_result);

        if((u8l_success) && (u8l_result <= (uint32_t)UINT8_MAX)) {
            *u8l_value = (uint8_t)u8l_result;
        } else {
            u8l_success = false;
            *u8l_value = 0U;
        }
    }
    return u8l_success;
}

bool try_strl2int8(const char s8l_str[], int32_t s8l_str_len, int8_t* s8l_value) {
    int32_t s8l_result = 0;
    bool s8l_success = try_strl2int32(s8l_str, s8l_str_len, &s8l_result);

    if((s8l_success) && (s8l_result <= INT8_MAX) && (s8l_result >= INT8_MIN)) {
        *s8l_value = (int8_t)s8l_result;
    } else {
        s8l_success = false;
        *s8l_value = 0;
    }

    return s8l_success;
}

bool try_strl2uint8_hex(const char u8l_hex_str[], int32_t u8l_hex_str_len, uint8_t* u8l_hex_value) {
    bool u8l_hex_success = false;
    if(NULL != u8l_hex_str) {
        uint64_t u8l_hex_result = 0U;
        u8l_hex_success = try_strl2uint64_hex(u8l_hex_str, u8l_hex_str_len, &u8l_hex_result);

        if((u8l_hex_success) && (u8l_hex_result <= (uint64_t)UINT8_MAX)) {
            *u8l_hex_value = (uint8_t)u8l_hex_result;
        } else {
            u8l_hex_success = false;
            *u8l_hex_value = 0U;
        }
    }

    return u8l_hex_success;
}
#endif

bool try_strl2uint16_hex(const char u16l_hex_str[], int32_t u16l_hex_str_len, uint16_t* u16l_hex_value) {
    uint64_t u16l_hex_result = 0U;
    bool u16l_hex_success = try_strl2uint64_hex(u16l_hex_str, u16l_hex_str_len, &u16l_hex_result);

    if((u16l_hex_success) && (u16l_hex_result <= (uint64_t)UINT16_MAX)) {
        *u16l_hex_value = (uint16_t)u16l_hex_result;
    } else {
        u16l_hex_success = false;
        *u16l_hex_value = 0U;
    }

    return u16l_hex_success;
}

bool try_strl2int8_hex(const char s8l_hex_str[], int32_t s8l_hex_str_len, int8_t* s8l_hex_value) {
    int64_t s8l_hex_result = 0;
    bool s8l_hex_success = try_strl2int64_hex(s8l_hex_str, s8l_hex_str_len, &s8l_hex_result);

    if((s8l_hex_success) && (s8l_hex_result <= INT8_MAX) && (s8l_hex_result >= INT8_MIN)) {
        *s8l_hex_value = (int8_t)s8l_hex_result;
    } else {
        s8l_hex_success = false;
        *s8l_hex_value = 0;
    }

    return s8l_hex_success;
}

bool try_str2bool(const char bool_str[], bool* bool_value) {
    uint8_t bool_tmp_result[6] = {0U, 0U, 0U, 0U, 0U, 0U};
    int32_t bool_str_len = -1;
    int32_t bool_str_index;
    bool bool_success = true;
    bool bool_str_not_empty = true;
    if((NULL != bool_str) && (NULL != bool_value)) {
        bool_str_not_empty = get_str_len(bool_str, &bool_str_len);
        if((bool_str_not_empty == false) || (bool_str_len > 5)) {
            bool_success = false;
        }

        if(bool_success) {
            for(bool_str_index = 0; bool_str_index < bool_str_len; bool_str_index++) {
                uint8_t bool_str_char = (uint8_t)bool_str[bool_str_index];
                bool_tmp_result[bool_str_index] = (uint8_t)tolower((int32_t)bool_str_char);
            }
            bool_tmp_result[bool_str_len] = 0U;

            if(is_true((const char*)bool_tmp_result)) {
                *bool_value = true;
            } else if(is_false((const char*)bool_tmp_result)) {
                *bool_value = false;
            } else {
                bool_success = false;
            }
        }
    } else {
        bool_success = false;
    }
    return bool_success;
}

#ifdef HAS_STR2_DOUBLE
bool is_valid_double_symbol(char symbol) {
    bool res = false;
    if('-' == symbol) {
        res = true;
    } else if('+' == symbol) {
        res = true;
    } else if('.' == symbol) {
        res = true;
    } else if(isdigit(symbol)) {
        res = true;
    } else if(' ' == symbol) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool proc_strtod(const char str[], const char** endptr, double* result) {
    bool strtod_success = true;
    if(NULL != result) {
        bool strtod_negative = false;
        double number = 0.0;
        uint32_t u32_number;
        uint32_t str_index = 0U;
        int32_t s32_number;
        int32_t exponent = 0;
        uint8_t num_digits = 0U;
        uint8_t num_decimals = 0U;
        uint8_t temp_value = 0U;

        /* Skip leading whitespace */
        while(0 < isspace((int32_t)(str[str_index]))) {
            str_index++;
        }

        /* Handle optional sign */
        if(('-' == str[str_index]) || ('+' == str[str_index])) {
            if('-' == str[str_index]) {
                strtod_negative = true;
            }
            str_index++;
        }

        /* Process string of digits */
        while(0 < isdigit((int32_t)(str[str_index]))) {
            temp_value = 0U;
            (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
            number = (number * 10.0) + ((double)temp_value);
            LOG_DEBUG(LINE, "digit=%c temp_value=%u", str[str_index], temp_value);
            LOG_DEBUG(LINE, "number:%f", number);
            str_index++;
            num_digits++;
        }
        LOG_DEBUG(LINE, "number:%f", number);

        LOG_DEBUG(LINE, "NextSymbol:[%c]", str[str_index]);

        if(('\n' == str[str_index]) || ('\r' == str[str_index])) {
            if(strtod_negative) {
                number = (-1.0) * number;
            }

            strtod_success = true;
            *endptr = &str[str_index + 1];
            *result = number;
            return strtod_success;
        }
        /* Process decimal part  */
        if(str[str_index] == '.') {
            str_index++;

            while(isdigit((int32_t)(str[str_index])) > 0) {
                (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
                number = (number * 10.0) + (double)temp_value;
                str_index++;
                num_digits++;
                num_decimals++;
            }

            exponent -= (int32_t)num_decimals;
        }

        if(0U == num_digits) {
            if(endptr != NULL) {
                *endptr = &str[str_index];
            }

            strtod_success = false;
        }
        if(strtod_success) {
            /* Correct for sign */
            if(strtod_negative) {
                number = (-1.0) * number;
            }

            /* Process an exponent string */
            if((str[str_index] == 'e') || (str[str_index] == 'E')) {
                /* Handle optional sign */
                strtod_negative = false;
                str_index++;

                if(('-' == str[str_index]) || ('+' == str[str_index])) {
                    if('-' == str[str_index]) {
                        strtod_negative = true;
                    }
                    str_index++;
                }

                if(isdigit((int32_t)(str[str_index])) > 0) {
                    /* Process string of digits */
                    s32_number = 0;
                    while(isdigit((int32_t)(str[str_index])) > 0) {
                        (void)try_dec_char_to_u8((uint8_t)str[str_index], &temp_value);
                        s32_number = (s32_number * 10) + (int32_t)temp_value;
                        str_index++;
                    }

                    if(strtod_negative) {
                        exponent -= s32_number;
                    } else {
                        exponent += s32_number;
                    }
                } else { /* No exponent after e */
                    strtod_success = false;
                }
            }

            if((exponent < DBL_MIN_10_EXP) || (exponent > DBL_MAX_10_EXP)) {
                if(endptr != NULL) {
                    *endptr = &str[str_index];
                }

                strtod_success = false;
            }

            if(strtod_success) {
                /* Scale the result */
                double p10 = 10.0;
                s32_number = exponent;
                if(s32_number < 0) {
                    s32_number = -s32_number;
                }

                u32_number = (uint32_t)(s32_number);

                while(u32_number != 0U) {
                    if((u32_number & 1U) > 0U) {
                        if(exponent < 0) {
                            number /= p10;
                        } else {
                            number *= p10;
                        }
                    }
                    u32_number >>= 1;
                    p10 *= p10;
                }

                if(endptr != NULL) {
                    *endptr = &str[str_index];
                }
                if(NULL != result) {
                    *result = number;
                }
            }
        }
    } else {
        strtod_success = false;
    }
    return strtod_success;
}
#endif

/* STRING TO FLOATING
 * ************************************************************************** */
#ifdef HAS_STR2_FLOAT
bool try_str2float(const char float_str[], float* float_value) {
    bool float_success = false;

    if((NULL != float_value) && (NULL != float_str)) {
        const char* float_ptr = NULL;
        double float_temp_value = 0.0;
#ifdef HAS_STR2_DOUBLE
        float_success = proc_strtod(float_str, &float_ptr, &float_temp_value);
#endif
        // float_temp_value=%f",float_success,float_str,float_ptr,float_temp_value);
        if((float_success) && (*float_ptr != '\0')) {
            float_success = false;
        } else {
            bool is_positive = (float_temp_value > 0.0);
            bool is_negative = (float_temp_value < 0.0);
            bool hi_pos_bound_exceeded = (float_temp_value > FLT_MAX);
            bool lo_pos_bound_exceeded = (float_temp_value < FLT_MIN);
            bool lo_neg_bound_exceeded = (float_temp_value < -FLT_MAX);
            if((is_positive) && ((hi_pos_bound_exceeded) || (lo_pos_bound_exceeded))) {
                float_success = false;
            } else if((is_negative) && (lo_neg_bound_exceeded)) {
                float_success = false;
            } else {
                *float_value = (float)float_temp_value;
            }
        }
    } else {
        float_success = false;
    }
    return float_success;
}
#endif

#ifdef HAS_STR2_DOUBLE
bool try_str2double(const char double_str[], double* double_value) {
    LOG_DEBUG(LINE, "TryParseDoubleIn[%s]", double_str);
    bool double_success = false;

    double_success = try_str2number(double_str, double_value);

#if 0
    const char* double_ptr = NULL;
    if(double_str) {
        if(double_value) {
            double_success = proc_strtod(double_str, &double_ptr, double_value);
            if((double_success  ) && (*double_ptr != '\0')) {
                double_success = false;
            }
        }
    }
#endif
    return double_success;
}
#endif

#ifdef HAS_STR2_DOUBLE
bool try_strl2double(const char double_str[], int32_t str_len, double* double_value) {
    bool double_success = false;
    LOG_DEBUG(LINE, "strl2double [%s] %u", double_str, str_len);
    if(double_str) {
        char tempStr[30] = "";
        memset(tempStr, 0x00, sizeof(tempStr));
        memcpy(tempStr, double_str, (uint32_t)str_len);
        double_success = try_str2double(tempStr, double_value);
    }
    return double_success;
}
#endif

bool AsciiChar2HexNibble(char ch, uint8_t* nibble_out) {
    bool res = false;
    if(nibble_out && is_hex_digit(ch)) {
        res = true;
        uint8_t nibble = 0x00;
        switch(ch) {
        case '1':
            nibble = 0x01;
            break;
        case '2':
            nibble = 0x02;
            break;
        case '3':
            nibble = 0x03;
            break;
        case '4':
            nibble = 0x04;
            break;
        case '5':
            nibble = 0x05;
            break;
        case '6':
            nibble = 0x06;
            break;
        case '7':
            nibble = 0x07;
            break;
        case '8':
            nibble = 0x08;
            break;
        case '9':
            nibble = 0x09;
            break;
        case 'A':
        case 'a':
            nibble = 0x0A;
            break;
        case 'B':
        case 'b':
            nibble = 0x0B;
            break;
        case 'C':
        case 'c':
            nibble = 0x0C;
            break;
        case 'D':
        case 'd':
            nibble = 0x0D;
            break;
        case 'e':
        case 'E':
            nibble = 0x0E;
            break;
        case 'F':
        case 'f':
            nibble = 0x0F;
            break;
        default:
            res = false;
            break;
        }
        *nibble_out = nibble;
    }

    return res;
}

uint8_t AsciiChar2Dec(char ch) {
    uint8_t dec_val = 0xFF;
    bool res = AsciiChar2HexNibble(ch, &dec_val);
    if(false == res) {
        dec_val = 0;
    }
    return dec_val;
}

#ifdef HAS_STR2_DOUBLE
static void dtoa_normal(double double_data, int32_t double_precision, char double_stringified[]) {
    uint32_t double_result_str_index = 0U;
    bool double_auto_precision = false;
    char double_number_to_char;
    double double_d = double_data;
    int32_t d_precision = double_precision;
    if(double_d < 0.0) {
        double_stringified[double_result_str_index] = '-';
        double_result_str_index++;
        double_d = (-1.0) * double_d;
    }

    if(d_precision < 0) { /* negative precision == automatic precision guess */
        double_auto_precision = true;
        if(double_d < 0.01) {
            d_precision = 10;
        } else if(double_d < 0.1) {
            d_precision = 9;
        } else if(double_d < 1.0) {
            d_precision = 8;
        } else if(double_d < 10.0) {
            d_precision = 7;
        } else if(double_d < 100.0) {
            d_precision = 6;
        } else if(double_d < 1000.0) {
            d_precision = 5;
        } else if(double_d < 10000.0) {
            d_precision = 4;
        } else if(double_d < 100000.0) {
            d_precision = 3;
        } else if(double_d < 1000000.0) {
            d_precision = 2;
        } else if(double_d < 10000000.0) {
            d_precision = 1;
        } else {
            d_precision = 0;
        }
    }

    /* round value according the precision */
    double_d += rounders[d_precision];
    if(d_precision == 0) {
        (void)utoa64_((uint64_t)double_d, &double_stringified[double_result_str_index], 10U, NULL);
    } else {
        uint64_t double_int_part = (uint64_t)double_d;
        uint32_t double_int_part_len = 0U;
        double_d -= (double)double_int_part;
        (void)utoa64_(double_int_part, &double_stringified[double_result_str_index], 10U, &double_int_part_len);
        double_result_str_index += double_int_part_len;
        double_stringified[double_result_str_index] = '.';
        double_result_str_index++;

        while(d_precision != 0) {
            d_precision--;
            double_d *= 10.0;
            double_int_part = (uint64_t)double_d;
            double_number_to_char = (char)('0' + double_int_part);
            double_stringified[double_result_str_index] = double_number_to_char;
            double_result_str_index++;
            double_d -= (double)double_int_part;
        }

        if(double_auto_precision) {
            while(double_stringified[double_result_str_index - 1U] == '0') {
                double_result_str_index--;
            }
            if(double_stringified[double_result_str_index - 1U] == '.') {
                double_result_str_index--;
            }
        }

        double_stringified[double_result_str_index] = '\0';
    }
}
#endif

#if defined(HAS_STR2_DOUBLE) && !defined(HAS_X86)
static uint8_t __fpclassifyl(double double_data_) { return FP_NORMAL; }
#endif

#ifdef HAS_STR2_DOUBLE
void dtoa_(double double_data_, int32_t double_precision_, char out_double_stringified_[]) {
    dtoa_normal(double_data_, double_precision_, out_double_stringified_);
#if(!defined(DeviceFamily_CC26X2) && !defined(STM32F4xx) && !defined(STM32F401) && !defined(X86_64) && !defined(ESP32))
    switch(__fpclassifyl(double_data_)) {
    case FP_NORMAL:
    case FP_ZERO:
    case FP_SUBNORMAL:
        dtoa_normal(double_data_, double_precision_, out_double_stringified_);
        break;
    case FP_INFINITE:
        (void)strcpy(out_double_stringified_, "INF");
        break;
    case FP_NAN:
        (void)strcpy(out_double_stringified_, "NAN");
        break;
    default:
        (void)strcpy(out_double_stringified_, "???");
        break;
    }
#endif /*DeviceFamily_CC26X2*/
}
#endif

#ifdef HAS_STR2_FLOAT
#ifndef STM32F4xx
static void ftoa_normal(float float_data, int32_t float_precision, char float_stringified[]) {
    uint32_t float_result_str_index = 0U;
    bool float_auto_precision = false;
    char float_number_to_char;
    float f_data = float_data;
    int32_t f_precision = float_precision;

    if(f_data < 0.0f) {
        float_stringified[float_result_str_index] = '-';
        float_result_str_index++;
        f_data = (-1.0f) * f_data;
    }
    if(f_precision < 0) { /* negative precision == automatic precision guess */
        float_auto_precision = true;
        if(f_data < 0.01) {
            f_precision = 10;
        } else if(f_data < 0.1) {
            f_precision = 9;
        } else if(f_data < 1.0) {
            f_precision = 8;
        } else if(f_data < 10.0) {
            f_precision = 7;
        } else if(f_data < 100.0) {
            f_precision = 6;
        } else if(f_data < 1000.0) {
            f_precision = 5;
        } else if(f_data < 10000.0) {
            f_precision = 4;
        } else if(f_data < 100000.0) {
            f_precision = 3;
        } else if(f_data < 1000000.0) {
            f_precision = 2;
        } else if(f_data < 10000000.0) {
            f_precision = 1;
        } else {
            f_precision = 0;
        }
    }
    /* round value according the precision */
    f_data += rounders[f_precision];
    if(f_precision == 0) {
        (void)utoa64_((uint64_t)f_data, &float_stringified[float_result_str_index], 10U, NULL);
    } else {
        uint64_t float_int_part = (uint64_t)f_data;
        uint32_t float_int_part_len = 0U;
        f_data -= (float)float_int_part;
        (void)utoa64_(float_int_part, &float_stringified[float_result_str_index], 10U, &float_int_part_len);
        float_result_str_index += float_int_part_len;
        float_stringified[float_result_str_index] = '.';
        float_result_str_index++;

        while(f_precision != 0) {
            f_precision--;
            f_data *= 10.0f;
            float_int_part = (uint64_t)f_data;
            float_number_to_char = (char)('0' + float_int_part);
            float_stringified[float_result_str_index] = float_number_to_char;
            float_result_str_index++;
            f_data -= (float)float_int_part;
        }

        if(float_auto_precision) {
            while(float_stringified[float_result_str_index - 1U] == '0') {
                float_result_str_index--;
            }
            if(float_stringified[float_result_str_index - 1U] == '.') {
                float_result_str_index--;
            }
        }

        float_stringified[float_result_str_index] = '\0';
    }
}
#endif /*STM32F413xx*/
#endif

#ifndef __GNUC__
uint8_t __fpclassifyf(float float_data_) { return FP_SUBNORMAL; } /*GCC defines __fpclassifyf*/
#endif

#ifdef HAS_STR2_FLOAT
void ftoa_(float float_data_, int32_t float_precision_, char float_stringified_[]) {
#ifndef STM32F4xx
    uint32_t code = (uint32_t)__fpclassifyf(float_data_);
    switch(code) {
    case FP_NORMAL:
    case FP_ZERO:
    case FP_SUBNORMAL:
        ftoa_normal(float_data_, float_precision_, float_stringified_);
        break;
    case FP_INFINITE:
        (void)strcpy(float_stringified_, "INF");
        break;
    case FP_NAN:
        (void)strcpy(float_stringified_, "NAN");
        break;
    default:
        (void)strcpy(float_stringified_, "???");
        break;
    }
#endif /*STM32F413xx*/
}
#endif

#define XX 222U
#define BASE64_EQ 61U

bool try_hex_char_to_u8(uint8_t hex_char, uint8_t* hex_char_to_u8_value) {
    uint8_t hex_char_to_u8_result = 0U;
    bool hex_char_to_u8_success = true;

    switch(hex_char) {
    case(uint8_t)'0':
    case(uint8_t)'1':
    case(uint8_t)'2':
    case(uint8_t)'3':
    case(uint8_t)'4':
    case(uint8_t)'5':
    case(uint8_t)'6':
    case(uint8_t)'7':
    case(uint8_t)'8':
    case(uint8_t)'9':
        hex_char_to_u8_result = (uint8_t)(hex_char - (uint8_t)'0');
        break;
    case(uint8_t)'a':
    case(uint8_t)'b':
    case(uint8_t)'c':
    case(uint8_t)'d':
    case(uint8_t)'e':
    case(uint8_t)'f':
        hex_char_to_u8_result = ((hex_char - (uint8_t)'a') + 10U);
        break;
    case(uint8_t)'A':
    case(uint8_t)'B':
    case(uint8_t)'C':
    case(uint8_t)'D':
    case(uint8_t)'E':
    case(uint8_t)'F':
        hex_char_to_u8_result = ((hex_char - (uint8_t)'A') + 10U);
        break;
    default:
        hex_char_to_u8_success = false;
        break;
    }
    if(NULL != hex_char_to_u8_value) {
        (*hex_char_to_u8_value) = hex_char_to_u8_result;
    }
    return hex_char_to_u8_success;
}

static bool try_dec_char_to_u8(uint8_t dec_char, uint8_t* dec_char_to_u8_value) {
    uint8_t dec_char_to_u8_result = 0U;
    bool dec_char_to_u8_success = true;

    if((dec_char < (uint8_t)'0') || ((uint8_t)'9' < dec_char)) {
        dec_char_to_u8_success = false;
    }

    if(dec_char_to_u8_success) {
        dec_char_to_u8_result = dec_char - (uint8_t)'0';
    }
    if(NULL != dec_char_to_u8_value) {
        (*dec_char_to_u8_value) = dec_char_to_u8_result;
    }
    return dec_char_to_u8_success;
}

uint8_t char_to_u8(uint8_t dec_char) {
    uint8_t dec_char_to_u8_value = 0;
    bool res = try_dec_char_to_u8(dec_char, &dec_char_to_u8_value);
    if(false == res) {
        dec_char_to_u8_value = 0;
    }
    return dec_char_to_u8_value;
}

static bool is_signed(const char first_str_char, int32_t* first_digit_index) {
    bool negative = false;
    *first_digit_index = 0;
    if(first_str_char == '-') {
        negative = true;
        *first_digit_index = 1;
    }
    if(first_str_char == '+') {
        *first_digit_index = 1;
    }
    return negative;
}

static bool get_str_len(const char char_str[], int32_t* str_len) {
    bool str_not_empty = true;
    if(NULL != char_str) {
        if(*str_len < 0) {
            if(char_str != NULL) {
                *str_len = (int32_t)strlen(char_str);
            } else {
                *str_len = 0;
            }
        }

        if(*str_len == 0) {
            str_not_empty = false;
        }
    } else {
        str_not_empty = false;
    }

    return str_not_empty;
}

bool is_dec_digit(const char character) {
    bool res = false;
    if(('0' <= character) && (character <= '9')) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool is_dec_str(const char str_to_check[], int32_t str_to_check_len) {
    bool is_dec_str_result = false;
    int32_t valid_dec_cnt = 0;
    if(NULL != str_to_check) {
        bool len_check_passed = (0 < str_to_check_len);
        if(len_check_passed) {
            int32_t i = 0;
            for(i = 0; i < str_to_check_len; i++) {
                if(is_dec_digit(str_to_check[i])) {
                    valid_dec_cnt++;
                } else {
                    if(('-' == str_to_check[i]) || ('+' == str_to_check[i])) {
                        if(0 == i) {
                            valid_dec_cnt++;
                        }
                    }
                }
            }
            if(str_to_check_len == valid_dec_cnt) {
                is_dec_str_result = true;
            }
        }
    }
    return is_dec_str_result;
}

bool is_hex_digit(const char character) {
    bool res = false;
    if((('A' <= character) && (character <= 'F')) || (('a' <= character) && (character <= 'f')) ||
       (('0' <= character) && (character <= '9'))) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

static bool is_true(const char* true_str_to_check) {
    bool is_true_result = false;
    if(NULL != true_str_to_check) {
        int32_t check_for_yes = strcmp(true_str_to_check, "yes");
        int32_t check_for_true = strcmp(true_str_to_check, "true");
        int32_t check_for_on = strcmp(true_str_to_check, "on");
        int32_t check_for_1 = strcmp(true_str_to_check, "1");

        if((check_for_yes == 0) || (check_for_true == 0) || (check_for_on == 0) || (check_for_1 == 0)) {
            is_true_result = true;
        }
    }

    return is_true_result;
}

static bool is_false(const char* false_str_to_check) {
    bool is_false_result = false;
    if(NULL != false_str_to_check) {
        int32_t check_for_no = strcmp(false_str_to_check, "no");
        int32_t check_for_false = strcmp(false_str_to_check, "false");
        int32_t check_for_off = strcmp(false_str_to_check, "off");
        int32_t check_for_0 = strcmp(false_str_to_check, "0");

        if((check_for_no == 0) || (check_for_false == 0) || (check_for_off == 0) || (check_for_0 == 0)) {
            is_false_result = true;
        }
    }

    return is_false_result;
}

/*Mind byte order of you CPU core*/
uint32_t assemble_uint32(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4) {
    uint32_t v32 = 0;
    uint8_t v8[4] = {0x00, 0x00, 0x00, 0x00};
    v8[0] = byte4;
    v8[1] = byte3;
    v8[2] = byte2;
    v8[3] = byte1;
    (void)memcpy((uint8_t*)&v32, (uint8_t*)&v8[0], 4);

    return v32;
}

#ifdef HAS_STR2_DOUBLE
static bool number_compose_mantissa(Text2NumberFsm_t* Node) {
    bool res = false;
    if(Node) {
        Node->mantissa = ((double)Node->sign) * (((double)Node->integer) + ((double)Node->fraction));
        // if(Node->spot_mantissa){
        //}else{
        //    Node->mantissa = 1.0;
        //}
        LOG_DEBUG(LINE, "Mantissa %f", Node->mantissa);
        res = true;
    }
    return res;
}
#endif

/*Does not work*/
uint16_t float_to_uint16(float val) {
    uint16_t out = (uint16_t)val;
    return out;
}

uint16_t double_to_uint16(double val) {
    uint16_t out = (uint16_t)val;
    return out;
}

bool try_str2array(char* in_str_array, uint8_t* out_array, uint16_t array_size, uint32_t* const out_array_len) {
    bool res = false;
    uint8_t out_shift = 0;
    uint32_t len_str_in = strlen(in_str_array);
#ifdef HAS_CONVERT_DEBUG
    printf("[d]len_str_in %u", len_str_in);
#endif
    res = is_hex_str(in_str_array, len_str_in, &out_shift);
    if(res) {
#ifdef HAS_CONVERT_DEBUG
        printf("[d]shift %u", out_shift);
#endif
        if(0 == (len_str_in % 2)) {
            uint32_t i;
            for(i = 0; i < (len_str_in / 2); i++) {
                res = try_strl2uint8_hex(&in_str_array[out_shift + i * 2], 2, &out_array[i]);
                if(res) {
                    (*out_array_len)++;
                } else {
                    break;
                }
            }
            if(0U < (*out_array_len)) {
                res = true;
            }
        }
    } else {
#ifdef HAS_CONVERT_DEBUG
        printf("[d] not a hex str [%s]", in_str_array);
#endif
    }

    return res;
}

bool try_strl2array(const char* const str_array, uint32_t len_str_in, uint8_t* const out_array, uint16_t array_size,
                    uint32_t* const ret_len) {
    bool res = false;
    if(str_array) {
        if(len_str_in) {
            if(out_array) {
                if(ret_len) {
                    uint8_t out_shift = 0;
                    res = is_hex_str(str_array, len_str_in, &out_shift);
                    if(res) {
                        if(0 == (len_str_in % 2)) {
                            uint32_t i = 0;
                            for(i = 0; i < (len_str_in / 2); i++) {
                                res = try_strl2uint8_hex(&str_array[out_shift + i * 2], 2, &out_array[i]);
                                if(res) {
                                    (*ret_len)++;
                                } else {
                                    break;
                                }
                            }
                            if(0U < (*ret_len)) {
                                res = true;
                            }
                        } else {
                            LOG_ERROR(LINE, "LenErr");
                        }
                    } else {
                        LOG_ERROR(LINE, "NotHexStrErr");
                    }
                } else {
                    LOG_ERROR(LINE, "ret_len err");
                }
            } else {
                LOG_ERROR(LINE, "out_array err");
            }
        } else {
            LOG_ERROR(LINE, "ZeroLenErr");
        }

    } else {
        LOG_ERROR(LINE, "str_array err");
    }
    return res;
}

#ifdef HAS_STR2_DOUBLE
bool text_2_number_init(Text2NumberFsm_t* Node) {
    bool res = false;
    if(Node) {
        Node->value = 0.0;
        Node->sign = 1;
        Node->integer = 0;
        Node->exponent_integer = 0;
        Node->fraction = 0.0;
        Node->fraction_order = 1;
        Node->spot_mantissa = false;
        Node->spot_exponent = false;
        Node->mantissa = 1.0;
        Node->exponent_sign = 1;
        Node->exponenta = 1.0;
        Node->cur_letter = '\0';
        Node->state = PARSE_NUMBER_STATE_PARSE_SIGN;
        res = true;
    }
    return res;
}
#endif

bool number_compose_result(Text2NumberFsm_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->spot_mantissa) {
            // LOG_DEBUG(LINE,"Int:%Le", Node->integer);
            // LOG_DEBUG(LINE,"Int:%lf", Node->integer);
            // LOG_DEBUG(LINE,"Int:%Le", Node->integer);
            LOG_DEBUG(LINE, "Frac:%f", Node->fraction);
            LOG_DEBUG(LINE, "sign %f", (double)Node->sign);
            Node->value = ((double)Node->sign) * (((double)Node->integer) + Node->fraction);
            // LOG_DEBUG(LINE,"Val:%f", Node->value);
            // LOG_DEBUG(LINE,"Val:%lf", Node->value);
            // LOG_DEBUG(LINE,"Val:%Le", Node->value);
            Node->state = PARSE_NUMBER_STATE_DONE;
            res = true;
        } else {
            LOG_ERROR(LINE, "NoMantissa");
        }
    }
    return res;
}

#ifdef HAS_STR2_DOUBLE
static bool number_proc_scale_suffix(Text2NumberFsm_t* Node) {
    bool res = true;
    Node->mantissa = 1.0;
    Node->spot_mantissa = true;
    Node->state = PARSE_NUMBER_STATE_DONE;
    Node->spot_exponent = true;
    Node->integer = 1;
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_parse_sign(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case 'u': {
        Node->exponent_integer = 6;
        Node->exponent_sign = -1;

        res = number_proc_scale_suffix(Node);
        Node->state = PARSE_NUMBER_STATE_DONE;
    } break;

    case 'm': {
        Node->exponent_integer = 3;
        Node->exponent_sign = -1;

        res = number_proc_scale_suffix(Node);
        //   Node->fraction = 0.0;
        Node->state = PARSE_NUMBER_STATE_DONE;
        res = true;
    } break;

    case 'k': {
        Node->exponent_integer = 3;
        Node->exponent_sign = 1;

        res = number_proc_scale_suffix(Node);
        Node->fraction = 0.0;
        res = true;
    } break;

    case 'M': {
        Node->exponent_integer = 6;
        Node->exponent_sign = 1;

        res = number_proc_scale_suffix(Node);
        Node->fraction = 0.0;
        res = true;
    } break;
    case 'G': {
        Node->exponent_integer = 9;
        Node->exponent_sign = 1;

        Node->mantissa = 1.0;
        Node->spot_mantissa = true;
        Node->spot_exponent = true;
        Node->integer = 1;
        Node->fraction = 0.0;
        Node->spot_exponent = true;
        Node->state = PARSE_NUMBER_STATE_DONE;
        res = true;
    } break;
    case 'n': {
        Node->mantissa = 1.0;
        Node->spot_mantissa = true;
        Node->spot_exponent = true;
        Node->integer = 1;
        Node->fraction = 0.0;
        Node->exponent_sign = -1;
        Node->exponent_integer = 9;
        Node->spot_exponent = true;
        Node->state = PARSE_NUMBER_STATE_DONE;
        res = true;
    } break;
    case 'E':
    case 'e': {
        Node->mantissa = 1.0;
        Node->spot_mantissa = false;
        Node->integer = 1;
        Node->fraction = 0.0;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_SIGN;
        res = true;

    } break;

    case ' ': {
        res = true;
    } break;
    case '+': {
        Node->sign = 1;
        Node->state = PARSE_NUMBER_STATE_PARSE_INTEGER;
        res = true;
    } break;
    case '-': {
        Node->sign = -1;
        Node->state = PARSE_NUMBER_STATE_PARSE_INTEGER;
        res = true;
    } break;
    case '0': {
        Node->sign = 1;
        Node->spot_mantissa = true;
        Node->state = PARSE_NUMBER_STATE_PARSE_INTEGER;
        res = true;
    } break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        uint8_t digit = 0;
        Node->spot_mantissa = true;
        res = try_hex_char_to_u8((uint8_t)Node->cur_letter, &digit);
        Node->integer *= 10;
        // LOG_DEBUG(LINE,"1CurInt %Lf",(double)Node->integer);
        Node->integer += digit;
        // LOG_DEBUG(LINE,"2CurInt %Lf",(double)Node->integer);
        Node->state = PARSE_NUMBER_STATE_PARSE_INTEGER;
    } break;
    case '.': {
        Node->fraction_order = 1;
        Node->integer = 0.0;
        Node->spot_mantissa = false;
        Node->state = PARSE_NUMBER_STATE_PARSE_FRACTION;
        res = true;
    } break;
    case '\n':
        res = false;
        break;
    case '\r':
        res = false;
        break;
    default:
        res = false;
        break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_mantissa_save(Text2NumberFsm_t* Node) {
    bool res = false;
    if(Node) {
        Node->mantissa = ((double)Node->sign) * (((double)Node->integer) + Node->fraction);
        LOG_DEBUG(LINE, "Mantissa:%f", Node->mantissa);
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_scale_suffix_after_num(Text2NumberFsm_t* Node) {
    bool res = true;
    res = number_mantissa_save(Node);
    Node->state = PARSE_NUMBER_STATE_DONE;
    Node->spot_exponent = true;
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_parse_integer(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case 'Y': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 24;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'Z': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 21;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'P': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 15;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'T': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 12;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'G': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 9;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'M': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 6;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'k': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 3;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'h': {
        Node->exponent_sign = 1;
        Node->exponent_integer = 2;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'd': {
        Node->exponent_sign = -1;
        Node->exponent_integer = 1;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'c': {
        Node->exponent_sign = -1;
        Node->exponent_integer = 2;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'm': {
        Node->exponent_sign = -1;
        Node->exponent_integer = 3;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'u': {
        Node->exponent_sign = -1;
        Node->exponent_integer = 6;
        res = number_scale_suffix_after_num(Node);
    } break;

    case 'n': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 9;
    } break;

    case 'p': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 12;
    } break;

    case 'f': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 15;
    } break;

    case 'a': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 18;
    } break;

    case 'z': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 21;
    } break;

    case 'y': {
        res = number_scale_suffix_after_num(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 24;
    } break;

    case 'E':
    case 'e': {
        res = number_mantissa_save(Node);
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_SIGN;
    } break;
    case ' ': {
        res = false;
    } break;
    case '.': {
        Node->fraction_order = 1;
        Node->state = PARSE_NUMBER_STATE_PARSE_FRACTION;
        res = true;
    } break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_letter, &digit);
        LOG_PARN(LINE, "ParseDigit %u", digit);
        Node->integer *= 10;
        // LOG_DEBUG(LINE,"1CurInt %Lf",(double)Node->integer);
        Node->integer += digit;
        // LOG_DEBUG(LINE,"2CurInt %Lf",(double) Node->integer);
        Node->spot_mantissa = true;
        res = true;
    } break;

    case '\r':
    case '\n': {
        res = number_compose_result(Node);
    } break;

    default: {
        res = false;
    } break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_parse_exponenta_sign(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case '+': {
        Node->exponent_sign = 1;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER;
        res = true;
    } break;

    case '-': {
        Node->exponent_sign = -1;
        res = true;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER;
    } break;

    case '0': {
        Node->exponent_integer = 0;
        Node->exponent_sign = 1;
        Node->spot_exponent = true;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER;
        res = true;
    } break;
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_letter, &digit);
        LOG_PARN(LINE, "ParseExpInt %u", digit);
        Node->exponent_integer *= 10;
        Node->spot_exponent = true;
        Node->exponent_integer += digit;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER;
        res = true;
    } break;

    case '\r':
    case '\n': {
        res = false;
    } break;
    default:
        res = false;
        break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_exponenta_calc(Text2NumberFsm_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->spot_exponent) {
            int32_t rank = ((int32_t)Node->exponent_integer) * ((int32_t)Node->exponent_sign);
            LOG_DEBUG(LINE, "ExpRank %d", rank);
            double power = (double)rank;
            LOG_DEBUG(LINE, "power %f", power);
            if(rank < 306) {
                if(-306 < rank) {
                    Node->exponenta = pow(10.0, power);
                    LOG_DEBUG(LINE, "Exponenta: %f", Node->exponenta);
                    res = true;
                } else {
                    Node->exponenta = 0.0;
                    LOG_ERROR(LINE, "MathError:TooSmalExpPower %d", rank);
                    res = false;
                }
            } else {
                LOG_ERROR(LINE, "MathError:TooBigExpPower %d", rank);
                res = false;
            }
        } else {
            LOG_ERROR(LINE, "NoExponents");
        }
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_final_value_calc(Text2NumberFsm_t* Node) {
    bool res = false;
    LOG_DEBUG(LINE, "ComposeResult");
    res = number_exponenta_calc(Node);
    if(res) {
        if(Node->spot_mantissa) {
            res = number_compose_mantissa(Node);
            // double mantissa = 0.0;
            // mantissa = ((double)Node->sign) * (((double)Node->integer) + ((double)Node->fraction));
            Node->value = Node->mantissa * (Node->exponenta);
            Node->state = PARSE_NUMBER_STATE_DONE;
        } else {
            LOG_DEBUG(LINE, "NoMantissa");
            res = false;
        }
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_parse_exponenta_integer(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_letter, &digit);
        LOG_PARN(LINE, "ParseExpInt %u", digit);
        Node->exponent_integer *= 10;
        Node->exponent_integer += digit;
        Node->spot_exponent = true;
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER;
        res = true;
    } break;

    case '\r':
    case '\n': {
        res = number_final_value_calc(Node);
    } break;
    default:
        res = false;
        break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_scale_suffix_after_fraction(Text2NumberFsm_t* Node) {
    bool res = false;
    res = number_compose_mantissa(Node);
    Node->state = PARSE_NUMBER_STATE_DONE;
    Node->spot_exponent = true;
    Node->spot_mantissa = true;
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_parse_fracion(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case 'G': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = 1;
        Node->exponent_integer = 9;
    } break;

    case 'M': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = 1;
        Node->exponent_integer = 6;
    } break;

    case 'k': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = 1;
        Node->exponent_integer = 3;
    } break;

    case 'h': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = 1;
        Node->exponent_integer = 2;
    } break;

    case 'd': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 1;
    } break;

    case 'c': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 2;
    } break;

    case 'm': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 3;
    } break;

    case 'u': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 6;
    } break;

    case 'n': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 9;
    } break;

    case 'p': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 12;
    } break;

    case 'f': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 15;
    } break;

    case 'a': {
        res = number_proc_scale_suffix_after_fraction(Node);
        Node->exponent_sign = -1;
        Node->exponent_integer = 18;
    } break;

    case 'E':
    case 'e': {
        res = number_compose_mantissa(Node);
        Node->state = PARSE_NUMBER_STATE_PARSE_EXPONENTA_SIGN;
    } break;
    case ' ': {
        LOG_ERROR(LINE, "TornFlowErr!");
        res = false;
    } break;
    case '.': {
        LOG_ERROR(LINE, "DoubleDotErr!");
        res = false;
    } break;
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9': {
        uint8_t digit = 0;
        res = try_hex_char_to_u8((uint8_t)Node->cur_letter, &digit);
        double fraction_digit = ((double)digit) / (pow(10.0, (double)Node->fraction_order));
        LOG_DEBUG(LINE, "+ %f", fraction_digit);
        Node->spot_mantissa = true;
        Node->fraction += fraction_digit;

        Node->fraction_order++;
        res = true;
    } break;
    case '-':
    case '+': {
        res = false;
    } break;

    case '\r':
    case '\n': {
        res = number_compose_result(Node);
    } break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
static bool number_proc_done(Text2NumberFsm_t* Node) {
    bool res = false;
    switch(Node->cur_letter) {
    case '\n':
    case '\r': {
        res = number_final_value_calc(Node);
        // res = true;
    } break;
    default: {
        res = false;
    } break;
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
bool number_proc_one(Text2NumberFsm_t* Node) {
    bool res = false;
#ifdef HAS_STRING_PARSER_DIAG
    LOG_DEBUG(LINE, "Proc: %s", NumberParserFsm2Str(Node));
#endif
    if(Node) {
        switch(Node->state) {
        case PARSE_NUMBER_STATE_PARSE_SIGN:
            res = number_proc_parse_sign(Node);
            break;
        case PARSE_NUMBER_STATE_PARSE_INTEGER:
            res = number_proc_parse_integer(Node);
            break;
        case PARSE_NUMBER_STATE_PARSE_FRACTION:
            res = number_proc_parse_fracion(Node);
            break;
        case PARSE_NUMBER_STATE_PARSE_EXPONENTA_SIGN:
            res = number_proc_parse_exponenta_sign(Node);
            break;
        case PARSE_NUMBER_STATE_PARSE_EXPONENTA_INTEGER:
            res = number_proc_parse_exponenta_integer(Node);
            break;
        case PARSE_NUMBER_STATE_DONE:
            res = number_proc_done(Node);
            break;

        default:
            res = false;
            break;
        }
    }
    return res;
}
#endif

#ifdef HAS_STR2_DOUBLE
bool try_str2number(const char* const in_text, double* const double_value) {
    bool res = false;
    uint32_t len = 0;
    if(in_text) {
        len = strlen(in_text);
        if(len) {
            if(double_value) {
                res = true;
            }
        }
    }

    if(res) {
        Text2NumberFsm_t Fsm;
        res = text_2_number_init(&Fsm);
        uint32_t i = 0;
        uint32_t ok = 0;
        uint32_t err = 0;
        LOG_DEBUG(LINE, "ParseDoubleIn:%u:[%s]", len, in_text);

        for(i = 0; i < len; i++) {
            Fsm.cur_letter = in_text[i];
            res = number_proc_one(&Fsm);
            if(res) {
                ok++;
            } else {
                err++;
                LOG_DEBUG(LINE, "ProcErr: ch[%u]=[%c] ", i, in_text[i]);
                break;
            }
        }

        if(0 == err) {
            Fsm.cur_letter = '\n';
            res = number_proc_one(&Fsm);
            if(res) {
                ok++;
            } else {
                err++;
            }
        }
        if(0 == err) {
            *double_value = Fsm.value;
            res = true;
        } else {
            LOG_DEBUG(LINE, "err:%u,len:%u,ok:%u", err, len, ok);
            res = false;
        }
    }
    return res;
}
#endif

/*TODO test it
 *
 * text      [IN]   value in string
 * type      [IN]   expected data type
 * out_buff  [OUT]  binary result
 * buff_size [IN] - out buff size
 * */
bool try_str2type(const char* const in_text, StorageType_t type, uint8_t* out_buff, uint32_t buff_size) {
    bool res = false;
    LOG_DEBUG(LINE, "Parse:%s In[%s]OutSize:%u byte", in_text, StorageTypeToStr(type), buff_size);
    if(in_text) {
        if(out_buff) {
            if(buff_size) {
                switch(type) {

                case TYPE_STRUCT: {
                    res = true;
                } break;

                case TYPE_INT8: {
                    int8_t val = 0;
                    res = try_str2int8(in_text, &val);
                    if(res) {
                        memcpy(out_buff, &val, 1);
                    }
                } break;

                case TYPE_UINT8: {
                    uint8_t val = 0;
                    res = try_str2uint8(in_text, &val);
                    if(res) {
                        memcpy(out_buff, &val, 1);
                    }
                } break;

                case TYPE_UINT16: {
                    uint16_t value = 0;
                    res = try_str2uint16(in_text, &value);
                    if(res) {
                        memcpy(out_buff, &value, 2);
                    }
                } break;

                case TYPE_INT16: {
                    int16_t val = 0;
                    res = try_str2int16(in_text, &val);
                    if(res) {
                        memcpy(out_buff, &val, 2);
                    }
                } break;

                case TYPE_UINT32: {
                    uint32_t val = 0;
                    res = try_str2uint32(in_text, &val);
                    if(res) {
                        memcpy(out_buff, &val, 4);
                    }
                } break;

                case TYPE_INT32: {
                    int32_t val = 0;
                    res = try_str2int32(in_text, &val);
                    if(res) {
                        memcpy(out_buff, &val, 4);
                    }
                } break;

                default:
                    LOG_ERROR(LINE, "UndefType:%s", StorageTypeToStr(type));
                    res = false;
                    break;
                } // switch
            }
        }
    }
    return res;
}
