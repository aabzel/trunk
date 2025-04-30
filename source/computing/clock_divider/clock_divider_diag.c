#include "clock_divider_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"

const char* ClockDividerConfigToStr(const ClockDividerConfig_t* const Config) {
    static char text[250] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->divider);
        snprintf(text, sizeof(text), "%sSmTg:%u,", text, Config->schmitt_trigger_num);
        snprintf(text, sizeof(text), "%sAmp:%f,", text, Config->amp);
    }
    return text;
}

const char* ClockDividerNodeToStr(const ClockDividerHandle_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sS:%5u,", text, Node->sample_cnt);
        snprintf(text, sizeof(text), "%sOut:%f,", text, Node->cur_out);
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->divider);
        snprintf(text, sizeof(text), "%sAmp:%f,", text, Node->amp);
        snprintf(text, sizeof(text), "%sSmTg:%u,", text, Node->schmitt_trigger_num);
    }
    return text;
}

bool clock_divider_diag(uint8_t num) { return false; }
