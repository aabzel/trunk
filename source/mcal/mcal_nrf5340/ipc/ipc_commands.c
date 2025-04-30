#include "ipc_commands.h"

#include <stdio.h>

#include "convert.h"
#include "nrfx_ipc.h"
#include "data_utils.h"
#include "nrf_ipc.h"
#include "table_utils.h"
#include "ipc_drv.h"
#include "log.h"
#include "writer_config.h"

bool ipc_signal_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t send_index = 0;
    if(1==argc) {
        res = try_str2uint8(argv[0], &send_index);
        if(false == res) {
            LOG_ERROR(IPC, "ParseErr SendIdx");
        }
    }
    if(res) {
        nrfx_ipc_signal(send_index);
        LOG_INFO(IPC, "Signal %u",send_index);
    }else{
        LOG_ERROR(IPC, "Usage ips SendIdx");
    }
    return res;
}

bool ipc_rx_event_command(int32_t argc, char* argv[]) {
    bool res=false;
    uint8_t event_index = 0;
    bool on_off = 0;
    if(2==argc){
        res = try_str2uint8(argv[0], &event_index);
        if(false == res) {
            LOG_ERROR(IPC, "ParseErr EventIdx");
        }
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(IPC, "ParseErr OnOff");
        }
    }
    if(res) {
        if(on_off) {
            nrfx_ipc_receive_event_enable(event_index);
        }else {
            nrfx_ipc_receive_event_disable(event_index);
        }
        LOG_INFO(IPC, "EventIndex %u",event_index);
    }
    return res;
}

bool ipc_rx_event_chan_command(int32_t argc, char* argv[]) {
    bool res=false;
    uint8_t event_index =0;
    uint8_t channel_index=0;
    if(2==argc) {
        res = try_str2uint8(argv[0], &event_index);
        if(false == res) {
            LOG_ERROR(IPC, "ParseErr EventIdx");
        }
        res = try_str2uint8(argv[1], &channel_index);
        if(false == res) {
            LOG_ERROR(IPC, "ParseErr ChannelIdx");
        }
    }
    if(res) {
        nrfx_ipc_receive_event_channel_assign(  event_index,   channel_index);
        LOG_INFO(IPC, "EventIndex %u ChannelIndex %u",event_index,channel_index);
    }
    return res;
}

bool ipc_diag_command(int32_t argc, char* argv[]) {
    bool res=false;
    if(0==argc) {
        res=true;
    }
    if(res) {
        LOG_INFO(IPC, "IntCnt %u ",Ipc.it_cnt);
        static const table_col_t cols[] = {{5, "Chn"},
                                           {7, "IntEn"},
                                           {6, "Pend"},
                                           {6, "Send"},
                                           {6, "Rx"},
        };
        uint32_t i =0;
        char log_line[150];
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t int_pending = nrf_ipc_int_pending_get(NRF_IPC);
        for(i=0;i<IPC_CH_NUM;i++) {
            strcpy(log_line, TSEP);
            uint32_t send=nrf_ipc_send_config_get(NRF_IPC, i);
            uint32_t rx=nrf_ipc_receive_config_get(NRF_IPC, i);
            uint32_t it_en = nrf_ipc_int_enable_check(NRF_IPC, (((uint32_t )1U)<<i));
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, (0<it_en)?"+":".");
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, GET_BIT_NUM(int_pending,i));
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, (0<send)?"Tx":".");
            snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, (0<rx)?"Rx":".");
            cli_printf("%s" CRLF, log_line);
            res=true;
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
