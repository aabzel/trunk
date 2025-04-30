#include "delta_sigma_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"
#include "log.h"


const char* DeltaSigmaConfigToStr(const DeltaSigmaConfig_t* const Config){
    static char text[250] = "";
    if(Config){
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%sT:%f V,", text,Config->target);
        snprintf(text, sizeof(text), "%sSamRate:%u Hz,", text,Config->sample_frequency_hz);
    }
    return text;
}

const char* DeltaSigmaNodeToStr(const DeltaSigmaHandle_t* const Node) {
    static char text[350] = "";
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sS:%5u,", text,Node->sample_cnt);
        snprintf(text, sizeof(text), "%sT:%9.6f s,", text,Node->up_time_s);
        snprintf(text, sizeof(text), "%sTar:%9.6f V,", text,Node->target);
        snprintf(text, sizeof(text), "%sErr:%9.6f V,", text,Node->error);
        snprintf(text, sizeof(text), "%sSum:%9.6f V,", text,Node->sum_error);
        snprintf(text, sizeof(text), "%sPDM:%d,", text, Node->pdm);
        snprintf(text, sizeof(text), "%sDAC:%9.6f V,", text,Node->dac_out);
    }
    return text;
}


bool delta_sigma_diag(uint8_t num){
	return false;
}
