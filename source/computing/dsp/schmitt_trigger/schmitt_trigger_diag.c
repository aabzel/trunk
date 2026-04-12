#include "schmitt_trigger_diag.h"

#include <stdio.h>
#include <string.h>

#include "schmitt_trigger_const.h"
#include "sensitivity_diag.h"

const char* SchmittTriggerStateToStr(SchmittTriggerState_t code) {
    const char* name = "?";
    switch(code) {
    case SCHMITT_TRIGGER_STATE_UP:
        name = "Up";
        break;
    case SCHMITT_TRIGGER_STATE_DOWN:
        name = "Down";
        break;
    default:
        name = "Undef";
        break;
    }
    return name;
}

const char* SchmittTriggerNodeToStr(const SchmittTriggerHandle_t* const Node) {
    static char lText[300] = "?";
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Node->num);
        snprintf(lText, sizeof(lText), "%sSwiVal:%7.3f,", lText, Node->switching_value);
        snprintf(lText, sizeof(lText), "%s+/-%7.3f,", lText, Node->hysteresis);
        snprintf(lText, sizeof(lText), "%sVal:%7.3f,", lText, Node->value);
        snprintf(lText, sizeof(lText), "%sDownVal:%7.3f,", lText, Node->down_val);
        snprintf(lText, sizeof(lText), "%sUpVal:%7.3f,", lText, Node->up_val);
        snprintf(lText, sizeof(lText), "%sSt:%s,", lText, SchmittTriggerStateToStr(Node->state));
        snprintf(lText, sizeof(lText), "%sUpCnt:%u,", lText, Node->up_handler_cnt);
        snprintf(lText, sizeof(lText), "%sDownCnt:%u,", lText, Node->down_handler_cnt);
        snprintf(lText, sizeof(lText), "%sUnits:%s,", lText, UnitsToStr(Node->units));
        snprintf(lText, sizeof(lText), "%sInit:%u,", lText, Node->init);
        snprintf(lText, sizeof(lText), "%s%s,", lText, Node->name);
    }
    return lText;
}


const char* SchmittTriggerShortConfigToStr(const SchmittTriggerShortConfig_t* const Config){
    static char lText[300] = "?";
    if(Config) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sTrsld:%7.3f,", lText, Config->switching_value);
        snprintf(lText, sizeof(lText), "%s+/-%7.3f,", lText, Config->hysteresis);
        snprintf(lText, sizeof(lText), "%sUp:%f,", lText, Config->up_val);
        snprintf(lText, sizeof(lText), "%sDown:%f,", lText, Config->down_val);
    }
    return lText;
}




