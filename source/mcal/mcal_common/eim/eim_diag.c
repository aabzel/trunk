#include "eim_diag.h"

#include "diag_inc.h"
#include "common_diag.h"
#include "eim_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "table_utils.h"
#include "writer_config.h"


const char* EimConfigToStr(const EimConfig_t* const Config) {
    strncpy(text, "", sizeof(text) - 1);
    if(Config) {
        snprintf(text, sizeof(text), "%sEIM_%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sInt:%u,", text, Config->interrupt_on);
    }
    return text;
}

bool EimDiagConfig(const EimConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_EIM, "%s", EimConfigToStr(Config));
        res = true;
    }

    return res;
}

bool eim_diag(void) {
    bool res = false;
    LOG_INFO(LG_EIM, "Cnt:%u", EIM_COUNT);
    static const table_col_t cols[] = {
        {5, "No"},
        {5, "num"},
        {8, "name"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t cnt = 0;
    uint8_t num = 0;
    for(num = 0; num <= EIM_COUNT; num++) {
        EimHandle_t* Node = EimGetNode(num);
        if(Node) {
            char line[200] = {0};
            strcpy(line, TSEP);
            snprintf(line, sizeof(line), "%s %1u   " TSEP, line, Node->num);
            cli_printf(TSEP " %3u ", cnt);
            cli_printf("%s" CRLF, line);
            cnt++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


bool eim_diag_one(uint8_t num) {
    bool res = false;
    return res;
}

