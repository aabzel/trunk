#include "tbfp_diag.h"

#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <stdio.h>

#ifdef HAS_CALENDAR
#include "calendar.h"
#endif

#include "byte_utils.h"
#include "data_utils.h"
#include "debug_info.h"
#include "crc8_sae_j1850.h"
#include "log.h"
#include "array_diag.h"
#include "system_diag.h"
#include "storage.h"
#include "table_utils.h"
#include "interfaces_diag.h"
#include "time_diag.h"
#include "time_mcal.h"
#include "log_utils.h"
#include "protocol_diag.h"
#include "tbfp.h"
#include "writer_config.h"
#ifdef HAS_GNSS
#include "gnss_diag.h"
#include "gnss_drv.h"
#endif

const char* TbfpRxState2Str(RxState_t rx_state) {
    char* name = "?";
    switch(rx_state) {
    case WAIT_INIT: name = "Init"; break;
    case WAIT_PREAMBLE: name = "WaitPre"; break;
    case WAIT_FLAGS: name = "WaitFlags"; break;
    case WAIT_SERIAL_NUM: name = "WaitSn"; break;
    case WAIT_LEN: name = "WaitLen"; break;
    case WAIT_FRAME_ID: name = "WaitFrameId"; break;
    case WAIT_PAYLOAD: name = "WaitPayload"; break;
    case WAIT_CRC: name = "WaitCrc8"; break;
    case WAIT_RETX_CNT: name = "WaitFlag"; break;
    case WAIT_UNDEF: name = "?"; break;
    case RX_DONE: name = "RxDone"; break;
    }
    return name;
}


const char* TbfpPayloadIdToStr(const TbfpPayloadId_t id) {
    const char* name = "?";
    switch( (uint8_t) id) {
    case FRAME_ID_STORAGE: name = "Stor"; break;
    case FRAME_ID_MEM: name = "Mem"; break;
    case FRAME_ID_KEYBOARD: name = "Kye"; break;
    case FRAME_ID_ACK: name = "Ack"; break;
    case FRAME_ID_CHAT: name = "Chat"; break;
    case FRAME_ID_CMD: name = "Cmd"; break;
    case FRAME_ID_PING: name = "Ping"; break;
    case FRAME_ID_TUNNEL: name = "Tunnel"; break;
    case FRAME_ID_PONG: name = "Pong"; break;
#ifdef HAS_DECAWAVE
    case FRAME_ID_DECAWAVE: name = "DecaWave"; break;
#endif

#ifdef HAS_RTCM3
    case FRAME_ID_RTCM3: name = "RTCM3"; break;
#endif

#if 0
        case  FRAME_ID_POLL: name="Poll"; break;
        case  FRAME_ID_PESPONSE: name="Resp"; break;
        case  FRAME_ID_PESPONSE_POLL: name="Resp+Poll"; break;
        case  FRAME_ID_T_DELAY: name="tDelay"; break;
        case  FRAME_ID_T_LOOP: name="tLoop"; break;
        case  FRAME_ID_TIMINGS: name="Timings"; break;
#endif
    default: name = "?"; break;
    }
    return name;
}

bool tbfp_print_ping_frame(TbfPingFrame_t* pingFrame) {
    bool res = true;
    if(pingFrame) {
        cli_printf("MAC: 0x%" PRIX64 CRLF, pingFrame->mac);
#ifdef HAS_CALENDAR
        struct tm time_date;
        res = SecondsToTimeDate(pingFrame->time_stamp, &time_date);
        if(res) {
            res = is_valid_time_date(&time_date);
            if(res) {
                res = print_time_date("Rem:", &time_date, true) && res;
            } else {
                LOG_ERROR(TBFP, "InvalRemoteTime %u", pingFrame->time_stamp);
                print_time_date("Rem:", &time_date, true);
            }
        } else {
            res = false;
        }
#endif
#ifdef HAS_GNSS
        res = is_valid_time_date(&Gnss.time_date);
        if(res) {
            res = print_time_date("Loc:", &Gnss.time_date, true) && res;
        } else {
            LOG_ERROR(TBFP, "InvalLocTime %u", pingFrame->time_stamp);
            print_time_date("Loc:", &time_date, true);
        }
        res = is_valid_gnss_coordinates(pingFrame->coordinate);
        if(res) {
            res = print_coordinate("Rem:", pingFrame->coordinate, true);
            LOG_INFO(TBFP, "Rem: height: %f m", pingFrame->height_m);
        } else {
            LOG_ERROR(TBFP, "InvalRemoteDot");
        }
        res = is_valid_gnss_coordinates(Gnss.coordinate_cur);
        if(res) {
            res = print_coordinate("Loc:", Gnss.coordinate_cur, true);
            LOG_INFO(TBFP, "Loc: height: %f m", Gnss.height_m);
        } else {
            LOG_ERROR(TBFP, "InvalLocalDot");
        }
#endif
    } else {
        res = false;
    }
    return res;
}

