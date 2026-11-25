#include "can_diff_mcal.h"

#include "array.h"
#include "can_diag.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"

COMPONENT_GET_CONFIG(CanDiff, can_diff)

CanDiffHandle_t* CanDiffGetNode(uint8_t num) {
    CanDiffHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = can_diff_inst_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(num == CanDiffInstance[i].num) {
            if(CanDiffInstance[i].valid) {
                Node = &CanDiffInstance[i];
                break;
            }
        }
    }
    return Node;
}

/*ISO-26262 require verify configuration*/
bool CanDiffIsValidConfig(const CanDiffConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
        ifn(Config->name) {
            LOG_ERROR(CAN_DIFF, "%u,NameErr", Config->num);
            res = false;
        }
    }
    return res;
}

bool can_diff_watch(const uint8_t num, const uint8_t can_num, const uint32_t can_id, const CanIdentifier_t id_type) {
    bool res = false;
    LOG_INFO(CAN_DIFF, "Set,Watcher:CAN%u,ID:0x%x,%s", can_num, can_id, CanIdTypeToStr(id_type));
    CanDiffHandle_t* Node = CanDiffGetNode(num);
    if(Node) {
        Node->can_id = can_id;
        Node->can_num = can_num;
        Node->id_type = id_type;
        Node->init = true;
        memset(Node->diffData, 0, CAN_MAX_PAYLOAD_SIZE);
        res = true;
    }
    return res;
}

bool can_diff_init_custom(void) {
    bool res = false;
    LOG_INFO(CAN_DIFF, "Version:%s", CAN_DIFF_VERSION);
    return res;
}

bool can_diff_proc_one(uint8_t i) {
    bool res = false;
    LOG_PARN(CAN_DIFF, "Proc:%u", i);
    CanDiffHandle_t* Node = CanDiffGetNode(i);
    if(Node) {
        Node->spin++;
    }
    return res;
}

bool can_diff_init_common(const CanDiffConfig_t* const Config, CanDiffHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->name = Config->name;
            Node->can_id = Config->can_id;
            Node->can_num = Config->can_num;
            Node->id_type = Config->id_type;
            Node->num = Config->num;
            Node->valid = Config->valid;
            res = true;
        }
    }
    return res;
}

bool can_diff_init_node(CanDiffHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->valid = true;
        res = true;
    }
    return res;
}

bool can_diff_proc_frame(const CanMessage_t* const pRxMesg) {
    bool res = false;
    if(pRxMesg) {
        uint32_t cnt = can_diff_get_cnt();
        uint32_t i = 0;
        for(i = 0; i < cnt; i++) {
            CanDiffHandle_t* Node = CanDiffGetNode(i);
            if(Node) {
                if(pRxMesg->can_bus_num == Node->can_num) {
                    if(pRxMesg->identifier.extended == Node->can_id) {
                        if(pRxMesg->id_type == Node->id_type) {
                            memcpy(&Node->MessageCur, pRxMesg, sizeof(CanMessage_t));
                            res = array_u8_xor(Node->MessageCur.data, Node->MessagePrev.data, Node->diffData,
                                               CAN_MAX_PAYLOAD_SIZE);
                            memcpy(&Node->MessagePrev, &Node->MessageCur, sizeof(CanMessage_t));
                            if(Node->live) {
                                cli_printf("\rCAN%u,ID:0x%08x,%s,%s", pRxMesg->can_bus_num,
                                           pRxMesg->identifier.extended, CanIdTypeToStr(pRxMesg->id_type),
                                           ArrayToStr(Node->diffData, CAN_MAX_PAYLOAD_SIZE));
                            }
                            res = true;
                        }
                    }
                }
            }
        }
    }
    return res;
}

bool can_diff_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN_DIFF, "CAN_DIFF%u", num);
    const CanDiffConfig_t* Config = CanDiffGetConfig(num);
    if(Config) {
        res = CanDiffIsValidConfig(Config);
        if(res) {
#ifdef HAS_CAN_DIFF_DIAG
            LOG_WARNING(CAN_DIFF, "Config:%s", CanDiffConfigToStr(Config));
#endif
            CanDiffHandle_t* Node = CanDiffGetNode(num);
            if(Node) {
                res = can_diff_init_common(Config, Node);
                res = can_diff_init_node(Node);
                Node->valid = true;
                Node->init = true;
                LOG_INFO(CAN_DIFF, "Init,Ok,%u", num);
                res = true;
            } else {
                LOG_ERROR(CAN_DIFF, "NodeErr %u", num);
            }
        } else {
            LOG_ERROR(CAN_DIFF, "ConfigErr %u", num);
        }
    } else {
        LOG_PARN(CAN_DIFF, "ConfigErr %u", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(CAN_DIFF, CAN_DIFF, can_diff)
COMPONENT_PROC_PATTERT(CAN_DIFF, CAN_DIFF, can_diff)
