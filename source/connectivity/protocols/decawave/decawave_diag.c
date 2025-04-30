
#include "decawave_diag.h"

#include <stdio.h>

#ifdef HAS_FAT_FS
#include "fat_fs_drv.h"
#endif
#include "decawave.h"
#include "decawave_types.h"
#include "log.h"
#include "protocol_diag.h"
#include "table_utils.h"
#include "utils_math.h"
#include "uwb_diag.h"
#include "writer_config.h"

const char* DecaMes2Str(DwcaMess_t code) {
    const char* name = "?";
    switch((uint8_t)code) {
    case DECA_BLINK:
        name = "Blink";
        break;
    case DECA_RANGING_INIT:
        name = "RangInit";
        break;
    case DECA_POLL:
        name = "Poll";
        break;
    case DECA_RESP:
        name = "Resp";
        break;
    case DECA_RESP_POLL:
        name = "RespPoll";
        break;
    case DECA_FINAL:
        name = "Final";
        break;
    }
    return name;
}

const char* DecaWaveVarId2Str(UwbVatiable_t var_id) {
    const char* name = "?";
    switch((uint8_t)var_id) {
    case UWB_VAR_INITIATOR_T_LOOP:
        name = "INITIATOR_T_LOOP";
        break;
    case UWB_VAR_INITIATOR_T_DELAY:
        name = "INITIATOR_T_DELAY";
        break;
    case UWB_VAR_RESPONDER_T_DELAY:
        name = "RESPONDER_T_DELAY";
        break;
    case UWB_VAR_RESPONDER_T_LOOP:
        name = "RESPONDER_T_LOOP";
        break;
    case UWB_VAR_RESPONDER_TIMINGS:
        name = "RESPONDER_TIMINGS";
        break;
    case UWB_VAR_SHARE_DIST:
        name = "SHARE_DIST";
        break;
    case UWB_VAR_RAW_DATA:
        name = "RAW_DATA";
        break;
    }
    return name;
}

bool decawave_diag_distanse(uint8_t num) {
    bool res = false;
    double dist = 0.0;
    res = decawave_dist_get(num, &dist);
    LOG_INFO(DECAWAVE, "Dist %f m", dist);

    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        char log_line[150];
        static const table_col_t cols_units[] = {
                {9, "text"},
                {9, "m"},
                {29, "m"},
                };
        table_cap(&(curWriterPtr->stream), cols_units, ARRAY_SIZE(cols_units));
        static const table_col_t cols[] = {{9, "Comment"}, {9, "Phase1"}, {9, "Phase2"}, {9, "Average"}, {9, "DS-TWR"}};
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "measure");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase1.distance_m.cur));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase2.distance_m.cur));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->avarage_distance_m.cur));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->final.distance_m.cur));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "min");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase1.distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase2.distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->avarage_distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->final.distance_m.min));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "max");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase1.distance_m.max));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase2.distance_m.max));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->avarage_distance_m.max));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->final.distance_m.max));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "delta");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( Node->phase1.distance_m.max - Node->phase1.distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( Node->phase2.distance_m.max - Node->phase2.distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( Node->avarage_distance_m.max - Node->avarage_distance_m.min));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( Node->final.distance_m.max - Node->final.distance_m.min));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "average");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( AVERAGE_2(Node->phase1.distance_m.max, Node->phase1.distance_m.min)));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( AVERAGE_2(Node->phase2.distance_m.max, Node->phase2.distance_m.min)));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( AVERAGE_2(Node->avarage_distance_m.max, Node->avarage_distance_m.min)));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str( AVERAGE_2(Node->final.distance_m.max, Node->final.distance_m.min)));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP); /*Real*/
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "real");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase1.distance_real_m));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->phase2.distance_real_m));
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "0.0");
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, UwbDistance2Str(Node->final.distance_real_m));
        cli_printf("%s" CRLF, log_line);

        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %7s " TSEP, log_line, "AnDelay");
        snprintf(log_line, sizeof(log_line), "%s %7.2f " TSEP, log_line, Node->phase1.ant_delay_m);
        snprintf(log_line, sizeof(log_line), "%s %7.2f " TSEP, log_line, Node->phase2.ant_delay_m);
        snprintf(log_line, sizeof(log_line), "%s %7.2f " TSEP, log_line, 0.0);
        snprintf(log_line, sizeof(log_line), "%s %7.2f " TSEP, log_line, Node->phase2.ant_delay_m);
        cli_printf("%s" CRLF, log_line);

        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        res = true;
    }

    return res;
}

const char* DecaWaveHeader2Str( const DecaWaveHeader_t* const Header){
    static char text[80]="";
    if(Header) {
        snprintf(text,sizeof(text), "Type:%s,SN:%u,From:0x%x,To:0x%x,Payload:%u Byte",
                 DecaMes2Str(Header->message),
              Header->sequence_number,
              Header->source_addr,
              Header->destination_addr,
              Header->payload_size);
    }
    return text;
}

bool DecaWaveHeaderDiag(log_level_t level, const char* const prefix, const DecaWaveHeader_t* const Header) {
    bool res = false;
    if(Header) {
        log_write(level, DECAWAVE, "[%s] %s", prefix, DecaWaveHeader2Str( Header));
        res = true;
    }
    return res;
}

#ifdef HAS_DECAWAVE_SNIFFER
bool decawave_log_sd(const DecaWaveHeader_t* const Header) {
    bool res = false;
    if(Header) {
        char file_name[20]="DecaWaveRx.txt";
        res = fat_fs_write(file_name, DecaWaveHeader2Str(Header));
    }
    return res;
}
#endif


bool decawave_protocol_diag(uint8_t num) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        LOG_INFO(DECAWAVE, "ProtocolDiag %u", num);
        LOG_INFO(DECAWAVE, "MyID 0x%x", Node->addr);
        LOG_INFO(DECAWAVE, "err %u", Node->err_cnt);
        LOG_INFO(DECAWAVE, "CrcOk %u", Node->crc_ok_cnt);
        LOG_INFO(DECAWAVE, "CrcErr %u", Node->crc_err_cnt);
        LOG_INFO(DECAWAVE, "RxByte %u", Node->rx_byte);
        LOG_INFO(DECAWAVE, "RxPkt %u", Node->rx_pkt_cnt);
        LOG_INFO(DECAWAVE, "TxByte %u", Node->tx_byte);
        res = true;
    }
    return res;
}

bool decawave_diag_flow(uint8_t num) {
    bool res = false;
    DecaWaveHandle_t* Node = DecaWaveGetNode(num);
    if(Node) {
        LOG_INFO(DECAWAVE, "DiagFlow %u", num);
#ifdef HAS_PROTOCOL_DIAG
        res = flow_ctrl_diag(DECAWAVE, &Node->Flow, IF_UWB);
#endif
    }
    return res;
}
