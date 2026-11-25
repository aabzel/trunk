#include "can_enhanced_fifo_diag.h"

#include "array_diag.h"
#include "byte_utils.h"
#include "can_custom_diag.h"
#include "can_enhanced_fifo.h"
#include "can_mcal.h"
#include "can_misc.h"
#include "common_diag.h"
#include "connectivity_diag.h"
#include "data_utils.h"
#include "debugger.h"
#include "diag_inc.h"
#include "fc7300x_misc.h"
#include "float_diag.h"
#include "log.h"
#include "num_to_str.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#include "can_message_buffer_diag.h"

const char* CanFilterSchemeToStr(const CanFSCH_t filter_scheme) {
    char* name = "?";
    switch(filter_scheme) {
    case CAN_FSCH_MASK_AND_FILTER:
        name = "MskFlt";
        break;
    case CAN_FSCH_RANGE:
        name = "Range";
        break;
    case CAN_FSCH_TWO_IDS:
        name = "TwoId";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}

static const char* CanStdFilterElement0ToStr(const CanStdFiltElement0_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_MASK_AND_FILTER == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%sSTD_ID_FILTER:0x%x,", temp, Node->STD_ID_FILTER);
            snprintf(temp, sizeof(temp), "%sSTD_ID_MASK:0x%x,", temp, Node->STD_ID_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_MASK:%u,", temp, Node->RTR_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER:%u,", temp, Node->RTR_FILTER);
        }
    }
    return temp;
}

static const char* CanStdFilterElement1ToStr(const CanStdFiltElement1_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_RANGE == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%s0x%X<=ID<=0x%X,", temp, Node->STD_ID_FILTER1, Node->STD_ID_FILTER2);
            snprintf(temp, sizeof(temp), "%sRTR_MASK:%u,", temp, Node->RTR_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER:%u,", temp, Node->RTR_FILTER);
        }
    }
    return temp;
}

static const char* CanStdFilterElement2ToStr(const CanStdFiltElement2_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_TWO_IDS == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%sID=0x%X,", temp, Node->STD_ID_FILTER1);
            snprintf(temp, sizeof(temp), "%sID=0x%X,", temp, Node->STD_ID_FILTER2);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER1:%u,", temp, Node->RTR_FILTER1);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER2:%u,", temp, Node->RTR_FILTER2);
        }
    }
    return temp;
}

const char* CanStdFilterElementToStr(const CanStdFiltElement_t* const Node) {
    char* name = "?";
    switch(Node->FilterScheme2.FSCH) {
    case CAN_FSCH_MASK_AND_FILTER:
        name = CanStdFilterElement0ToStr(&(Node->FilterScheme0));
        break;
    case CAN_FSCH_RANGE:
        name = CanStdFilterElement1ToStr(&(Node->FilterScheme1));
        break;
    case CAN_FSCH_TWO_IDS:
        name = CanStdFilterElement2ToStr(&(Node->FilterScheme2));
        break;
    default:
        break;
    }
    return name;
}

static const char* CanExtFilterElement0ToStr(const CanExtFiltElement0_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_MASK_AND_FILTER == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%sEXT_ID_FILTER:0x%08X,", temp, Node->EXT_ID_FILTER);
            snprintf(temp, sizeof(temp), "%sEXT_ID_MASK:0x%08X,", temp, Node->EXT_ID_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_MASK:%u,", temp, Node->RTR_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER:%u,", temp, Node->RTR_FILTER);
        }
    }
    return temp;
}

static const char* CanExtFilterElement1ToStr(const CanExtFiltElement1_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_RANGE == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%s0x%07X<=ID<=0x%08X,", temp, Node->EXT_ID_FILTER1, Node->EXT_ID_FILTER2);
            snprintf(temp, sizeof(temp), "%sRTR_MASK:%u,", temp, Node->RTR_MASK);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER:%u,", temp, Node->RTR_FILTER);
        }
    }
    return temp;
}

static const char* CanExtFilterElement2ToStr(const CanExtFiltElement2_t* const Node) {
    static char temp[150] = {0};
    if(Node) {
        strcpy(temp, "");
        if(CAN_FSCH_TWO_IDS == Node->FSCH) {
            snprintf(temp, sizeof(temp), "%sID=0x%08X,", temp, Node->EXT_ID_FILTER1);
            snprintf(temp, sizeof(temp), "%sID=0x%08X,", temp, Node->EXT_ID_FILTER2);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER1:%u,", temp, Node->RTR_FILTER1);
            snprintf(temp, sizeof(temp), "%sRTR_FILTER2:%u,", temp, Node->RTR_FILTER2);
        }
    }
    return temp;
}

const char* CanExtFilterElementToStr(const CanExtFiltElement_t* const Node) {
    char* name = "?";
    switch(Node->FilterScheme1.FSCH) {
    case CAN_FSCH_MASK_AND_FILTER:
        name = CanExtFilterElement0ToStr(&(Node->FilterScheme0));
        break;
    case CAN_FSCH_RANGE:
        name = CanExtFilterElement1ToStr(&(Node->FilterScheme1));
        break;
    case CAN_FSCH_TWO_IDS:
        name = CanExtFilterElement2ToStr(&(Node->FilterScheme2));
        break;
    default:
        break;
    }
    return name;
}

