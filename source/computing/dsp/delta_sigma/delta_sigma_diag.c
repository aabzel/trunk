#include "delta_sigma_diag.h"

#include <stdio.h>
#include <string.h>

#include "delta_sigma.h"
#include "log.h"
#include "num_to_str.h"

const char* DeltaSigmaConfigToStr(const DeltaSigmaConfig_t* const Config) {
    static char lText[250] = "";
    if(Config) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sN:%u,", lText, Config->num);
        snprintf(lText, sizeof(lText), "%sT:%f V,", lText, Config->target);
        snprintf(lText, sizeof(lText), "%sSamRate:%u Hz,", lText, Config->sample_frequency_hz);
    }
    return lText;
}

const char* DeltaSigmaNodeToStr(const DeltaSigmaHandle_t* const Node) {
    static char lText[350] = "";
    if(Node) {
        strcpy(lText, "");
        snprintf(lText, sizeof(lText), "%sS:%5u,", lText, Node->sample_cnt);
        snprintf(lText, sizeof(lText), "%sT:%9.6f s,", lText, Node->up_time_s);
        snprintf(lText, sizeof(lText), "%sTar:%9.6f V,", lText, Node->target);
        snprintf(lText, sizeof(lText), "%sErr:%9.6f V,", lText, Node->error);
        snprintf(lText, sizeof(lText), "%sSum:%9.6f V,", lText, Node->sum_error);
        snprintf(lText, sizeof(lText), "%sPDM:%d,", lText, Node->pdm);
        snprintf(lText, sizeof(lText), "%sDAC:%9.6f V,", lText, Node->dac_out);
    }
    return lText;
}

bool delta_sigma_diag(uint8_t num) {
    bool res = false;
    DeltaSigmaHandle_t* Node = DeltaSigmaGetNode(num);
    if(Node) {
        LOG_INFO(DELTA_SIGMA, "%s", DeltaSigmaNodeToStr(Node));
        res = true;
    }
    return res;
}
