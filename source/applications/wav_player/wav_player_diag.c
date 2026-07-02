#include "wav_player_diag.h"

#include "wav_player_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* WavPlayerConfigToStr(const WavPlayerConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* WavPlayerNodeToStr(const WavPlayerHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool wav_player_diag_one(uint8_t num) {
    bool res = false;
    const WavPlayerConfig_t *Config = WavPlayerGetConfig(num);
    if(Config) {
        LOG_INFO(WAV_PLAYER, "%s", WavPlayerConfigToStr(Config));
        WavPlayerHandle_t *Node = WavPlayerGetNode(num);
        if(Node) {
            LOG_INFO(WAV_PLAYER, "%s", WavPlayerNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool wav_player_diag(void) {
    bool res = false;
    res = wav_player_diag_one(1);
    return res;
}


bool wav_player_raw_reg_diag(uint8_t num) {
    bool res = false;
    WavPlayerHandle_t *Node = WavPlayerGetNode(num);
    if(Node){
        res = true;
    }
    return res;
}
