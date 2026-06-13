#include "encoder_lamp_diag.h"

#include "encoder_lamp_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* EncoderLampConfigToStr(const EncoderLampConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sEncNum:%u,", text, Config->encoder_num);
        snprintf(text, sizeof(text), "%sPwmNum:%u,", text, Config->pwm_num);
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* EncoderLampNodeToStr(const EncoderLampHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sduty:%d,", text, Node->duty);
        snprintf(text, sizeof(text), "%sdutyPrev:%d,", text, Node->duty_prev);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool encoder_lamp_diag_one(uint8_t num) {
    bool res = false;
    const EncoderLampConfig_t *Config = EncoderLampGetConfig(num);
    if(Config) {
        LOG_INFO(ENCODER_LAMP, "%s", EncoderLampConfigToStr(Config));
        EncoderLampHandle_t *Node = EncoderLampGetNode(num);
        if(Node) {
            LOG_INFO(ENCODER_LAMP, "%s", EncoderLampNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool encoder_lamp_diag(void) {
    bool res = false;
    res = encoder_lamp_diag_one(1);
    return res;
}