/* 58.8.55 FLEXCAN_ERFFELn (Enhanced Rx FIFO Filter Element Register) */
bool can_diag_enhanced_rx_fifo_filter(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint8_t ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
        uint8_t std_id_flt_el_cnt = can_std_id_filter_element_cnt_get(num);
        LOG_INFO(CAN, "ExtFiltElem:%u", ext_id_flt_el_cnt);
        LOG_INFO(CAN, "StdFiltElem:%u", std_id_flt_el_cnt);

        LOG_INFO(CAN, "FLEXCAN_ERFFEL_COUNT:%u", FLEXCAN_ERFFEL_COUNT);
        LOG_INFO(CAN, "FLEXCAN_FILTER_ELEMENT_COUNT:%u", FLEXCAN_FILTER_ELEMENT_COUNT);
        uint32_t offset = ((uint32_t)&Info->CANx->ERFFEL[0]) - ((uint32_t)&Info->CANx->MCR);
        LOG_INFO(CAN, "CAN%u,ERFFEL,Offset:0x%x", num, offset);
        uint32_t i = 0;

        static const table_col_t cols[] = {
            {6, "FltEl"},
            {12, "dword"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        for(i = 0; i < FLEXCAN_FILTER_ELEMENT_COUNT; i++) {
            if(Info->CANx->ERFFEL[i]) {

                char temp[150] = {0};
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, i);
                snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Info->CANx->ERFFEL[i]);
                cli_printf("%s" CRLF, temp);
                res = true;
            }
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        cli_printf(CRLF);
    }
    return res;
}

/*
 58.8.55 FLEXCAN_ERFFELn (Enhanced Rx FIFO Filter Element Register)
*/
bool can_diag_enhanced_rx_fifo_filter_std(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint8_t ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
        uint8_t std_id_flt_el_cnt = can_std_id_filter_element_cnt_get(num);
        LOG_INFO(CAN, "ExtFiltElem:%u", ext_id_flt_el_cnt);
        LOG_INFO(CAN, "StdFiltElem:%u", std_id_flt_el_cnt);

        static const table_col_t cols[] = {
            {5, "FltEl"}, {12, "Dword"}, {5, "FSCH"}, {8, "FSCH"}, {64, "Decipher"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t i = 0;

        uint32_t cnt = 0;
        for(i = ext_id_flt_el_cnt * 2; i < FLEXCAN_FILTER_ELEMENT_COUNT; i++) {
            if(cnt < std_id_flt_el_cnt) {
                CanStdFiltElement_t StdFiltEl;
                StdFiltEl.dword = Info->CANx->ERFFEL[i];
                char temp[300] = {0};
                strcpy(temp, TSEP);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, i);
                snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Info->CANx->ERFFEL[i]);
                snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, StdFiltEl.FilterScheme0.FSCH);
                snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, CanFilterSchemeToStr(StdFiltEl.FilterScheme0.FSCH));
                snprintf(temp, sizeof(temp), "%s %62s " TSEP, temp, CanStdFilterElementToStr(&StdFiltEl));
                cli_printf("%s" CRLF, temp);
                res = true;
                cnt++;
            }
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        cli_printf(CRLF);
    }
    return res;
}

bool can_diag_enhanced_rx_fifo_filter_ext(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        uint8 ext_id_flt_el_cnt = can_ext_id_filter_element_cnt_get(num);
        LOG_INFO(CAN, "ExtFiltElem:%u", ext_id_flt_el_cnt);
        static const table_col_t cols[] = {
            {6, "FltEl"}, {20, "qword"}, {5, "FSCH"}, {8, "FSCH"}, {74, "Decipher"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t i = 0;
        for(i = 0; i < ext_id_flt_el_cnt; i++) {
            CanExtFiltElement_t ExtFiltElement;
            memcpy(&ExtFiltElement.qword, &Info->CANx->ERFFEL[2 * i], 8);
            char temp[300] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, i);
            snprintf(temp, sizeof(temp), "%s 0x%16s " TSEP, temp, ArrayToStr(ExtFiltElement.byte, 8));
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, ExtFiltElement.FilterScheme1.FSCH);
            snprintf(temp, sizeof(temp), "%s %s " TSEP, temp, CanFilterSchemeToStr(ExtFiltElement.FilterScheme1.FSCH));
            snprintf(temp, sizeof(temp), "%s %62s " TSEP, temp, CanExtFilterElementToStr(&ExtFiltElement));
            cli_printf("%s" CRLF, temp);
            res = true;
        }

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        cli_printf(CRLF);
    }
    return res;
}

