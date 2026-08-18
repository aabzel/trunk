#include "gm67_diag.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "gm67_drv.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

const char* Gm67ConfigToStr(const Gm67Config_t* const Config) {
    static char name[80] = "?";
    if(Config) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sNUM:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sUART:%u", name, Config->uart_num);
    }
    return name;
}

bool Gm67DiagConfig(const Gm67Config_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_NOTICE(GM67, "%s", Gm67ConfigToStr(Config));
        res = true;
    }
    return res;
}

bool gm67_diag(void) {
    bool res = false;

    static const table_col_t cols[] = {
        {3, "Num"},
        {8, "Frames"},
        {7, "RxCnt"},
        {8, "i"},
        {8, "RxTime"},
        {5, "New"},
        {5, "Unpr"},
        {8, "RxSize"},
    };
    char line[150] = {0};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t cnt = gm67_get_cnt();
    uint8_t i = 0;
    for(i = 1; i <= cnt; i++) {
        Gm67Handle_t* Node = Gm67GetNode(i);
        if(Node) {
            strcpy(line, TSEP);
            snprintf(line, sizeof(line), "%s %1u " TSEP, line, Node->num);
            snprintf(line, sizeof(line), "%s %6u " TSEP, line, Node->rx_frame_cnt);
            snprintf(line, sizeof(line), "%s %5u " TSEP, line, Node->rx_cnt);
            snprintf(line, sizeof(line), "%s %6u " TSEP, line, Node->i);
            snprintf(line, sizeof(line), "%s %6u " TSEP, line, Node->rx_time_ms);
            snprintf(line, sizeof(line), "%s %3u " TSEP, line, Node->new_frame);
            snprintf(line, sizeof(line), "%s %3u " TSEP, line, Node->unptoc_frame);
            snprintf(line, sizeof(line), "%s %6u " TSEP, line, Node->rx_size);
            cli_printf("%s" CRLF, line);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