bool tbfp_error(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
#ifdef HAS_INTERFACES_DIAG
        {8, "interf"},
#endif
        {9, "LackFrame"},
        {9, "LenErCnt"},
        {9, "crcErCnt"},
#ifdef HAS_TBFP_DIAG
#ifdef HAS_TBFP_FLOW_CONTROL
        {9, "TornFlow"}, {9, "LostRx"},
#endif
        {9, "TxErCnt"},  {9, "ErCnt"},
#endif /*HAS_TBFP_DIAG*/
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t tbfp_cnt = tbfp_get_cnt();
    for(i = 0; i <= tbfp_cnt; i++) {
        TbfpHandle_t* TbfpNode = TbfpGetNode(i);
        if(TbfpNode) {

            cli_printf(TSEP);

#ifdef HAS_INTERFACES_DIAG
            cli_printf(" %6s " TSEP, InterfaceToStr(TbfpNode->interface));
#endif
            cli_printf(" %7u " TSEP, TbfpNode->lack_frame_in_data);
            cli_printf(" %7u " TSEP, TbfpNode->len_err_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->crc_err_cnt);
#ifdef HAS_TBFP_DIAG
            cli_printf(" %7u " TSEP, TbfpNode->err_tx_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->err_cnt);
#ifdef HAS_PROTOCOL_DIAG
            res = flow_ctrl_diag(TBFP, &TbfpNode->Flow, TbfpNode->interface);
#endif /*HAS_PROTOCOL_DIAG*/
#endif /*HAS_TBFP_DIAG*/
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool tbfp_rate_diago(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
#ifdef HAS_INTERFACES_DIAG
            {8, "interf"},
#endif
            {9, "rxMin"}, {9, "rxCur"}, {9, "rxMax"},

                                       {9, "txMin"},  {9, "txCur"}, {9, "txMax"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t tbfp_cnt = tbfp_get_cnt();
    for(i = 0; i <= tbfp_cnt; i++) {
        TbfpHandle_t* TbfpNode = TbfpGetNode(i);
        if(TbfpNode) {
            cli_printf(TSEP);
#ifdef HAS_INTERFACES_DIAG
            cli_printf(" %6s " TSEP, InterfaceToStr(TbfpNode->interface));
#endif
            cli_printf(" %7u " TSEP, TbfpNode->rx_rate.min);
            cli_printf(" %7u " TSEP, TbfpNode->rx_rate.cur);
            cli_printf(" %7u " TSEP, TbfpNode->rx_rate.max);
            cli_printf(" %7u " TSEP, TbfpNode->tx_rate.min);
            cli_printf(" %7u " TSEP, TbfpNode->tx_rate.cur);
            cli_printf(" %7u " TSEP, TbfpNode->tx_rate.max);
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool tbfp_diag(void) {
    bool res = false;
    uint32_t i;
    static const table_col_t cols[] = {
#ifdef HAS_INTERFACES_DIAG
        {10, "interf"},
#endif

        {9, "rxCnt"},
        {9, "txCnt"},

#ifdef HAS_TBFP_DIAG
#ifdef HAS_TBFP_FLOW_CONTROL
        {9, "maxFlow"}, {9, "curFlow"},
#endif
        {9, "preCnt"},  {9, "minLen"},  {9, "maxLen"},
#endif /*HAS_TBFP_DIAG*/
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t tbfp_cnt = tbfp_get_cnt();
    for(i = 0; i <= tbfp_cnt; i++) {
        TbfpHandle_t* TbfpNode = TbfpGetNode(i);
        if(TbfpNode) {
            cli_printf(TSEP);
#ifdef HAS_INTERFACES_DIAG
            cli_printf(" %8s " TSEP, InterfaceToStr(TbfpNode->interface));
#endif
            cli_printf(" %7u " TSEP, TbfpNode->rx_pkt_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->tx_pkt_cnt);

#ifdef HAS_TBFP_FLOW_CONTROL
            cli_printf(" %7u " TSEP, TbfpNode->Flow.maximum_continuous);
            cli_printf(" %7u " TSEP, TbfpNode->Flow.cur);
#endif /*HAS_TBFP_FLOW_CONTROL*/
#ifdef HAS_TBFP_DIAG
            cli_printf(" %7u " TSEP, TbfpNode->preamble_cnt);
            cli_printf(" %7u " TSEP, TbfpNode->min_len);
            cli_printf(" %7u " TSEP, TbfpNode->max_len);
#endif /*HAS_TBFP_DIAG*/
            cli_printf(CRLF);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}




const char* TbfpNode2Str(const TbfpHandle_t* const Node) {
    if(Node) {
        strcpy(text,"");
        snprintf(text,sizeof(text),"%sN:%u,",text,  Node->num);
        snprintf(text,sizeof(text),"%sPRE:0x%x,",text,  Node->preamble_val);
        snprintf(text,sizeof(text),"%sIF:%s,",text,  InterfaceToStr(Node->interface));
        if(Node->rx_array_size) {
            snprintf(text, sizeof(text), "%sRxMem:%p,", text,  Node->RxArray);
            snprintf(text, sizeof(text), "%sRxSz:%u,", text,  Node->rx_array_size);
        }
        snprintf(text,sizeof(text),"%sUART:%u,",text,  Node->uart_num);
#ifdef HAS_PROTOCOL_DIAG
        snprintf(text,sizeof(text),"%s%s,",text, FlowCtrl2Str(&Node->Flow));
#endif
    }
    return text;
}

const char* TbfpFlagToStr(TbfpFrameFlags_t flags) {
    static char lText[50] = {0};
    strcpy(lText,"");
    snprintf(lText, sizeof(lText), "%sLT:%u,", lText,  flags.lifetime);
    snprintf(lText, sizeof(lText), "%sCRC:%u,", lText,  flags.crc_check_need);
    snprintf(lText, sizeof(lText), "%sACK:%u,", lText,  flags.ack_need);
    return lText;
}

const char* TbfpHeaderToStr(const TbfpHeader_t* const Header) {
    static char lText[80] = {0};
    if(Header) {
        strcpy(lText,"");
        snprintf(lText,sizeof(lText),"%sPRE:0x%x,",lText,  Header->preamble);
        snprintf(lText,sizeof(lText),"%sSN:%u,",lText,  Header->snum);
        snprintf(lText, sizeof(lText), "%sLEN:%u,", lText,  Header->len);
        snprintf(lText,sizeof(lText),"%sFlag:[%s],",lText,  TbfpFlagToStr(Header->flags));
        snprintf(lText,sizeof(lText),"%sPLD:[%s],",lText,  TbfpPayloadIdToStr(Header->payload_id));
    }
    return lText;
}

const char* TbfpPayloadToStr(const TbfpPayloadId_t payload_id,
                             const uint8_t* const payload ){
    char* name = "?";
    if(payload) {
         switch(payload_id) {
             case FRAME_ID_STORAGE: {
                 name = StorageFrameHeaderToStr(( StorageFrameHeader_t* ) payload);
             }break;
             default: break;
         }
    }
    return name;
}

bool tbfp_parse_frame(const uint8_t* const data, const uint32_t size) {
    bool res = false ;
    LOG_INFO(TBFP, "Size:%u",size);
    if(data) {
        if(size) {
            TbfpHeader_t* Header = (TbfpHeader_t*) data;
            LOG_INFO(TBFP, "%s",TbfpHeaderToStr(Header));
            LOG_INFO(TBFP, "[%s]",TbfpPayloadToStr(  Header->payload_id,
                                                     &data[sizeof(TbfpHeader_t)]      )   );
            uint32_t crc_index = Header->len + sizeof(TbfpHeader_t) ;
            LOG_INFO(TBFP, "CRC:0x%02x",data[crc_index]);
            res = true;
        }
    }
    return res;
}

/*0x80000000 */
bool tbfp_generate_jump(const uint32_t base_address){
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(1);
    if(Node) {
        LOG_WARNING(TBFP, "GenerateJumpToAddr:0x%08X Packet", base_address);
        LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
        uint16_t payload_len = 4 ;
        LOG_INFO(TBFP, "PayLoadSize:%u byte", payload_len);
        TbfpHeader_t Header = {0};
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 1;
        Header.flags.crc_check_need = 1;
        Header.flags.lifetime = 1;
        Header.payload_id = FRAME_ID_JUMP;
        Header.snum = 1;
        Header.len = payload_len;
        memcpy(Node->TxFrame, &Header, sizeof(TbfpHeader_t));
        memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], &base_address, 4);
        uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
        uint16_t total_frame_len = frame_len + 1;
        Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
        LOG_INFO(TBFP, "JumpFrame:%s", ArrayToStr(Node->TxFrame, total_frame_len));
        uint32_t i = 0;
        for(i=0; i < total_frame_len; i++) {
            cli_printf("$%02X", Node->TxFrame[i]);
        }
        cli_printf(CRLF);
        res = true;
    }
    return res;
}

bool tbfp_storage_erase_generate(void) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(1);
    if(Node) {
        LOG_INFO(TBFP, "GenerateErasePacket");
        LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
        uint16_t payload_len = (uint16_t)sizeof(StorageFrameHeader_t) ;
        LOG_INFO(TBFP, "PayLoadSize:%u byte", payload_len);
        TbfpHeader_t Header = {0};
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 1;
        Header.flags.crc_check_need = 1;
        Header.flags.lifetime = 1;
        Header.payload_id = FRAME_ID_STORAGE;
        Header.snum = 1;
        Header.len = payload_len;
        memcpy(Node->TxFrame, &Header, sizeof(TbfpHeader_t));
        StorageFrameHeader_t StorageData;
        StorageData.address = 0;
        StorageData.asic_num = 1;
        StorageData.operation = ACCESS_ERASE;
        StorageData.size = 0; /* Bytes to read */

        memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));

        uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
        uint16_t total_frame_len = frame_len + 1;
        Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
        LOG_INFO(TBFP, "StoreEraseFrame:%s", ArrayToStr(Node->TxFrame, total_frame_len));
        uint32_t i = 0;
        for(i=0; i < total_frame_len; i++) {
            cli_printf("$%02X", Node->TxFrame[i]);
        }
        cli_printf(CRLF);
        res = true;
    }
    return res;
}

bool tbfp_storage_write_generate(uint32_t address, uint16_t size, uint8_t pattern) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(1);
    if(Node) {
        LOG_INFO(TBFP, "Address:0x%08x,Size:%u,Pattern:0x%02x", address, size, pattern);
        LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
        uint16_t payload_len = (uint16_t)sizeof(StorageFrameHeader_t) + size;
        LOG_INFO(TBFP, "PayLoadLen:%u byte", payload_len);
        TbfpHeader_t Header = {0};
        Header.preamble = Node->preamble_val;
        Header.flags.ack_need = 1;
        Header.flags.crc_check_need = 1;
        Header.flags.lifetime = 1;
        Header.payload_id = FRAME_ID_STORAGE;
        Header.snum = 1;
        Header.len = payload_len;
        memcpy(Node->TxFrame, &Header, sizeof(TbfpHeader_t));
        StorageFrameHeader_t StorageData;
        StorageData.address = address;
        StorageData.asic_num = 1;
        StorageData.operation = ACCESS_WRITE_ONLY;
        StorageData.size = size; /* Bytes to read */

        memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));
        uint32_t data_index = sizeof(TbfpHeader_t) + sizeof(StorageFrameHeader_t);

        memset(&Node->TxFrame[data_index], pattern, size);

        uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
        uint16_t total_frame_len = frame_len + 1;
        Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
        LOG_INFO(TBFP, "StoreWriteFrame:%s", ArrayToStr(Node->TxFrame, total_frame_len));
        uint32_t i = 0;
        for(i=0; i < total_frame_len; i++) {
            cli_printf("$%02X", Node->TxFrame[i]);
        }
        cli_printf(CRLF);
        res = true;
    }
    return res;
}

bool tbfp_storage_read_generate(uint32_t address, uint16_t size) {
    bool res = false;
    TbfpHandle_t* Node = TbfpGetNode(1);
    if(Node) {
    	if(Node->TxFrame) {
            LOG_INFO(TBFP, "%s", TbfpNode2Str(Node));
            uint16_t payload_len = (uint16_t)sizeof(StorageFrameHeader_t);
            LOG_INFO(TBFP, "PayLoadLen:%u byte", payload_len);
            TbfpHeader_t Header = {0};
            Header.preamble = Node->preamble_val;
            Header.flags.ack_need = 1;
            Header.flags.crc_check_need = 0;
            Header.flags.lifetime = 1;
            Header.payload_id = FRAME_ID_STORAGE;
            Header.snum = 1;
            Header.len = payload_len;
            memcpy(Node->TxFrame, &Header, sizeof(TbfpHeader_t));
            StorageFrameHeader_t StorageData;
            StorageData.operation = ACCESS_READ_ONLY;
            StorageData.address = address;
            StorageData.asic_num = 1;
            StorageData.size = size; /* Bytes to read */

            memcpy(&Node->TxFrame[sizeof(TbfpHeader_t)], &StorageData, sizeof(StorageFrameHeader_t));

            uint16_t frame_len = payload_len + sizeof(TbfpHeader_t);
            uint16_t total_frame_len = frame_len+1;
            Node->TxFrame[frame_len] = crc8_sae_j1850_calc(Node->TxFrame, frame_len);
            LOG_INFO(TBFP, "StoreReadFrame:%s", ArrayToStr(Node->TxFrame, total_frame_len));
            uint32_t i = 0;
            for(i=0; i<total_frame_len; i++) {
                cli_printf("$%02X", Node->TxFrame[i]);
            }
            cli_printf(CRLF);
            res = true;
    	}
    }
    return res;
}

