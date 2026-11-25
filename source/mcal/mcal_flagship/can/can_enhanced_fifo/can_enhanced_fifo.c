#include "can_enhanced_fifo.h"

#include "bit_utils.h"
#include "can_mcal.h"
#include "can_misc.h"
#include "log.h"

uint8_t can_ext_id_filter_element_cnt_get(uint8_t num) {
    uint8_t ext_id_filter_element_cnt = 0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegERFCR_t ERFCR;
        ERFCR.dword = Info->CANx->ERFCR;
        ext_id_filter_element_cnt = (uint8_t)ERFCR.NEXIF;
    }
    return ext_id_filter_element_cnt;
}

uint8_t can_std_id_filter_element_cnt_get(uint8_t num) {
    uint8_t std_id_filter_element_cnt = 0;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegERFCR_t ERFCR;
        ERFCR.dword = Info->CANx->ERFCR;
        /* NFE=3 NEXIF=2*/
        std_id_filter_element_cnt = (ERFCR.NFE + 1) * 2 - ((uint8_t)ERFCR.NEXIF * 2);
    }
    return std_id_filter_element_cnt;
}

/* 58.8.50 FLEXCAN_ERFSR (Enhanced Rx FIFO Status Register)  */
bool can_proc_erfsr(CanHandle_t* Node) {
    CanRegERFSR_t ERFSR;
    ERFSR.dword = Node->CANx->ERFSR;
    bool res = false;

    if(ERFSR.ERFOVF) {
        LOG_ERROR(CAN, "CAN%u,EnhancedRxFIFO_OverFlow", Node->num);
        res = true;
    }

    if(ERFSR.ERFF) {
        LOG_WARNING(CAN, "CAN%u,EnhancedRxFIFOfull", Node->num);
        res = true;
    }

    if(ERFSR.ERFDA) {
        LOG_INFO(CAN, "CAN%u,FrameAvailable. %u Frames!", Node->num, ERFSR.ERFEL);
        res = true;
    }

    if(ERFSR.ERFWMI) {
        uint32_t watermark = can_enhanced_watermark_get(Node->num);
        LOG_WARNING(CAN, "CAN%u,RxWatermark:%u<=%u,Frames", Node->num, watermark, ERFSR.ERFEL);
        res = true;
    }

    if(ERFSR.ERFEL) {
        if(0 < ERFSR.ERFEL) {
            LOG_INFO(CAN, "CAN%u,NumberOfCANmessagesInFIFO:%u Elements", Node->num, ERFSR.ERFEL);
        } else {
            LOG_DEBUG(CAN, "CAN%u,NumberOfCANmessagesInFIFO:%u Elements", Node->num, ERFSR.ERFEL);
        }
        res = true;
    }

    if(ERFSR.ERFE) {
        LOG_PARN(CAN, "CAN%u,EnhancedRxFIFOempty", Node->num);
        res = true;
    }

    if(ERFSR.ERFUFW) {
        LOG_PARN(CAN, "CAN%u,EnhancedRxFIFO_UndefFlow", Node->num);
        res = true;
    }

    return res;
}

bool can_init_rx_fifo_enhanced_default(FLEXCAN_InitType* const pInit) {
    bool res = true;

    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.bWaterMarkInt = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.eFifoDataLength = FLEXCAN_DATAWIDTH_64;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = 0U;
    pInit->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = NULL;
    return res;
}

