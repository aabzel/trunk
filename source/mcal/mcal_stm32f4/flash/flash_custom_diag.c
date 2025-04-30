#include "flash_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "flash_custom_types.h"
#include "flash_mcal.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool flash_parse_acr(uint32_t reg_val) {
    bool res = false;
    RegFlashAccessCtrl_t FlashAccessCtrl;
    uint32_t size = sizeof(RegFlashAccessCtrl_t);
    if(4 == size) {
        res = true;
        FlashAccessCtrl.reg_val = reg_val;
        cli_printf(CRLF "latency %u" CRLF, FlashAccessCtrl.latency);
        cli_printf("Prefetch %u" CRLF, FlashAccessCtrl.prften);
        cli_printf("Instruction cache %u" CRLF, FlashAccessCtrl.icen);
        cli_printf("Data cache %u" CRLF, FlashAccessCtrl.dcen);
        cli_printf("Instruction cache reset %u" CRLF, FlashAccessCtrl.icrst);
        cli_printf("Data cache reset %u" CRLF, FlashAccessCtrl.dcrst);
    } else {
        LOG_ERROR(LG_FLASH, "size %u", size);
    }
    return res;
}

bool flash_parse_sr(uint32_t reg_val) {
    bool res = false;
    RegFlashstatus_t Flashstatus;
    uint32_t size = sizeof(RegFlashstatus_t);
    if(4 == size) {
        res = true;
        Flashstatus.reg_val = reg_val;
        cli_printf(CRLF "End of operation %u" CRLF, Flashstatus.eop);
        cli_printf("Operation error %u" CRLF, Flashstatus.operr);
        cli_printf("Write protection error %u" CRLF, Flashstatus.wrperr);
        cli_printf("Programming sequence error %u" CRLF, Flashstatus.pgserr);
        cli_printf("Programming alignment error %u" CRLF, Flashstatus.pgaerr);
        cli_printf("Programming parallelism error %u" CRLF, Flashstatus.pgperr);
        cli_printf("Read Protection Error %u" CRLF, Flashstatus.rderr);
        cli_printf("Busy %u" CRLF, Flashstatus.bsy);
    } else {
        LOG_ERROR(LG_FLASH, "size %u", size);
    }
    return res;
}

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
