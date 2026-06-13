#include "incremental_encoder_mcal.h"

#include "bit_utils.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "core_driver.h"
#include "gpio_mcal.h"
#include "iqueue.h"
#include "lib_iqueue.h"
#include "log.h"

COMPONENT_IS_VALID(IncrementalEncoder, incremental_encoder)
COMPONENT_GET_NODE(IncrementalEncoder, incremental_encoder)
COMPONENT_GET_CONFIG(IncrementalEncoder, incremental_encoder)

bool incremental_encoder_init_custom(void) {
    bool res = false;
    LOG_INFO(INCREMENTAL_ENCODER, "Version:%u", INCREMENTAL_ENCODER_VERSION);
    return res;
}

IncrementalEncoderHandle_t* IncrementalEncoderPadToNode(const Pad_t Pad) {
    IncrementalEncoderHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = incremental_encoder_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(IncrementalEncoderInstance[i].valid) {
            if(Pad.byte == IncrementalEncoderInstance[i].PadA.byte) {
                Node = &IncrementalEncoderInstance[i];
                break;
            }
            if(Pad.byte == IncrementalEncoderInstance[i].PadB.byte) {
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
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,Name,Err", Config->num);
            res = false;
        }

        ifn(Config->limit_down < Config->limit_up) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,Limits,Err", Config->num);
            res = false;
        }

        ifn(Config->EventMem) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,EventMem,Err", Config->num);
            res = false;
        }

        ifn(1 < Config->event_mem_size) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,event_mem_size,Err", Config->num);
            res = false;
        }

        ifn(4 < Config->cnt_pre_revolution) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,cnt_pre_revolution,Err", Config->num);
            res = false;
        }

        res = gpio_is_valid_pad(Config->PadA);
        ifn(res) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,PadA,Err", Config->num);
            res = false;
        }

        res = gpio_is_valid_pad(Config->PadB);
        ifn(res) {
            LOG_ERROR(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,PadB,Err", Config->num);
            res = false;
        }
    }
    return res;
}

int32_t incremental_encoder_get_counter(const uint8_t num) {
    int32_t cnt = 0;
    IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
    if(Node) {
        cnt = Node->cnt;
    }
    return cnt;
}

int32_t incremental_encoder_get_counter_limited(const uint8_t num) {
    int32_t cnt = 0;
    IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
    if(Node) {
        cnt = Node->cnt_limited;
    }
    return cnt;
}

float incremental_encoder_get_revolutions(const uint8_t num) {
    float revolutions = 0.0f;
    IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
    if(Node) {
        if(Node->cnt_pre_revolution) {
            revolutions = (float)Node->cnt / (float)Node->cnt_pre_revolution;
        }
    }
    return revolutions;
}

bool incremental_encoder_set_counter(uint8_t num, int32_t counter){
    bool res = false;
    IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
    if(Node) {
        Node->cnt = counter;
        Node->cnt_limited = counter;
        Node->error_cnt = 0;
        Node->revolutions = 0;
        res = true;
    }
    return res;
}

bool incremental_encoder_set_0(uint8_t num) {
    bool res = false;
    res = incremental_encoder_set_counter(num, 0);
    return res;
}

static bool incremental_encoder_ccw(IncrementalEncoderHandle_t* Node) {
    Node->cnt--;
    Node->cnt_limited--;
    Node->cnt_limited = int32_range_limiter(Node->cnt_limited, Node->limit_down, Node->limit_up);
    return true;
}

static bool incremental_encoder_cw(IncrementalEncoderHandle_t* Node) {
    Node->cnt++;
    Node->cnt_limited++;
    Node->cnt_limited = int32_range_limiter(Node->cnt_limited, Node->limit_down, Node->limit_up);
    return true;
}

static bool incremental_encoder_error(IncrementalEncoderHandle_t* Node) {
    Node->error_cnt++;
    return false;
}

static bool incremental_encoder_state_B0A0_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;

    switch(Node->input) {
    case INC_ENCODER_INPUT_A_RISE: {
        res = incremental_encoder_ccw(Node);
    } break;
    case INC_ENCODER_INPUT_A_FALL: {
        res = incremental_encoder_error(Node);
    } break;
    case INC_ENCODER_INPUT_B_RISE: {
        res = incremental_encoder_cw(Node);
    } break;
    case INC_ENCODER_INPUT_B_FALL: {
        res = incremental_encoder_error(Node);
    } break;
    default: {
        res = incremental_encoder_error(Node);
    } break;
    }
    return res;
}

static bool incremental_encoder_state_B0A1_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case INC_ENCODER_INPUT_A_RISE: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_B_FALL: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_A_FALL: {
        res = incremental_encoder_cw(Node);
    } break;

    case INC_ENCODER_INPUT_B_RISE: {
        res = incremental_encoder_ccw(Node);
    } break;

    default: {
        res = incremental_encoder_error(Node);
    } break;
    }
    return res;
}

static bool incremental_encoder_state_B1A1_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case INC_ENCODER_INPUT_A_RISE: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_B_RISE: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_A_FALL: {
        res = incremental_encoder_ccw(Node);
    } break;

    case INC_ENCODER_INPUT_B_FALL: {
        res = incremental_encoder_cw(Node);
    } break;

    default: {
        res = incremental_encoder_error(Node);
    } break;
    }
    return res;
}

static bool incremental_encoder_state_B1A0_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case INC_ENCODER_INPUT_A_RISE: {
        res = incremental_encoder_cw(Node);
    } break;

    case INC_ENCODER_INPUT_A_FALL: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_B_RISE: {
        res = incremental_encoder_error(Node);
    } break;

    case INC_ENCODER_INPUT_B_FALL: {
        res = incremental_encoder_ccw(Node);
    } break;

    default: {
        res = incremental_encoder_error(Node);
    } break;
    }
    return res;
}

