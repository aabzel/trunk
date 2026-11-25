#include "can_message_buffer.h"

#include "bit_utils.h"
#include "can_custom_diag.h"
#include "can_diag.h"
#include "can_mailbox_config.h"
#include "can_mcal.h"
#include "can_misc.h"
#include "code_generator.h"
#include "common_functions.h"
#include "log.h"

static bool CanIsValidMailBoxConfig(const CanMessageBufferConfig_t* const MailBox) {
    bool res = false;
    if(MailBox) {
        res = true;
        ifn(MailBox->direction) {
            LOG_ERROR(CAN, "MbDirErr");
            res = false;
        }

        ifn(MailBox->id_type) {
            LOG_ERROR(CAN, "CanIdTypeErr");
            res = false;
        }

        if(31 < MailBox->mb_index) {
            LOG_ERROR(CAN, "MbIndexBigErr");
            res = false;
        }

        if(0 == MailBox->cans.word) {
            LOG_ERROR(CAN, "MbNoCanNumErr");
            res = false;
        }

        if((~WORD_MASK_10BIT) & MailBox->cans.word) {
            LOG_ERROR(CAN, "MbCanNumBigErr,CANs:0x%x", MailBox->cans.word);
            res = false;
        }

        ifn(MailBox->name) {
            LOG_ERROR(CAN, "MbCanNameErr");
            res = false;
        }

        if(0x20000000 < MailBox->frame_id) {
            LOG_ERROR(CAN, "MbIDtooBigErr");
            res = false;
        }
    }
    return res;
}

bool can_message_buffer_to_mb_setting(const CanMessageBufferConfig_t* const MbConfig,
                                      FLEXCAN_MbSettingType* const MbSetting) {
    bool res = false;
    if(MbConfig) {
        if(MbSetting) {
            /* 0 is rx, 1 is tx */
            MbSetting->bIsTxMB = CanMessageBuffDirToIsTx(MbConfig->direction);
            /* if enable can current MB interrupt, set 1U */
            MbSetting->bEnMBInt = MbConfig->interrupt_on;
            /* FLEXCAN ID type, 0 STD, 1 EXT */
            MbSetting->eRxFrameType = CanMessageBuffetIdTypeToFrameType(MbConfig->id_type);
            /* FLEXCAN received ID */
            MbSetting->u32RxCanId = MbConfig->frame_id;
            /* FLEXCAN received ID mask, if mask bit is 1, received FLEXCAN
             * id bit must same to u32RxCanId, or mask bit is 0, id bit is ignored */
            MbSetting->u32RxCanIdMask = MASK_29BIT;
            res = true;
        }
    }
    return res;
}

bool can_mailbox_interrupt_flag_clear(uint8_t num, uint8_t mailbox_num) {
    bool res = false;
    LOG_DEBUG(CAN, "CAN%u,ClrIntFlag,MailBox:%u", num, mailbox_num);
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegIFLAG1_t IFLAG1 = {0};
        IFLAG1.dword = FLEXCAN_HWA_GetFlag1(Info->CANx);
        SET_BIT_NUM(IFLAG1.dword, mailbox_num);
        Info->CANx->IFLAG1 = IFLAG1.dword;
        FLEXCAN_HWA_SetFlag1(Info->CANx, IFLAG1.dword);
        res = true;
    }
    return res;
}

bool can_mailbox_interrupt_mask_set(uint8_t num, uint8_t mailbox_num, bool on_off) {
    bool res = false;
    LOG_INFO(CAN, "CAN%u,SetInt,MailBox:%u,En:%u", num, mailbox_num, on_off);
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegIMASK1_t Reg = {0};
        Reg.dword = FLEXCAN_HWA_GetMask1(Info->CANx);
        Reg.dword = bit_ctrl(Reg.dword, mailbox_num, on_off);
        FLEXCAN_HWA_SetMask1MbInterrupt(Info->CANx, Reg.dword);
        res = true;
    }
    return res;
}

