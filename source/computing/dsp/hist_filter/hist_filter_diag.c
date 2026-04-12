#include "hist_filter_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "schmitt_trigger_diag.h"
#include "log.h"

const char* HistFilterConfigToStr(const HistFilterConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sTG0:%s,", text, SchmittTriggerShortConfigToStr(&Config->SchmittTriggerShortConfig[0]));
        snprintf(text, sizeof(text), "%sTG1:%s,", text, SchmittTriggerShortConfigToStr(&Config->SchmittTriggerShortConfig[1]));
        snprintf(text, sizeof(text), "%sTG2:%s,", text, SchmittTriggerShortConfigToStr(&Config->SchmittTriggerShortConfig[2]));
        snprintf(text, sizeof(text), "%sTG3:%s,", text, SchmittTriggerShortConfigToStr(&Config->SchmittTriggerShortConfig[3]));
    }
    return text;
}


const char* HistFilterNodeToStr(const HistFilterHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool hist_filter_diag(void) {
    bool res = false;
    return res;
}

bool hist_filter_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