IncrementalEncoderState_t incremental_encoder_read_state(IncrementalEncoderHandle_t* Node) {
    IncrementalEncoderState_t state = INC_ENCODER_STATE_UNDEF;
    uint32_t state_i = 0;
    GpioLogicLevel_t lla = gpio_get_state_short(Node->PadA);
    GpioLogicLevel_t llb = gpio_get_state_short(Node->PadB);
    if(GPIO_LVL_HI == lla) {
        SET_BIT_NUM(state_i, 0);
    }
    if(GPIO_LVL_HI == llb) {
        SET_BIT_NUM(state_i, 1);
    }
    state = state_i;
    return state;
}

bool incremental_encoder_update_logic_state(IncrementalEncoderHandle_t* Node) {
    bool res = false;
    switch(Node->input) {
    case INC_ENCODER_INPUT_A_RISE: {
        SET_BIT_NUM(Node->logic_state, 0);
    } break;
    case INC_ENCODER_INPUT_A_FALL: {
        RESET_BIT_NUM(Node->logic_state, 0);
    } break;
    case INC_ENCODER_INPUT_B_RISE: {
        SET_BIT_NUM(Node->logic_state, 1);
    } break;
    case INC_ENCODER_INPUT_B_FALL: {
        RESET_BIT_NUM(Node->logic_state, 1);
    } break;
    default: {
    } break;
    }
    return res;
}

bool incremental_encoder_proc_input(IncrementalEncoderHandle_t* Node) {
    bool res = false;

    res = incremental_encoder_update_logic_state(Node);

    switch(Node->prev_state) {
    case INC_ENCODER_STATE_B0A0: {
        res = incremental_encoder_state_B0A0_proc_input(Node);
    } break;
    case INC_ENCODER_STATE_B0A1: {
        res = incremental_encoder_state_B0A1_proc_input(Node);
    } break;
    case INC_ENCODER_STATE_B1A1: {
        res = incremental_encoder_state_B1A1_proc_input(Node);
    } break;
    case INC_ENCODER_STATE_B1A0: {
        res = incremental_encoder_state_B1A0_proc_input(Node);
    } break;
    default: {
        Node->error_cnt++;
        res = false;
    } break;
    }
    return res;
}

bool incremental_encoder_init_common(const IncrementalEncoderConfig_t* const Config,
                                     IncrementalEncoderHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->PadA = Config->PadA;
            Node->limit_up = Config->limit_up;
            Node->limit_down = Config->limit_down;
            Node->PadB = Config->PadB;
            Node->EventMem = Config->EventMem;
            Node->event_mem_size = Config->event_mem_size;
            Node->cnt_pre_revolution = Config->cnt_pre_revolution;
            res = true;
        }
    }
    return res;
}

bool incremental_encoder_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u,Proc", num);
    IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
    if(Node) {
        log_level_t ll = log_level_get(INCREMENTAL_ENCODER);
        if(LOG_LEVEL_NOTICE == ll) {
            cli_printf("\r%s", IncrementalEncoderMainToStr(Node));
        }

#ifdef HAS_IQUEUE
        size_t size = 0;
        i_status ret = iqueue_size(&Node->iQueue, &size);
        res = iqueue_ret_res(ret);
        if(res) {
            if(0 < size) {
                IncrementalEncoderEvent_t Event = {0};
                enter_critical();
                ret = iqueue_dequeue((iqueue_t*)&Node->iQueue, (void*)&Event);
                exit_critical();
                res = iqueue_ret_res(ret);
                if(res) {
                    Node->input = Event.input;
                    Node->new_state = Event.state;
                    if(Node->new_state != Node->prev_state) {
                        LOG_PARN(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u:NewState:%u->%u", num, Node->prev_state,
                                 Node->new_state);
                    }
                    res = incremental_encoder_proc_input(Node);
                    LOG_DEBUG(INCREMENTAL_ENCODER, "%s", IncrementalEncoderEventToStr(&Event, Node));
                    Node->prev_state = Node->new_state;
                    Node->prev_event_time_us = Event.timestamp_us;
                }
            }
        }
#endif

        Node->spin++;
    }
    return res;
}

bool incremental_encoder_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(INCREMENTAL_ENCODER, "INCREMENTAL_ENCODER_%u", num);
    const IncrementalEncoderConfig_t* Config = IncrementalEncoderGetConfig(num);
    res = IncrementalEncoderIsValidConfig(Config);
    if(res) {
#ifdef HAS_INCREMENTAL_ENCODER_DIAG
        LOG_WARNING(INCREMENTAL_ENCODER, "%s", IncrementalEncoderConfigToStr(Config));
#endif
        IncrementalEncoderHandle_t* Node = IncrementalEncoderGetNode(num);
        if(Node) {
            res = incremental_encoder_init_common(Config, Node);
            gpio_init_ext_int(Config->PadA);
            gpio_init_ext_int(Config->PadB);
            res = incremental_encoder_set_0(num);
            Node->spin = 0;
            Node->valid = true;

#ifdef HAS_IQUEUE
            i_status ret =
                iqueue_init(&Node->iQueue, Node->event_mem_size, sizeof(IncrementalEncoderEvent_t), Node->EventMem);
            res = iqueue_ret_res(ret);
#endif

            Node->new_state = incremental_encoder_read_state(Node);
            Node->logic_state = Node->new_state;
            Node->prev_state = Node->new_state;
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
