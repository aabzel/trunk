#include "nmea_diag.h"

#include <stdio.h>
#include <string.h>

#include "table_utils.h"
#include "log.h"
#include "writer_config.h"
#include "time_mcal.h"
#include "writer_generic.h"
#include "nmea_protocol.h"
#include "time_diag.h"
#include "gnss_diag.h"

#ifndef HAS_NMEA_DIAG
#error "+HAS_NMEA_DIAG"
#endif

const char* NmeaPosModeToStd(PositionMode_t pos_mode) {
    const char *name = "?";
    switch (pos_mode) {
    case PM_RTK_FIXED:
        name = "RtkFixed";
        break;
    case PM_RTK_FLOAT:
        name = "RtkFloat";
        break;
    case PM_DEAD_RECKONING_FIX:
        name = "DeadReckFix";
        break;
    case PM_DEAD_RECKONING_FIX_BUT_USER_LIMITS_EXCEEDED:
        name = "DeadReckFixUseLimExceeded";
        break;
    case PM_GNSS_FIX_BUT_USER_LIMITS_EXCEEDED:
        name = "GnssFixButUserLimExceeded";
        break;
    case PM_NO_POSITION_FIX:
        name = "NoPosFix";
        break;
    case PM_2D_GNSS_FIX:
        name = "2dGnssFix";
        break;
    case PM_3D_GNSS_FIX:
        name = "3dGnssFix";
        break;
    case PM_COMBINED_GNSS_DEAD_RECKONING_FIX:
        name = "CombGnssDeadReckFix";
        break;
    default:
        name = "Err";
        break;
    }
    return name;
}

bool nmea_data(uint8_t num) {
    bool res = false;
    NmeaHandle_t *Node = NmeaGetNode(num);
    if (Node) {
        res = true;
        print_time_date("NMEA:", &Node->rmc.time_date, true);
        LOG_INFO(NMEA, "RTK StartCnt:%d", Node->rtk_start_cnt);
    LOG_INFO(NMEA,"PosMode: %u %s", Node->pos_mode,
              NmeaPosModeToStd(Node->pos_mode));
    LOG_INFO(NMEA,"RTKFixedDuration:%u ms=%f s=%f min",
              Node->cur_rtk_fixed_duration,
              MSEC_2_SEC(Node->cur_rtk_fixed_duration),
              MSEC_2_MIN(Node->cur_rtk_fixed_duration));
    LOG_INFO(NMEA,"RTKFixedMaxDuration:%u ms=%f s=%f min",
              Node->rtk_fixed_max_duration_ms,
              MSEC_2_SEC(Node->rtk_fixed_max_duration_ms),
              MSEC_2_MIN(Node->rtk_fixed_max_duration_ms));
        LOG_INFO(NMEA, "RCM");
        print_coordinate("NMEA:", Node->rmc.coordinate_ddmm, true);
        Node->rmc.coordinate_dd = encode_gnss_coordinates(Node->rmc.coordinate_ddmm);
        print_coordinate("NMEA:", Node->rmc.coordinate_dd, true);

        LOG_INFO(NMEA, "GGA");
        print_coordinate("NMEA:", Node->gga.coordinate_ddmm, true);
        Node->gga.coordinate_dd = encode_gnss_coordinates(Node->gga.coordinate_ddmm);
        print_coordinate("NMEA:", Node->gga.coordinate_dd, true);

        LOG_INFO(NMEA, "speed_knots:%f", Node->rmc.speed_knots);
        LOG_INFO(NMEA, "height:%f", Node->gga.height);
        LOG_INFO(NMEA, "nb_sat:%u", Node->gga.nb_sat);

        LOG_INFO(NMEA, "General");
        print_coordinate("NMEA:", Node->coordinate_dd, true);
    }
    return res;
}

const char* NmeaNodeMainToStr(const NmeaHandle_t *const Node){
    static char text[100]={0};
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%s,Cor:%s", text, GnssCoordinateToStr(&Node->coordinate_dd));
        snprintf(text, sizeof(text), "%s,%s", text, TimeDate2StrShort(&Node->rmc.time_date));
    }
    return text;
}


const char* NmeaNodeToStr(const NmeaHandle_t *const Node){
    static char text[300]={0};
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%s,%s", text, TimeDate2StrShort(&Node->rmc.time_date));
        snprintf(text, sizeof(text), "%s,Rx:%u bytes", text, Node->rx_byte_cnt);
        snprintf(text, sizeof(text), "%s,Cor:%s", text, GnssCoordinateToStr(&Node->coordinate_dd));
        snprintf(text, sizeof(text), "%s,MsgCnt:%2u", text, Node->msg_cnt);
        snprintf(text, sizeof(text), "%s,CrcRead:%2u", text, Node->crc_read_cnt);
        snprintf(text, sizeof(text), "%s,CrcOk:%2u", text, Node->crc_ok_cnt);
        snprintf(text, sizeof(text), "%s,CrcErr:%2u", text, Node->crc_err_cnt);
        snprintf(text, sizeof(text), "%s,Proc:%2u", text, Node->proc_msg_cnt);
        snprintf(text, sizeof(text), "%s,RxUndef:%2u", text, Node->undef_err_cnt);
    }
    return text;
}

bool nmea_diag(uint8_t num) {
    bool res = false;
    NmeaHandle_t *Node = NmeaGetNode(num);
    if (Node) {
        LOG_INFO(NMEA, "%s", NmeaNodeToStr(Node));
        res= true;
    }
    return res;
}

bool nmea_messages(uint8_t num) {
    bool res = false;
    NmeaHandle_t *Node = NmeaGetNode(num);
    if (Node) {
        res = true;
        static const table_col_t cols[] = { { 5, "mess" }, { 8, "hCnt" }, { 8, "pCnt" }, };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        cli_printf(TSEP" GGA "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->gga.fcnt.h_cnt,
                Node->gga.fcnt.cnt);
        cli_printf(TSEP" GLL "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->gll.fcnt.h_cnt,
                Node->gll.fcnt.cnt);
        cli_printf(TSEP" GSA "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->gsa.fcnt.h_cnt,
                Node->gsa.fcnt.cnt);
        cli_printf(TSEP" GSV "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->gsv.fcnt.h_cnt,
                Node->gsv.fcnt.cnt);
        cli_printf(TSEP" PBUX"TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->pbux.fcnt.h_cnt,
                Node->pbux.fcnt.cnt);
        cli_printf(TSEP" RMC "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->rmc.fcnt.h_cnt,
                Node->rmc.fcnt.cnt);
        cli_printf(TSEP" VTG "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->vtg.fcnt.h_cnt,
                Node->vtg.fcnt.cnt);
        cli_printf(TSEP" ZDA "TSEP" %6u "TSEP" %6u "TSEP CRLF, Node->zda.fcnt.h_cnt,
                Node->zda.fcnt.cnt);
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }

    return res;
}