static bool can_enhanced_init_filters(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) {
    bool res = false;
    LOG_WARNING(CAN, "CAN%u,EnhancedFifoInitFiltefs", Config->num);
    CanHandle_t* Node = CanGetNode(Config->num);
    if(Node) {
        uint32_t i = 0;
        uint32_t filter_cnt = ARRAY_SIZE(Node->EnhancedFifoFilterList);
        LOG_WARNING(CAN, "CAN%u,EnhancedFifoInitFiltefs", Config->num);
        for(i = 0; i < Node->rx_id_cnt; i++) {
            if(i < filter_cnt) {
                FLEXCAN_FifoFilterType* FifoFilter = NULL;
                FifoFilter = &(Node->EnhancedFifoFilterList[i]);
                CanIdentifier_t id_size = can_id_val_to_id_type(Node->rx_id[i]);
                /*FLEXCAN ID type, 0 STD, 1 EXT */
                FifoFilter->eRxFrameType = CanMessageBuffetIdTypeToFrameType(id_size);
                /*FLEXCAN received ID */
                FifoFilter->u32RxCanId = Node->rx_id[i];
                LOG_INFO(CAN, "CAN%u,FILT_%u,SetRxFor:0x%x", Config->num, i, Node->rx_id[i]);
                /* FLEXCAN received ID mask, if mask bit is 1, received CAN_ID bit must
                 * same to u32RxCanId, or mask bit is 0, id bit is ignored*/
                uint8_t bit_len = can_id_type_to_bit_len(id_size);
                FifoFilter->u32RxCanIdMask = generate_32bit_mask(bit_len);
            }
        }
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = Node->EnhancedFifoFilterList;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = Node->rx_id_cnt;
        res = true;
    } else {
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.pRxFilterFifoList = NULL;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.u8RxFilterFifoCnt = 0;
    }
    return res;
}

static bool can_enhanced_init_tx(uint32_t num, FLEXCAN_InitType* const Init) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        Node->aMbList[0].bIsTxMB = CONNECT_DIR_TRANSMIT;
        Node->aMbList[0].bEnMBInt = 1;
        Node->aMbList[0].eRxFrameType = FLEXCAN_ID_STD;
        Node->aMbList[0].u32RxCanId = 0;
        Node->aMbList[0].u32RxCanIdMask = 0;

        Node->aMbList[1].bIsTxMB = CONNECT_DIR_TRANSMIT;
        Node->aMbList[1].bEnMBInt = 1;
        Node->aMbList[1].eRxFrameType = FLEXCAN_ID_EXT;
        Node->aMbList[1].u32RxCanId = 0;
        Node->aMbList[1].u32RxCanIdMask = 0;

        Node->aMbList[2].bIsTxMB = CONNECT_DIR_RECEIVER;
        Node->aMbList[2].bEnMBInt = 1;
        Node->aMbList[2].eRxFrameType = FLEXCAN_ID_STD;
        Node->aMbList[2].u32RxCanId = 0;
        Node->aMbList[2].u32RxCanIdMask = 0;

        Node->aMbList[3].bIsTxMB = CONNECT_DIR_RECEIVER;
        Node->aMbList[3].bEnMBInt = 1;
        Node->aMbList[3].eRxFrameType = FLEXCAN_ID_EXT;
        Node->aMbList[3].u32RxCanId = 0;
        Node->aMbList[3].u32RxCanIdMask = 0;

#if 0
        Node->aMbList[1].bIsTxMB = CONNECT_DIR_TRANSMIT;
        Node->aMbList[1].bEnMBInt = 0;
        Node->aMbList[1].eRxFrameType = FLEXCAN_ID_STD;
        Node->aMbList[1].u32RxCanId = 0;
        Node->aMbList[1].u32RxCanIdMask = 0;

        Node->aMbList[3].bIsTxMB = CONNECT_DIR_TRANSMIT;
        Node->aMbList[3].bEnMBInt = 0;
        Node->aMbList[3].eRxFrameType = FLEXCAN_ID_EXT;
        Node->aMbList[3].u32RxCanId = 0;
        Node->aMbList[3].u32RxCanIdMask = 0;

        Node->aMbList[5].bIsTxMB = CONNECT_DIR_RECEIVER;
        Node->aMbList[5].bEnMBInt = 0;
        Node->aMbList[5].eRxFrameType = FLEXCAN_ID_STD;
        Node->aMbList[5].u32RxCanId = 0;
        Node->aMbList[5].u32RxCanIdMask = 0;
#endif

        Init->tMbCfg.pMBList = Node->aMbList;
        Init->tMbCfg.u8MBCnt = 4;
    }
    return res;
}

