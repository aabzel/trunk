#include "decimator_diag.h"

#include <stdio.h>
#include <string.h>

#include "decimator_const.h"

const char* DecimatorStateToStr(DecimatorState_t code){
    const char* name="?";
    switch(  code ) {
        case DECIMATOR_STATE_ONE: name="1"; break;
        case DECIMATOR_STATE_ZERO:  name="0";  break;
        default:  name="?";  break;
    }
    return name;
}

const char* DecimatorConfigToStr(const DecimatorConfig_t* const Config){
    static char text[80] = {0};
    if(Config) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%sSamPerBit:%u Sam,", text,Config->samples_per_bit);
        snprintf(text, sizeof(text), "%s[%s],", text,Config->name);
    }
    return text;
}


const char* DecimatorNodeToStr(const DecimatorHandle_t* const Node){
    static char text[80]={0};
    if(Node){
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Node->num);
        snprintf(text, sizeof(text), "%sSamPerBit:%u sam,", text,Node->samples_per_bit);
        snprintf(text, sizeof(text), "%s[%s],", text,Node->name);
        snprintf(text, sizeof(text), "%sState:%s", text,DecimatorStateToStr(Node->state));
        snprintf(text, sizeof(text), "%sPrevState:%s", text,DecimatorStateToStr(Node->prev_state));
    }
    return text;
}
