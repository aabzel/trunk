#include "echo_effect_diag.h"

#include <stdio.h>
#include <string.h>

#include "echo_effect.h"
#include "common_diag.h"
#include "circular_buffer_diag.h"
#include "num_to_str.h"
#include "log.h"

const char* EchoEffectConfigToStr(const EchoEffectConfig_t* const Config){
    static char text[250] = "";
    if(Config){
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%sScale:%f,", text,Config->scale);
        snprintf(text, sizeof(text), "%s%s,", text,Config->name);
        snprintf(text, sizeof(text), "%sSampleCnt:%u,", text,Config->capacity);
        snprintf(text, sizeof(text), "%sMem:%p", text,Config->inArray);
    }
    return text;
}

const char* EchoEffectNodeToStr(const EchoEffectHandle_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sFactor:%u/%u,", text,Node->numerator,Node->denominator);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%s[%s]", text , CircularBufferNodeToStr(&Node->CircularBuffer));
    }
    return text;
}

bool echo_effect_diag(uint8_t num) {
    bool res = false;
    LOG_INFO(ECHO_EFFECT,"Diag,N:%u", num);
    const EchoEffectConfig_t* Config=EchoEffectGetConfig(  num);
    if(Config) {
        LOG_INFO(ECHO_EFFECT,"%s", EchoEffectConfigToStr(Config));
        res = true;
    }

    EchoEffectHandle_t* Node = EchoEffectGetNode(num);
    if(Node) {
        LOG_INFO(ECHO_EFFECT,"%s", EchoEffectNodeToStr(Node));
        res = true;
    }
    return res;
}
