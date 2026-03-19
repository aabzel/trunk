#include "erm_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "erm_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

const char* ErmConfigToStr(const ErmConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        sprintf(text, "ERM%u", Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }

    return text;
}

bool ErmDiagConfig(const ErmConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_ERM, "%s", ErmConfigToStr(Config));
    }

    return res;
}

bool erm_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
            {5, "No"},
            {10, "name"}
    };
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < 1; num++) {
        ErmHandle_t* Node = ErmGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

