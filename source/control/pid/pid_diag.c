#include "pid_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "pid.h"
#include "storage_diag.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_GPIO
#include "gpio_diag.h"
#endif



const char* PidNodeManualToStr(const PidHandle_t* const Node) {
    static char temp[250] = "";
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sManual:%u,", temp, Node->manual);
        snprintf(temp, sizeof(temp), "%sOut:%5.3f,", temp, Node->out);
        snprintf(temp, sizeof(temp), "%sErr:%5.2f,", temp, Node->error);
        snprintf(temp, sizeof(temp), "%sSumErr:%5.2f,", temp, Node->error_sum);
        snprintf(temp, sizeof(temp), "%sDiffErr:%5.2f,", temp, Node->error_diff);
    }

    return temp;
}

const char* PidNodeToStr(const PidHandle_t* const Node) {
    static char temp[250] = "";
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sN%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sDiffErr:%5.2f,", temp, Node->error_diff);
        snprintf(temp, sizeof(temp), "%sOut:%5.2f,", temp, Node->out);
        //snprintf(temp, sizeof(temp), "%sRead:%5.2f,", temp, Node->read);
        snprintf(temp, sizeof(temp), "%sSumErr:%5.1f,", temp, Node->error_sum);
        snprintf(temp, sizeof(temp), "%sP:%5.4f,", temp, Node->p);
        snprintf(temp, sizeof(temp), "%sI:%5.4f,", temp, Node->i);
        snprintf(temp, sizeof(temp), "%sD:%5.4f,,", temp, Node->d);
        snprintf(temp, sizeof(temp), "%sTrg:%5.2f->", temp, Node->last_target);
        snprintf(temp, sizeof(temp), "%s%5.2f,", temp, Node->target);
        snprintf(temp, sizeof(temp), "%sErr:%5.2f,", temp, Node->error);
        snprintf(temp, sizeof(temp), "%sshift:%5.2f,", temp, Node->shift);
        snprintf(temp, sizeof(temp), "%sd_sum:%5.2f,", temp, Node->d_sum);
    }
    return temp;
}

const char* PidConfigToStr(const PidConfig_t* const Config) {
    static char temp[150] = "";
    strcpy(temp, "");
    if(Config) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sADC:%u,", temp, Config->adc_channel_num);
        snprintf(temp, sizeof(temp), "%sPWM:%u,", temp, Config->pwm_dac_num);
        snprintf(temp, sizeof(temp), "%sPeriod:%f s,", temp, Config->period_s);
        snprintf(temp, sizeof(temp), "%sP:%f,", temp, Config->p);
        snprintf(temp, sizeof(temp), "%sI:%f,", temp, Config->i);
        snprintf(temp, sizeof(temp), "%sD:%f,", temp, Config->d);
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
        snprintf(temp, sizeof(temp), "%sUnits:%s", temp, StorageUnitsToStr(Config->units));
    }

    return temp;
}

bool pid_diag(char* key_word1, char* key_word2) {
    bool res = false;
    replace_char(key_word1, '_', ' ');
    replace_char(key_word2, '_', ' ');
    uint32_t cnt = pid_get_cnt();
    LOG_INFO(PID, "Cnt:%u", cnt);
    static const table_col_t cols[] = {
        {15, "temp"}, {5, "Num"}, {9, "target"},  {9, "read"},     {10, "out"}, {9, "P"},  {9, "I"},
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
