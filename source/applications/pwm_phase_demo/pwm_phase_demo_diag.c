#include "pwm_phase_demo_diag.h"

#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* PwmPhaseDemoConfigToStr(const PwmPhaseDemoConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* PwmPhaseDemoNodeToStr(const PwmPhaseDemoHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool pwm_phase_demo_diag(void) {
    bool res = false;
    return res;
}

bool pwm_phase_demo_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
