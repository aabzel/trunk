#include "can_mcal.h"

#include <stdio.h>
#include <string.h>

#include "array.h"
#include "code_generator.h"
#include "common_diag.h"
#include "compiler_const.h"
#include "float_diag.h"
#include "common_functions.h"
#include "std_includes.h"

#ifdef HAS_LOG
#include "log.h"
#endif

const uint32_t CanTypicalBitRates[]={
        1000000, 800000, 500000, 250000, 125000, 100000, 95238, 83333, 50000, 47619, 33333, 20000, 10000, 5000
};

uint32_t can_get_typical_bitrate_cnt(void){
    uint32_t  cnt = ARRAY_SIZE(CanTypicalBitRates);
    return cnt;
}

#ifdef HAS_CAN_DIFF
#include "can_diff_mcal.h"
#endif

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_LED_MONO
#include "led_mono_drv.h"
#endif

#ifdef HAS_ISO_TP
#include "iso_tp_mcal.h"
#endif

#ifdef HAS_TBFP
#include "tbfp.h"
#endif

COMPONENT_GET_CONFIG(Can, can)

COMPONENT_GET_NODE(Can, can)

/*Need to adjust Enhanced CAN filters */
uint8_t can_id_type_to_bit_len(const CanIdentifier_t id_type) {
    uint8_t bit_len = 0;
    switch(id_type) {
    case CAN_FRAME_ID_STANDARD:
        bit_len = 11;
        break;
    case CAN_FRAME_ID_EXTENDED:
        bit_len = 29;
        break;
    default:
        bit_len = 0;
        break;
    }
    return bit_len;
}

bool can_is_std_id(const uint32_t can_id) {
    bool res = true;
    if(can_id <= CAN_STD_ID_MAX_VAL) {
        res = true;
    }
    return res;
}

bool can_is_ext_id(const uint32_t can_id) {
    bool res = true;
    // if(CAN_STD_ID_MAX_VAL < can_id) {
    if(can_id <= CAN_EXT_ID_MAX_VAL) {
        res = true;
    }
    //}
    return res;
}

static bool can_init_node_errors(CanHandle_t* const Node) {
    bool res = true;
    Node->error = false; // Do not reset error! It needs for unit tests
    Node->err_code = 0;
    Node->error_cnt = 0;
    Node->error_overrun_cnt = 0;
    Node->error_bus_off_cnt = 0;
    Node->error_bus_off_done_cnt = 0;
    Node->error_data_phase_cnt = 0;
    Node->error_overrun = false;
    Node->error_bus_off = false;
    Node->error_bus_off_done = false;
    Node->error_data_phase = false;
    return res;
}

static bool can_init_node_rx(CanHandle_t* const Node) {
    bool res = true;
#ifdef HAS_CAN_FD
    Node->RxMessage.bit_rate_switch = CAN_FD_BIT_RATE_SWITCH_OFF;
#endif
    Node->RxMessage.is_fd = false;
    Node->RxMessage.mesg_buff_idx = 0xFF;
    Node->RxMessage.size = CAN_MAX_PAYLOAD_SIZE;
    Node->RxMessage.can_bus_num = Node->num;
    Node->RxMessage.id_type = CAN_FRAME_ID_STANDARD;
    Node->RxMessage.frame_type = CAN_TX_FRAME_DATA;
    Node->RxMessage.identifier.standard = 0;
    memset(Node->RxMessage.data, 0, CAN_MAX_PAYLOAD_SIZE);
    Node->rx_cnt = 0;
    Node->rx_done = false;
    Node->rx_bytes = 0; // Total rx byte
    Node->unproc_rx_message = false;
    return res;
}

static bool can_init_node_warning(CanHandle_t* const Node) {
    bool res = true;
    Node->warning_tx_cnt = 0;
    Node->warning_rx_cnt = 0;
    Node->warning_tx = false;
    Node->warning_rx = false;
    return res;
}

static bool can_init_node_tx(CanHandle_t* const Node) {
    bool res = true;
    Node->tx_cnt = 0;
    Node->tx_bytes = 0; // Total tx byte
    Node->tx_done = false;
    return res;
}

