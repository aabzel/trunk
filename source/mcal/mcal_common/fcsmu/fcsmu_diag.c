#include "fcsmu_diag.h"

#include <stdio.h>
#include <string.h>

#include "fcsmu_mcal.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* FcsmuConfigToStr(const FcsmuConfig_t* const Config) {
    if(Config) {
        sprintf(text, "FCSMU%u", Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }

    return text;
}

bool FcsmuDiagConfig(const FcsmuConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_FCSMU, "%s", FcsmuConfigToStr(Config));
    }

    return res;
}

bool fcsmu_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {5, "No"},
        {10, "spin"},
        {10, "name"},
    };
    char temp[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = 0;
    cnt = fcsmu_get_cnt();
    for(num = 0; num < cnt; num++) {
        FcsmuHandle_t* Node = FcsmuGetNode(num);
        if(Node) {
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %8u " TSEP, temp, Node->spin);
            snprintf(temp, sizeof(temp), "%s %8s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s" CRLF, temp);
            cli_printf("%s" CRLF, temp);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
