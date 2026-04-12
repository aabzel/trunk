#include "sw_sd_card_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* SwSdCardConfigToStr(const SwSdCardConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* SwSdCardNodeToStr(const SwSdCardHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool sw_sd_card_diag(void) {
    bool res = false;
    return res;
}
