#include "incremental_encoder_diag.h"

#include "incremental_encoder_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "gpio_mcal.h"
#include "log.h"


const char* IncrementalEncoderInputToStr(const IncrementalEncoderInput_t input ){
    const char* name = "?";
    switch(input) {
        case INC_ENCODER_INPUT_A_RISE:     name = "Arise";       break;
        case INC_ENCODER_INPUT_A_FALL:     name = "Afall";      break;
        case INC_ENCODER_INPUT_B_RISE:     name = "Brise";      break;
        case INC_ENCODER_INPUT_B_FALL:     name = "Bfall";      break;
        default:        name = "?";        break;
    }
    return name;
}

const char* IncrementalEncoderStateToStr(const IncrementalEncoderState_t state){
    const char* name = "?";
    switch(state) {
        case INC_ENCODER_STATE_B0A0:     name = "B0_A0" ;       break;
        case INC_ENCODER_STATE_B0A1:     name = "B0_A1" ;      break;
        case INC_ENCODER_STATE_B1A1:     name = "B1_A1" ;      break;
        case INC_ENCODER_STATE_B1A0:     name = "B1_A0" ;      break;
        default:        name = "?";        break;
    }
    return name;
}

const char* IncrementalEncoderConfigToStr(const IncrementalEncoderConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sA:%s,", text, GpioPadToStr(Config->PadA));
        snprintf(text, sizeof(text), "%sB:%s,", text, GpioPadToStr(Config->PadA));
        snprintf(text, sizeof(text), "%sEvMem:%p,", text, Config->EventMem);
        snprintf(text, sizeof(text), "%sCntPerRev:%u,", text, Config->cnt_pre_revolution);
        snprintf(text, sizeof(text), "%sEvCnt:%u,", text, Config->event_mem_size);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* IncrementalEncoderEventToStr(const IncrementalEncoderEvent_t* const Event,
                                         IncrementalEncoderHandle_t *Node){
    strcpy(text, "");
    if(Event) {
        float revolutions= incremental_encoder_get_revolutions(Node->num);
        int32_t diff_us =((int32_t)  Event->timestamp_us)- ((int32_t) Node->prev_event_time_us);
        snprintf(text, sizeof(text), "%sTSPrev:%u us,", text, Node->prev_event_time_us);
        snprintf(text, sizeof(text), "%sTS:%u us,", text, Event->timestamp_us);
        snprintf(text, sizeof(text), "%stD:%d,", text, diff_us);
        snprintf(text, sizeof(text), "%s[%s->", text, IncrementalEncoderStateToStr(Node->prev_state));
        snprintf(text, sizeof(text), "%s(%s)->", text, IncrementalEncoderInputToStr(Event->input));
        snprintf(text, sizeof(text), "%s%s],", text, IncrementalEncoderStateToStr(Event->state));
        //snprintf(text, sizeof(text), "%sIn:%u=", text, Event->input);
        snprintf(text, sizeof(text), "%sCNT:%d,", text, Node->cnt);
        snprintf(text, sizeof(text), "%sREV:%5.2f,", text, revolutions);
        snprintf(text, sizeof(text), "%sNewLoState:%s,", text, IncrementalEncoderStateToStr(Node->logic_state));
        snprintf(text, sizeof(text), "%sError:%u,", text, Node->error_cnt);
    }
    return text;
}

const char* IncrementalEncoderMainToStr(const IncrementalEncoderHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        float revolutions= incremental_encoder_get_revolutions(Node->num);
        snprintf(text, sizeof(text), "%sCNT:%d,", text, Node->cnt);
        snprintf(text, sizeof(text), "%srState:%s,", text, IncrementalEncoderStateToStr(Node->new_state));
        snprintf(text, sizeof(text), "%slState:%u,", text, Node->logic_state);
        snprintf(text, sizeof(text), "%sREV:%5.2f,", text, revolutions);
        snprintf(text, sizeof(text), "%sErr:%u,", text, Node->error_cnt);
    }
    return text;
}




const char* IncrementalEncoderNodeToStr(const IncrementalEncoderHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
#if 0
        GpioLogicLevel_t lla = gpio_get_state_short(Node->PadA);
        GpioLogicLevel_t llb = gpio_get_state_short(Node->PadB);

        IncrementalEncoderState_t new_state= incremental_encoder_read_state(Node);
        snprintf(text, sizeof(text), "%sA:%u,", text, lla);
        snprintf(text, sizeof(text), "%sB:%u,", text, llb);
#endif
        snprintf(text, sizeof(text), "%sNewLoState:%s,", text, IncrementalEncoderStateToStr(Node->logic_state));
        snprintf(text, sizeof(text), "%sNewReState:%s,", text,IncrementalEncoderStateToStr( Node->new_state));
        snprintf(text, sizeof(text), "%sCNT:%d,", text, Node->cnt);
        snprintf(text, sizeof(text), "%sCntLim:%d,", text, Node->cnt_limited);
        snprintf(text, sizeof(text), "%sRev:%d,", text, Node->revolutions);
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool incremental_encoder_diag_one(uint8_t num) {
    bool res = false;

    const IncrementalEncoderConfig_t* Config=IncrementalEncoderGetConfig(num);
    if(Config){
        LOG_INFO(SYS,"%s",IncrementalEncoderConfigToStr(Config));
        res = true;
    }

    IncrementalEncoderHandle_t* Node=IncrementalEncoderGetNode(num);
    if(Node){
        LOG_INFO(SYS,"%s",IncrementalEncoderNodeToStr(Node));
        res = true;
    }
    return res;
}

bool incremental_encoder_diag(void) {
    bool res = false;
    res = incremental_encoder_diag_one(1);
    return res;
}
