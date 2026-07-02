#include "mpu_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "debugger.h"
#include "log.h"
#include "mcal_types.h"
#include "mpu_mcal.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

const char* MpuInfoToStr(const MpuInfo_t* const Info) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(Info) {
        sprintf(text, "MPU%u,", Info->num);
        snprintf(text, sizeof(text), "%sMPUx:0x%p,", text, Info->MPUx);
        snprintf(text, sizeof(text), "%sIrq:%d,", text, Info->irq_n);
    }
    return text;
}

const char* MpuRegionSizeInfoToStr(const MpuRegionSizeInfo_t* const RegionInfo) {
    memset(text, 0, sizeof(text));
    strcpy(text, "");
    if(RegionInfo) {
        snprintf(text, sizeof(text), "%scode:0x%08X=", text, RegionInfo->code);
        snprintf(text, sizeof(text), "%sSize:%u,", text, RegionInfo->size);
    }
    return text;
}

bool mpu_diag_low_level(uint8_t num, const char* const keyword) {
    bool res = false;
    uint8_t i = 0;
    cli_printf(CRLF);
    static const table_col_t cols[] = {
        {5, "No"},
        {5, "En"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(i = 0; i < 1; i++) {
        MpuHandle_t* Node = MpuGetNode(i);
        if(Node) {

            char temp[120] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s", temp);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
