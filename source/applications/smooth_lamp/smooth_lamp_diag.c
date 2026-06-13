#include "smooth_lamp_diag.h"

#include "smooth_lamp.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"


const char* SmoothLampTypeToStr(SmoothLampType_t code) {
    const char* name = "?";
    switch(code) {
        case SMOOTH_LAPM_TYPE_PWM:        name = "PWM";        break;
        case SMOOTH_LAPM_TYPE_LED:        name = "PwmLED";        break;
        case SMOOTH_LAPM_TYPE_DRV8870:        name = "DRV8870";        break;
        default:        name = "?";        break;
    }
    return name;
}

const char* SmoothLampConfigToStr(const SmoothLampConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sScale:%f,", text, Config->scale);
        snprintf(text, sizeof(text), "%sFreq:%f Hz,", text, Config->pwm_freq_hz);
        snprintf(text, sizeof(text), "%sSam:%f Hz,", text, Config->sample_rate_hz);
        snprintf(text, sizeof(text), "%sdownLim:%f,", text, Config->limit_down);
        snprintf(text, sizeof(text), "%sUpLim:%f,", text, Config->limit_up);
        snprintf(text, sizeof(text), "%sPID:%u,", text, Config->pid_num);
        snprintf(text, sizeof(text), "%sTypeN:%u,", text, Config->type_num);
        snprintf(text, sizeof(text), "%sLampT:%s,", text, SmoothLampTypeToStr(Config->lamp_type));
        snprintf(text, sizeof(text), "%sCmd:%u,", text, Config->cmd);
    }
    return text;
}


const char* SmoothLampNodeToStr(const SmoothLampHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sDuty:%7.3f,", text, Node->signal_out);
        snprintf(text, sizeof(text), "%sCmd:%u,", text, Node->cmd);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sPwmFreq:%f,", text, Node->pwm_freq_hz);
        snprintf(text, sizeof(text), "%sScale:%f,", text, Node->scale);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sLS:%f,", text, Node->logistic_shift_s);
        snprintf(text, sizeof(text), "%s[%f-", text, Node->limit_down);
        snprintf(text, sizeof(text), "%s%f],", text, Node->limit_up);
        snprintf(text, sizeof(text), "%sTime:%llu,", text, Node->up_time_us);
    }
    return text;
}


bool smooth_lamp_diag(void) {
    bool res = false;
    const SmoothLampConfig_t* Config=SmoothLampGetConfig(1);
    if(Config) {
        LOG_INFO(SMOOTH_LAMP,"%s",SmoothLampConfigToStr(Config));
    }

    SmoothLampHandle_t* Node=SmoothLampGetNode(1);
    if(Node) {
        LOG_INFO(SMOOTH_LAMP,"%s",SmoothLampNodeToStr(Node));
    }
    return res;
}