bool can_init_node(CanHandle_t* const Node) {
    bool res = true;
    if(Node) {
        res = can_init_node_errors(Node);
        res = can_init_node_rx(Node);
        res = can_init_node_tx(Node);
        res = can_init_node_warning(Node);
        Node->re_init = false;
        Node->isr_cnt = 0;
        Node->isr_done = false;
        Node->heart_beat_sn = 0;
        Node->valid = true;
        Node->spin = 0;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool can_filter_allow_id(uint8_t num, const uint32_t id) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_is_my_id(uint8_t num, const uint32_t can_id) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_filter_ban_id(uint8_t num, const uint32_t id) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_mcal_transmit_message(uint8_t num, const CanMessage_t* const Message) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

#if 0
/*Data Length  code*/
uint8_t CanDlcToSize(const CanDlc_t dlc) {
    uint8_t size = 0;
    switch(dlc) {
    case CAN_DLC_0:
        size = 0;
        break;
    case CAN_DLC_1:
        size = 1;
        break;
    case CAN_DLC_2:
        size = 2;
        break;
    case CAN_DLC_3:
        size = 3;
        break;
    case CAN_DLC_4:
        size = 4;
        break;
    case CAN_DLC_5:
        size = 5;
        break;
    case CAN_DLC_6:
        size = 6;
        break;
    case CAN_DLC_7:
        size = 7;
        break;
    case CAN_DLC_8:
        size = 8;
        break;
    case CAN_DLC_12:
        size = 12;
        break;
    case CAN_DLC_16:
        size = 16;
        break;
    case CAN_DLC_20:
        size = 20;
        break;
    case CAN_DLC_24:
        size = 24;
        break;
    case CAN_DLC_32:
        size = 32;
        break;
    case CAN_DLC_48:
        size = 48;
        break;
    case CAN_DLC_64:
        size = 64;
        break;

    default:
        size = 0;
        break;
    }
    return size;
}
#endif

_WEAK_FUN_ bool can_mcal_baudrate_set(const uint8_t num, const uint32_t baudrate) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
InterfaceType_t can_num_to_interface(const uint8_t num) {
    InterfaceType_t interface_if = {0};
    interface_if.interface_name = INTERFACE_NAME_CAN;
    interface_if.num = num;
    return interface_if;
}

uint32_t can_segment_to_bit_duration_tq(const CanSegmentInfo_t* const Info) {
    uint32_t bit_diration_tq = 0;
    if(Info) {
        bit_diration_tq = Info->synchronization + Info->propagation + Info->phase_1 + Info->phase_2;
    }
    return bit_diration_tq;
}

uint8_t CanDlcToSize(const CanDlc_t dlc_code) {
    uint8_t payload_size = 0;
    if(dlc_code <= 8) {
        payload_size = dlc_code;
    } else {
        switch(dlc_code) {
        case 9:
            payload_size = 12;
            break;
        case 10:
            payload_size = 16;
            break;
        case 11:
            payload_size = 20;
            break;
        case 12:
            payload_size = 24;
            break;
        case 13:
            payload_size = 32;
            break;
        case 14:
            payload_size = 48;
            break;
        case 15:
            payload_size = 64;
            break;
        default:
            payload_size = 64;
            break;
        }
    }
    return payload_size;
}

bool can_wait_tx_done_ll(CanHandle_t* const Node) {
    bool res = true;

    uint32_t cur_ms = 0;
    uint32_t dutation_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(false == Node->tx_done) {
        cur_ms = time_get_ms32();
        dutation_ms = cur_ms - start_ms;
        if(CAN_TX_DONE_TIMEOUT_MS < dutation_ms) {
            res = false;
            LOG_ERROR(CAN, "TxTimeOut");
            break;
        }
    }
    return res;
}

static bool can_is_std_is_valid(CanMessage_t* const Message) {
    bool res = true;
    res = can_is_std_id(Message->identifier.standard);
    return res;
}

static bool can_is_ext_is_valid(CanMessage_t* const Message) {
    bool res = true;
    if(Message->identifier.extended <= CAN_EXT_ID_MAX_VAL) {
        res = true;
    }
    return res;
}

/*TODO test it*/
CanIdentifier_t can_id_val_to_id_type(const uint32_t id_val) {
    CanIdentifier_t id_type = CAN_FRAME_ID_UNDEF;
    if(id_val <= CAN_STD_ID_MAX_VAL) {
        id_type = CAN_FRAME_ID_STANDARD;
    } else {
        if(id_val <= CAN_EXT_ID_MAX_VAL) {
            id_type = CAN_FRAME_ID_EXTENDED;
        } else {
            id_type = CAN_FRAME_ID_UNDEF;
        }
    }
    return id_type;
}

bool can_is_message_valid(const CanMessage_t* const Message) {
    bool res = true;
    if(Message) {
        if(Message->size <= 64) {
            if(0 < Message->size) {
                switch(Message->id_type) {
                case CAN_FRAME_ID_STANDARD:
                    res = can_is_std_is_valid(Message);
                    log_res(CAN, res, "Std");
                    break;
                case CAN_FRAME_ID_EXTENDED:
                    res = can_is_ext_is_valid(Message);
                    log_res(CAN, res, "Ext");
                    break;
                default:
                    res = false;
                    break;
                }
            }
        }
    }
    return res;
}

bool can_tx_indication(CanHandle_t* const Node) {
    bool res = false;
    Node->tx_time_stamp = time_get_ms32();
#ifdef HAS_LED_MONO
    led_mono_sw_pwm(Node->led_num_tx, 10, 50);
#endif
    return res;
}

uint8_t can_interface_to_can_num(const InterfaceType_t interface_if) {
    uint8_t can_num = 0xFF;
    if(INTERFACE_NAME_CAN == interface_if.interface_name) {
        can_num = interface_if.num;
    }

    return can_num;
}

bool can_is_init(uint8_t num) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = Node->init_done;
    }
    return res;
}

