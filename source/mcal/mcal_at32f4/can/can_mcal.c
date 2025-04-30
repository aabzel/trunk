#include "can_mcal.h"

#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"

uint32_t g_can_rx_cnt = 0;
static volatile uint8_t rx_buff[CAN_COUNT][1];

static const CanInfo_t CanInfo[] = {
#ifdef CAN1
    {
        .valid = true,
        .CANx = CAN1,
        .num = 1,
        .clock_bus = CLOCK_BUS_AHB1,
        .clock_type = CRM_CAN1_PERIPH_CLOCK,
        .irqn_tx = CAN1_TX_IRQn,
        .irqn_rx0 = CAN1_RX0_IRQn,
        .irqn_rx1 = CAN1_RX1_IRQn,
        .irqn_sce = CAN1_SE_IRQn,
    },
#endif

#ifdef CAN2
    {
        .valid = true,
        .CANx = CAN2,
        .num = 2,
        .clock_bus = CLOCK_BUS_AHB1,
        .clock_type = CRM_CAN2_PERIPH_CLOCK,
        .irqn_tx = CAN2_TX_IRQn,
        .irqn_rx0 = CAN2_RX0_IRQn,
        .irqn_rx1 = CAN2_RX1_IRQn,
        .irqn_sce = CAN2_SE_IRQn,
    }
#endif
};

COMPONENT_GET_INFO(Can)

static can_mode_type CanModeToAt32CanMode(CanMode_t mode) {
    can_mode_type mode_type = 0;
    switch((uint8_t)mode) {
    case CAN_CFG_MODE_COMMUNICATE:
        mode_type = CAN_MODE_COMMUNICATE;
        break;
    case CAN_CFG_MODE_LOOPBACK:
        mode_type = CAN_MODE_LOOPBACK;
        break;
    case CAN_CFG_MODE_LISTENONLY:
        mode_type = CAN_MODE_LISTENONLY;
        break;
    case CAN_CFG_MODE_LISTENONLY_LOOPBACK:
        mode_type = CAN_MODE_LISTENONLY_LOOPBACK;
        break;
    }
    return mode_type;
}

static confirm_state ReTxOnOfToReTxProhibit(bool re_tx) {
    confirm_state prohibit_re_tx = TRUE;
    switch((uint32_t)re_tx) {
    case true:
        prohibit_re_tx = FALSE;
        break;
    case false:
        prohibit_re_tx = TRUE;
        break;
    }
    return prohibit_re_tx;
}

// https://habr.com/ru/articles/727760/
static uint16_t can_calc_div(uint32_t apb1_freq, uint32_t bit_rate, uint8_t bts1_val, uint8_t bts2_val) {
    LOG_INFO(CAN, "CalcDiv,pclk:%u Hz,BitRate:%u Hz,BTS1:%u,BTS2:%u", apb1_freq, bit_rate, bts1_val, bts2_val);
    // 100000000.0/(500000.0*(1.0+6.0+1.0)) = 25
    uint16_t calc_div = apb1_freq / (bit_rate * ((uint32_t)(1 + bts1_val + bts2_val)));

    LOG_INFO(CAN, "CalcDiv %u", calc_div);

    return calc_div;
}

static uint8_t BitSegmentCodeToValue(uint8_t code) {
    uint8_t value = 0;
    value = code + 1;
    return value;
}

static bool can_api_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(Node->CANx) {
            if(bit_rate) {
                can_baudrate_type CanBaudrateStruct = {0};

                crm_clocks_freq_type clocks_struct = {0};
                crm_clocks_freq_get(&clocks_struct);

                LOG_INFO(CAN, "APB1Freq %u Hz", clocks_struct.apb1_freq);
                uint8_t bts1_val = BitSegmentCodeToValue(CAN_BTS1_8TQ);
                uint8_t bts2_val = BitSegmentCodeToValue(CAN_BTS2_1TQ);
                uint16_t div = can_calc_div(clocks_struct.apb1_freq, bit_rate, bts1_val, bts2_val);

                CanBaudrateStruct.baudrate_div = div;
                CanBaudrateStruct.rsaw_size = CAN_RSAW_1TQ;
                CanBaudrateStruct.bts1_size = CAN_BTS1_8TQ;
                CanBaudrateStruct.bts2_size = CAN_BTS2_1TQ;
                error_status ret = 0;
                ret = can_baudrate_set(Node->CANx, &CanBaudrateStruct);
                if(SUCCESS == ret) {
                    res = true;
                    LOG_INFO(CAN, "BitRateSetOk,%u Bit/s", bit_rate);
                } else {
                    res = false;
                    LOG_ERROR(CAN, "BitRateSetErr");
                }
            }
        }
    }
    return res;
}

