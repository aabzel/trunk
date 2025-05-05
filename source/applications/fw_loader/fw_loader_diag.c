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
    }
    return text;
}

const char* FwLoaderDiag2Str(const FwLoaderHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
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
