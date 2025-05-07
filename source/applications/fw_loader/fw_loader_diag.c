#include "fw_loader_diag.h"

#include <stdio.h>
#include <string.h>

#include "fw_loader.h"
#include "log.h"

bool fw_loader_diag(void) {
    bool res = true;
    return res;
}

const char* FwLoaderConfigToStr(const FwLoaderConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCOM%u,", text, Config->com_num);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Config->bit_rate);
        snprintf(text, sizeof(text), "%sTBFP:%u,", text, Config->tbfp_num);
        snprintf(text, sizeof(text), "%sRate:%u bps,", text, Config->bit_rate);
        snprintf(text, sizeof(text), "%sFile:%s,", text, Config->hex_file_name);
    }
    return text;
}


const char* FwLoaderDiag2Str(const FwLoaderHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sCOM%u,", text, Node->com_num);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Node->bit_rate);
        snprintf(text, sizeof(text), "%sTBFP:%u,", text, Node->tbfp_num);
        snprintf(text, sizeof(text), "%sRate:%u bps,", text, Node->bit_rate);
        snprintf(text, sizeof(text), "%sFile:%s,", text, Node->hex_file_name);
        snprintf(text, sizeof(text), "%sinit:%u,", text, Node->init);
    }
    return text;
}

bool FwLoaderDiag(const FwLoaderHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(FW_LOADER, "%s", FwLoaderDiag2Str(Node));
        res = true;
    }
    return res;
}
