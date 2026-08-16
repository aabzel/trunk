#include "manchester_decode_diag.h"

#include "manchester_decode_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "log.h"

const char* ManchesterDecodeStateToStr(const ManchesterDecodeState_t state){
    const char* name="?";
    switch(state) {
        case MANCH_DECODE_STATE_00_START0  : { name="00_START0";}break;
        case MANCH_DECODE_STATE_01_START0  : { name="01_START0";}break;
        case MANCH_DECODE_STATE_10_START0  : { name="10_START0";}break;
        case MANCH_DECODE_STATE_11_START0  : { name="11_START0";}break;
        case MANCH_DECODE_STATE_00_START1  : { name="00_START1";}break;
        case MANCH_DECODE_STATE_01_START1  : { name="01_START1";}break;
        case MANCH_DECODE_STATE_10_START1  : { name="10_START1";}break;
        case MANCH_DECODE_STATE_11_START1  : { name="11_START1";}break;
        case MANCH_DECODE_STATE_00_DONE    : { name="00_DONE";}break;
        case MANCH_DECODE_STATE_01_DONE    : { name="01_DONE";}break;
        case MANCH_DECODE_STATE_10_DONE    : { name="10_DONE";}break;
        case MANCH_DECODE_STATE_11_DONE    : { name="11_DONE";}break;
        default:{ name="?";}break;
    }
    return name;
}

const char* ManchesterDecodeActionToStr(const ManchesterDecodeAction_t action) {
    const char* name="?";
    switch(action) {
        case MANCH_DECODE_ACTION_ERROR  :{ name="Err";} break;
        case MANCH_DECODE_ACTION_RX0    :{ name="Rx0";} break;
        case MANCH_DECODE_ACTION_RX1    :{ name="Rx1";} break;
        case MANCH_DECODE_ACTION_START0 :{ name="Start0";}break;
        case MANCH_DECODE_ACTION_START1 :{ name="Start1";} break;
        case MANCH_DECODE_ACTION_UNREAL :{ name="Enreal";} break;
        case MANCH_DECODE_ACTION_UNDEF  :{ name="Undef";} break;
        default:{ name="?";}break;
    }
    return name;
}

const char* ManchesterDecodeConfigToStr(const ManchesterDecodeConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* ManchesterDecodeNodeToStr(const ManchesterDecodeHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sCurFlow:%u Bits,", text, Node->cur_flow);
        snprintf(text, sizeof(text), "%sMaxFlow:%u Bits,", text, Node->max_flow);
        snprintf(text, sizeof(text), "%sErr:%u,", text, Node->error_cnt);
        snprintf(text, sizeof(text), "%sPrevState:%s,", text,ManchesterDecodeStateToStr( Node->prev_state));
        snprintf(text, sizeof(text), "%sState:%s,", text,ManchesterDecodeStateToStr( Node->state));
        snprintf(text, sizeof(text), "%sState:%s,", text,ManchesterDecodeActionToStr( Node->out));
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sCnt:%u,", text, Node->rx_cnt);
        snprintf(text, sizeof(text), "%sPhase:%d,", text, Node->rx_cnt_phase);
        snprintf(text, sizeof(text), "%sRxByte:0x%x,", text, Node->rx_byte);
    }
    return text;
}

bool manchester_decode_diag(void) {
    bool res = false;
    return res;
}

bool manchester_decode_diag_one(uint8_t num) {
    bool res = false;
    ManchesterDecodeHandle_t* Node=ManchesterDecodeGetNode(num);
    if(Node){
        LOG_INFO(MANCHESTER_DECODE, "%s",ManchesterDecodeNodeToStr(Node));
        res = true;
    }
    return res;
}
