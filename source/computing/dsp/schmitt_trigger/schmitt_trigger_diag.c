#include "schmitt_trigger_diag.h"

#include <stdio.h>
#include <string.h>

#include "schmitt_trigger_const.h"
#include "sensitivity_diag.h"

const char* SchmittTriggerState2Str(SchmittTriggerState_t code) {
    const char* name = "?";
    switch(code) {
    case SCHMITT_TRIGGER_STATE_UP:
        name = "Up";
        break;
    case SCHMITT_TRIGGER_STATE_DOWN:
        name = "Down";
        break;
    default:
        name = "Middle";
        break;
    }
    return name;
}



const char* SchmittTriggerNode2Str(const SchmittTriggerHandle_t* const Node) {
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sUnits:%s,", text, UnitsToStr(Node->units));
        snprintf(text, sizeof(text), "%sTrsld:%7.3f,", text, Node->switching_value);
        snprintf(text, sizeof(text), "%s+/-%7.3f,", text, Node->hysteresis);
        snprintf(text, sizeof(text), "%sVal:%7.3f,", text, Node->value);
        snprintf(text, sizeof(text), "%sSt:%s,", text, SchmittTriggerState2Str(Node->state));
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%s%s,", text, Node->name);
        snprintf(text, sizeof(text), "%sUp:%u,", text, Node->up_handler_cnt);
        snprintf(text, sizeof(text), "%sDown:%u,", text, Node->down_handler_cnt);
    }
    return text;
}