bool can_init_common(const CanConfig_t* const Config, CanHandle_t* const Node) {
    bool res = true;
    if(Config) {
        if(Node) {
#ifdef HAS_CAN_FD
            Node->bit_rate_fd = Config->bit_rate_fd;
            Node->fd_enable = Config->fd_enable;
#endif

#ifdef HAS_LED_MONO
            Node->led_num_tx = Config->led_num_tx;
            Node->led_num_rx = Config->led_num_rx;
#endif

#ifdef HAS_GPIO
            Node->PadTx = Config->PadTx;
            Node->PadRx = Config->PadRx;
#endif
            Node->bit_rate = Config->bit_rate;
            Node->my_id = Config->my_id;
            Node->bus_off_auto_recovery = Config->bus_off_auto_recovery;
            Node->clock_source = Config->clock_source;
            Node->dma_channel_rx = Config->dma_channel_rx;
            Node->dma_channel_tx = Config->dma_channel_tx;
            Node->heart_beat = Config->heart_beat;
            Node->identifier = Config->identifier;
            Node->interrupt_on = Config->interrupt_on;
            Node->mac_mode = Config->mac_mode;
            Node->mode = Config->mode;
            Node->move_mode = Config->move_mode;
            Node->num = Config->num;
            Node->padding = Config->padding;
            Node->payload_size = Config->payload_size;
            Node->re_tx = Config->re_tx;
            Node->rx_fifo_on_off = Config->rx_fifo_on_off;
            Node->rx_id = Config->rx_id;
            Node->rx_id_cnt = Config->rx_id_cnt;
            Node->slcan_num = Config->slcan_num;
            Node->valid = Config->valid;
            Node->watermark = Config->watermark;
            res = true;
        }
    }
    return res;
}

bool CanIsValidConfig(const CanConfig_t* const Config) {
    bool res = true;
    if(Config) {
        res = true;
        ifn(Config->rx_id) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,NoRxIDinfo,Err", Config->num);
        }

        ifn(0 < Config->rx_id_cnt) {
            // res = false;
            LOG_WARNING(CAN, "CAN%u,RxIDarrayZero,Err", Config->num);
        }

        ifn(Config->mac_mode) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,MacMode,Err", Config->num);
        }

        ifn(Config->clock_source) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,ClockSource,Err", Config->num);
        }

        ifn(0 < Config->payload_size) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,PayloadSize,Err", Config->num);
        }

        ifn(0 < Config->identifier) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,ID,Err", Config->num);
        }

        ifn(Config->move_mode) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,MoveMode,Err", Config->num);
        }

        ifn(0 < Config->bit_rate) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,BitRate,Err", Config->num);
        }

        ifn(0 < Config->mode) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,Mode,Err", Config->num);
        }

        ifn(Config->name) { LOG_WARNING(CAN, "CAN%u,Name,Err", Config->num); }

        ifn(Config->rx_id) { LOG_WARNING(CAN, "CAN%u,RxId,Err", Config->num); }

