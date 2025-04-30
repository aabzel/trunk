#include "clock_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"

const char* ClkSrc2Str(ClockSource_t src) {
    const char* name = "?";
    switch(src) {
    case CLOCK_SRC_INTERNAL:
        name = "Int";
        break;
    case CLOCK_SRC_EXTERNAL:
        name = "Ext";
        break;
    default:
        break;
    }
    return name;
}

const char* ClockBusToStr(ClockBus_t clock_bus) {
    const char* name = "?";
    switch((uint32_t)clock_bus) {
    case CLOCK_BUS_AHB1:
        name = "AHB1";
        break;
    case CLOCK_BUS_AHB2:
        name = "AHB2";
        break;
    case CLOCK_BUS_APB1:
        name = "APB1";
        break;
    case CLOCK_BUS_APB2:
        name = "APB2";
        break;
    default:
        break;
    }
    return name;
}

const char* ClockSettingToStr(const ClockSetting_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDiv:%u,", text, Node->divider);
        snprintf(text, sizeof(text), "%sPer:%u", text, Node->period);
    }
    return text;
}
