#include "base64.h"

#include <string.h>

#include "log.h"

static const char base64Alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
static const char basis64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

static bool base64_is_allowed_char(char base64) {
    bool res = false;
    uint32_t i = 0;
    size_t len = strlen(base64Alphabet);
    for(i = 0; i < len; i++) {
        if(base64 == base64Alphabet[i]) {
            res = true;
            break;
        }
    }

    return res;
}

bool is_base64(const uint8_t* const encode_data, uint32_t data_size) {
    bool res = true;
    uint32_t i = 0;
    for(i = 0; i < data_size; i++) {
        res = base64_is_allowed_char(encode_data[i]);
        if(false == res) {
            LOG_ERROR(SYS, "NotAbase64 Char Str[%u]=%c", i, encode_data[i]);
        }
    }
    return res;
}

bool base64_decode(const char* const decode_str, int32_t decode_str_len, uint8_t decode_data[],
                   uint32_t* decode_data_size) {
    static const uint8_t basis[] = {
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  62U,
        XX,  XX,  XX,  63U, 52U, 53U, 54U, 55U, 56U, 57U, 58U, 59U, 60U, 61U, XX,  XX,  XX,  XX,  XX,  XX,  XX,  0U,
        1U,  2U,  3U,  4U,  5U,  6U,  7U,  8U,  9U,  10U, 11U, 12U, 13U, 14U, 15U, 16U, 17U, 18U, 19U, 20U, 21U, 22U,
        23U, 24U, 25U, XX,  XX,  XX,  XX,  XX,  XX,  26U, 27U, 28U, 29U, 30U, 31U, 32U, 33U, 34U, 35U, 36U, 37U, 38U,
        39U, 40U, 41U, 42U, 43U, 44U, 45U, 46U, 47U, 48U, 49U, 50U, 51U, XX,  XX,  XX,  XX,  XX,

        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,
        XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX,  XX};

    bool decode_success = true;
    uint32_t decode_data_index = 0U;
    uint32_t decode_str_base_index = 0U;
    int32_t i;
    uint8_t decode_value;
    uint8_t decode_str_char_0;
    uint8_t decode_str_char_1;
    uint8_t decode_str_char_2;
    uint8_t decode_str_char_3;
    int32_t len = decode_str_len;

    *decode_data_size = 0U;
    if(len < 0) {
        len = (int32_t)strlen(decode_str);
    }

    if((len % 4) != 0) {
        decode_success = false;
    }

    for(i = 0; i < len; i++) {
        uint8_t decode_str_char = (uint8_t)decode_str[i];
        if((decode_success == false) || (decode_str_char == BASE64_EQ)) {
            break;
        }
        if(basis[decode_str_char] == XX) {
            decode_success = false;
        }
    }

    if(decode_success) {
        while(4 < len) {
            decode_str_char_0 = (uint8_t)decode_str[0U + decode_str_base_index];
            decode_str_char_1 = (uint8_t)decode_str[1U + decode_str_base_index];
            decode_str_char_2 = (uint8_t)decode_str[2U + decode_str_base_index];
            decode_str_char_3 = (uint8_t)decode_str[3U + decode_str_base_index];

            decode_value = ((uint8_t)(basis[decode_str_char_0] << 2U) | (uint8_t)(basis[decode_str_char_1] >> 4U));
            decode_data[decode_data_index] = decode_value;
            decode_data_index++;

            decode_value = ((uint8_t)(basis[decode_str_char_1] << 4U) | (uint8_t)(basis[decode_str_char_2] >> 2U));
            decode_data[decode_data_index] = decode_value;
            decode_data_index++;

            decode_value = ((uint8_t)(basis[decode_str_char_2] << 6U) | basis[decode_str_char_3]);
            decode_data[decode_data_index] = decode_value;
            decode_data_index++;

            decode_str_base_index += 4U;
            len -= 4;
        }

        if(0 != len) {
            decode_str_char_0 = (uint8_t)decode_str[0U + decode_str_base_index];
            decode_str_char_1 = (uint8_t)decode_str[1U + decode_str_base_index];
            decode_str_char_2 = (uint8_t)decode_str[2U + decode_str_base_index];
            decode_str_char_3 = (uint8_t)decode_str[3U + decode_str_base_index];

            decode_value = ((uint8_t)(basis[decode_str_char_0] << 2U) | (uint8_t)(basis[decode_str_char_1] >> 4U));
            decode_data[decode_data_index] = decode_value;
            decode_data_index++;
            if(decode_str_char_2 != BASE64_EQ) {
                decode_value = ((uint8_t)(basis[decode_str_char_1] << 4U) | (uint8_t)(basis[decode_str_char_2] >> 2U));
                decode_data[decode_data_index] = decode_value;
                decode_data_index++;
                if(decode_str_char_3 != BASE64_EQ) {
                    decode_value = ((uint8_t)(basis[decode_str_char_2] << 6U) | basis[decode_str_char_3]);
                    decode_data[decode_data_index] = decode_value;
                    decode_data_index++;
                }
            }
        }

        *decode_data_size = decode_data_index;
    }

    return decode_success;
}