static bool can_init_interrupts(CanInfo_t* const Info) {
    bool res = false;
    if(Info) {
        LOG_WARNING(CAN, "InitInt");
        /* can interrupt config */
        nvic_irq_enable(Info->irqn_sce, 5, 5);
        nvic_irq_enable(Info->irqn_rx0, 5, 5);
        nvic_irq_enable(Info->irqn_rx1, 5, 5);
        nvic_irq_enable(Info->irqn_tx, 5, 5);

        can_interrupt_enable(Info->CANx, CAN_RF0MIEN_INT, TRUE);
        /* error interrupt enable */
        can_interrupt_enable(Info->CANx, CAN_ETRIEN_INT, TRUE);
        can_interrupt_enable(Info->CANx, CAN_EOIEN_INT, TRUE);

        res = true;
    }
    return res;
}

static bool can_api_filter_init_ll(CanHandle_t* Node) {
    bool res = false;
    if(Node) {
        LOG_WARNING(CAN, "CAN%u FilterInit..", Node->num);
        can_filter_init_type CanFilterInitStruct = {0};
        /* can filter init */
        CanFilterInitStruct.filter_activate_enable = TRUE;
        CanFilterInitStruct.filter_mode = CAN_FILTER_MODE_ID_MASK;
        CanFilterInitStruct.filter_fifo = CAN_FILTER_FIFO0;
        CanFilterInitStruct.filter_number = 0;
        CanFilterInitStruct.filter_bit = CAN_FILTER_32BIT;
        CanFilterInitStruct.filter_id_high = 0;
        CanFilterInitStruct.filter_id_low = 0;
        CanFilterInitStruct.filter_mask_high = 0;
        CanFilterInitStruct.filter_mask_low = 0;
        can_filter_init(Node->CANx, &CanFilterInitStruct);
        res = true;
    }
    return res;
}

