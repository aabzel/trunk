#include "incremental_encoder_mcal.h"

#include "interrupt_mcal.h"
#include "bit_utils.h"
#include "gpio_mcal.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(IncrementalEncoder, incremental_encoder)
COMPONENT_GET_CONFIG(IncrementalEncoder, incremental_encoder)

IncrementalEncoderHandle_t* IncrementalEncoderPadToNode(const Pad_t Pad) {
    IncrementalEncoderHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = incremental_encoder_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(IncrementalEncoderInstance[i].valid) {
            if(Pad.byte == IncrementalEncoderInstance[i].PadA.byte ) {
                Node = &IncrementalEncoderInstance[i];
                break;
            }
            if(Pad.byte == IncrementalEncoderInstance[i].PadB.byte ) {
                Node = &IncrementalEncoderInstance[i];
                break;
            }
        }
    }
    return Node;
}


/*ISO-26262 require verify configuration*/
bool IncrementalEncoderIsValidConfig(const IncrementalEncoderConfig_t* const Config) {
    bool res = false;
    if (Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool incremental_encoder_init_custom(void) {
    bool res = false;
    LOG_INFO(INCREMENTAL_ENCODER, "Version:%u", INCREMENTAL_ENCODER_VERSION);
    return res;
}

bool incremental_encoder_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,Proc", num);
    IncrementalEncoderHandle_t *Node = IncrementalEncoderGetNode(num);
    if (Node) {
        log_level_t ll =log_level_get(INCREMENTAL_ENCODER);
        IncrementalEncoderState_t real_state = incremental_encoder_read_state(Node);
        if(real_state!=Node->prev_state ) {
            LOG_PARN(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u:NewState:%u->%u", num,Node->prev_state,real_state);
        }
        if(LOG_LEVEL_DEBUG==ll){
            interrupt_control_all(false);
            cli_printf("\r%s",IncrementalEncoderMainToStr(Node));
            interrupt_control_all(true);
        }
        Node->prev_state = real_state;
        Node->spin++;
    }
    return res;
}

bool incremental_encoder_init_common(const IncrementalEncoderConfig_t* const Config,
                                     IncrementalEncoderHandle_t* const Node) {
    bool res = false;
    if (Config) {
        if (Node) {
            Node->name = Config->name;
            Node->PadA = Config->PadA;
            Node->PadB = Config->PadB;
            Node->cnt_pre_revolution = Config->cnt_pre_revolution;
            res = true;
        }
    }
    return res;
}

IncrementalEncoderState_t incremental_encoder_read_state(IncrementalEncoderHandle_t* Node) {
    IncrementalEncoderState_t state = INC_ENCODER_STATE_UNDEF;
    uint32_t state_i = 0;
    GpioLogicLevel_t lla = gpio_get_state_short(Node->PadA);
    GpioLogicLevel_t llb = gpio_get_state_short(Node->PadB);
    if (GPIO_LVL_HI == lla) {
        SET_BIT_NUM(state_i, 0);
    }
    if (GPIO_LVL_HI == llb) {
        SET_BIT_NUM(state_i, 1);
    }
    state = state_i;
    return state;
}

bool incremental_encoder_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u", num);
    const IncrementalEncoderConfig_t *Config = IncrementalEncoderGetConfig(num);
    res = IncrementalEncoderIsValidConfig(Config);
    if (res) {
#ifdef HAS_INCREMENTAL_ENCODER_DIAG
        LOG_WARNING(INCREMENTAL_ENCODER, "%s", IncrementalEncoderConfigToStr(Config));
#endif
        IncrementalEncoderHandle_t *Node = IncrementalEncoderGetNode(num);
        if (Node) {
            res = incremental_encoder_init_common(Config, Node);
            gpio_init_ext_int(Config->PadA);
            gpio_init_ext_int(Config->PadB);
            Node->spin = 0;
            Node->revolutions = 0;
            Node->cnt = 0;
            Node->valid = true;
            Node->state = incremental_encoder_read_state(Node);
            Node->init = true;
        } else {
            LOG_ERROR(INCREMENTAL_ENCODER, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(INCREMENTAL_ENCODER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(INCREMENTAL_ENCODER, INCREMENTAL_ENCODER, incremental_encoder)
COMPONENT_PROC_PATTERT(INCREMENTAL_ENCODER, INCREMENTAL_ENCODER, incremental_encoder)
