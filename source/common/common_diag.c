#include "common_diag.h"

#include <stdio.h>
#include <string.h>

#include "byte_utils.h"
#include "common_types.h"
#include "data_utils.h"
#include "diag_inc.h"
#include "std_includes.h"

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_GNSS
#include "gnss_utils.h"
#endif

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

char* HexWordToStr(uint16_t word) {
    snprintf(text, sizeof(text), "0x%04x", word);
    return text;
}

char* QWordToStr(uint32_t qword) {
    snprintf(text, sizeof(text), "0x%08x=%u", (unsigned int)qword, (unsigned int)qword);
    return text;
}

char* ByteRateToStr(double bit_s) {
    snprintf(text, sizeof(text), "%7.1f Byte/s", bit_s / 8.0);
    return text;
}

const char* BigValToStr(double big_val) {
    char* name = "?";
#ifdef HAS_NUM_DIAG
    name = (char*)DoubleToStr(big_val);
#endif
    return name;
}

char* BitRateToStr(double bit_s) {
    snprintf(text, sizeof(text), "%s Bit/s", BigValToStr(bit_s));
    return text;
}

char* RfFreqToStr(uint32_t rf_freq) {
    snprintf(text, sizeof(text), "%u Hz=%f MHz", (unsigned int)rf_freq, ((double)rf_freq) / 1000000.0);
    return text;
}

char* ByteToStr(uint8_t byte) {
    snprintf(text, sizeof(text), "0x%02x", byte);
    return text;
}

const char* U8DecToStr(const void* const data) {
    if(data) {
        uint8_t* byte = (uint8_t*)data;
        snprintf(text, sizeof(text), "%d", (uint8_t)*byte);
    }
    return text;
}

const char* U8ToStr(const void* const data) {
    if(data) {
        uint8_t* byte = (uint8_t*)data;
        snprintf(text, sizeof(text), "0x%02x", (uint8_t)*byte);
    }
    return text;
}

const char* U16ToStr(const void* const data) {
    if(data) {
        uint16_t* word = (uint16_t*)data;
        snprintf(text, sizeof(text), "0x%04x", (uint16_t)*word);
    }
    return text;
}

const char* U32ToStr(const void* const data) {
    if(data) {
        uint32_t* word = (uint32_t*)data;
        snprintf(text, sizeof(text), "0x%08x", (uint32_t)*word);
    }
    return text;
}

const char* U16DecToStr(const void* const data) {
    if(data) {
        uint16_t* dword = (uint16_t*)data;
        snprintf(text, sizeof(text), "%u", (uint16_t)*dword);
    }
    return text;
}

const char* U32DecToStr(const void* const data) {
    if(data) {
        uint32_t* dword = (uint32_t*)data;
        snprintf(text, sizeof(text), "%u", (uint32_t)*dword);
    }
    return text;
}

const char* BitToAsterisk(const uint8_t bit) {
    const char* name = "_";
    if(bit) {
        name = "*";
    }
    return name;
}

#define COMMON_MASK_4BIT ((uint32_t)0x0000000FU)
static const char hex2asciiLUT[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};
bool hex2ascii(const uint8_t* const in_hex, uint32_t hex_len, uint8_t* out_ascii, uint32_t ascii_len) {
    bool res = false;
    if(in_hex && out_ascii && ((2 * hex_len + 1) <= ascii_len) && (0 < hex_len)) {
        res = true;
        uint32_t i = 0;
        uint32_t j = 0;
        for(i = 0; i < hex_len; i++) {
            out_ascii[j++] = hex2asciiLUT[COMMON_MASK_4BIT & (in_hex[i] >> 4)];
            out_ascii[j++] = hex2asciiLUT[COMMON_MASK_4BIT & (in_hex[i])];
        }
        out_ascii[j] = 0x00;
    }
    return res;
}

