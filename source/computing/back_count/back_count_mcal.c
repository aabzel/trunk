#include "back_count_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_IS_VALID(BackCount, back_count)
COMPONENT_GET_NODE(BackCount, back_count)
COMPONENT_GET_CONFIG(BackCount, back_count)


/*ISO-26262 require verify configuration*/

bool BackCountIsValidConfig(const BackCountConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(BACK_COUNT, "BACK_COUNT_%u,Name,Err", Config->num);
            res = false;
        }
    }
    return res;
}


bool back_count_init_custom(void) {
    bool res = false;
    LOG_INFO(BACK_COUNT, "Version:%u", BACK_COUNT_VERSION);
    return res;
}

static bool back_count_proc_on( BackCountHandle_t* Node){
    bool res = false;
    uint32_t up_time_ms = time_get_ms32();
    uint32_t on_duration_ms =up_time_ms - Node->on_time_ms ;
    if(Node->time_out_ms<=on_duration_ms) {
        Node->off_time_ms = time_get_ms32();
        Node->state = BACK_COUNT_STATE_OFF;
        Node->count--;
    }
    return res;
}

static bool back_count_proc_off( BackCountHandle_t* Node){
    bool res = false;
    uint32_t up_time_ms = time_get_ms32();
    uint32_t off_duration_ms = up_time_ms - Node->off_time_ms ;
    if(Node->time_out_ms <= off_duration_ms) {
        if(0 < Node->count){
            Node->state = BACK_COUNT_STATE_ON;
            Node->on_time_ms = time_get_ms32();
        }else {
            Node->state = BACK_COUNT_STATE_IDLE;
        }
    }
    return res;
}

static bool back_count_proc_idle(BackCountHandle_t* Node) {
    bool res = false;
    if(0 < Node->count) {
        Node->state = BACK_COUNT_STATE_ON;
        Node->on_time_ms = time_get_ms32();
    }
    return res;
}

bool back_count_proc_one_ll(BackCountHandle_t* Node) {
    bool res = false;
    switch(Node->state){
        case BACK_COUNT_STATE_IDLE:  {
            res = back_count_proc_idle(Node);
        } break;

        case BACK_COUNT_STATE_ON:  {
            res = back_count_proc_on( Node);
        } break;

        case BACK_COUNT_STATE_OFF: {
            res=back_count_proc_off( Node);

        } break;

        default: {Node->state = BACK_COUNT_STATE_IDLE;} break;
    }
    Node->spin++;
    return res;
}

bool back_count_add(uint8_t num, uint32_t val){
    bool res = false;
    LOG_PARN(BACK_COUNT, "BACK_COUNT_%u,+%u", num, val);
    BackCountHandle_t* Node = BackCountGetNode(num);
    if(Node) {
        Node->count += val;
        res = true;
    }
    return res;
}

bool back_count_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(BACK_COUNT, "BACK_COUNT_%u,Proc", num);
    BackCountHandle_t* Node = BackCountGetNode(num);
    if(Node) {
        res = back_count_proc_one_ll(Node);
    }
    return res;
}

bool back_count_is_valid_num(const uint8_t num) {
    bool res = false;
    BackCountHandle_t *Node = BackCountGetNode(num);
    if(Node) {
        res = Node->init;
    }
    return res;
}


bool back_count_init_common(const BackCountConfig_t* const Config, BackCountHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->time_out_ms = Config->time_out_ms;
            Node->count = Config->count;
            Node->name = Config->name;
            res = true;
        }
    }
    return res;
}

bool back_count_init_node(BackCountHandle_t* const Node) {
    bool res = false;
    if (Node) {
        Node->spin = 0;
        Node->valid = true;
        Node->state = BACK_COUNT_STATE_IDLE;
        Node->off_time_ms = 0;
        Node->on_time_ms = 0;
        res = true;
    }
    return res;
}

uint8_t back_count_state_get(uint8_t num) {
    uint8_t led_val = 0xFF;
    BackCountHandle_t *Node = BackCountGetNode(num);
    if(Node) {
        switch(Node->state){
            case BACK_COUNT_STATE_IDLE: led_val = 0xFF; break;
            case BACK_COUNT_STATE_ON:led_val = 1; break;
            case BACK_COUNT_STATE_OFF: led_val = 0; break;
            default : led_val = 0xFF; break;
        }
    }
    return led_val;
}




bool back_count_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(BACK_COUNT, "BACK_COUNT_%u", num);
    const BackCountConfig_t *Config = BackCountGetConfig(num);
    res = BackCountIsValidConfig(Config);
    if(res) {
#ifdef HAS_BACK_COUNT_DIAG
        LOG_WARNING(BACK_COUNT, "%s", BackCountConfigToStr(Config));
#endif
        BackCountHandle_t *Node = BackCountGetNode(num);
        if(Node) {
            res = back_count_init_common(Config, Node);
            res = back_count_init_node(Node);
            Node->init = true;
        } else {
            LOG_ERROR(BACK_COUNT, "NodeErr %u", num);
        }
    } else {
        LOG_PARN(BACK_COUNT, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(BACK_COUNT, BACK_COUNT, back_count)
COMPONENT_PROC_PATTERT(BACK_COUNT, BACK_COUNT, back_count)
