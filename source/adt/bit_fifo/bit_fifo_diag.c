#include "bit_fifo_diag.h"

#include "common_diag.h"
#include "array_diag.h"
#include "diag_inc.h"
#include "log.h"

#ifdef HAS_NUM_DIAG
#include "num_to_str.h"
#endif

const char* BitFifoMemToBitStr(const uint8_t* const data, const uint32_t size) {
    static char lText[200] = { 0 };
    memset(lText, 0, sizeof(lText));
    if(data) {
        if(size) {
            uint32_t i = 0;
            for (i = 0; i < size; i++) {
                uint8_t rev_bits = swap_bits_u8_fast(data[i]);
                snprintf(lText, sizeof(lText), "%s%s", lText, utoa_bin8_plain(rev_bits));
            }
        }
    }
    return lText;
}


const char* BitFifoConfigToStr(const BitFifoConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sMem:%p,", text, Config->buffer);
        snprintf(text, sizeof(text), "%sSZ:%u,", text, Config->size);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* BitFifoNodeToStr(const BitFifoHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sOVF:%u,", text, Node->overflow_cnt);
        snprintf(text, sizeof(text), "%sRD:%u,", text, Node->read_bit);
        snprintf(text, sizeof(text), "%sCap:%u Sam,", text, Node->capacity_bits);
        snprintf(text, sizeof(text), "%sSZ:%u Byte,", text, Node->size);
        snprintf(text, sizeof(text), "%sWR:%u,", text, Node->write_bit);
        snprintf(text, sizeof(text), "%s[%s],", text, BitFifoMemToBitStr(Node->buffer,Node->size));
        //snprintf(text, sizeof(text), "%s[%s],", text, Node->name);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool bit_fifo_diag(void) {
    bool res = false;
    return res;
}

bool bit_fifo_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
