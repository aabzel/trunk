#include "running_line_diag.h"

#include <stdio.h>
#include <string.h>

#include "running_line.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

static char text[250] = "";

const char* RunningLineConfigToStr(const RunningLineConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sText:%p,", text, Config->Text);
        snprintf(text, sizeof(text), "%sSize:%u,", text, Config->size);
        snprintf(text, sizeof(text), "%sPeriod:%u ms,", text, Config->duration_ms);
    }
    return text;
}

const char* RunningLineNodeToStr(const RunningLineHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sText:[%s],", text, running_line_get_text(Node->num));
        snprintf(text, sizeof(text), "%sLen:%u,", text, Node->size - Node->i_start);
        snprintf(text, sizeof(text), "%sPeriod:%u ms,", text, Node->duration_ms);
    }
    return text;
}

bool running_line_diag(void) {
    bool res = false;
    uint16_t num = 1;
    static const table_col_t cols[] = {
        {5, "No"}, {6, "Start"}, {6, "size"}, {6, "len"}, {6, "Period"}, {8, "next"}, {16, "Line"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    char line[350] = "";
    uint16_t i = 0;
    uint32_t cnt = running_line_get_cnt();
    for(i = 0; i <= cnt; i++) {
        RunningLineHandle_t* Node = RunningLineGetNode(i);
        if(Node) {
            uint32_t len = strlen(running_line_get_text(Node->num));
            strcpy(line, TSEP);
            snprintf(line, sizeof(line), "%s %3u " TSEP, line, Node->num);
            snprintf(line, sizeof(line), "%s %4u " TSEP, line, Node->i_start);
            snprintf(line, sizeof(line), "%s %4u " TSEP, line, Node->size);
            snprintf(line, sizeof(line), "%s %4u " TSEP, line, len);
            snprintf(line, sizeof(line), "%s %4u " TSEP, line, Node->duration_ms);
            snprintf(line, sizeof(line), "%s %6u " TSEP, line, Node->next_update_time_ms);
            snprintf(line, sizeof(line), "%s %s " TSEP, line, running_line_get_text(Node->num));
            cli_printf("%s", line);
            cli_printf(CRLF);
            num++;
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
