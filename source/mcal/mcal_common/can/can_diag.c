#include "can_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "can_mcal.h"
#include "common_diag.h"
#include "connectivity_diag.h"
#include "diag_inc.h"
#include "log.h"
#include "num_to_str.h"
#include "mcal_diag.h"
#include "table_utils.h"
#include "writer_config.h"

static char cText[150] = "";

const char* CanIdTypeToStr(const CanIdentifier_t identifier) {
    char* name = "?";
    switch(identifier) {
        case CAN_FRAME_ID_STANDARD:       name = "Std";  /*11bit*/      break;
        case CAN_FRAME_ID_EXTENDED:       name = "Ext";  /*29bit*/      break;
        default:       name = "?";        break;
    }
    return name;
}

const char* CanPriorityToStr(const CanPriority_t priority) {
    char* name = "?";
    switch(priority) {
    case CAN_PRIORITY_TOP:       name = "TOP!";      break;
    case CAN_PRIORITY_HIGHER:    name = "higher";    break;
    case CAN_PRIORITY_HI:        name = "Hi";        break;
    case CAN_PRIORITY_MEDIUMHI:  name = "MediumHi";  break;
    case CAN_PRIORITY_MEDIUMLO:  name = "MediumLo";  break;
    case CAN_PRIORITY_LOW:       name = "Low";       break;
    case CAN_PRIORITY_LOWER:     name = "Lower";     break;
    case CAN_PRIORITY_LOWEST:    name = "Lowest";    break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanMacModeToStr(const CanMacMode_t mac_mode) {
    char* name = "?";
    switch(mac_mode) {
    case CAN_MAC_MODE_LEGACY_FIFO:      name = "LEGACY_FIFO";        break;
    case CAN_MAC_MODE_ENHANCED_FIFO:    name = "ENHANCED_FIFO";      break;
    case CAN_MAC_MODE_MESSAGE_BUFFER:   name = "MESSAGE_BUFFER";     break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanModeToStr(CanMode_t mode) {
    char* name = "?";
    switch(mode) {
    case CAN_CFG_MODE_COMMUNICATE:     name = "Communicate";        break;
    case CAN_CFG_MODE_LOOPBACK:        name = "LoopBack";        break;
    case CAN_CFG_MODE_LISTENONLY:      name = "ListenOnly";        break;
    case CAN_CFG_MODE_LISTENONLY_LOOPBACK:        name = "ListenOnlyLoopBack";        break;
    case CAN_CFG_MODE_FREEZE:          name = "Freeze";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanClkStrToStr(const CanClockSource_t clock_source) {
    char* name = "?";
    switch(clock_source) {
    case CAN_CLOCK_SOURCE_PERIPHERAL:    name = "Periph";        break;
    case CAN_CLOCK_SOURCE_OSCILLATOR:    name = "Oscill";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanFrameTypeToStr(const CanTxFrame_t frame_type) {
    char* name = "?";
    switch(frame_type) {
    case CAN_TX_FRAME_DATA:        name = "Dat";        break;
    case CAN_TX_FRAME_REMOTE:      name = "Rem";        break;
    default:        name = "?";        break;
    }
    return name;
}

const char* CanMessageToStr(const CanMessage_t* const Message) {
    if(Message) {
        strcpy(cText, "");
        snprintf(cText, sizeof(cText), "%sCAN%u,", cText, Message->can_bus_num);
        snprintf(cText, sizeof(cText), "%sTS:%u,", cText, Message->time_stamp);
        snprintf(cText, sizeof(cText), "%sFilt:%u,", cText, Message->mesg_buff_idx);
        snprintf(cText, sizeof(cText), "%sID:0x%x,", cText, Message->identifier.extended);
        snprintf(cText, sizeof(cText), "%sIDType:%s,", cText, CanIdTypeToStr(Message->id_type));
        snprintf(cText, sizeof(cText), "%sFrame:%s,", cText, CanFrameTypeToStr(Message->frame_type));
        snprintf(cText, sizeof(cText), "%sSize:%u,", cText, Message->size);
        snprintf(cText, sizeof(cText), "%sData:0x%s", cText, ArrayToStr(Message->data, Message->size));
    }
    return cText;
}

const char* CanConfigToStr(const CanConfig_t* const Config) {
    if(Config) {
        strcpy(cText, "");
        snprintf(cText, sizeof(cText), "%sCAN%u,", cText, Config->num);
        snprintf(cText, sizeof(cText), "%sMacMode:%s,", cText, CanMacModeToStr(Config->mac_mode));
        snprintf(cText, sizeof(cText), "%s%sBit/s,", cText, u32valToStr(Config->bit_rate));
        snprintf(cText, sizeof(cText), "%sIDtype:%s,", cText, CanIdTypeToStr(Config->identifier));
        snprintf(cText, sizeof(cText), "%sMode:%s", cText, CanModeToStr(Config->mode));
        snprintf(cText, sizeof(cText), "%sClkSrc:%s,", cText, CanClkStrToStr(Config->clock_source));
        snprintf(cText, sizeof(cText), "%sBoffArec:%s,", cText, OnOffToStr(Config->bus_off_auto_recovery));
        snprintf(cText, sizeof(cText), "%sInt:%s,", cText, OnOffToStr(Config->interrupt_on));
        snprintf(cText, sizeof(cText), "%sReTx:%s,", cText, OnOffToStr(Config->re_tx));
        // snprintf(cText, sizeof(cText), "%sRxID:0x%x,", cText, Config->rx_id);
        snprintf(cText, sizeof(cText), "%sRxIDcnt:%u,", cText, Config->rx_id_cnt);
        snprintf(cText, sizeof(cText), "%sMoveMode:%s,", cText, McalMoveModeToStr(Config->move_mode));
#ifdef HAS_CAN_FD
        snprintf(cText, sizeof(cText), "%sFD:%sBit/s,", cText, u32valToStr(Config->bit_rate_fd));
        snprintf(cText, sizeof(cText), "%sFD:%s,", cText, OnOffToStr(Config->fd_enable));
#endif
    }
    return cText;
}

const char* CanMessageBufferConfigToStr(const CanMessageBufferConfig_t* const MbConfig) {
    if(MbConfig) {
        strcpy(cText, "");
        snprintf(cText, sizeof(cText), "%s%s,", cText, CansToStr(MbConfig->cans));
        snprintf(cText, sizeof(cText), "%sMB:%u,", cText, MbConfig->mb_index);
        snprintf(cText, sizeof(cText), "%sID:%u,", cText, MbConfig->frame_id);
        snprintf(cText, sizeof(cText), "%sInt:%u,", cText, MbConfig->interrupt_on);
        snprintf(cText, sizeof(cText), "%s%s,", cText, MbConfig->name);
        snprintf(cText, sizeof(cText), "%sDir:%s,", cText, ConnectivityDirectionToStr(MbConfig->direction));
        snprintf(cText, sizeof(cText), "%sFrame:%s,", cText, CanIdTypeToStr(MbConfig->id_type));
    }
    return cText;
}

bool CanDiagNode(const CanHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(CAN, "IsrCnt:%u", Node->isr_cnt);
        LOG_INFO(CAN, "IsrErrCnt:%u", Node->error_cnt);
        LOG_INFO(CAN, "RxCnt:%u", Node->rx_cnt);
        LOG_INFO(CAN, "TxCnt:%u", Node->tx_cnt);
        LOG_INFO(CAN, "ErrCode:%u", Node->err_code);
        LOG_INFO(CAN, "RxID:0x%x", Node->rx_id);
        LOG_INFO(CAN, "Spin:%u", Node->spin);
        res = true;
    }
    return res;
}

bool can_show_my_id(const uint8_t num){
    bool out_res = false;
    uint32_t id = 0;
    LOG_INFO(CAN, "CAN%u,ListOfMyIDs:", num);
    for(id = 0; id <= CAN_EXT_ID_MAX_VAL; id++) {
        bool res = can_is_my_id(num, id);
        if(res) {
            cli_printf(CRLF"0x%X,"CRLF,id);
            out_res = true;
        }
        diag_progress_log(id ,   CAN_EXT_ID_MAX_VAL, 10000);
    }
    return out_res;
}

bool can_diag_interrupt(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {6, "CAN"},
        {9, "ISR"},
        {9, "RX"},
        {9, "TX"},
        {9, "Err"},
    };

    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(num = 0; num <= CAN_COUNT; num++) {
        CanHandle_t* Node = CanGetNode(num);
        if(Node) {
            char temp[300] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->isr_cnt);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->rx_cnt);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->tx_cnt);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->error_cnt);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


bool can_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {6, "CAN"},   {9, "Rate"},
#ifdef HAS_CAN_FD
        {9, "Rate2"},
        {14, "SegmentCtrl1"},
#endif
        {7, "TEC"},     
        {7, "REC"},
        {7, "RxCnt"}, {7, "TxCnt"}, 
        {7, "aLst"},
        {5, "psc"},
        {5, "syn"},
        {5, "pro"},
        {5, "ph1"},
        {5, "ph2"},
        {7, "SamPo"},
        {6, "dDur"},
       // {32, "SegmentCbt"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(num = 0; num <= CAN_COUNT; num++) {
        CanSegmentInfo_t SegmentInfo = {0};
        uint32_t bit_rate = 0;
#ifdef HAS_CAN_FD
        uint32_t bit_rate2 = 0;
        CanSegmentInfo_t SegmentInfoFd = {0};
        res = can_fd_segments_get(num, &SegmentInfoFd);
        res = can_fd_mcal_baudrate_get(num, &bit_rate2);
#endif
        uint32_t rec = 0;
        uint32_t tec = 0;
        res = can_mcal_baudrate_get(num, &bit_rate);
        res = can_tec_get(num, &rec);
        res = can_rec_get(num, &tec);
        res = can_segments_get(num, &SegmentInfo);
        float sample_point=can_segment_to_fetch_present( &SegmentInfo);
        uint32_t bit_duration_tq=can_segment_to_bit_duration_tq(&SegmentInfo) ;

        CanHandle_t* Node = CanGetNode(num);
        if(Node) {
            char temp[300] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, bit_rate);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, tec);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, rec);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->rx_cnt);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->tx_cnt);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, Node->arbitration_lost_cnt);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.prescaler);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.synchronization);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.propagation);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.phase_1);
            snprintf(temp, sizeof(temp), "%s %3u " TSEP, temp, SegmentInfo.phase_2);
            snprintf(temp, sizeof(temp), "%s %5.2f " TSEP, temp, sample_point);
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, bit_duration_tq);
           // snprintf(temp, sizeof(temp), "%s %30s " TSEP, temp, CanSegmentInfoToStr(&SegmentInfo));