bool can_init_one(uint8_t num) {
    bool res = false;
    const CanConfig_t* Config = CanGetConfig(num);
    if(Config) {
        LOG_WARNING(CAN, "SpotCfg:%s", CanConfigTo2Str(Config));
        CanHandle_t* Node = CanGetNode(num);
        if(Node) {
            LOG_WARNING(CAN, "CAN%u Init..", num);

            Node->rx_id = Config->rx_id;
            Node->mode = Config->mode;
            Node->tx_id = Config->tx_id;
            Node->re_tx = Config->re_tx;
            Node->bit_rate = Config->bit_rate;

            CanInfo_t* Info = CanGetInfo(num);
            if(Info) {
                Node->CANx = Info->CANx;
                crm_periph_clock_enable(Info->clock_type, TRUE);
                can_base_type CanBaseStruct = {0};
                can_default_para_init(&CanBaseStruct);
                CanBaseStruct.mode_selection = CanModeToAt32CanMode(Config->mode);
                CanBaseStruct.ttc_enable = FALSE;
                CanBaseStruct.aebo_enable = TRUE;
                CanBaseStruct.aed_enable = TRUE;
                CanBaseStruct.prsf_enable = ReTxOnOfToReTxProhibit(Config->re_tx);
                CanBaseStruct.mdrsel_selection = CAN_DISCARDING_FIRST_RECEIVED;
                CanBaseStruct.mmssr_selection = CAN_SENDING_BY_ID;
                error_status ret = 0;
                ret = can_base_init(Info->CANx, &CanBaseStruct);
                if(SUCCESS == ret) {
                    LOG_INFO(CAN, "InitOk");
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(CAN, "InitErr", ret);
                }

                if(res) {
                    res = can_api_baudrate_set_ll(Node, Config->bit_rate);
                    if(res) {
                        LOG_INFO(CAN, "BaudRateSetOk");
                        res = true;
                    } else {
                        res = false;
                        LOG_ERROR(CAN, "BaudRateSetErr");
                    }
                }

                if(res) {
                    res = can_api_filter_init_ll(Node);
                    if(res) {
                        LOG_INFO(CAN, "FilterSetOk");
                        res = true;
                    } else {
                        res = false;
                        LOG_ERROR(CAN, "FilterSetErr");
                    }
                }

                if(res) {
                    res = can_init_interrupts(Info);
                }
            } else {
                res = false;
                LOG_ERROR(CAN, "InfoErr");
            }
            log_level_get_set(CAN, LOG_LEVEL_INFO);
        } else {
            res = false;
            LOG_ERROR(CAN, "NodeErr");
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NoConfig", num);
    }
    return res;
}

bool can_api_baudrate_set(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_api_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}

bool can_check(void) { return false; }

static can_identifier_type CanIdTypeToAt32IdType(CanIdentifier_t id_type) {
    can_identifier_type code = 0;
    switch((uint8_t)id_type) {
    case CAN_FRAME_ID_STANDARD:
        code = CAN_ID_STANDARD;
        break;
    case CAN_FRAME_ID_EXTENDED:
        code = CAN_ID_EXTENDED;
        break;
    }
    return code;
}

bool can_wait_tx_done(CanHandle_t* Node, can_tx_mailbox_num_type transmit_mailbox) {
    bool res = false;

    uint32_t cur_ms = 0;
    uint32_t dutation_ms = 0;
    uint32_t start_ms = time_get_ms32();
    while(1) {
        can_transmit_status_type ret = 0;
        ret = can_transmit_status_get(Node->CANx, transmit_mailbox);
        if(CAN_TX_STATUS_SUCCESSFUL == ret) {
            res = true;
            break;
        }
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

bool can_api_transmit_data(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u:Tx:%s", num, CanMessageToStr(Message));
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->CANx) {
            res = can_is_message_valid(Message);
            if(res) {
                uint8_t transmit_mailbox;
                static can_tx_message_type TxMessageStruct = {0};

                TxMessageStruct.frame_type = CAN_TFT_DATA;
                TxMessageStruct.standard_id = Message->identifier.standard;
                TxMessageStruct.extended_id = Message->identifier.extended;
                TxMessageStruct.id_type = CanIdTypeToAt32IdType(Message->id_type);
                TxMessageStruct.dlc = Message->dlc;
                memcpy(TxMessageStruct.data, Message->data, Message->dlc);

                transmit_mailbox = can_message_transmit(Node->CANx, &TxMessageStruct);
                LOG_PARN(CAN, "CAN%u,MailBox:%u", num, transmit_mailbox);
                res = true;
                // res = can_wait_tx_done(Node,(can_tx_mailbox_num_type) transmit_mailbox);
            } else {
                LOG_ERROR(CAN, "InvalidMessage");
            }
        } else {
            LOG_ERROR(CAN, "CanErr");
        }
    } else {
        LOG_DEBUG(CAN, "CAN%u NodeErr", num);
    }
    return res;
}

bool can_api_baudrate_get(uint8_t num, uint32_t* const bit_rate) {
    bool res = false;
#warning TODO implement later
    return res;
}

static CanTxFrame_t CanAt32IdTypeToCanIdType(can_trans_frame_type frame_type) {
    CanTxFrame_t frame = 0;
    switch((uint8_t)frame_type) {
    case CAN_TFT_DATA:
        frame = CAN_TX_FRAME_DATA;
        break;
    case CAN_TFT_REMOTE:
        frame = CAN_TX_FRAME_REMOTE;
        break;
    }
    return frame;
}

static CanIdentifier_t CanAt32IdToCanId(can_identifier_type id_type) {
    CanIdentifier_t Identifier = 0;
    switch((uint8_t)id_type) {
    case CAN_ID_STANDARD:
        Identifier = CAN_FRAME_ID_STANDARD;
        break;
    case CAN_ID_EXTENDED:
        Identifier = CAN_FRAME_ID_EXTENDED;
        break;
    }
    return Identifier;
}

bool CanAt32MsgToCanMsg(can_rx_message_type* RxMessageAt32, CanMessage_t* RxMessage) {
    bool res = false;
    if(RxMessageAt32) {
        if(RxMessage) {
            memcpy(RxMessage->data, RxMessageAt32->data, 8);
            RxMessage->id_type = CanAt32IdToCanId(RxMessageAt32->id_type);
            RxMessage->frame_type = CanAt32IdTypeToCanIdType(RxMessageAt32->frame_type);
            RxMessage->dlc = RxMessageAt32->dlc;
            RxMessage->identifier.extended = RxMessageAt32->extended_id;
            RxMessage->identifier.standard = RxMessageAt32->standard_id;
            res = true;
        }
    }
    return res;
}
