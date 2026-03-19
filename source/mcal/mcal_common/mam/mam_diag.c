#include "mam_diag.h"

#include "common_diag.h"
#include "control_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* MamConfigToStr(const MamConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* MamNodeToStr(const MamHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

const char* MamMastersToStr(const MamMaster_t Masters) {
    static char lText[140] = {0};
    strcpy(lText, "");
    if(Masters.core0) {
        snprintf(lText, sizeof(lText), "%sCPU0,", lText);
    }
    if(Masters.core1) {
        snprintf(lText, sizeof(lText), "%sCPU1,", lText);
    }
    if(Masters.core2) {
        snprintf(lText, sizeof(lText), "%sCPU2,", lText);
    }
    if(Masters.enet) {
        snprintf(lText, sizeof(lText), "%sENET,", lText);
    }
    if(Masters.hsm) {
        snprintf(lText, sizeof(lText), "%sHSM,", lText);
    }
    if(Masters.dma0) {
        snprintf(lText, sizeof(lText), "%sDMA0,", lText);
    }
    if(Masters.dma1) {
        snprintf(lText, sizeof(lText), "%sDMA1,", lText);
    }
    return lText;
}

const char* MamDiagRegion(const MamMemoryAccessConfig_t* const Region) {
    if(Region) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Region->num);
        snprintf(text, sizeof(text), "%sMasters:[%s],", text, MamMastersToStr(Region->Masters));
        snprintf(text, sizeof(text), "%sAddr:0x%08X,", text, Region->address);
        snprintf(text, sizeof(text), "%sPerm:%s,", text, ControlPermissionToStr(Region->access));
        snprintf(text, sizeof(text), "%s%s,", text, Region->name);
    }
    return text;
}
