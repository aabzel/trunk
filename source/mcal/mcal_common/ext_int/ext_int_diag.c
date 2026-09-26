#include "ext_int_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "ext_int_mcal.h"
#include "gpio_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "table_utils.h"
#include "writer_config.h"


const char* ExtIntDropToStr(const PinIntDrop_t drop) {
    const char* name = "?";
    switch(drop) {
        case PIN_INT_DROP_FALLING:     name = "Fall";        break;
        case PIN_INT_DROP_RISING:      name = "Rise";        break;
        default:  name = "?";    break;
    }
    return name;
}

const char* ExtIntEdgeToStr(const PinIntEdge_t code) {
    const char* name = "?";
    switch(code) {
        case PIN_INT_EDGE_NONE:        name = "None";        break;
        case PIN_INT_EDGE_FALLING:     name = "Fall";        break;
        case PIN_INT_EDGE_RISING:      name = "Rise";        break;
        case PIN_INT_EDGE_BOTH:        name = "Both";        break;
        default:  name = "?";    break;
    }
    return name;
}

const char* ExtIntNodeToStr(const ExtIntHandle_t* const Node) {
    static char lText[180]={0};
    strcpy(lText,"");
    if(Node) {
        sprintf(lText, "N:%u,", Node->num);
        snprintf(lText, sizeof(lText), "%sITcnt:%u,", lText, Node->it_cnt);
        snprintf(lText, sizeof(lText), "%sRcnt:%u,", lText, Node->rising_cnt);
        snprintf(lText, sizeof(lText), "%sFcnt:%u,", lText, Node->falling_cnt);
        snprintf(lText, sizeof(lText), "%s%s,", lText, Node->name);
        snprintf(lText, sizeof(lText), "%sPad:%s,", lText, GpioPadToStr(Node->Pad));
        // snprintf(text, sizeof(text), "%sBcnt:%u,", lText, Node->both_cnt);
    }
    return lText;
}

const char* ExtIntEventToStr(const ExtIntEvent_t *const Event,   ExtIntHandle_t *pNode){
    static char lText[80]={0};
    strcpy(lText,"");
    if(Event) {
        //int64_t diff_us_s64 =((int64_t) Event->timestamp_us)-((int64_t)pNode->prev_event_time_us);
        int32_t diff_us_s32 =((int32_t) Event->timestamp_us)-((int32_t)pNode->prev_event_time_us);
        //int32_t diff_us_s32 =(int32_t) diff_us_s64;
        snprintf(lText, sizeof(lText), "Ev:%s,", ExtIntDropToStr(Event->drop));
        snprintf(lText, sizeof(lText), "%sPrevTS:%u us,", lText, pNode->prev_event_time_us);
        snprintf(lText, sizeof(lText), "%sTS:%u us,", lText, Event->timestamp_us);
        snprintf(lText, sizeof(lText), "%sDiff:%d us", lText, diff_us_s32);
    }
    return lText;
}

const char* ExtIntEventToStr1(const ExtIntEvent_t* const pEvent) {
    static char lText[80]={0};
    if(pEvent) {
        strcpy(lText,"");
        snprintf(lText, sizeof(lText), "%sTS:%u us,", lText, pEvent->timestamp_us);
        snprintf(lText, sizeof(lText), "Ev:%s", ExtIntDropToStr(pEvent->drop));
    }
    return lText;
}

const char* ExtIntConfigToStr(const ExtIntConfig_t* const Config) {
    strcpy(text,"");
    if(Config) {
        sprintf(text, "N:%u,", Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sPad:%s,", text, GpioPadToStr(Config->Pad));
        snprintf(text, sizeof(text), "%sEdge:%s,", text, ExtIntEdgeToStr(Config->edge));
        snprintf(text, sizeof(text), "%sCbRising:%p,", text, Config->CallBackRising);
        snprintf(text, sizeof(text), "%sCbFalling:%p,", text, Config->CallBackFalling);
        snprintf(text, sizeof(text), "%sPri:%u,", text, Config->irq_priority);
    }
    return text;
}

bool ExtIntDiagConfig(const ExtIntConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(EXT_INT, "%s", ExtIntConfigToStr(Config));
        res = true;
    }
    return res;
}

bool ext_int_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {5, "Num"}, {11, "name"}, {6, "Pad"},
        {6, "EdgeC"},
        {6, "EdgeE"},
        {4, "LL"}, {8, "IT"}, {8, "Rise"}, {8, "fall"}, {8, "Both"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < EXT_INT_COUNT; num++) {
        ExtIntHandle_t* Node = ExtIntGetNode(num);
        if(Node) {
            GpioLogicLevel_t ll= gpio_get_state_short(Node->Pad);

            char temp_str[120] = {0};
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Node->name);
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, GpioPadToStr(Node->Pad));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, ExtIntEdgeToStr(Node->edge));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, ExtIntEdgeToStr(Node->edge_effective));
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, ll);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->it_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->rising_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->falling_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->both_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s", temp_str);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