#ifdef HAS_CAN_FD
        ifn(0 < Config->bit_rate_fd) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,BitRateFd,Err", Config->num);
        }

        ifn(Config->bit_rate <= Config->bit_rate_fd) {
            res = false;
            LOG_ERROR(CAN, "CAN%u,BitRatesNonSense,Err", Config->num);
        }
#endif

        if(!res) {
            LOG_ERROR(CAN, "CAN%u,Config,Err", Config->num);
        }
    }
    return res;
}

bool can_is_allowed(uint8_t num) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        const CanConfig_t* Config = CanGetConfig(num);
        if(Config) {
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool can_mcal_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_health_monitor_proc_one(uint8_t num) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_mesg_buff_rx(uint8_t can_num, uint8_t mb_idx, uint32_t can_id) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_init_custom(void) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_heartbeat_proc_one(uint8_t num) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        LOG_PARN(CAN, "CAN%u,HeartBeat,Proc", num);
        CanMessage_t Message = {0};
        Message.id_type = CAN_FRAME_ID_STANDARD;
        Message.frame_type = CAN_TX_FRAME_DATA;
        Message.identifier.standard = 0x7FF;
        Message.size = 8;
        array_incr(Message.data, 8, 0);
        snprintf((char*)Message.data, 8, "CAN%u,%u", num, Node->heart_beat_sn);
        res = can_mcal_transmit_message(num, &Message);
        if(res) {
            LOG_PARN(CAN, "CAN%u,TxOk", num);
            Node->heart_beat_sn++;
        } else {
            LOG_DEBUG(CAN, "CAN%u,TxErr", num);
        }
    }
    return res;
}

bool can_segment_info_calc(uint32_t bus_freq_hz, uint32_t baud_rate_hz, CanSegmentInfo_t* const Segment) {
    bool res = true;
    LOG_INFO(CAN, "BitRate:%u Hz", baud_rate_hz);
    if(Segment) {
        float bit_duration_s = 1.0f / ((float)baud_rate_hz);
        LOG_INFO(CAN, "BitTime:%s s", FloatBigToStr(bit_duration_s));
        float time_quanta_s = bit_duration_s / 10.0f;
        float main_prescaler = bit_duration_s / time_quanta_s;
        LOG_INFO(CAN, "MainPrescaler:%s", FloatBigToStr(main_prescaler));
        Segment->synchronization = 1;
        Segment->propagation = 3;
        Segment->phase_1 = 3;
        Segment->phase_2 = 3;
        Segment->prescaler = (uint32_t)(main_prescaler * 10.0f);
        res = true;
    }
    return res;
}

_WEAK_FUN_ bool can_segments_get(uint8_t num, CanSegmentInfo_t* const SegmentInfo) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_phy_disconnect(uint8_t num) {
    bool res = true;
#ifdef HAS_GPIO
    CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        res = gpio_deinit_pad(Config->PadTx);
        res = gpio_deinit_pad(Config->PadRx) && res;
    }
#endif
    return res;
}

_WEAK_FUN_
bool can_phy_connect(uint8_t num) {
    bool res = true;
#ifdef HAS_GPIO
    CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        res = gpio_init_pad(Config->PadTx);
        res = gpio_init_pad(Config->PadRx) && res;
    }
#endif
    return res;
}

bool can_phy_connect_ctrl(const uint8_t num, const bool on_off) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u,En:%u", num, on_off);
    if (on_off) {
        res = can_phy_connect(num);
    } else {
        res = can_phy_disconnect(num);
    }
    return res;
}

