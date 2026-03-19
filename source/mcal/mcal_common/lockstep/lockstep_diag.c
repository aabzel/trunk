#include "lockstep_diag.h"

#include <stdio.h>
#include <string.h>

#include "lockstep_mcal.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* LockStepConfigToStr(const LockStepConfig_t* const Config) {
    if(Config) {
        sprintf(text, "N:%u,", Config->num);
        snprintf(text, sizeof(text), "%sName:%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sITon:%u", text, Config->interrupt_on);
    }

    return text;
}

bool LockStepDiagConfig(const LockStepConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LOCKSTEP, "%s", LockStepConfigToStr(Config));
    }

    return res;
}

static bool lockstep_diag_int_ll(const LockStepHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(LOCKSTEP, "ISR:");
        LOG_INFO(LOCKSTEP, "isITon:%u", Node->interrupt_on);
        LOG_INFO(LOCKSTEP, "it_done:%u", Node->it_done);
        LOG_INFO(LOCKSTEP, "itCnt:%u", Node->it_cnt);
        res = true;
    }
    return res;
}

bool lockstep_diag_one(uint32_t num) {
    bool res = false;
    LockStepHandle_t* Node = LockStepGetNode(num);
    if(Node) {
        LOG_WARNING(LOCKSTEP, "LockStepHandle_t:%u", num);
        LOG_INFO(LOCKSTEP, "N:%u", Node->num);
        LOG_INFO(LOCKSTEP, "spin:%u", Node->spin);
        LOG_INFO(LOCKSTEP, "init:%u", Node->init);

        lockstep_diag_int_ll(Node);
        LOG_INFO(LOCKSTEP, "Name:%s", Node->name);
        LOG_INFO(LOCKSTEP, "valid:%u", Node->valid);
#ifdef HAS_LOCKSTEP_CUSTOM_DIAG
        res = lockstep_diag_custom_one(num);
#endif
        res = true;
    }
    return res;
}

bool lockstep_diag(void) {
    bool res = false;
    uint8_t num = 0;
    uint32_t cnt = lockstep_get_cnt();
    static const table_col_t cols[] = {
        {5, "No"},
        {11, "name"},
        {5, "init"},
        {10, "spin"},
    };
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num <= cnt; num++) {
        LockStepHandle_t* Node = LockStepGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %9s " TSEP, temp_str, Node->name);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, Node->init);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, Node->spin);
            snprintf(temp_str, sizeof(temp_str), "%s" TSEP, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
