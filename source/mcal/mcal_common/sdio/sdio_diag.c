#include "sdio_diag.h"

#include "common_diag.h"
#include "debugger.h"
#include "diag_inc.h"
#include "log.h"
#include "sdio_custom.h"
#include "sdio_mcal.h"

const char* SdioConfigToStr(const SdioConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sMoveMode:%u,", text, Config->move_mode);
        snprintf(text, sizeof(text), "%sBitRate:%u,", text, Config->bit_rate_hz);
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* SdioNodeToStr(const SdioHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool sdio_diag(void) {
    bool res = false;
    return res;
}

bool sdio_raw_reg_diag(uint8_t num) {
    bool res = false;
    const SdioInfo_t* Info = SdioGetInfo(num);
    if(Info) {
        LOG_INFO(LG_SDIO, "SDIO%u,Base:0x%p", num, Info->SDIOx);
        uint32_t reg_cnt = sdio_reg_cnt();
        res = debug_raw_reg_diag(LG_SDIO, (uint32_t)Info->SDIOx, SdioReg, reg_cnt);
    }

    return res;
}
