#include "acc_diag.h"

#include "acc_custom_diag.h"
#include "acc_mcal.h"
#include "common_diag.h"
#include "debugger.h"
#include "diag_inc.h"
#include "log.h"

const char* AccConfigToStr(const AccConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* AccNodeToStr(const AccHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool acc_diag(void) {
    bool res = false;
    return res;
}

bool acc_raw_reg_diag(uint8_t num) {
    bool res = false;
    const AccInfo_t* Info = AccGetInfo(num);
    if(Info) {
        LOG_INFO(SYS, "ACC%u,Base:0x%p", num, Info->ACCx);
        uint32_t reg_cnt = acc_reg_cnt();
        if(Info->ACCx) {
            res = debug_raw_reg_diag(SYS, (uint32_t)Info->ACCx, AccReg, reg_cnt);
        }
    }

    return res;
}
