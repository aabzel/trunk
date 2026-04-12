#include "clock_diag.h"

#include <stdio.h>
#include <string.h>

#include "clock_mcal.h"
#include "log.h"
#include "num_to_str.h"
#include "shared_array.h"

const char* ClkSrcToStr(ClockSource_t src) {
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

const char* ClockMuxToStr(const ClockMux_t clock_mux) {
    const char* name = "?";
    switch(clock_mux) {
    case CLOCK_MUX_INTERNAL_RC_FAST:
        name = "InternalRcFast";
        break;
    case CLOCK_MUX_INTERNAL_RC_SLOW:
        name = "InternalRcSlow";
        break;
    case CLOCK_MUX_PLL:
        name = "PLL";
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

const char* ClockConfigToStr(const ClockConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sConfig:%08p,", text, Config);
        snprintf(text, sizeof(text), "%score_clock:%u Hz,", text, Config->core_clock_hz);
        snprintf(text, sizeof(text), "%sIrqPri:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%shf_source:%u,", text, Config->hf_source);
        snprintf(text, sizeof(text), "%slf_source:%u,", text, Config->lf_source);
        snprintf(text, sizeof(text), "%score_source:%u,", text, Config->core_source);
        snprintf(text, sizeof(text), "%spll0:%u Hz,", text, Config->pll0);
        snprintf(text, sizeof(text), "%spll1:%u Hz", text, Config->pll1);
    }
    return text;
}

bool clock_diag(void) {
    bool res = false;
    LOG_WARNING(SYS, "%s", ClockConfigToStr(&ClockConfig));
    res = true;
    return res;
}
