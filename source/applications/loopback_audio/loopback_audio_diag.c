#include "loopback_audio_diag.h"

#include "loopback_audio_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* LoopbackAudioConfigToStr(const LoopbackAudioConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sREC%u,", text, Config->rec_num);
        snprintf(text, sizeof(text), "%sPLAY%u,", text, Config->player_num);
        snprintf(text, sizeof(text), "%sLED%u,", text, Config->led_num);
        snprintf(text, sizeof(text), "%sRxMem:%p,", text, Config->RxSampleArray);
        snprintf(text, sizeof(text), "%sTxMem:%p,", text, Config->TxSampleArray);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sSamCnt:%u Sam,", text, Config->sample_array_size);
    }
    return text;
}

const char* LoopbackAudioNodeToStr(const LoopbackAudioHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sErrCnt:%u,", text, Node->error_cnt);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sREC:[%s],", text,  Node->rec_file_name);
        snprintf(text, sizeof(text), "%sPLAY:[%s],", text,  Node->play_file_name);
        snprintf(text, sizeof(text), "%sPHA_180:%u,", text, Node->tx_rx_180);
    }
    return text;
}


bool loopback_audio_diag_one(uint8_t num) {
    bool res = false;
    const LoopbackAudioConfig_t *Config = LoopbackAudioGetConfig(num);
    if(Config) {
        LOG_INFO(LOOPBACK_AUDIO, "%s", LoopbackAudioConfigToStr(Config));
        LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
        if(Node) {
            LOG_INFO(LOOPBACK_AUDIO, "%s", LoopbackAudioNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool loopback_audio_diag(void) {
    bool res = false;
    res = loopback_audio_diag_one(1);
    return res;
}


bool loopback_audio_raw_reg_diag(uint8_t num) {
    bool res = false;
    LoopbackAudioHandle_t *Node = LoopbackAudioGetNode(num);
    if(Node){
        res = true;
    }
    return res;
}
