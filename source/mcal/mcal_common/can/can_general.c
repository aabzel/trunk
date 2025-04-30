#include "can_mcal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "log.h"

#ifdef HAS_ISO_TP
#include "iso_tp.h"
#endif

COMPONENT_GET_CONFIG(Can, can)

COMPONENT_GET_NODE(Can, can)

static bool can_is_std_is_valid(CanMessage_t* const Message) {
    bool res = false;
    if(Message->identifier.standard <= 0x7FF) {
        res = true;
    }
    return res;
}

static bool can_is_ext_is_valid(CanMessage_t* const Message) {
    bool res = false;
    if(Message->identifier.extended <= 0x1FFFFFFF) {
        res = true;
    }
    return res;
}

bool can_is_message_valid(CanMessage_t* const Message) {
    bool res = false;
    if(Message) {
        if(Message->dlc <= 8) {
            if(0 < Message->dlc) {
                switch((uint8_t)Message->id_type) {
                case CAN_FRAME_ID_STANDARD:
                    res = can_is_std_is_valid(Message);
                    break;
                case CAN_FRAME_ID_EXTENDED:
                    res = can_is_ext_is_valid(Message);
                    break;
                }
            }
        }
    }
    return res;
}

bool can_init_custom(void){
    return true;
}

bool can_is_init(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

bool can_is_allowed(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        const CanConfig_t* Config = CanGetConfig(num);
        if(Config) {
            res = true;
        }
    }
    return res;
}

bool can_heartbeat_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u heartbeat poc", num);
    CanMessage_t Message = {0};
    Message.id_type = CAN_FRAME_ID_STANDARD;
    Message.frame_type = CAN_TX_FRAME_DATA;
    Message.identifier.standard = 0x7FF;
    Message.dlc = 1;
    Message.data[0] = 'h';
    res = can_api_transmit_data(num, &Message);
    if(res) {
        LOG_DEBUG(CAN, "CAN%u TxOk", num);
    } else {
        LOG_DEBUG(CAN, "CAN%u TxErr", num);
    }
    return res;
}

bool can_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->unproc_rx_message) {
            LOG_NOTICE(CAN, "CAN%u,Rx:%s", num, CanMessage2Str(&Node->RxMessage));
            Node->unproc_rx_message = false;
#ifdef HAS_ISO_TP
            static IsoTpFrame_t RxFrame = {0};
            memcpy(RxFrame.data, Node->RxMessage.data, 8);
            res = iso_tp_proc_rx(num, Node->RxMessage.identifier.standard, &RxFrame);
#endif
        }
    }
    return res;
}

bool can_api_transmit_buff(uint8_t num, uint16_t id, const uint8_t* const data, uint8_t size) {
    bool res = false;
    if(data) {
        if(size) {
            CanMessage_t TxMessage = {0};
            TxMessage.identifier.standard = id;
            TxMessage.id_type = CAN_FRAME_ID_STANDARD;
            TxMessage.frame_type = CAN_TX_FRAME_DATA;
            TxMessage.dlc = size;
            memcpy(TxMessage.data, data, size);
            res = can_api_transmit_data(num, &TxMessage);
            if(res) {
                LOG_DEBUG(CAN, "CAN%u TxOk", num);
            } else {
                LOG_DEBUG(CAN, "CAN%u TxErr", num);
            }
        }
    }
    return res;
}

bool can_send_api(uint8_t num, uint8_t* array, uint16_t size) {
    bool res = false;
    return res;
}

bool can_heartbeat_proc(void) {
    bool res = true;
    uint32_t ok = 0;
    uint32_t cnt = can_get_cnt();
    LOG_PARN(CAN, "ProcAll:%u", cnt);
    uint32_t num = 0;
    for(num = 0; num <= cnt; num++) {
        res = can_heartbeat_proc_one(num);
        if(res) {
            LOG_PARN(CAN, "CAN%u Proc Ok", num);
            ok++;
        } else {
            LOG_PARN(CAN, "CAN%u Proc Err", num);
        }
    }
    if(ok) {
        res = true;
        LOG_PARN(CAN, "Proc %u CAN", ok);
    } else {
        res = false;
    }
    return res;
}


COMPONENT_PROC_PATTERT(CAN, CAN, can)

COMPONENT_INIT_PATTERT(CAN, CAN, can)