bool can_config_enhanced_fifo_init(const CanConfig_t* const Config, FLEXCAN_InitType* const Init) {
    bool res = false;
    if(CAN_MAC_MODE_ENHANCED_FIFO == Config->mac_mode) {

        res = can_enhanced_init_tx(Config->num, Init);

        Init->tRxFifoFilterCfg.bEnFifo = CanMacModeToEnableFifo(Config->mac_mode);
        Init->tRxFifoFilterCfg.eFifoType = CanMacModeToFifoType(Config->mac_mode);

        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.bEnFifoDMA = FALSE;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.bDataAvaliableInt = TRUE;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.bOverflowInt = TRUE;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.bUnderflowInt = TRUE;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.bWaterMarkInt = TRUE;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.eFifoDataLength = FLEXCAN_DATAWIDTH_8;
        Init->tRxFifoFilterCfg.tEnhancedFifoCfg.u8FifoWaterMark = Config->watermark;
        res = can_enhanced_init_filters(Config, Init);
    }
    return res;
}

uint32_t can_enhanced_watermark_get(uint32_t num) {
    uint32_t watermark = 0;
    CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegERFCR_t ERFCR;
        ERFCR.dword = Info->CANx->ERFCR;
        watermark = ERFCR.ERFWM;
    }
    return watermark;
}

bool can_enhanced_watermark_set(uint32_t num, uint32_t watermark) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        CanRegERFCR_t ERFCR;
        ERFCR.dword = Node->CANx->ERFCR;
        ERFCR.ERFWM = watermark;
        Node->CANx->ERFCR = ERFCR.dword;
        res = true;
    }
    return res;
}

static bool can_is_valid_std_id_filter0(const uint32_t id, const uint32_t filter) {
    bool res = false;
    CanStdFiltElement0_t FilterScheme0;
    FilterScheme0.dword = filter;
    uint32_t ok_cnt = 0;
    uint32_t b = 0;
    for(b = 0; b < 11; b++) {
        uint8_t id_n = get_bit_from_32bit(id, b);
        uint8_t filter_n = get_bit_from_32bit(FilterScheme0.STD_ID_FILTER, b);
        if(id_n == filter_n) {
            ok_cnt++;
        } else {
            uint8_t mask_n = get_bit_from_32bit(FilterScheme0.STD_ID_MASK, b);
            if(0 == mask_n) {
                ok_cnt++;
            }
        }
    }

    if(11 == ok_cnt) {
        res = true;
    }

    return res;
}

static bool can_is_valid_std_id_filter1(const uint32_t id, const uint32_t filter) {
    bool res = false;
    CanStdFiltElement1_t FilterScheme1;
    FilterScheme1.dword = filter;
    if(FilterScheme1.STD_ID_FILTER1 <= id) {
        if(id <= FilterScheme1.STD_ID_FILTER2) {
            res = true;
        }
    }
    return res;
}

static bool can_is_valid_std_id_filter2(const uint32_t id, const uint32_t filter) {
    bool res = false;
    CanStdFiltElement2_t FilterScheme2;
    FilterScheme2.dword = filter;
    if(id == FilterScheme2.STD_ID_FILTER1) {
        if(id == FilterScheme2.STD_ID_FILTER2) {
            res = true;
        }
    }
    return res;
}

static bool can_is_valid_ext_id_filter0(const uint32_t id, const uint64_t filter) {
    bool res = false;
    CanExtFiltElement0_t FilterScheme0;
    FilterScheme0.qword = filter;
    uint32_t ok_cnt = 0;
    uint32_t b = 0;
    for(b = 0; b < 29; b++) {
        uint8_t id_n = get_bit_from_32bit(id, b);
        uint8_t filter_n = get_bit_from_32bit((uint32_t)FilterScheme0.EXT_ID_FILTER, b);
        if(id_n == filter_n) {
            ok_cnt++;
        } else {
            uint8_t mask_n = get_bit_from_32bit((uint32_t)FilterScheme0.EXT_ID_MASK, b);
            if(0 == mask_n) {
                ok_cnt++;
            }
        }
    }

    if(29 == ok_cnt) {
        res = true;
    }

    return res;
}

