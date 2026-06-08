#include "ir_receiver_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "ir_samsung_mcal.h"
#include "log.h"
//#include "timer_mcal.h"
#include "time_mcal.h"

COMPONENT_GET_NODE(IrReceiver, ir_receiver)
COMPONENT_GET_CONFIG(IrReceiver, ir_receiver)

/*ISO-26262 require verify configuration*/
bool IrReceiverIsValidConfig(const IrReceiverConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            ifn(Config->name) { LOG_ERROR(IR_RECEIVER, "%u,NameErr", Config->num); }
            ifn(Config->signal_cur) { LOG_ERROR(IR_RECEIVER, "%u,signal_cur,Err", Config->num); }
            ifn(Config->signal_fix) { LOG_ERROR(IR_RECEIVER, "%u,signal_fix,Err", Config->num); }
            ifn(Config->signal_size) { LOG_ERROR(IR_RECEIVER, "%u,signal_size,Err", Config->num); }

            ifn(Config->exp_size) { LOG_ERROR(IR_RECEIVER, "%u,exp_size,Err", Config->num); }
        }
    }
    return res;
}

bool ir_receiver_init_custom(void) {
    bool res = false;
    LOG_INFO(IR_RECEIVER, "Version:%s", IR_RECEIVER_VERSION);
    return res;
}

bool ir_receiver_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(IR_RECEIVER, "Proc %u", i);
    log_level_t ll = log_level_get(IR_RECEIVER);
    IrReceiverHandle_t* Node = IrReceiverGetNode(i);
    if(Node) {
        if(Node->spot_frame) {
            // IrReceiverFrameRisingDiag(Node);
            if(LOG_LEVEL_DEBUG == ll) {
                IrReceiverFrameDiag(Node);
            }
#ifdef HAS_IR_SAMSUNG
            res = ir_samsung_proc_signal(1, Node->signal_fix, Node->exp_size);
#endif
            memset(Node->signal_fix, 0, Node->signal_size * sizeof(IrReceiverEvent_t));
            Node->spot_frame = false;
        }

        uint32_t up_time_ms = time_get_ms32();
        uint32_t diff_ms = up_time_ms - Node->rx_time_ms;
        if(500 < diff_ms) {
            Node->event_i = 0;
            Node->spot_frame = false;
        }
        Node->spin++;
    }
    return res;
}

bool ir_receiver_init_common(const IrReceiverConfig_t* const Config, IrReceiverHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->IrPad = Config->IrPad;
            Node->timer_num = Config->timer_num;
            Node->signal_cur = Config->signal_cur;
            Node->signal_fix = Config->signal_fix;
            Node->signal_size = Config->signal_size;
            Node->exp_size = Config->exp_size;
            res = true;
        }
    }
    return res;
}

bool ir_receiver_proc_event(const uint8_t num, const PinIntEdge_t event) {
    bool res = false;
    IrReceiverHandle_t* Node = IrReceiverGetNode(num);
    if(Node) {
        uint32_t up_time_us = time_get_us32();

        IrReceiverEvent_t Event;
        Event.event = event;
        Event.up_time_us = up_time_us;

        uint32_t diff_us = up_time_us - Node->time_stamp_prev_us;
        if(5500 < diff_us) {
            Node->event_i = 0;
            memcpy(Node->signal_fix, Node->signal_cur, Node->signal_size * sizeof(IrReceiverEvent_t));
            memset(Node->signal_cur, 0, Node->signal_size * sizeof(IrReceiverEvent_t));
            Node->spot_frame = true;
        }

        Node->rx_time_ms = time_get_ms32();
        if(Node->event_i < Node->signal_size) {
            Node->signal_cur[Node->event_i] = Event;
            Node->signal_fix[Node->event_i] = Event;
            Node->event_i++;
        } else {
            memcpy(Node->signal_fix, Node->signal_cur, Node->signal_size * sizeof(IrReceiverEvent_t));
            memset(Node->signal_cur, 0, Node->signal_size * sizeof(IrReceiverEvent_t));
            Node->spot_frame = true;
            Node->event_i = 0;
        }

        if(Node->exp_size == Node->event_i) {
            memcpy(Node->signal_fix, Node->signal_cur, Node->signal_size * sizeof(IrReceiverEvent_t));
            memset(Node->signal_cur, 0, Node->signal_size * sizeof(IrReceiverEvent_t));
            Node->spot_frame = true;
        }

        Node->time_stamp_prev_us = up_time_us;
        res = true;
    }
    return res;
}

bool ir_receiver_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(IR_RECEIVER, "IR_RECEIVER%u", num);
    const IrReceiverConfig_t* Config = IrReceiverGetConfig(num);
    if(Config) {
        res = IrReceiverIsValidConfig(Config);
        if(res) {
#ifdef HAS_IR_RECEIVER_DIAG
            LOG_WARNING(IR_RECEIVER, "%s", IrReceiverConfigToStr(Config));
#endif
            IrReceiverHandle_t* Node = IrReceiverGetNode(num);
            if(Node) {
                res = ir_receiver_init_common(Config, Node);
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(IR_RECEIVER, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(IR_RECEIVER, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(IR_RECEIVER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(IR_RECEIVER, IR_RECEIVER, ir_receiver)
COMPONENT_PROC_PATTERT(IR_RECEIVER, IR_RECEIVER, ir_receiver)