_WEAK_FUN_ bool can_init_one(uint8_t num) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_mcal_filter_id_mask_set(const uint8_t can_num,
                                 const uint8_t filt_num,
                                 const CanIdentifier_t format,
                                 const uint32_t filt_id,
                                 const uint32_t filt_mask) {
    bool res = false;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_loopback_get(const uint8_t num, bool* const on_off) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_
bool can_loopback_set(const uint8_t num, const bool on_off) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_tec_get(uint8_t num, uint32_t* const tec) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_rec_get(uint8_t num, uint32_t* const rec) {
    bool res = true;
    LOG_ERROR(CAN, "%s(),NotImplemented", __FUNCTION__);
    return res;
}

_WEAK_FUN_ bool can_proc_one(uint8_t num) {
    bool res = true;
    LOG_PARN(CAN, "CAN%u Proc", num);
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->unproc_rx_message) {
#ifdef HAS_CAN_DIAG
            LOG_NOTICE(CAN, "CAN%u,Rx:%s", num, CanMessageToStr(&Node->RxMessage));
#endif
            Node->unproc_rx_message = false;
            /*Is allowed RX*/

#ifdef HAS_CAN_DIFF
            res = can_diff_proc_frame(&Node->RxMessage);
#endif

#ifdef HAS_ISO_TP
            static IsoTpFrame_t RxFrame = {0};
            memcpy(RxFrame.data, Node->RxMessage.data, 8);
            res = iso_tp_proc_rx(num, Node->RxMessage.identifier.standard, &RxFrame);
#endif

#ifdef HAS_TBFP
            InterfaceType_t ifCan;
            ifCan.interface_name = INTERFACE_NAME_CAN;
            ifCan.num = num;
            res = tbfp_data_rx(ifCan, Node->RxMessage.data, Node->RxMessage.size);
#endif
        }
    }
    return res;
}

bool can_mcal_transmit_buff(uint8_t num, uint32_t id, const uint8_t* const data, uint8_t size) {
    bool res = true;
    if(data) {
        if(size) {
            CanMessage_t TxMessage = {0};
            TxMessage.identifier.standard = id;
            TxMessage.id_type = CAN_FRAME_ID_STANDARD;
            TxMessage.frame_type = CAN_TX_FRAME_DATA;
            TxMessage.size = size;
            memcpy(TxMessage.data, data, size);
            res = can_mcal_transmit_message(num, &TxMessage);
            // log_res_num(CAN, res, num, "Tx");
            if(res) {
#ifdef HAS_LOG
                LOG_DEBUG(CAN, "CAN%u,TxOk", num);
#endif
            } else {
#ifdef HAS_LOG
                LOG_ERROR(CAN, "CAN%u,TxErr", num);
#endif
            }
        }
    }
    return res;
}

bool can_heartbeat_proc(void) {
    bool res = true;
    uint32_t ok = 0;
#ifdef HAS_LOG
    LOG_PARN(CAN, "ProcAll:%u", CAN_COUNT);
#endif
    uint32_t num = 0;
    for(num = 0; num <= CAN_COUNT; num++) {
        res = can_heartbeat_proc_one(num);
        if(res) {
            ok++;
        }
    }
    if(ok) {
        res = true;
#ifdef HAS_LOG
        LOG_PARN(CAN, "Proc %u CAN", ok);
#endif
    } else {
        res = false;
    }
    return res;
}

bool can_health_monitor_proc(void) {
    bool res = true;
    uint32_t ok = 0;
#ifdef HAS_LOG
    LOG_PARN(CAN, "ProcAll:%u", CAN_COUNT);
#endif
    uint32_t num = 0;
    for(num = 0; num <= CAN_COUNT; num++) {
        res = can_health_monitor_proc_one(num);
        if(res) {
            ok++;
        }
    }
    if(ok) {
        res = true;
#ifdef HAS_LOG
        LOG_PARN(CAN, "ProcOk,%u,CANs", ok);
#endif
    } else {
        res = false;
    }
    return res;
}

float can_segment_to_fetch_present(const CanSegmentInfo_t* const Info) {
    float fetch_present = 0.0f;
    if(Info) {
        uint32_t bit_fetch_uptime_tq =Info->synchronization + Info->propagation + Info->phase_1;
        uint32_t bit_diration_tq = Info->synchronization + Info->propagation + Info->phase_1 + Info->phase_2;
        fetch_present = (     100.0f*((float)bit_fetch_uptime_tq)     )/(     (float)bit_diration_tq    );
    }
    return fetch_present;
}


uint32_t can_segment_to_main_pre_scaler(const CanSegmentInfo_t* const Segment) {
    uint32_t bit_prescaler = 0;
    if(Segment) {
        uint32_t bit_dur_tq = 0;
        bit_dur_tq += Segment->synchronization;
        bit_dur_tq += Segment->propagation;
        bit_dur_tq += Segment->phase_1;
        bit_dur_tq += Segment->phase_2;
        bit_prescaler = (Segment->prescaler) * bit_dur_tq;
    }
    return bit_prescaler;
}

