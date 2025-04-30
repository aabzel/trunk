#include "schmitt_trigger.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif
#include "log.h"
#include "schmitt_trigger_config.h"
#include "schmitt_trigger_diag.h"
#include "sys_config.h"

COMPONENT_GET_NODE(SchmittTrigger, schmitt_trigger)

COMPONENT_GET_CONFIG(SchmittTrigger, schmitt_trigger)

static bool schmitt_trigger_run_callback(SchmittTriggerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        /* LOG_DEBUG(SCHMITT_TRIGGER, "TG%u,  CallBacks (Down:%p,Up: %p)", Node->num, Node->down_call_back,
                  Node->up_call_back);*/
#ifdef HAS_FLASH
        res = is_flash_addr((uint32_t)Node->up_call_back);
        res = is_flash_addr((uint32_t)Node->down_call_back) && res;
#else
        res = true;
#endif
        if(res) {
            switch(Node->state) {
            case SCHMITT_TRIGGER_STATE_UP: {
                LOG_DEBUG(SCHMITT_TRIGGER, "TG%u,CallBackUp:%p", Node->num, Node->up_call_back);
                res = Node->up_call_back();
                if(res) {
                    Node->up_handler_cnt++;
                } else {
                    LOG_ERROR(SCHMITT_TRIGGER, "TG%u,UpCallBackErr", Node->num);
                }
            } break;
            case SCHMITT_TRIGGER_STATE_DOWN: {
                LOG_DEBUG(SCHMITT_TRIGGER, "TG%u,CallBackDown:%p", Node->num, Node->down_call_back);
                res = Node->down_call_back();
                if(res) {
                    Node->down_handler_cnt++;
                } else {
                    LOG_ERROR(SCHMITT_TRIGGER, "TG%u DownCallBackErr", Node->num);
                }
            } break;
            default:
                break;
            }
        }
    }
    return res;
}

bool schmitt_trigger_init_one(uint8_t num) {
    bool res = false;
    const SchmittTriggerConfig_t* Config = SchmittTriggerGetConfig(num);
    if(Config) {
        SchmittTriggerHandle_t* Node = SchmittTriggerGetNode(num);
        if(Node) {
            LOG_WARNING(SCHMITT_TRIGGER, "%u,Init:%s", num, Config->name);
            Node->hysteresis = Config->hysteresis;
            Node->name = Config->name;
            Node->up_call_back = Config->up_call_back;
            Node->down_call_back = Config->down_call_back;
            Node->switching_value = Config->switching_value;
            Node->units = Config->units;

            Node->init = true;
            Node->state = SCHMITT_TRIGGER_STATE_UNDEF;
            Node->prev_state = SCHMITT_TRIGGER_STATE_UNDEF;
            Node->valid = true;
            Node->value = 0.0;
            Node->up_handler_cnt = 0;
            Node->down_handler_cnt = 0;
            res = true;
            log_level_get_set(SCHMITT_TRIGGER, LOG_LEVEL_INFO);
        }
    }

    return res;
}

bool schmitt_trigger_set_val(uint8_t num, double val) {
    bool res = false;
    SchmittTriggerHandle_t* Node = SchmittTriggerGetNode(num);
    if(Node) {
        Node->switching_value = val;
        res = true;
    }

    return res;
}

SchmittTriggerState_t schmitt_trigger_get_state(uint8_t num) {
    SchmittTriggerState_t out_state = SCHMITT_TRIGGER_STATE_UNDEF;
    SchmittTriggerHandle_t* Node = SchmittTriggerGetNode(num);
    if(Node) {
        out_state = Node->state;
    }
    return out_state;
}

bool schmitt_trigger_proc_val_ll(SchmittTriggerHandle_t* const Node, double val) {
    bool res = false;
    if(Node) {
        res = true;
        LOG_DEBUG(SCHMITT_TRIGGER, "%s", SchmittTriggerNode2Str(Node));
        Node->value = val;
        if(val < (Node->switching_value - Node->hysteresis)) {
            Node->state = SCHMITT_TRIGGER_STATE_DOWN;
        } else if((Node->switching_value + Node->hysteresis) < val) {
            Node->state = SCHMITT_TRIGGER_STATE_UP;
        } else {
            /*retain current state*/
        }

        if(Node->state != Node->prev_state) {
            LOG_DEBUG(SCHMITT_TRIGGER, "TG%u,border: %f, Cross, NewState:%s, Val:%f", Node->num, Node->switching_value,
                      SchmittTriggerState2Str(Node->state), val);
            res = schmitt_trigger_run_callback(Node);
            if(res) {
                LOG_PARN(SCHMITT_TRIGGER, "TG%u CallBackOk", Node->num);
            } else {
                LOG_ERROR(SCHMITT_TRIGGER, "TG%u CallBackErr", Node->num);
                res = false;
            }
        }
        Node->prev_state = Node->state;
    } else {
        LOG_ERROR(SCHMITT_TRIGGER, "NodeErr %u", Node->num);
    }

    return res;
}

bool schmitt_trigger_init_custom(void) { return true; }

bool schmitt_trigger_proc_val(uint8_t num, double val) {
    bool res = false;
    SchmittTriggerHandle_t* Node = SchmittTriggerGetNode(num);
    if(Node) {
        res = schmitt_trigger_proc_val_ll(Node, val);
    } else {
        LOG_ERROR(SCHMITT_TRIGGER, "NodeErr %u", num);
    }

    return res;
}

COMPONENT_INIT_PATTERT(SCHMITT_TRIGGER, SCHMITT_TRIGGER, schmitt_trigger)