const char* ResToStr(bool res) {
    const char* name = "?";
    switch((uint32_t)res) {
    case false:
        name = "Err";
        break;
    case true:
        name = "Ok";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* OnOffToStr(uint8_t status) {
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

const char* OkToStr(bool status) {
    const char* name = "?";
    switch(status) {
    case false:
        name = "Err";
        break;
    case true:
        name = "Ok";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* YesNoToStr(uint8_t status) {
    const char* name = "?";
    switch(status) {
    case 0:
        name = "No";
        break;
    case 1:
        name = "Yes";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

char* uint2str(uint32_t val) {
    snprintf(text, sizeof(text), "%u", (unsigned int)val);
    return text;
}

const char* u32valToStr(uint32_t val) {
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

#ifdef HAS_LD_SCRIPT
extern void __text_start__, __text_end__;
extern void __data_start__, __data_end__;
extern void __bss_start__, __bss_end__;
extern void ITCM_FuncStart, ITCM_FuncEnd;
extern void __RamFunc_start__, __RamFunc_end__;
#endif

#ifdef HAS_PROCCESS_SECTOR

static const ProccessSectorInfo_t ProccessSectorInfo[] = {
#ifdef HAS_LD_SCRIPT
    {
        .valid = true,
        .start = &__text_start__,
        .end = &__text_end__,
        .name = "text",
    },
    {
        .valid = true,
        .start = &__data_start__,
        .end = &__data_end__,
        .name = "data",
    },
    {
        .valid = true,
        .start = &__bss_start__,
        .end = &__bss_end__,
        .name = "BSS",
    },
#ifdef HAS_RAM_FUNCTION
    {
        .valid = true,
        .start = &ITCM_FuncStart,
        .end = &ITCM_FuncEnd,
        .name = "ITCM_Func",
    },
    {
        .valid = true,
        .start = &__RamFunc_start__,
        .end = &__RamFunc_end__,
        .name = "RamFunc",
    },
#endif
#endif
};
#endif

#ifdef HAS_PROCCESS_SECTOR
static uint32_t proccess_sector_get_cnt(void) { return ARRAY_SIZE(ProccessSectorInfo); }
#endif

bool common_diag(void) {
    bool res = false;
#ifdef HAS_PROCCESS_SECTOR
    uint32_t cnt = 0;
    static const table_col_t cols[] = {
        {5, "Num"}, {12, "start"}, {12, "end"}, {8, "size"}, {11, "name"},
    };
    // float period_max = 0.0f;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    cnt = proccess_sector_get_cnt();
    uint8_t i = 0;
    for(i = 0; i < cnt; i++) {
        uint32_t size = ProccessSectorInfo[i].end - ProccessSectorInfo[i].start;

        char log_line[150] = {0};
        strcpy(log_line, TSEP);

        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, ProccessSectorInfo[i].start);
        snprintf(log_line, sizeof(log_line), "%s 0x%08x " TSEP, log_line, ProccessSectorInfo[i].end);
        snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, size);
        snprintf(log_line, sizeof(log_line), "%s %9s " TSEP, log_line, ProccessSectorInfo[i].name);

        cli_printf("%s" CRLF, log_line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
#endif
    return res;
}

const char* ProgressRealToStr(float cur, float total) {
    if(cur <= total) {
        uint32_t progress_x100 = (uint32_t)((10000.0 * cur) / total);
        uint32_t units = progress_x100 / 100;
        uint32_t fraq = progress_x100 % 100;
        // snprintf(text,sizeof(text),"\r %u/%u,%6.2f %%", cur, total, progress);
        snprintf(text, sizeof(text), "%u.%u %%", units, fraq);
    }
    return text;
}

const char* ProgressFloatToStr(float cur, float total) {
    if(cur <= total) {
        uint32_t progress_x100 = (uint32_t)((10000.0 * cur) / total);
        uint32_t units = progress_x100 / 100;
        uint32_t fraq = progress_x100 % 100;
        snprintf(text, sizeof(text), "%u.%u %%", units, fraq);
    }
    return text;
}

const char* ProgressToStr(uint32_t cur, uint32_t total) {
    char* out_text = "?";
    if(cur <= total) {
        out_text = (char*)ProgressRealToStr((float)cur, (float)total);
    }
    return out_text;
}

bool print_progress(uint32_t cur, uint32_t total) {
    bool res = false;
    if(cur <= total) {
        cli_printf("\r%s", ProgressToStr(cur, total));
        res = true;
    }
    return res;
}

float diag_progress_log(uint32_t cur, uint32_t total, uint32_t parts) {
    float progress_pp = 0.0;
    if(cur <= total) {
        progress_pp = ((float)(100U * cur)) / ((float)total);
        if(parts < (total / 3)) {
            if(0 == (cur % (total / parts))) {
                cli_printf("\rProgress:%s", ProgressToStr(cur, total));
            }
        }
    }
    return progress_pp;
}

const char* UnsignedBigEndianToStr(const uint8_t* const memory, const uint32_t param_size) {
    static char temp[100] = {0};
    strcpy(temp, "");
    if(memory) {
        switch(param_size) {
        case 1: {
            uint8_t byte = 0;
            memcpy(&byte, memory, 1);
            snprintf(temp, sizeof(temp), "%u", byte);
        } break;

        case 2: {
            uint16_t word = 0;
            memcpy(&word, memory, 2);
            snprintf(temp, sizeof(temp), "%u", reverse_byte_order_uint16(word));
        } break;

        case 4: {
            uint32_t dword = 0;
            memcpy(&dword, memory, 4);
            snprintf(temp, sizeof(temp), "%u", reverse_byte_order_uint32(dword));
        } break;

        case 8: {
            uint64_t qword = 0;
            memcpy(&qword, memory, 8);
            snprintf(temp, sizeof(temp), "%u", reverse_byte_order_uint64(qword));
        } break;
        default:
            break;
        }
    }
    return temp;
}