bool can_init_mail_box_tx(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(Config->num);
    if(Node) {
        // Init->tMbCfg.aDataWidthRange=;
        /* Can Tx MB and Filter configuration parameter*/
        uint32_t m = 0;
        uint32_t ok_cnt = 0;
        uint32_t cnt = can_mailbox_get_cnt();
        for(m = 0; m < cnt; m++) {
            CanMessageBufferConfig_t* MbConfig = &CanMessageBufferConfig[m];
            res = CanIsValidMailBoxConfig(MbConfig);
            if(res) {
                res = CHECK_BIT_NUM(MbConfig->cans.word, Config->num);
                if(res) {
                    if(CONNECT_DIR_TRANSMIT == MbConfig->direction) {
                        uint8_t mb_index = MbConfig->mb_index;
                        LOG_INFO(CAN, "%s", CanMessageBufferConfigToStr(MbConfig));
                        res = can_mailbox_interrupt_flag_clear(Config->num, mb_index);
                        res = can_mailbox_interrupt_mask_set(Config->num, mb_index, true);
                        res = can_mailbox_direction_set(Config->num, mb_index, MbConfig->direction);
                        if(res) {
#if 0
                            res = can_message_buffer_to_mb_setting(&CanMessageBufferConfig[m],
                                    &Node->aMbList[mb_index]);
                            if(res) {
                                LOG_INFO(CAN, "%s", FlexCanMbSettingToStr(&Node->aMbList[mb_index]));
                            }
                            ok_cnt = ok_cnt_update(ok_cnt, res);
#endif
                        }
                    }
                }
            }
        }
#if 0
        Init->tMbCfg.pMBList = Node->aMbList;
#endif
        Init->tMbCfg.u8MBCnt = ok_cnt;
        Init->tMbCfg.aDataWidthRange[0] = FLEXCAN_DATAWIDTH_8;
        res = true;
    }

    return res;
}

bool can_config_mail_box_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) {
    bool res = false;
    if(CAN_MAC_MODE_MESSAGE_BUFFER == Config->mac_mode) {
        CanHandle_t* Node = CanGetNode(Config->num);
        if(Node) {
            /* Can Tx MB and Rx MB Filter configuration parameter*/
            uint32_t m = 0;
            uint32_t ok_cnt = 0;
            uint32_t cnt = can_mailbox_get_cnt();
            for(m = 0; m < cnt; m++) {
                CanMessageBufferConfig_t* MbConfig = &CanMessageBufferConfig[m];
                res = CanIsValidMailBoxConfig(MbConfig);
                if(res) {
                    res = CHECK_BIT_NUM(MbConfig->cans.word, Config->num);
                    if(res) {
                        uint8_t mb_index = MbConfig->mb_index;

                        LOG_INFO(CAN, "%s", CanMessageBufferConfigToStr(MbConfig));
                        res = can_mailbox_interrupt_flag_clear(Config->num, mb_index);
                        res = can_mailbox_interrupt_mask_set(Config->num, mb_index, true);
                        res = can_mailbox_direction_set(Config->num, mb_index, MbConfig->direction);
                        if(res) {
#if 0
                            res = can_message_buffer_to_mb_setting(&CanMessageBufferConfig[m],
                                    &Node->aMbList[mb_index]);
                            if(res) {
                                LOG_INFO(CAN, "%s", FlexCanMbSettingToStr(&Node->aMbList[mb_index]));
                            }
#endif
                            ok_cnt = ok_cnt_update(ok_cnt, res);
                        }
                    }
                }
            }
#if 0
            Init->tMbCfg.pMBList = Node->aMbList;
#endif
            Init->tMbCfg.u8MBCnt = ok_cnt;
            Init->tMbCfg.aDataWidthRange[0] = FLEXCAN_DATAWIDTH_8;
            res = true;
        }
    }
    return res;
}

CanMessageBufferConfig_t* CanMessageBufferConfigGet(const uint8_t num, const uint32_t frame_id) {
    CanMessageBufferConfig_t* MbConfig = NULL;
    uint32_t cnt = can_mailbox_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        bool res = can_is_my_can(CanMessageBufferConfig[i].cans, num);
        if(res) {
            if(frame_id == CanMessageBufferConfig[i].frame_id) {
                MbConfig = &CanMessageBufferConfig[i];
                break;
            }
        }
    }
    return MbConfig;
}

