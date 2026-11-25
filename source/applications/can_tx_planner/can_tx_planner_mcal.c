#include "can_tx_planner_mcal.h"

#include "can_mcal.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

CanTxPlannerHandle_t* CanTxPlannerGetNode(uint8_t num) {
    CanTxPlannerHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = can_tx_planner_get_cells();
    for(i = 0; i < cnt; i++) {
        if(num == CanTxPlannerInstance[i].num) {
            if(CanTxPlannerInstance[i].valid) {
                Node = &CanTxPlannerInstance[i];
                break;
            }
        }
    }
    return Node;
}

COMPONENT_GET_CONFIG(CanTxPlanner, can_tx_planner)

/*ISO-26262 require verify configuration*/
bool CanTxPlannerIsValidConfig(const CanTxPlannerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(CAN_TX_PLANNER, "%u,Name,Err", Config->num);
            res = false;
        }

        ifn(0 < Config->tx_period_ms) {
            LOG_ERROR(CAN_TX_PLANNER, "%u,TxPeriod,Err", Config->num);
            res = false;
        }
        ifn(Config->valid) {
            LOG_ERROR(CAN_TX_PLANNER, "%u,TxPeriod,Err", Config->num);
            res = false;
        }

        res = can_is_message_valid(&Config->TxMessage);
        ifn(res) {
            LOG_ERROR(CAN_TX_PLANNER, "%u,Message,Err", Config->num);
            res = false;
        }
    }
    return res;
}

bool can_tx_planner_init_custom(void) {
    bool res = false;
    LOG_INFO(CAN_TX_PLANNER, "Version:%s", CAN_TX_PLANNER_VERSION);
    return res;
}

bool can_tx_planner_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN_TX_PLANNER, "CAN_TX_PLANNER_%u,Proc", num);
    CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
    if(Node) {
        if(Node->on) {
            uint32_t up_time_ms = time_get_ms32();
            if(Node->tx_next_ms <= up_time_ms) {
                res = can_mcal_transmit_message((uint8_t)Node->TxMessage.can_bus_num, &Node->TxMessage);
                if(res) {
                    Node->TxMessage.time_stamp = up_time_ms;
                    Node->tx_period_real_ms = up_time_ms - Node->time_stamp_prev_ms;
                    Node->time_stamp_prev_ms = up_time_ms;
                    Node->tx_cnt++;
                }
                Node->tx_next_ms = up_time_ms + Node->tx_period_ms;
            }
        }
        Node->spin++;
    }
    return res;
}

static bool can_tx_planner_init_common(const CanTxPlannerConfig_t* const Config, CanTxPlannerHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->TxMessage = Config->TxMessage;
            Node->tx_period_ms = Config->tx_period_ms;
            Node->on = Config->on;
            Node->valid = Config->valid;
            res = true;
        }
    }
    return res;
}

static bool can_tx_planner_init_node(CanTxPlannerHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        Node->tx_cnt = 0;
        Node->tx_next_ms = 0;
        Node->spin = 0;
        res = true;
    }
    return res;
}

bool can_tx_planner_set(const uint8_t num, const bool en, const uint32_t tx_period_ms,
                        const CanMessage_t* const Messg) {
    bool res = false;
    LOG_WARNING(CAN_TX_PLANNER, "N%u,En:%u,TxPeriodMs:%u,Mesg:%s", num, en, tx_period_ms, CanMessageToStr(Messg));
    CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
    if(Node) {
        Node->on = en;
        Node->tx_period_ms = tx_period_ms;
        memcpy(&Node->TxMessage, Messg, sizeof(CanMessage_t));
        res = true;
    }
    return res;
}

bool can_tx_planner_set_period(const uint8_t num, const uint32_t tx_period_ms) {
    bool res = false;
    LOG_WARNING(CAN_TX_PLANNER, "N%u,TxPeriodMs:%u", num, tx_period_ms);
    CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
    if(Node) {
        Node->tx_period_ms = tx_period_ms;
        res = true;
    }
    return res;
}

bool can_tx_planner_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN_TX_PLANNER, "CAN_TX_PLANNER%u", num);
    const CanTxPlannerConfig_t* Config = CanTxPlannerGetConfig(num);
    if(Config) {
        res = CanTxPlannerIsValidConfig(Config);
        if(res) {
#ifdef HAS_CAN_TX_PLANNER_DIAG
            LOG_WARNING(CAN_TX_PLANNER, "%s", CanTxPlannerConfigToStr(Config));
#endif
            CanTxPlannerHandle_t* Node = CanTxPlannerGetNode(num);
            if(Node) {
                res = can_tx_planner_init_common(Config, Node);
                res = can_tx_planner_init_node(Node);
                LOG_INFO(CAN_TX_PLANNER, "CAN_TX_PLANNER%u, InitOk", num);
                Node->init = true;
                res = true;
            } else {
                LOG_ERROR(CAN_TX_PLANNER, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(CAN_TX_PLANNER, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(CAN_TX_PLANNER, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(CAN_TX_PLANNER, CAN_TX_PLANNER, can_tx_planner)
COMPONENT_PROC_PATTERT(CAN_TX_PLANNER, CAN_TX_PLANNER, can_tx_planner)
