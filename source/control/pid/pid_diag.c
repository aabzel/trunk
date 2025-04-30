#include "pid_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#ifdef HAS_GPIO
#include "gpio_diag.h"
#endif
#include "log.h"
#include "num_to_str.h"
#include "pid.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool pid_diag(char* key_word1, char* key_word2) {
    bool res = false;
    replace_char(key_word1, '_', ' ');
    replace_char(key_word2, '_', ' ');
    uint32_t cnt = pid_get_cnt();
    LOG_INFO(PID, "Cnt:%u", cnt);
    static const table_col_t cols[] = {
        {15, "name"}, {5, "Num"}, {9, "target"},  {9, "read"},     {10, "out"}, {9, "P"},  {9, "I"},
        {9, "D"},     {9, "err"}, {11, "errSum"}, {11, "errDiff"}, {5, "init"}, {5, "on"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    char line_str[200] = {0};
    uint8_t i = 0;
    for(i = 0; i <= cnt; i++) {
        const PidConfig_t* Config = PidGetConfig(i);
        if(Config) {
            PidHandle_t* Node = PidGetNode(i);
            if(Node) {
                strcpy(line_str, TSEP);
                sprintf(line_str, "%s %13s " TSEP, line_str, Config->name);
                sprintf(line_str, "%s %3u " TSEP, line_str, Node->num);
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->target));
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->read));
                sprintf(line_str, "%s %8s " TSEP, line_str, DoubleToStr(Node->out));
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->p));
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->i));
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->d));
                sprintf(line_str, "%s %7s " TSEP, line_str, DoubleToStr(Node->error));
                sprintf(line_str, "%s %9s " TSEP, line_str, DoubleToStr(Node->error_sum));
                sprintf(line_str, "%s %9s " TSEP, line_str, DoubleToStr(Node->error_diff));
                sprintf(line_str, "%s %3u " TSEP, line_str, Node->init);
                sprintf(line_str, "%s %3u " TSEP, line_str, Node->on);
                res = is_contain(line_str, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, line_str);
                }
            }
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

const char* PidConfigToStr(const PidConfig_t* const Config) {
    static char name[150] = "";
    strcpy(name, "");
    if(Config) {
        snprintf(name, sizeof(name), "%sN:%u,", name, Config->num);
        snprintf(name, sizeof(name), "%sADC:%u,", name, Config->adc_channel_num);
        snprintf(name, sizeof(name), "%sPWM:%u,", name, Config->pwm_dac_num);
        snprintf(name, sizeof(name), "%sPeriod:%llu us,", name, Config->period_us);
        snprintf(name, sizeof(name), "%sP:%f,", name, Config->p);
        snprintf(name, sizeof(name), "%sI:%f,", name, Config->i);
        snprintf(name, sizeof(name), "%sD:%f,", name, Config->d);
        snprintf(name, sizeof(name), "%s%s,", name, Config->name);
        snprintf(name, sizeof(name), "%sUnit:%u", name, Config->unit);
    }

    return name;
}

const char* PidNodeToStr(const PidHandle_t* const Node) {
    static char name[150] = "";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sN:%u,", name, Node->num);
        snprintf(name, sizeof(name), "%sOut:%5.3f,", name, Node->out);
        snprintf(name, sizeof(name), "%sRead:%5.2f,", name, Node->read);
        snprintf(name, sizeof(name), "%sTarget:%5.2f,", name, Node->target);
        snprintf(name, sizeof(name), "%sErr:%5.2f,", name, Node->error);
        snprintf(name, sizeof(name), "%sSumErr:%5.2f,", name, Node->error_sum);
        snprintf(name, sizeof(name), "%sDiffErr:%5.2f,", name, Node->error_diff);
        snprintf(name, sizeof(name), "%sP:%5.2f,", name, Node->p);
        snprintf(name, sizeof(name), "%sI:%5.2f,", name, Node->i);
        snprintf(name, sizeof(name), "%sD:%5.2f,,", name, Node->d);
    }

    return name;
}
