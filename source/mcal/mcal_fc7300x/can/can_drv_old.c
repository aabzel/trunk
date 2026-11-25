#include "can_drv.h"

#include <stdint.h>
#include <string.h>

#include "code_generator.h"
#include "data_utils.h"
#include "log.h"
#include "sys_config.h"
#include "time_utils.h"

uint32_t g_can_rx_cnt = 0;
static volatile uint8_t rx_buff[CAN_COUNT][1];

const static CanInfo_t CanInfo[] = {
#ifdef CAN1
    {
        .valid = true,
        .CANx = CAN1,
        .num = 1,
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
        .clock_type = CRM_CAN2_PERIPH_CLOCK,
        .irqn_tx = CAN2_TX_IRQn,
        .irqn_rx0 = CAN2_RX0_IRQn,
        .irqn_rx1 = CAN2_RX1_IRQn,
        .irqn_sce = CAN2_SE_IRQn,
    }
#endif
};

CanInfo_t* CanGetInfo(uint8_t num) {
    CanInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(CanInfo);
    for(i = 0; i < cnt; i++) {
        if(num == CanInfo[i].num) {
            if(CanInfo[i].valid) {
                Node = &CanInfo[i];
                break;
            }
        }
    }
    return Node;
}

static can_mode_type CanModeToFc7300xCanMode(CanMode_t mode) {
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
    switch(re_tx) {
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

bool can_api_baudrate_set_ll(CanHandle_t* const Node, uint32_t bit_rate) {
    bool res = false;
    if(Node) {
        if(Node->CANx) {
            if(bit_rate) {
                can_baudrate_type CanBaudrateStruct = {0};

                crm_clocks_freq_type clocks_struct = {0};
                crm_clocks_freq_get(&clocks_struct);

                LOG_INFO(CAN, "APB1Freq %u Hz", clocks_struct.apb1_freq);
                uint8_t bts1_val = BitSegmentCodeToValue(CAN_BTS1_6TQ);
                uint8_t bts2_val = BitSegmentCodeToValue(CAN_BTS2_1TQ);
                uint16_t div = can_calc_div(clocks_struct.apb1_freq, bit_rate, bts1_val, bts2_val);

                CanBaudrateStruct.baudrate_div = div;
                CanBaudrateStruct.rsaw_size = CAN_RSAW_1TQ;
                CanBaudrateStruct.bts1_size = CAN_BTS1_6TQ;
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

bool can_init_interrupts(CanInfo_t* const Info) {
    bool res = false;
    if(Info) {
        LOG_INFO(CAN, "InitInt");
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
        CanHandle_t* Node = CanGetNode(num);
        if(Node) {
            LOG_WARNING(CAN, "CAN%u Init..", num);
            CanInfo_t* Info = CanGetInfo(num);
            if(Info) {
                Node->CANx = Info->CANx;
                crm_periph_clock_enable(Info->clock_type, TRUE);
                can_base_type CanBaseStruct = {0};
                can_default_para_init(&CanBaseStruct);
                CanBaseStruct.mode_selection = CanModeToFc7300xCanMode(Config->mode);
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
            }
        }
    }
    return res;
}

bool can_set_baudrate(uint8_t num, uint32_t bit_rate) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_api_baudrate_set_ll(Node, bit_rate);
    }
    return res;
}

bool can_check(void) { return false; }

static can_identifier_type CanIdTypeToFc7300xIdType(CanIdentifier_t id_type) {
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

static bool can_wait_tx_done(CanHandle_t* Node, can_tx_mailbox_num_type transmit_mailbox) {
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
            break;
        }
    }
    return res;
}

bool can_api_transmit_data(uint8_t num, const CanMessage_t* const Message) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u Tx %s", num, CanMessage2Str(Message));
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(Node->CANx) {
            res = can_is_message_valid(Message);
            if(res) {
                uint8_t transmit_mailbox;
                can_tx_message_type TxMessageStruct = {0};
                TxMessageStruct.standard_id = Message->identifier.standard;
                TxMessageStruct.extended_id = Message->identifier.extended;
                TxMessageStruct.id_type = CanIdTypeToFc7300xIdType(Message->id_type);
                TxMessageStruct.frame_type = CAN_TFT_DATA;
                TxMessageStruct.dlc = Message->dlc;
                memcpy(TxMessageStruct.data, Message->data, 8);

                transmit_mailbox = can_message_transmit(Node->CANx, &TxMessageStruct);
                LOG_INFO(CAN, "CAN%u,MailBox:%u", num, transmit_mailbox);
                res = can_wait_tx_done(Node, transmit_mailbox);
            }
        }
    }
    return res;
}

/* ISR code */
bool CanSwIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(1);
    if(Node) {
        __IO uint32_t err_index = 0;
        flag_status ret = 0;
        ret = can_interrupt_flag_get(Node->CANx, CAN_ETR_FLAG);
        if(SET == ret) {
            res = true;
            err_index = Node->CANx->ests & 0x70;
            can_flag_clear(Node->CANx, CAN_ETR_FLAG);
            /* error type is stuff error */
            if(err_index == 0x00000010) {
                /* when stuff error occur: in order to ensure communication normally,
                user must restart can or send a frame of highest priority message here */
            }
        }
    }
    return res;
}

bool CanRxFifoxIRQHandler(uint8_t num, uint32_t can_flag, can_rx_fifo_num_type rx_fifo_num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(1);
    if(Node) {
        flag_status ret;
        ret = can_interrupt_flag_get(Node->CANx, can_flag);
        if(SET == ret) {
            can_rx_message_type rx_message_struct = {0};
            can_message_receive(Node->CANx, rx_fifo_num, &rx_message_struct);
            res = true;
        }
    }
    return res;
}
bool CanCheckIsrMailBox(CanHandle_t* Node, uint32_t can_flag) {
    bool res = false;
    flag_status ret = 0;
    ret = can_interrupt_flag_get(Node->CANx, can_flag);
    if(SET == ret) {
        res = true;
        can_flag_clear(Node->CANx, can_flag);
    }
    return res;
}

bool CanTxIRQHandler(uint8_t num) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        bool res = true;
        res = CanCheckIsrMailBox(Node, CAN_TM0TCF_FLAG) && res;
        res = CanCheckIsrMailBox(Node, CAN_TM1TCF_FLAG) && res;
        res = CanCheckIsrMailBox(Node, CAN_TM2TCF_FLAG) && res;
    }
    return res;
}
