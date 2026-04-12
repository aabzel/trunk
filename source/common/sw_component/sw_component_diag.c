#include "sw_component_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* SwComponentConfigToStr(const SwComponentConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* SwComponentNodeToStr(const SwComponentHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool sw_component_diag(void) {
    bool res = false;
    return res;
}

bool sw_component_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
