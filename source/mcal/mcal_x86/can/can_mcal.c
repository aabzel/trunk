#include "can_mcal.h"

#include <stdio.h>
#include <string.h>

#include "array.h"
#include "can_custom.h"
#include "code_generator.h"
#include "common_diag.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

#ifdef HAS_SLCAN
#include "slcan.h"
#endif

static const CanInfo_t CanInfo[] = {
#ifdef HAS_CAN0
    {
        .num = 0,
        .valid = true,
    },
#endif
};

COMPONENT_GET_INFO(Can)


#if 0
InterfaceType_t can_num_to_interface(uint8_t can_num) {
    InterfaceType_t interface_if = {0};
    uint32_t cnt = ARRAY_SIZE(CanInterfaceInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(CanInterfaceInfo[i].valid) {
            if(can_num == CanInterfaceInfo[i].num) {
                interface_if = CanInterfaceInfo[i].interface_if;
                break;
            }
        }
    }
    return interface_if;
}
#endif

#ifdef HAS_CAN_FD
static bool can_fd_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(bit_rate) {
        }
    }
    return res;
}
#endif

static bool can_mcal_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(bit_rate) {
#ifdef HAS_SLCAN
            res = slcan_baud_rate_set(1, bit_rate);
#endif
        }
    }
    return res;
}

#ifdef HAS_CAN_FD
bool can_fd_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_fd_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}
#endif

CanClockSource_t can_get_clk_src(const uint8_t num) {
    CanClockSource_t clk_src = 0;
    return clk_src;
}

bool can_mcal_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_mcal_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}

uint32_t can_base_clock_get(uint8_t num) {
    uint32_t base_clock = 0;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return base_clock;
}

bool can_check(void) { return false; }

bool can_mcal_transmit_message(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u:Tx:%s", num, CanMessageToStr(Message));
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_is_message_valid(Message);
        if(res) {
            res = false;
#ifdef HAS_SLCAN
            res = slcan_transmit_message(Node->slcan_num, Message);
            log_res(CAN, res, "SlCanTxMesg");
#endif
        } else {
            LOG_ERROR(CAN, "InvalidMessage");
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NodeErr", num);
    }
    return res;
}

#ifdef HAS_CAN_FD
bool can_fd_send(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        LOG_DEBUG(CAN_FD, "CAN%u,Send:%s", num, CanMessageToStr(Message));
    }
    return res;
}
bool can_fd_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    if(bit_rate) {
    }
    return res;
}
#endif

bool can_mcal_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
    if(bit_rate) {
        LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    }
    return res;
}

bool can_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->unproc_rx_message) {
#ifdef HAS_ISO_TP
            int8_t iso_tp_num = iso_tp_can_num_to_iso_tp_num(num);
            if(0 <= iso_tp_num) {
                res = iso_tp_rx_message((uint8_t)iso_tp_num, &Node->RxMessage);
            }
#endif
            memset(&Node->RxMessage, 0, sizeof(CanMessage_t));
            Node->unproc_rx_message = false;
        }
    }
    return res;
}

bool can_mesg_buff_rx(uint8_t can_num, uint8_t mb_idx, uint32_t can_id) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

bool can_health_monitor_proc_one(uint8_t num) {
    bool res = true;
    LOG_PARN(CAN, "CAN%u,Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
    }
    return res;
}

bool can_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotUsed", __FUNCTION__);
    return res;
}

bool can_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotUsed", __FUNCTION__);
    return res;
}

bool can_loopback_get(const uint8_t num, bool* const on_off) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

CanMacMode_t can_get_mac_mode(const uint8_t num) {
    CanMacMode_t mac_mode = CAN_MAC_PC_EMULATED;
    return mac_mode;
}

bool can_mcal_filter_id_mask_set(const uint8_t can_num,
                                 const uint8_t filt_num,
                                 const CanIdentifier_t format,
                                 const uint32_t filt_id,
                                 const uint32_t filt_mask) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}


bool can_loopback_set(const uint8_t num, const bool on_off) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

bool can_phy_disconnect(uint8_t num) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

bool can_phy_connect(uint8_t num) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

bool can_is_my_id(uint8_t num, const uint32_t can_id) {
    bool res = true;
    return res;
}

bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo) {
    bool res = false;
    return res;
}

bool can_filter_allow_id(uint8_t num, const uint32_t id) {
    bool res = false;
    return res;
}

bool can_filter_ban_id(uint8_t num, const uint32_t id) {
    bool res = false;
    return res;
}

bool can_init_custom(void) {
    bool res = true;
    LOG_WARNING(CAN, "CustomInit");
#ifdef HAS_SLCAN
    res = slcan_mcal_init();
#endif
    return res;
}

bool can_tx_done_reset(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->tx_done = false;
        res = true;
    }
    return res;
}

bool can_is_tx_done(const uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = Node->tx_done;
    }
    return res;
}


bool can_rx_all(const uint8_t can_num) {
    bool res = false;
    return res;
}

bool can_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(CAN, "CAN%u,Init..", num);
    const CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        LOG_WARNING(CAN, "SpotCfg:%s", CanConfigToStr(Config));
        res = CanIsValidConfig(Config);
        if(res) {
            CanHandle_t* Node = CanGetNode(num);
            if(Node) {
                res = can_init_common(Config, Node);
                res = can_init_node(Node);
                CanInfo_t* Info = CanGetInfo(num);
                if(Info) {
#ifdef HAS_SLCAN
                    res = slcan_baud_rate_set(1, Config->bit_rate);
                    res = slcan_mode_set(1, SLCAN_MODE_NORMAL);
                    res = slcan_open(1);
#endif
                    Node->heart_beat_sn = num;
                    /*Default SlCan config not always valid due to COM port number for slcan*/
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(CAN, "CAN%u,InfoErr", num);
                }
                log_level_get_set(CAN, LOG_LEVEL_INFO);
            } else {
                res = false;
                LOG_ERROR(CAN, "NodeErr");
            }
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NoConfig", num);
    }
    return res;
}
