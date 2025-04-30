
#include "rtcm3_commands.h"

#include <stdbool.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "io_utils.h"
#include "log.h"
#include "str_utils.h"
#include "system.h"
#include "system_diag.h"
#include "rtcm3_protocol.h"
#include "table_utils.h"
#include "writer_generic.h"
#include "writer_config.h"

static bool rtcm3_diag_lost(char* key_word1, char* key_word2) {
    bool res = false;
    uint8_t interface_base_gnss = IF_UART1;
    static const table_col_t cols[] = {{10, "interf"},
                                       {5, "Fwd"},
                                       {9, "lost"},
                                       {8, "lost,%"},
                                       {9, "RxCnt"},
    };
    char line_str[200] = "";
    char suffix_str[200] = "";
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    Interfaces_t intf;
    for(intf =(Interfaces_t) 0; intf<IF_CNT; intf++){
        strcpy(line_str, TSEP);
        snprintf(suffix_str, sizeof(suffix_str)," %8s " TSEP, InterfaceToStr((Interfaces_t)intf));
        strncat(line_str,suffix_str, sizeof(line_str));

        snprintf(suffix_str, sizeof(suffix_str),"  %1u  " TSEP, Rtcm3Protocol[interface_base_gnss].forwarding[intf]);
        strncat(line_str,suffix_str, sizeof(line_str));

        double lost_pkt_pc = ((double)100*Rtcm3Protocol[interface_base_gnss].lost_pkt_cnt[intf])/((double)Rtcm3Protocol[interface_base_gnss].rx_pkt_cnt);
        snprintf(suffix_str, sizeof(suffix_str)," %7u " TSEP,  Rtcm3Protocol[interface_base_gnss].lost_pkt_cnt[intf]);
        strncat(line_str,suffix_str, sizeof(line_str));

        snprintf(suffix_str, sizeof(suffix_str),"   %3.1f  " TSEP,(double) lost_pkt_pc);
        strncat(line_str,suffix_str, sizeof(line_str));

        snprintf(suffix_str, sizeof(suffix_str)," %7u " TSEP, Rtcm3Protocol[interface_base_gnss].rx_pkt_cnt);
        strncat(line_str,suffix_str, sizeof(line_str));

        if(is_contain(line_str, key_word1, key_word2)) {
            io_printf("%s"CRLF, line_str);
        }
    }
    res = true;

    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

static bool rtcm3_diag(void) {
    bool res = false;
    uint8_t interface = 0;
    static const table_col_t cols[] = {{10, "interf"},
                                       {9, "rxCnt"},
                                       {9, "crcErCnt"},
#ifdef HAS_DEBUG
                                       {9, "DiffRxCnt"},
                                       {9, "preCnt"},
                                       {9, "ErCnt"},
                                       {9, "minLen"},
                                       {9, "maxLen"},
#endif /*HAS_DEBUG*/
                                       {9, "jumbo"},
    };
    table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    for(interface = 0; interface < ARRAY_SIZE(Rtcm3Protocol); interface++) {
        if(interface==Rtcm3Protocol[interface].interface){
            io_printf(TSEP);
            io_printf(" %8s " TSEP, InterfaceToStr((Interfaces_t)Rtcm3Protocol[interface].interface));
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].rx_pkt_cnt);
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].crc_err_cnt);
    #ifdef HAS_DEBUG
            Rtcm3Protocol[interface].diff_rx_pkt_cnt = Rtcm3Protocol[interface].rx_pkt_cnt-Rtcm3Protocol[interface].prev_rx_pkt_cnt;
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].diff_rx_pkt_cnt);
            Rtcm3Protocol[interface].prev_rx_pkt_cnt = Rtcm3Protocol[interface].rx_pkt_cnt;
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].preamble_cnt);
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].err_cnt);
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].min_len);
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].max_len);
    #endif /*HAS_DEBUG*/
            io_printf(" %7u " TSEP, Rtcm3Protocol[interface].jumbo_frame_cnt);
            io_printf(CRLF);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
    return res;
}

bool rtcm3_diag_lost_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: rtcmd keyWord1 keyWord2");
    }
    if(true == res) {
        res = rtcm3_diag_lost(keyWord1, keyWord2);
    }
    return res;
}

bool rtcm3_rate_diag(void){
    bool res = false;

        res = true;
        uint8_t interface = 0;
        static const table_col_t cols[] = {{10, "interf"},
                                           {9, "rxMin"},
                                           {9, "rx"},
                                           {9, "rxMax"},
                                           {9, "txMin"},
                                           {9, "tx"},
                                           {9, "txMax"}
        };




        table_header(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));
        for(interface = 0; interface < ARRAY_SIZE(Rtcm3Protocol); interface++) {
            if(interface==Rtcm3Protocol[interface].interface){
                io_printf(TSEP);
                io_printf(" %8s " TSEP, InterfaceToStr((Interfaces_t)Rtcm3Protocol[interface].interface));
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].rx_rate.min);
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].rx_rate.cur);
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].rx_rate.max);
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].tx_rate.min);
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].tx_rate.cur);
                io_printf(" %7u " TSEP, Rtcm3Protocol[interface].tx_rate.max);
                io_printf(CRLF);
                res = true;
            }
        }
        table_row_bottom(&(curWriterPtr->s), cols, ARRAY_SIZE(cols));

    return res;
}

bool rtcm3_rate_command(int32_t argc, char* argv[]){
    bool res = false;
    if(0 == argc) {
        res = true;
        res = rtcm3_rate_diag();
    } else {
        LOG_ERROR(SYS, "Usage: rtcmr");
    }
    return res;
}

bool rtcm3_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(SYS, "Usage: rtcmd");
    }

    if(res) {
        res = rtcm3_diag();
    }
    return res;
}

bool rtcm3_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t interface = 0;
    if(1 == argc) {
        res = try_str2uint8(argv[0], &interface);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract interface %s", argv[0]);
        }
    } else {
        LOG_ERROR(SYS, "Usage: rtcmr interface");
    }
    if(res) {
        res = rtcm3_reset_rx(&Rtcm3Protocol[interface],WAIT_INIT);
    }
    return res;
}


bool rtcm3_fwd_command(int32_t argc, char* argv[]){
    bool res = false;
    bool status= 0;
    uint8_t interface1 = 0;
    uint8_t interface2 = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &interface1);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract interface1 %s", argv[0]);
        }

        res = try_str2uint8(argv[1], &interface2);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract interface2 %s", argv[1]);
        }

        res = try_str2bool(argv[2], &status);
        if(false == res) {
            LOG_ERROR(SYS, "Unable to extract status %s", argv[2]);
        }
    } else {
        LOG_ERROR(SYS, "Usage: rtcmf interface1 interface2 status");
    }
    if(res) {
        Rtcm3Protocol[interface1].forwarding[interface2] = status;
    }
    return res;
}
