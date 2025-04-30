#include "correlator_diag.h"

#include <stdio.h>
#include <string.h>

#include "correlator.h"
#include "common_diag.h"
#include "circular_buffer_diag.h"
#include "num_to_str.h"
#include "log.h"

const char* CorrelatorConfigToStr(const CorrelatorConfig_t* const Config){
    static char text[250] = "";
    if(Config){
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%ssize:%f,", text,Config->size);
        snprintf(text, sizeof(text), "%s%s,", text,Config->name);
        snprintf(text, sizeof(text), "%sSignalA:%p", text,Config->SignalA);
        snprintf(text, sizeof(text), "%sSignalB:%p", text,Config->SignalB);
    }
    return text;
}


const char* CorrelatorNodeToStr(const CorrelatorHandle_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sA:[%s]", text , CircularBufferNodeToStr(Node->SignalA));
        snprintf(text, sizeof(text), "%sB:[%s]", text , CircularBufferNodeToStr(Node->SignalB));
    }
    return text;
}

bool correlator_diag(uint8_t num) {
    bool res = false;
    LOG_INFO(CORRELATOR,"Diag,N:%u", num);
    const CorrelatorConfig_t* Config=CorrelatorGetConfig(  num);
    if(Config) {
        LOG_INFO(CORRELATOR,"%s", CorrelatorConfigToStr(Config));
        res = true;
    }

    CorrelatorHandle_t* Node = CorrelatorGetNode(num);
    if(Node) {
        LOG_INFO(CORRELATOR,"%s", CorrelatorNodeToStr(Node));
        res = true;
    }
    return res;
}
