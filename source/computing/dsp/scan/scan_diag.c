#include "scan_diag.h"

#include <stdio.h>
#include <string.h>

#include "scan_const.h"

const char* ScanStateToStr(ScanState_t code){
    const char* name="?";
    switch(  code ) {
        case SCAN_STATE_ACC: name="Acc"; break;
        case SCAN_STATE_CAPTURE:  name="Cap";  break;
        default:  name="?";  break;
    }
    return name;
}

const char* ScanInputToStr(ScanInput_t code) {
    const char* name="?";
    switch(  code ) {
        case SCAN_INPUT_DOWN: name="V"; break;
        case SCAN_INPUT_UP: name="^"; break;
        case SCAN_INPUT_TIME_OUT: name="TimeOut"; break;
        default:  name="?";  break;
    }
    return name;
}



const char* ScanActionToStr(ScanAction_t code) {
    const char* name="?";
    switch(  code ) {
        case SCAN_ACTION_NONE: name="None"; break;
        case SCAN_ACTION_CRLF: name="CRLF"; break;

        default:  name="?";  break;
    }
    return name;
}



const char* ScanConfigToStr(const ScanConfig_t* const Config){
    static char text[80] = {0};
    if(Config) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%sFs:%u Hz,", text,Config->sample_freq_hz);
        snprintf(text, sizeof(text), "%sThr:%f,", text,Config->threshold);
        snprintf(text, sizeof(text), "%sTO:%f s,", text,Config->timeout_s);
        snprintf(text, sizeof(text), "%s[%s],", text,Config->name);
    }
    return text;
}



const char* ScanNodeToStr(const ScanHandle_t* const Node){
    static char text[80]={0};
    if(Node){
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Node->num);
        //snprintf(text, sizeof(text), "%sFs:%u Hz,", text,Node->sample_freq_hz);
        snprintf(text, sizeof(text), "%sT:%f s,", text,Node->up_time_s);
        snprintf(text, sizeof(text), "%sV:%f,", text,Node->value_in);
        //snprintf(text, sizeof(text), "%sFile:[%s],", text,Node->name);
        snprintf(text, sizeof(text), "%sState:%s", text,ScanStateToStr(Node->state));
        snprintf(text, sizeof(text), "%sIn:%s", text,ScanInputToStr(Node->input));
        snprintf(text, sizeof(text), "%sA:%s", text,ScanActionToStr(Node->action));
        snprintf(text, sizeof(text), "%sPrevState:%s", text,ScanStateToStr(Node->prev_state));
    }
    return text;
}