/* TODO explore MB RAM to spot ID for RX */
bool can_message_buffer_id_check(const uint8_t num, const uint32_t frame_id) {
    bool res = false;
    CanMessageBufferConfig_t* MbConfig = CanMessageBufferConfigGet(num, frame_id);
    if(MbConfig) {
        if(CONNECT_DIR_RECEIVER == MbConfig->direction) {
            res = true;
        }
    }

    return res;
}

bool can_is_mode_message_buffer(const uint8_t num) {
    bool res = true;
    return res;
}

bool can_mailbox_direction_set(uint8_t num, uint8_t mailbox_num, ConnectivitDir_t dir) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
#if 0

        RESET_BIT_NUM(Node->Handle.tStatus.aRxInterruptMask[0], mailbox_num);
        RESET_BIT_NUM(Node->Handle.tStatus.aTxInterruptMask[0], mailbox_num);

        SET_BIT_NUM(Node->Handle.tStatus.aInterruptMask[0], mailbox_num);

        switch(dir) {
        case CONNECT_DIR_TRANSMIT: {
            SET_BIT_NUM(Node->Handle.tStatus.aTxInterruptMask[0], mailbox_num);
            res = true;
        } break;
        case CONNECT_DIR_RECEIVER: {
            SET_BIT_NUM(Node->Handle.tStatus.aRxInterruptMask[0], mailbox_num);
            res = true;
        } break;
        case CONNECT_DIR_RX_TX: {
            SET_BIT_NUM(Node->Handle.tStatus.aRxInterruptMask[0], mailbox_num);
            SET_BIT_NUM(Node->Handle.tStatus.aTxInterruptMask[0], mailbox_num);
            res = true;
        } break;
        default:
            res = false;
            break;
        }
#endif
    }
    return res;
}

ConnectivitDir_t can_mailbox_direction_get(uint8_t num, uint8_t mailbox_num) {
    ConnectivitDir_t direction = CONNECT_DIR_UNDEF;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
#if 0
        bool is_rx = CHECK_BIT_NUM(Node->Handle.tStatus.aRxInterruptMask[0], mailbox_num);
        bool is_tx = CHECK_BIT_NUM(Node->Handle.tStatus.aTxInterruptMask[0], mailbox_num);
        direction = connectivit_compose_direction(is_rx, is_tx);
#endif
    }
    return direction;
}

uint8_t can_message_buffer_to_size(const CanMessageBufferDataSize_t mbdsr0) {
    uint8_t mb_size = 8;
    switch(mbdsr0) {
    case CAN_MESG_BUFF_DATA_SIZE_8_BYTE: {
        mb_size = 8;
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_16_BYTE: {
        mb_size = 16;
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_32_BYTE: {
        mb_size = 32;
    } break;
    case CAN_MESG_BUFF_DATA_SIZE_64_BYTE: {
        mb_size = 64;
    } break;
    default:
        mb_size = 0;
        break;
    }
    return mb_size;
}

bool can_last_message_buffer_number_get(uint8_t num, uint8_t* const maxmb) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegMCR_t MCR = {0};
        MCR.dword = FLEXCAN_HWA_GetMCR(Info->CANx);
        if(maxmb) {
            *maxmb = MCR.MAXMB;
            res = true;
        }
    }
    return res;
}

bool can_last_message_buffer_number_set(uint8_t num, uint8_t maxmb) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        can_freeze_ctrl(num, true);
        CanRegMCR_t MCR = {0};
        MCR.dword = FLEXCAN_HWA_GetMCR(Info->CANx);
        MCR.MAXMB = maxmb;
        FLEXCAN_HWA_SetMCR(Info->CANx, MCR.dword);
        can_freeze_ctrl(num, false);
        res = true;
    }
    return res;
}

bool can_mailbox_interrupt_mask_get(uint8_t num, uint8_t mailbox_num) {
    bool res = false;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegIMASK1_t Reg;
        Reg.dword = FLEXCAN_HWA_GetMask1(Info->CANx);
        res = GET_BIT_NUM(Reg.dword, mailbox_num);
        LOG_DEBUG(CAN, "CAN%u,GetInt,Mb:%u,En:%u", num, mailbox_num, res);
    }
    return res;
}
