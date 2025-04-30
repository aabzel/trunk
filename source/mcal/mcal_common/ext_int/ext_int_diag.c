#include "ext_int_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "ext_int_mcal.h"
#include "gpio_diag.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* ExtIntEdgeToStr(PinIntEdge_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case PIN_INT_EDGE_NONE:
        name = "None";
        break;
    case PIN_INT_EDGE_FALLING:
        name = "Fall";
        break;
    case PIN_INT_EDGE_RISING:
        name = "Rise";
        break;
    case PIN_INT_EDGE_BOTH:
        name = "Both";
        break;
    }
    return name;
}

const char* ExtIntConfigToStr(const ExtIntConfig_t* const Config) {
    static char text[200] = "";
    if(Config) {
        sprintf(text, "N:%u", Config->num);
        snprintf(text, sizeof(text), "%sEdge:%s,", text, ExtIntEdgeToStr(Config->edge));
        snprintf(text, sizeof(text), "%sPad:%s,", text, GpioPad2Str(Config->Pad.byte));
        snprintf(text, sizeof(text), "%sInt:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%sPri:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }

    return text;
}

bool ExtIntDiagConfig(const ExtIntConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(EXT_INT, "%s", ExtIntConfigToStr(Config));
    }

    return res;
}

bool ext_int_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "Num"},  {5, "Pad"},  {6, "Edge"}, {8, "IT"},
                                       {8, "Rise"}, {8, "fall"}, {8, "Both"}, {6, "name"}};
    char temp_str[120] = {0};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < EXT_INT_COUNT; num++) {
        ExtIntHandle_t* Node = ExtIntGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, GpioPadToStr(Node->Pad));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, ExtIntEdgeToStr(Node->edge));
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->it_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->rising_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->falling_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->both_cnt);
            const ExtIntConfig_t* Config = ExtIntGetConfig(num);
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
