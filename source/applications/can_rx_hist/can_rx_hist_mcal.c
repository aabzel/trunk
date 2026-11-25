#include "can_rx_hist_mcal.h"

#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_NODE(CanRxHist, can_rx_hist)
COMPONENT_GET_CONFIG(CanRxHist, can_rx_hist)

CanRxHistHandle_t* CanRxHistCanNumToNode(const uint8_t can_num) {
    CanRxHistHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = can_rx_hist_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(can_num == CanRxHistInstance[i].can_num) {
            if(CanRxHistInstance[i].valid) {
                Node = &CanRxHistInstance[i];
                break;
            }
        }
    }
    return Node;
}

/*ISO-26262 require verify configuration*/

bool CanRxHistIsValidConfig(const CanRxHistConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(CAN_RX_HIST, "%u,NameErr", Config->num);
            res = false;
        }
    }
    return res;
}

bool can_rx_hist_init_custom(void) {
    bool res = false;
    LOG_INFO(CAN_RX_HIST, "Version:%u", CAN_RX_HIST_VERSION);
    return res;
}

bool can_rx_hist_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(CAN_RX_HIST, "Proc:%u", i);
    CanRxHistHandle_t* Node = CanRxHistGetNode(i);
    if(Node) {
        /*Delete old frames*/
        uint32_t i = 0;
        uint32_t up_time_ms = time_get_ms32();
        uint32_t cnt = Node->rx_mesg_array_cnt;
        for(i = 0; i < cnt; i++) {
            uint32_t silence = up_time_ms - Node->RxMesgArray[i].up_time_prev_ms;
            if(10000 < silence) {
                Node->RxMesgArray[i].rx_cnt = 0;
                Node->RxMesgArray[i].up_time_prev_ms = up_time_ms;
            }
        }
        Node->spin++;
    }
    return res;
}

bool can_rx_hist_raw_reg_diag(uint8_t i) {
    bool res = false;
#if 0
    CanRxHistInfo_t* Info = CanRxHistGetInfo(i);
    if(Info) {
        (void) Info;
    }
#endif
    return res;
}

bool can_rx_hist_init_common(const CanRxHistConfig_t* const Config, CanRxHistHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->can_num = Config->can_num;
            Node->rx_mesg_array_cnt = Config->rx_mesg_array_cnt;
            Node->RxMesgArray = Config->RxMesgArray;
            res = true;
        }
    }
    return res;
}

bool can_rx_hist_init_node(CanRxHistHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        res = true;
    }
    return res;
}

static CanRxMesgInfo_t* can_rx_hist_get_frame_by_id(const CanRxHistHandle_t* const Node, const uint32_t extended,
                                                    const CanIdentifier_t id_type) {
    CanRxMesgInfo_t* RxMesg = NULL;
    if(Node) {
        uint32_t i = 0;
        for(i = 0; i < Node->rx_mesg_array_cnt; i++) {
            if(extended == Node->RxMesgArray[i].Message.identifier.extended) {
                if(id_type == Node->RxMesgArray[i].Message.id_type) {
                    RxMesg = &(Node->RxMesgArray[i]);
                    break;
                }
            }
        }
    }
    return RxMesg;
}

static CanRxMesgInfo_t* can_rx_hist_first_spare_frame_ll(const CanRxHistHandle_t* const Node) {
    CanRxMesgInfo_t* RxMesg = NULL;
    uint32_t i = 0;
    for(i = 0; i < Node->rx_mesg_array_cnt; i++) {
        if(0 == Node->RxMesgArray[i].rx_cnt) {
            RxMesg = &(Node->RxMesgArray[i]);
            break;
        }
    }
    return RxMesg;
}

bool can_rx_hist_add_message(const uint8_t can_num, const CanMessage_t* const Message) {
    bool res = false;
    CanRxHistHandle_t* Node = CanRxHistCanNumToNode(can_num);
    if(Node) {
        uint32_t up_time_ms = Message->time_stamp;
        CanRxMesgInfo_t* MesgInfo = can_rx_hist_get_frame_by_id(Node, Message->identifier.extended, Message->id_type);
        if(MesgInfo) {
        } else {
            MesgInfo = can_rx_hist_first_spare_frame_ll(Node);
        }

        if(MesgInfo) {
            memcpy(&MesgInfo->Message, Message, sizeof(CanMessage_t));
            MesgInfo->rx_cnt++;
            MesgInfo->rx_period_ms = up_time_ms - MesgInfo->up_time_prev_ms;
            MesgInfo->up_time_prev_ms = up_time_ms;
        }
    }
    return res;
}

bool can_rx_hist_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN_RX_HIST, "CAN_RX_HIST%u", num);
    const CanRxHistConfig_t* Config = CanRxHistGetConfig(num);
    if(Config) {
        res = CanRxHistIsValidConfig(Config);
        if(res) {
#ifdef HAS_CAN_RX_HIST_DIAG
            LOG_WARNING(CAN_RX_HIST, "Config:%s", CanRxHistConfigToStr(Config));
#endif
            CanRxHistHandle_t* Node = CanRxHistGetNode(num);
            if(Node) {
                res = can_rx_hist_init_common(Config, Node);
                res = can_rx_hist_init_node(Node);
                Node->valid = true;
                Node->init = true;
                LOG_INFO(CAN_RX_HIST, "Init,Ok,%u", num);
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
