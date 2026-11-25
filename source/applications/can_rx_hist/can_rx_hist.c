#include "can_rx_hist.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(CanRxHist, can_rx_hist)
COMPONENT_GET_CONFIG(CanRxHist, can_rx_hist)

/*ISO-26262 require verify configuration*/
_WEAK_FUN_
bool CanRxHistIsValidConfig(const CanRxHistConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        if(res) {
            if(Config->name) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(CAN_RX_HIST, "%u,NameErr", Config->num);
            }
        }
    }
    return res;
}

_WEAK_FUN_
bool can_rx_hist_init_custom(void) {
    bool res = false;
    LOG_INFO(CAN_RX_HIST, "Version:%s", CAN_RX_HIST_VERSION);
    return res;
}

_WEAK_FUN_
bool can_rx_hist_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(CAN_RX_HIST, "Proc %u", i);
    CanRxHistHandle_t* Node = CanRxHistGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

_WEAK_FUN_
bool can_rx_hist_init_common(const CanRxHistConfig_t* const Config, CanRxHistHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->interrupt_on = Config->interrupt_on;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool can_rx_hist_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN_RX_HIST, "CAN_RX_HIST%u", num);
    const CanRxHistConfig_t* Config = CanRxHistGetConfig(num);
    if(Config) {
        res = CanRxHistIsValidConfig(Config);
        if(res) {
#ifdef HAS_CAN_RX_HIST_DIAG
            LOG_WARNING(CAN_RX_HIST, "%s", CanRxHistConfigToStr(Config));
#endif
            CanRxHistHandle_t* Node = CanRxHistGetNode(num);
            if(Node) {
                Node->valid = true;
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(CAN_RX_HIST, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(CAN_RX_HIST, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(CAN_RX_HIST, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(CAN_RX_HIST, CAN_RX_HIST, can_rx_hist)
COMPONENT_PROC_PATTERT(CAN_RX_HIST, CAN_RX_HIST, can_rx_hist)
