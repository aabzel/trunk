#include "nvs_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "flash_mcal.h"
#include "float_diag.h"
#include "log.h"
#include "nvs_mcal.h"
#include "macro_utils.h"
#include "nvs_custom_diag.h"

#ifdef HAS_CRC16
#include "crc16_ccitt.h"
#endif

const char* NvsConfigToStr(const NvsConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sStart:0x%08x", text, Config->start);
        snprintf(text, sizeof(text), "%sSize:%u", text, Config->size);
    }
    return text;
}

const char* NvsNodeToStr(const NvsHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sStart:0x%08x", text, Node->start);
        snprintf(text, sizeof(text), "%sSize:%u", text, Node->size);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool nvs_diag_one(uint8_t num) {
    bool res = false;
    res = nvs_custom_diag_one(num);
#ifdef HAS_CRC16
    uint16_t crc16_data = nvs_calc_crc16(num);
    LOG_INFO(NVS, "NSV%u,CRC16:0x%04X", num, crc16_data);
#endif
    return res;
}

bool nvs_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {3, "No"}, {12, "start"}, {12, "end"}, {8, "size"}, {5, "init"}, {10, "name"}, {10, "Usage"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint16_t nvs_cnt = nvs_get_cnt();
    uint8_t i = 0;
    for(i = 0; i <= nvs_cnt; i++) {
        NvsHandle_t* Node = NvsGetNode(i);
        if(Node) {
            uint32_t end = Node->start + Node->size - 1;

            float usage_pec = 0.0;
            uint32_t spare = 0;
            uint32_t busy = 0;
            res = flash_scan((uint8_t*)Node->start, Node->size, &usage_pec, &spare, &busy, 0xFF);

            char log_line[150] = {0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s 0x%08X " TSEP, log_line, Node->start);
            snprintf(log_line, sizeof(log_line), "%s 0x%08X " TSEP, log_line, end);
            snprintf(log_line, sizeof(log_line), "%s %u " TSEP, log_line, Node->size);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->init);
            snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, Node->name);
            snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, FloatToStr(usage_pec, 4));
            cli_printf("%s" CRLF, log_line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
