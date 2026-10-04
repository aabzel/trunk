#include "drv8870_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "drv8870_mcal.h"
#include "log.h"

const char* Drv8870ModeToStr(const Drv8870Mode_t mode) {
    const char* name = "?";
    switch(mode) {
    case DRV8870_MODE_BRAKE:
        name = "Brake";
        break;
    case DRV8870_MODE_FORWARD:
        name = "Forward";
        break;
    case DRV8870_MODE_REVERSE:
        name = "Reverse";
        break;
    case DRV8870_MODE_HI_Z:
        name = "HiZ";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

const char* Drv8870ConfigToStr(const Drv8870Config_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sDuty:%f %%,", text, Config->duty);
        snprintf(text, sizeof(text), "%sPwmFreq:%f Hz,", text, Config->pwm_frequency_hz);
        snprintf(text, sizeof(text), "%sIn1Pwm:%u,", text, Config->in1_pwm_num);
        snprintf(text, sizeof(text), "%sIn2Pwm:%u,", text, Config->in2_pwm_num);
    }
    return text;
}

const char* Drv8870NodeToStr(const Drv8870Handle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sMode:%s,", text, Drv8870ModeToStr(Node->mode));
        snprintf(text, sizeof(text), "%sPwmFreq:%6.1f Hz,", text, Node->pwm_frequency_hz);
        snprintf(text, sizeof(text), "%sDuty:%6.2f %%,", text, Node->duty);
        snprintf(text, sizeof(text), "%sIN1:%u,", text, Node->in1_pwm_num);
        snprintf(text, sizeof(text), "%sIN2:%u,", text, Node->in2_pwm_num);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
    }
    return text;
}

bool drv8870_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"}, {8, "duty"}, {10, "Freq"}, {4, "IN1"}, {4, "IN2"}, {12, "snip"}, {7, "name"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint16_t drv8870_cnt = drv8870_get_cnt();
    uint8_t i = 0;
    for(i = 0; i <= drv8870_cnt; i++) {
        Drv8870Handle_t* Node = Drv8870GetNode(i);
        if(Node) {
            char log_line[150] = {0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, num);
            snprintf(log_line, sizeof(log_line), "%s %6.2f " TSEP, log_line, Node->duty);
            snprintf(log_line, sizeof(log_line), "%s %8.2f " TSEP, log_line, Node->pwm_frequency_hz);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->in1_pwm_num);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->in2_pwm_num);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->spin);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, Node->name);
            cli_printf("%s" CRLF, log_line);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
