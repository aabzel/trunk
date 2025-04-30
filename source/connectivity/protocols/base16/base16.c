#include "base16.h"

#include <string.h>
#include <ctype.h>

#include "byte_utils.h"
#include "convert.h"
#include "log.h"

static const char base16Alphabet[] = "0123456789ABCDEF";

bool base16_is_allowed_char(char base16) {
    bool res = false;
    uint32_t i = 0;
    size_t len = strlen(base16Alphabet);
    for(i = 0; i < len; i++) {
        if((base16 == base16Alphabet[i]) || (base16 == tolower(base16Alphabet[i]))) {
            res = true;
            break;
        }
    }

    return res;
}

uint8_t base16_char_to_val(char hex_char) {
    uint8_t u8_value = 0;
    bool res = try_hex_char_to_u8(hex_char, &u8_value);
    if(false==res){
    	LOG_ERROR(BASE16, "ERROR");
    }
    return u8_value;
}

bool is_base16(const uint8_t* const encode_data, uint32_t data_size) {
    bool res = true;
    uint8_t out_shift = 0;
    res = is_hex_str(encode_data, data_size, &out_shift);
    if(false == res) {
        LOG_ERROR(BASE16, "NotBase16 Str [%s]", encode_data);
    }

    return res;
}

bool base16_decode(const char* const base16_str, uint32_t base16_str_len, uint8_t* const raw_data,
                   uint32_t* raw_data_size) {
    bool res = false;

//   uint16_t array_size = 0xFFFF;
    uint32_t bin_array_len = 0;
    res = try_strl2array(base16_str, base16_str_len, raw_data, 1, &bin_array_len);
    if(res) {
        if(bin_array_len == (base16_str_len / 2)) {
            res = true;
            if(raw_data_size) {
                *raw_data_size = bin_array_len;
            }
        } else {
            LOG_ERROR(BASE16, "OutLenErr [%u]", bin_array_len);
            res = false;
        }
    }

    return res;
}

bool base16_encode(const uint8_t* const raw_data, uint32_t buff_len, char* const base16_data) {
    bool res = false;
    if(raw_data) {
        if(buff_len) {
            uint32_t i = 0;
            uint32_t j = 0;
            if(base16_data) {
                for(i = 0; i < buff_len; i++, j += 2) {
                    base16_data[j] = base16Alphabet[HI_NIBBLE(raw_data[i])];
                    base16_data[j + 1] = base16Alphabet[LO_NIBBLE(raw_data[i])];
                    res = true;
                }
            }
        }
    }
    return res;
}