static bool can_is_valid_ext_id_filter1(const uint32_t id, const uint64_t filter) {
    bool res = false;
    CanExtFiltElement1_t FilterScheme1;
    FilterScheme1.qword = filter;
    if(FilterScheme1.EXT_ID_FILTER1 <= id) {
        if(id <= FilterScheme1.EXT_ID_FILTER2) {
            res = true;
        }
    }
    return res;
}

static bool can_is_valid_ext_id_filter2(const uint32_t id, const uint64_t filter) {
    bool res = false;
    CanExtFiltElement2_t FilterScheme2;
    FilterScheme2.qword = filter;
    if(id == FilterScheme2.EXT_ID_FILTER1) {
        if(id == FilterScheme2.EXT_ID_FILTER2) {
            res = true;
        }
    }
    return res;
}

bool can_is_valid_ext_id(const uint32_t id, const uint64_t filter) {
    bool res = false;
    if(id <= CAN_EXT_ID_MAX_VAL) {
        CanExtFiltElement_t FiltElement;
        FiltElement.qword = filter;
        switch(FiltElement.FilterScheme0.FSCH) {
        case CAN_FSCH_MASK_AND_FILTER:
            res = can_is_valid_ext_id_filter0(id, filter);
            break;
        case CAN_FSCH_RANGE:
            res = can_is_valid_ext_id_filter1(id, filter);
            break;
        case CAN_FSCH_TWO_IDS:
            res = can_is_valid_ext_id_filter2(id, filter);
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool can_is_valid_std_id(const uint32_t id, const uint32_t filter) {
    bool res = false;
    if(id <= CAN_STD_ID_MAX_VAL) {
        CanStdFiltElement_t FiltElement;
        FiltElement.dword = filter;
        switch(FiltElement.FilterScheme0.FSCH) {
        case CAN_FSCH_MASK_AND_FILTER:
            res = can_is_valid_std_id_filter0(id, filter);
            break;
        case CAN_FSCH_RANGE:
            res = can_is_valid_std_id_filter1(id, filter);
            break;
        case CAN_FSCH_TWO_IDS:
            res = can_is_valid_std_id_filter2(id, filter);
            break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

bool can_enhanced_id_check_std(uint8_t num, const uint32_t can_id) {
    bool match = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint8_t ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
        uint8_t std_id_flt_el_cnt = can_std_id_filter_element_cnt_get(num);
        uint32_t cnt = 0;
        uint32_t sfi = 0;
        for(sfi = ext_id_flt_el_cnt * 2; sfi < FLEXCAN_FILTER_ELEMENT_COUNT; sfi++) {
            if(cnt < std_id_flt_el_cnt) {
                match = can_is_valid_std_id(can_id, Info->CANx->ERFFEL[sfi]);
                if(match) {
                    break;
                }
                cnt++;
            }
        }
    }
    LOG_DEBUG(CAN, "CAN%u,ID:0x%08X,Match:%u", num, can_id, match);
    return match;
}

bool can_enhanced_id_check_ext(uint8_t num, const uint32_t can_id) {
    bool match = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        bool res = can_is_ext_id(can_id);
        if(res) {
            uint8_t ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
            uint32_t cnt = 0;
            uint32_t efi = 0;
            for(efi = 0; efi < ext_id_flt_el_cnt; efi++) {
                uint64_t qword = 0;
                memcpy(&qword, &Info->CANx->ERFFEL[2 * efi], sizeof(uint64_t));
                match = can_is_valid_ext_id(can_id, qword);
                if(match) {
                    break;
                }
                cnt++;
            }
        }
    }
    LOG_DEBUG(CAN, "CAN%u,ID:0x%08X,Match:%u", num, can_id, match);
    return match;
}

bool can_enhanced_id_check(uint8_t num, const uint32_t can_id) {
    bool match = false;

    match = can_enhanced_id_check_std(num, can_id);
    if(!match) {
        match = can_enhanced_id_check_ext(num, can_id);
    }
    LOG_DEBUG(CAN, "CAN%u,ID:0x%08X,Match:%u", num, can_id, match);
    return match;
}

static bool can_filter_std_apply(uint8_t num, const uint32_t dword) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint8_t ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
        uint8_t sfi = ext_id_flt_el_cnt * 2;
        /* Configure the filter elements by writing in the ERFFELn registers (ERFFELn registers are implemented in RAM;
           thus, they must be explicitly initialized prior to any reception). */
        Info->CANx->ERFFEL[sfi] = dword;
    }
    return res;
}

static bool can_filter_ext_apply(uint8_t num, const uint64_t qword) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        memcpy(&(Info->CANx->ERFFEL[0]), &qword, 8);
        res = true;
    }
    return res;
}

