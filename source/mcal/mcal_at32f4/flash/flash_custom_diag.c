#include "flash_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "flash_custom_drv.h"
#include "flash_custom_types.h"
#include "flash_mcal.h"
#include "log.h"
#include "log_utils.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool diag_flash_usage(char* keyWord1, char* keyWord2) {
    bool res = false;
    return res;
}

bool diag_flash_prot(char* key_word1, char* key_word2) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {5, "sector"}, {12, "start"}, {8, "size"}, {8, "busy"}, {7, "usage"}, {8, "total"}, {14, "name"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t spare = 0, i = 0;
    uint32_t busy = 0, num = 0;
    uint32_t total = 0;
    uint32_t cnt = flash_get_sector_cnt();
    float usage_pec = 0.0;
    char temp_str[120];

    for(i = 0; i < cnt; i++) {
        strcpy(temp_str, TSEP);
        snprintf(temp_str, sizeof(temp_str), "%s %2u  " TSEP, temp_str, FlashSectorConfig[i].sector);
        snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, (unsigned int)FlashSectorConfig[i].start);
        snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)FlashSectorConfig[i].size);
        total += FlashSectorConfig[i].size;
        res = flash_scan((uint8_t*)FlashSectorConfig[i].start, FlashSectorConfig[i].size, &usage_pec, &spare, &busy);
        if(res) {
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)busy);
            snprintf(temp_str, sizeof(temp_str), "%s %5.2f " TSEP, temp_str, usage_pec);
        }
        snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, (unsigned int)total / 1024);
        snprintf(temp_str, sizeof(temp_str), "%s %12s " TSEP, temp_str, MemContent2Str(FlashSectorConfig[i].content));

        if(is_contain(temp_str, key_word1, key_word2)) {
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

const char* FlashStatusToStr(flash_status_type code) {
    char* name = "?";
    switch(code) {
    case FLASH_OPERATE_BUSY:
        name = "Busy";
        break;
    case FLASH_PROGRAM_ERROR:
        name = "ProgErr";
        break;
    case FLASH_EPP_ERROR:
        name = "EppError";
        break;
    case FLASH_OPERATE_DONE:
        name = "OpDone";
        break;
    case FLASH_OPERATE_TIMEOUT:
        name = "OpTimeOut";
        break;
    }
    return name;
}

bool flash_raw_reg_diag(void) {
    bool res = false;
    const FlashInfo_t* Info = FlashGetInfo(1);
    if(Info) {
        LOG_INFO(LG_FLASH, "LG_FLASH,Base:0x%p", Info->FLASHx);
        cli_printf("RegCnt:%u" CRLF, Info->regCnt);
        res = debug_raw_reg_diag(LG_FLASH, (uint32_t)Info->FLASHx, (Reg32_t*)Info->RegArray, Info->regCnt);
    }
    return res;
}
