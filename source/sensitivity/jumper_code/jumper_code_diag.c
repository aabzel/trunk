#include "jumper_code_diag.h"

#include "jumper_code_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* JumperCodeConfigToStr(const JumperCodeConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* JumperCodeNodeToStr(const JumperCodeHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sCode:%u,", text, Node->code);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool jumper_code_diag_one(uint8_t num) {
    bool res = false;
    const JumperCodeConfig_t *Config = JumperCodeGetConfig(num);
    if(Config) {
        LOG_INFO(JUMPER_CODE, "%s", JumperCodeConfigToStr(Config));
        JumperCodeHandle_t *Node = JumperCodeGetNode(num);
        if(Node) {
            uint32_t code = jumper_code_get(num);
            LOG_INFO(JUMPER_CODE, "%s,Code:%u", JumperCodeNodeToStr(Node),code);
            res = true;
        }
    }
    return res;
}

bool jumper_code_diag(void) {
    bool res = false;
    res = jumper_code_diag_one(1);
    return res;
}

bool jumper_code_raw_reg_diag(uint8_t num) {
    bool res = false;
    JumperCodeHandle_t *Node = JumperCodeGetNode(num);
    if(Node){
        res = true;
    }
    return res;
}
