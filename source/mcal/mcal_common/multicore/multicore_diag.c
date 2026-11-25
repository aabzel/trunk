#include "multicore_diag.h"

#include <stdio.h>
#include <string.h>

#include "byte_diag.h"
#include "gpio_diag.h"
#include "log.h"
#include "multicore_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

const char* MultiCoresToStr(const ControlCores_t Cores) {
    static char lText[5] = {0};
    memset(lText, 0, sizeof(lText));
    strcpy(lText, "");
    snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(Cores.core0, "0"));
    snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(Cores.core1, "1"));
    snprintf(lText, sizeof(lText), "%s%s", lText, ByteNameToStr(Cores.core2, "2"));
    return lText;
}

const char* MultiCoreConfigToStr(const MultiCoreConfig_t* const Config) {
    if(Config) {
        memset(text, 0, sizeof(text));
        sprintf(text, "MULTICORE%u", Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }

    return text;
}

bool MultiCoreDiagConfig(const MultiCoreConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(MULTICORE, "%s", MultiCoreConfigToStr(Config));
    }

    return res;
}

bool multicore_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"}, {10, "name"}};
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t cnt = 0;
    cnt = multicore_get_cnt();
    for(num = 0; num < cnt; num++) {
        MultiCoreHandle_t* Node = MultiCoreGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            const MultiCoreConfig_t* Config = MultiCoreGetConfig(num);
            if(Config) {
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Config->name);
            }
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
