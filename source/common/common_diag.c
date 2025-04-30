#include "common_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_GNSS
#include "gnss_utils.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif
#include "data_utils.h"

#include "shared_array.h"

char* HexWord2Str(uint16_t word) {
    snprintf(text, sizeof(text), "0x%04x", word);
    return text;
}

char* QWord2Str(uint32_t qword) {
    snprintf(text, sizeof(text), "0x%08x=%u", (unsigned int)qword, (unsigned int)qword);
    return text;
}

char* ByteRate2Str(double bit_s) {
    snprintf(text, sizeof(text), "%7.1f Byte/s", bit_s / 8.0);
    return text;
}

const char* BigVal2Str(double big_val) {
    char* name = "?";
#ifdef HAS_NUM_DIAG
    name = DoubleToStr(big_val);
#endif
    return name;
}

char* BitRate2Str(double bit_s) {
    snprintf(text, sizeof(text), "%s Bit/s", BigVal2Str(bit_s));
    return text;
}

char* RfFreq2Str(uint32_t rf_freq) {
    snprintf(text, sizeof(text), "%u Hz=%f MHz", (unsigned int)rf_freq, ((double)rf_freq) / 1000000.0);
    return text;
}

char* Byte2Str(uint8_t byte) {
    snprintf(text, sizeof(text), "0x%02x", byte);
    return text;
}

const char* Bit2Str(uint8_t bit) {
    const char* name = "_";
    if(bit) {
        name = "*";
    }
    return name;
}

static const char hex2asciiLUT[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
bool hex2ascii(uint8_t* in_hex, uint32_t hex_len, uint8_t* out_ascii, uint32_t ascii_len) {
    bool res = false;
    if(in_hex && out_ascii && ((2 * hex_len + 1) <= ascii_len) && (0 < hex_len)) {
        res = true;
        uint32_t i = 0;
        uint32_t j = 0;
        for(i = 0; i < hex_len; i++) {
            out_ascii[j++] = hex2asciiLUT[MASK_4BIT & (in_hex[i] >> 4)];
            out_ascii[j++] = hex2asciiLUT[MASK_4BIT & (in_hex[i])];
        }
        out_ascii[j] = 0x00;
    }
    return res;
}

char* Array2Str(uint8_t* array, uint32_t len) {
    if(len < sizeof(text)) {
        memset(text, 0, sizeof(text));
        memcpy(text, array, len);
    }
    return text;
}

const char* OnOff2Str(uint8_t status) {
    const char* name = "?";
    switch(status) {
    case false:
        name = "Off";
        break;
    case true:
        name = "On";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* OnOffToStr(uint8_t on_off) {
    const char* name = OnOff2Str(on_off);
    return name;
}

const char* Ok2Str(bool status) {
    const char* name = "?";
    switch((uint8_t)status) {
    case false:
        name = "Err";
        break;
    case true:
        name = "Ok";
        break;
    }
    return name;
}

const char* YesNo2Str(uint8_t status) {
    const char* name = "?";
    switch(status) {
    case 0:
        name = "No";
        break;
    case 1:
        name = "Yes";
        break;
    }
    return name;
}

char* uint2str(uint32_t val) {
    snprintf(text, sizeof(text), "%u", (unsigned int)val);
    return text;
}

const char* u32val2Str(uint32_t val) {
    char* name = "?";
#ifdef HAS_NUM_DIAG
    name = (char*)uint32ToStr(val);
#endif
    return name;
}

#ifdef HAS_GNSS
char* mm2str(uint32_t base_acc_mm) {
    snprintf(text, sizeof(text), "%u mm=%f m", base_acc_mm, MM_TO_METER(base_acc_mm));
    return text;
}
#endif
