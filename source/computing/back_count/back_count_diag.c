#include "back_count_diag.h"

#include "back_count_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* BackCountConfigToStr(const BackCountConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sCnt:%u,", text, Config->count);
        snprintf(text, sizeof(text), "%sTimeOut:%u ms,", text, Config->time_out_ms);
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* BackCountNodeToStr(const BackCountHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool back_count_diag_one(uint8_t num) {
    bool res = false;
    const BackCountConfig_t *Config = BackCountGetConfig(num);
    if(Config) {
        LOG_INFO(BACK_COUNT, "%s", BackCountConfigToStr(Config));
        BackCountHandle_t *Node = BackCountGetNode(num);
        if(Node) {
            LOG_INFO(BACK_COUNT, "%s", BackCountNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool back_count_diag(void) {
    bool res = false;
    res = back_count_diag_one(1);
    return res;
}


bool back_count_raw_reg_diag(uint8_t num) {
    bool res = false;
    BackCountHandle_t *Node = BackCountGetNode(num);
    if(Node){
        res = true;
    }
    return res;
}