uint32_t base64_encode(const uint8_t encode_data[], uint32_t encode_data_size, char encode_result[]) {
    // const static char basis64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    uint32_t encode_result_index = 0U;
    uint32_t encode_data_base_index = 0U;
    uint8_t basis64_char_index;
    uint8_t encode_data_char_0;
    uint8_t encode_data_char_1;
    uint8_t encode_data_char_2;
    uint32_t s = encode_data_size;

    while(s > 2U) {
        encode_data_char_0 = encode_data[0U + encode_data_base_index];
        encode_data_char_1 = encode_data[1U + encode_data_base_index];
        encode_data_char_2 = encode_data[2U + encode_data_base_index];

        basis64_char_index = (encode_data_char_0 >> 2U) & 0x3fU;
        encode_result[encode_result_index] = basis64[basis64_char_index];
        encode_result_index++;

        basis64_char_index = (uint8_t)((encode_data_char_0 & 3U) << 4U) | (encode_data_char_1 >> 4U);
        encode_result[encode_result_index] = basis64[basis64_char_index];
        encode_result_index++;

        basis64_char_index = (uint8_t)((encode_data_char_1 & 0x0fU) << 2U) | (encode_data_char_2 >> 6U);
        encode_result[encode_result_index] = basis64[basis64_char_index];
        encode_result_index++;

        basis64_char_index = encode_data_char_2 & 0x3fU;
        encode_result[encode_result_index] = basis64[basis64_char_index];
        encode_result_index++;

        encode_data_base_index += 3U;
        s -= 3U;
    }

    if(s != 0U) {
        encode_data_char_0 = encode_data[0U + encode_data_base_index];
        encode_data_char_1 = encode_data[1U + encode_data_base_index];

        basis64_char_index = (encode_data_char_0 >> 2U) & 0x3fU;
        encode_result[encode_result_index] = basis64[basis64_char_index];
        encode_result_index++;

        if(s == 1U) {
            basis64_char_index = (uint8_t)((encode_data_char_0 & 3U) << 4U);
            encode_result[encode_result_index] = basis64[basis64_char_index];
            encode_result_index++;
            encode_result[encode_result_index] = '=';
            encode_result_index++;
        } else {
            basis64_char_index = (uint8_t)((encode_data_char_0 & 3U) << 4U) | (encode_data_char_1 >> 4U);
            encode_result[encode_result_index] = basis64[basis64_char_index];
            encode_result_index++;

            basis64_char_index = (uint8_t)((encode_data_char_1 & 0x0fU) << 2U);
            encode_result[encode_result_index] = basis64[basis64_char_index];
            encode_result_index++;
        }

        encode_result[encode_result_index] = '=';
        encode_result_index++;
    }

    encode_result[encode_result_index] = '\0';
    return encode_result_index;
}