/*
 Must be called before receiving the package
 * */
bool can_filter_allow_id(uint8_t num, const uint32_t id_val) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(CAN_MAC_MODE_ENHANCED_FIFO == Node->mac_mode) {
            CanIdentifier_t id_type = can_id_val_to_id_type(id_val);
            switch(id_type) {
            case CAN_FRAME_ID_STANDARD: {
                CanStdFiltElement0_t FilterScheme0;
                FilterScheme0.STD_ID_FILTER = id_val;
                FilterScheme0.STD_ID_MASK = CAN_STD_ID_MAX_VAL;
                FilterScheme0.RTR_MASK = 0;
                FilterScheme0.RTR_FILTER = 0;
                FilterScheme0.FSCH = CAN_FSCH_MASK_AND_FILTER;
                res = can_filter_std_apply(num, FilterScheme0.dword);
            } break;
            case CAN_FRAME_ID_EXTENDED: {
                CanExtFiltElement0_t FilterScheme0;
                FilterScheme0.EXT_ID_FILTER = id_val;
                FilterScheme0.EXT_ID_MASK = CAN_EXT_ID_MAX_VAL;
                FilterScheme0.RTR_MASK = 0;
                FilterScheme0.RTR_FILTER = 0;
                FilterScheme0.FSCH = CAN_FSCH_MASK_AND_FILTER;
                res = can_filter_ext_apply(num, FilterScheme0.qword);
            } break;
            default:
                break;
            }
        }
    }

    return res;
}

bool can_filter_ban_id(uint8_t num, const uint32_t id_val) {
    bool res = false;
    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        if(CAN_MAC_MODE_ENHANCED_FIFO == Node->mac_mode) {
            CanIdentifier_t id_type = can_id_val_to_id_type(id_val);
            switch(id_type) {
            case CAN_FRAME_ID_STANDARD: {
                CanStdFiltElement1_t FilterScheme1;
                FilterScheme1.STD_ID_FILTER1 = id_val + 1;
                FilterScheme1.STD_ID_FILTER2 = id_val - 1;
                FilterScheme1.RTR_FILTER = 0;
                FilterScheme1.RTR_MASK = 0;
                FilterScheme1.FSCH = CAN_FSCH_RANGE;
                res = can_filter_std_apply(num, FilterScheme1.dword);
            } break;
            case CAN_FRAME_ID_EXTENDED: {
                CanExtFiltElement1_t FilterScheme1;
                FilterScheme1.EXT_ID_FILTER1 = id_val + 1;
                FilterScheme1.EXT_ID_FILTER2 = id_val - 1;
                FilterScheme1.RTR_FILTER = 0;
                FilterScheme1.RTR_MASK = 0;
                FilterScheme1.FSCH = CAN_FSCH_RANGE;
                res = can_filter_ext_apply(num, FilterScheme1.qword);
            } break;
            default:
                break;
            }
        }
    }

    return res;
}

bool can_filter_ctrl(uint8_t num, uint32_t can_id, CanFilterIdAccess_t accsess_cmd) {
    bool res = true;
    switch(accsess_cmd) {
    case CAN_FILTER_ID_ACCESS_ALLOW: {
        res = can_filter_allow_id(num, can_id);
    } break;
    case CAN_FILTER_ID_ACCESS_BAN: {
        res = can_filter_ban_id(num, can_id);
    } break;
    default:
        break;
    }
    return res;
}

bool can_is_mode_enhanced_fifo(const uint8_t num) {
    bool res = true;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        CanRegERFCR_t ERFCR = {0};
        ERFCR.dword = Info->CANx->ERFCR;
        if(ERFCR.ERFEN) {
            res = true;
        }
    }
    return res;
}