/*FLEXCAN supports an enhanced Rx FIFO engine which can store up to 12 CAN FD messages.
  The region 0x2000–0x204F  (0x204F-0x2000=79)contains the output of the FIFO which should be read by the CPU.
*/
bool can_diag_enhanced_fifo_region(uint8_t num, uint32_t size) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        if(size < FLEXCAN_ERX_FIFO_COUNT) {
            LOG_INFO(CAN, "CAN%u,EnhancedFifoRegionSize:%u", num, 4 * FLEXCAN_ERX_FIFO_COUNT);
            LOG_INFO(CAN, "CAN%u,ERX_FIFO,Offset:0x%p", num, &Info->CANx->ERX_FIFO[0] - &Info->CANx->MCR);
            uint32_t i = 0;
            for(i = 0; i < size; i++) {
                cli_printf("%08x", Info->CANx->ERX_FIFO[i]);
            }
            cli_printf(CRLF);
        }
    }
    return res;
}

const char* CanESItoStr(const CanESICode_t error_ind);

bool can_diag_enhanced_fifo_parse(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        cli_printf(CRLF);
        LOG_INFO(CAN, "CAN%u,EnhancedFifoRegionSize:%u", num, 4 * FLEXCAN_ERX_FIFO_COUNT);
        LOG_INFO(CAN, "CAN%u,ERX_FIFO,Offset:0x%p", num, &Info->CANx->ERX_FIFO[0] - &Info->CANx->MCR);

        static const table_col_t cols[] = {
            {5, "CAN"}, {8, "TimStp"}, {8, "IDstd"}, {12, "IDext"}, {4, "Size"}, {4, "EDL"},  {5, "IDE"},
            {6, "ESI"}, {5, "RTR"},    {4, "SRR"},   {4, "IDHIT"},  {5, "BRS"},  {4, "PRIO"}, {64, "DAT"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        uint32_t offset = 0;
        uint32_t can_frame_cnt = FLEXCAN_ERX_FIFO_COUNT / sizeof(CanEnhancedRxFIFOStructure_t);
        for(offset = 0; offset < can_frame_cnt; offset += sizeof(CanEnhancedRxFIFOStructure_t)) {
            CanEnhancedRxFIFOStructure_t* Frame = (CanEnhancedRxFIFOStructure_t*)(Info->CANx->ERX_FIFO + offset);
            char temp[150] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, Frame->TIME_STAMP);
            snprintf(temp, sizeof(temp), "%s 0x%04x " TSEP, temp, Frame->ID.STANDARD);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Frame->ID.EXTENDED);

            snprintf(temp, sizeof(temp), "%s %2u " TSEP, temp, CanDlcToSize(Frame->DLC));
            snprintf(temp, sizeof(temp), "%s %2s " TSEP, temp, CanEDLToStr(Frame->EDL));
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanIDEToStr(Frame->IDE));
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanESItoStr(Frame->ESI));
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanFrameRTRToStr(Frame->RTR));
            snprintf(temp, sizeof(temp), "%s %2s " TSEP, temp, CanSRRToStr(Frame->SRR));
            snprintf(temp, sizeof(temp), "%s %u " TSEP, temp, Frame->IDHIT);
            snprintf(temp, sizeof(temp), "%s %3s " TSEP, temp, CanBRSToStr(Frame->BRS));
            snprintf(temp, sizeof(temp), "%s %u " TSEP, temp, Frame->ID.PRIO);
            snprintf(temp, sizeof(temp), "%s 0x%s " TSEP, temp, ArrayToStr(Frame->data, 64));
            cli_printf("%s" CRLF, temp);
            res = true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        // cli_printf(CRLF);
    }
    return res;
}

bool can_enhanced_id_check_all(const uint8_t num) {
    bool res = false;
    bool spot = false;
    LOG_INFO(CAN, "CAN%u,CheckAll_ID", num);
    uint16_t id = 0;
    for(id = 0; id < CAN_STD_ID_MAX_VAL; id++) {
        res = can_enhanced_id_check(num, id);
        if(res) {
            cli_printf("0x%04x 0b%s %s" CRLF, id, utoa_bin16(id), OnOffToStr(res));
            spot = true;
        }
    }
    return spot;
}

bool can_std_id_check_all(const uint8_t num) {
    bool res = false;
    bool spot = false;
    LOG_INFO(CAN, "CAN%u,CheckStdAll_ID", num);
    uint16_t id = 0;
    for(id = 0; id < CAN_STD_ID_MAX_VAL; id++) {
        res = can_enhanced_id_check_std(num, id);
        if(res) {
            cli_printf("0x%04x 0b%s %s" CRLF, id, utoa_bin16(id), OnOffToStr(res));
            spot = true;
        }
    }
    return spot;
}

bool can_ext_id_check_all(const uint8_t num) {
    bool res = false;
    bool spot = false;
    LOG_INFO(CAN, "CAN%u,CheckExtAll_ID", num);
    uint32_t id = 0;
    for(id = 0; id < CAN_EXT_ID_MAX_VAL; id++) {
        res = can_enhanced_id_check_ext(num, id);
        if(res) {
            cli_printf("0x%04x 0b%s %s" CRLF, id, utoa_bin16(id), OnOffToStr(res));
            spot = true;
        }
    }
    return spot;
}