bool can_is_valid_segment(const CanSegmentInfo_t* const Segment) {
    bool res = true;
    if(Segment) {
        res = true;
        ifn(Segment->phase_1 == Segment->phase_2) { res = false; }
        ifn(Segment->synchronization < Segment->propagation) { res = false; }
        ifn(Segment->synchronization < Segment->phase_1) { res = false; }
        ifn(Segment->synchronization < Segment->phase_2) { res = false; }
    }
    return res;
}

uint32_t can_time_seg_to_bit_rate(const uint32_t clk_freq_hz, const CanSegmentInfo_t* const Segment) {
    uint32_t bit_rate_real = 0;
    if(Segment) {
        uint32_t prescaler = can_segment_to_main_pre_scaler(Segment);
#ifdef HAS_LOG
        LOG_DEBUG(CAN, "MainPcs:%u", prescaler);
#endif
        if(prescaler) {
            bit_rate_real = clk_freq_hz / prescaler;
        }
    }
    return bit_rate_real;
}

bool can_is_my_can(const Cans_t Cans, const uint8_t num) {
    bool res = true;
    switch(num) {
    case 0:
        res = Cans.can0;
        break;
    case 1:
        res = Cans.can1;
        break;
    case 2:
        res = Cans.can2;
        break;
    case 3:
        res = Cans.can3;
        break;
    case 4:
        res = Cans.can4;
        break;
    case 5:
        res = Cans.can5;
        break;
    case 6:
        res = Cans.can6;
        break;
    case 7:
        res = Cans.can7;
        break;
    case 8:
        res = Cans.can8;
        break;
    case 9:
        res = Cans.can9;
        break;
    case 10:
        res = Cans.can10;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

_WEAK_FUN_
bool can_tx_done_reset(const uint8_t num) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->tx_done = false;
        res = true;
    }
    return res;
}

_WEAK_FUN_
bool can_is_tx_done(const uint8_t num) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = Node->tx_done;
    }
    return res;
}

_WEAK_FUN_
bool can_rx_all(const uint8_t can_num) {
    bool res = false;
    return res;
}


uint32_t can_get_alien_rx_id(const uint8_t num) {
    uint32_t ret_id = 0;
    uint32_t id = 0;
    for(id = 0; id <= CAN_EXT_ID_MAX_VAL; id++) {
        bool res = can_is_my_id(num, id);
        if(!res) {
            ret_id = id;
            break;
        }
    }
    return ret_id;
}

uint32_t can_get_first_allowed_id(const uint8_t num) {
    uint32_t id = 0;
    for(id = 0; id <= CAN_EXT_ID_MAX_VAL; id++) {
        bool res = can_is_my_id(num, id);
        if(res) {
            break;
        }
    }
    return id;
}

/* Simulate receiving a packet by simply typing it into the console */
bool can_rx_frame_manual(const uint8_t num, const CanMessage_t* const Message) {
    bool res = true;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Message) {
            memcpy(&Node->RxMessage, Message, sizeof(CanMessage_t));
            Node->unproc_rx_message = true;
            res = true;
        }
    }
    return res;
}

static bool can_compele_test_frame(const uint8_t num, uint32_t id, CanMessage_t* const Message) {
    bool res = true;
    Message->frame_type = CAN_TX_FRAME_DATA;
    Message->can_bus_num = num;
    Message->identifier.standard = CAN_STD_ID_MAX_VAL & id;
    Message->id_type = CAN_FRAME_ID_STANDARD;
    Message->size = 8;
    Message->mesg_buff_idx = 0;
    Message->is_fd = false;
    memset(Message->data, 0x55, 8);
    return res;
}

bool can_std_send_hi_load(const uint8_t num, const uint32_t frame_cnt, uint32_t pause_ms, uint32_t id) {
    bool res = true;
    uint32_t i = 0;
    uint32_t ok = 0;
    for(i = 0; i < frame_cnt; i++) {
        CanMessage_t Message = {0};
        res = can_compele_test_frame(num, id, &Message);
        res = can_mcal_transmit_message(num, &Message);
        ok = ok_cnt_update(ok, res);
        diag_progress_log(i, frame_cnt, 1000);
        wait_in_loop_ms(pause_ms);
    }

    if(ok == frame_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}


COMPONENT_PROC_PATTERT(CAN, CAN, can)
COMPONENT_INIT_PATTERT(CAN, CAN, can)