#ifdef HAS_CAN_FD
            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, bit_rate2);
            snprintf(temp, sizeof(temp), "%s [%10s] " TSEP, temp, CanSegmentInfoToStr(&SegmentInfoFd));
#endif
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

#ifdef HAS_CAN_FD
bool can_fd_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {
        {6, "CAN"}, {12, "REG"}, {9, "rate"}, {7, "TEC"}, {7, "REC"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    for(num = 0; num <= CAN_COUNT; num++) {
        uint32_t bit_rate_fd = 0;
        uint32_t rec = 0;
        uint32_t tec = 0;
        res = can_fd_tec_get(num, &rec);
        res = can_fd_rec_get(num, &tec);
        res = can_fd_baudrate_get(num, &bit_rate_fd);
        CanHandle_t* Node = CanGetNode(num);
        if(Node) {
            char temp[300] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s CAN%u " TSEP, temp, num);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, Node->CANx);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, bit_rate_fd);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, tec);
            snprintf(temp, sizeof(temp), "%s %5u " TSEP, temp, rec);
            // res = CanDiagNode(Node);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
#endif

const char* CanSegmentInfoToStr(const CanSegmentInfo_t* const Info) {
    if(Info) {
        float fetch_present = can_segment_to_fetch_present(Info);
        uint32_t bit_diration_tq = can_segment_to_bit_duration_tq(Info);
        strcpy(cText, "");
        snprintf(cText, sizeof(cText), "%sPreScaler:%u,", cText, Info->prescaler);
        snprintf(cText, sizeof(cText), "%sBitDur:%u Tq,", cText, bit_diration_tq);
        snprintf(cText, sizeof(cText), "%sSync:%u,", cText, Info->synchronization);
        snprintf(cText, sizeof(cText), "%sProp:%u,", cText, Info->propagation);
        snprintf(cText, sizeof(cText), "%sPha1:%u,", cText, Info->phase_1);
        snprintf(cText, sizeof(cText), "%sPha2:%u,", cText, Info->phase_2);
        snprintf(cText, sizeof(cText), "%sFetch:%f %%,", cText, fetch_present);
    }
    return cText;
}

const char* CansToStr(const Cans_t Obj) {
    strcpy(cText, "");
    if(Obj.can0) {
        snprintf(cText, sizeof(cText), "%s,CAN0", cText);
    }

    if(Obj.can1) {
        snprintf(cText, sizeof(cText), "%s,CAN1", cText);
    }

    if(Obj.can2) {
        snprintf(cText, sizeof(cText), "%s,CAN2", cText);
    }

    if(Obj.can3) {
        snprintf(cText, sizeof(cText), "%s,CAN3", cText);
    }

    if(Obj.can4) {
        snprintf(cText, sizeof(cText), "%s,CAN4", cText);
    }

    if(Obj.can5) {
        snprintf(cText, sizeof(cText), "%s,CAN5", cText);
    }

    if(Obj.can6) {
        snprintf(cText, sizeof(cText), "%s,CAN6", cText);
    }

    if(Obj.can7) {
        snprintf(cText, sizeof(cText), "%s,CAN7", cText);
    }

    if(Obj.can8) {
        snprintf(cText, sizeof(cText), "%s,CAN8", cText);
    }

    if(Obj.can9) {
        snprintf(cText, sizeof(cText), "%s,CAN9", cText);
    }
    return cText;
}


uint32_t can_filter_id_mask_diag(const uint32_t filter_id, const uint32_t filter_mask) {
    cli_printf( "ID  :0x%08x=0b%s"CRLF, filter_id,   utoa_bin32(filter_id) );
    cli_printf( "Mask:0x%08x=0b%s"CRLF, filter_mask, utoa_bin32(filter_mask) );
    static const table_col_t cols[] = {
        {6, "Cnt"},
        {12, "ID,hex"},
        {12, "mask,hex"},
        {12, "passID,hex"},
        {43, "passID,bin"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t i = 0;
    uint32_t pass_cnt = 0;
    for(i=0; i<CAN_EXT_ID_MAX_VAL; i++) {
        if(filter_id==( i&filter_mask )) {
            pass_cnt++;
            char temp[120] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, pass_cnt);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, filter_id);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, filter_mask);
            snprintf(temp, sizeof(temp), "%s 0x%08x " TSEP, temp, i);
            snprintf(temp, sizeof(temp), "%s 0b%39s " TSEP, temp, utoa_bin32(i));
            cli_printf("%s" CRLF, temp);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return pass_cnt;
}
