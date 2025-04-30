#include "ds_twr_diag.h"

#include <stdio.h>
#include <string.h>

#include "uwb_if.h"
#include "uwb_diag.h"
#include "common_diag.h"
#include "ds_twr.h"
#include "ds_twr_types.h"
#include "log.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "utils_math.h"
#include "writer_config.h"

char* DsTwrInput2Str(DsTwrInput_t input) {
    char* name = "?";
    switch((uint8_t)input) {
    case DS_TWR_INPUT_NONE:
        name = "NONE";
        break;
    case DS_TWR_INPUT_RX_TIME_STAMP:
        name = "RX_TIME_STAMP";
        break;
    case DS_TWR_INPUT_TX_TIME_STAMP:
        name = "TX_TIME_STAMP";
        break;
    case DS_TWR_INPUT_RX_POLL:
        name = "RX_POLL";
        break;
    case DS_TWR_INPUT_RX_PESPONDER_TIMINGS:
        name = "RX_PESPONDER_TIMINGS";
        break;
    case DS_TWR_INPUT_RX_RESPONSE:
        name = "RX_RESPONSE";
        break;
    case DS_TWR_INPUT_RX_PESPONSE_POLL:
        name = "RX_PESPONSE_POLL";
        break;
    case DS_TWR_INPUT_START:
        name = "START";
        break;
    case DS_TWR_INPUT_TIME_OUT:
        name = "TIME_OUT";
        break;
    }
    return name;
}

char* DsTwrState2Str(DsTwrState_t state) {
    char* name = "?";
    switch((uint8_t)state) {
    case DS_TWR_IDLE:
        name = "IDLE";
        break;
    case DS_TWR_INITIATOR_LOOP:
        name = "INITIATOR_LOOP";
        break;
    case DS_TWR_INITIATOR_DELAY:
        name = "INITIATOR_DELAY";
        break;
    case DS_TWR_RESPONDER_DELAY:
        name = "RESPONDER_DELAY";
        break;
    case DS_TWR_RESPONDER_LOOP:
        name = "RESPONDER_LOOP";
        break;
    case DS_TWR_DONE:
        name = "DONE";
        break;
    case DS_TWR_INITIATOR_WAIT_TIMING:
        name = "INITIATOR_WAIT_TIMING";
        break;
    }
    return name;
}


bool ds_twr_diag(DsTwr_t* const Node) {
    bool res = false;
    LOG_INFO(DS_TWR, CRLF "DsTwrDiag");
    if(Node) {
        LOG_INFO(DS_TWR, "ProcCnt %u", Node->proc_cnt);


        if(Node->err_cnt) {
            LOG_ERROR(DS_TWR, "ErrCnt %u", Node->err_cnt);
        }

        LOG_INFO(DS_TWR, "OffSet %f m", Node->offset_m);
        LOG_INFO(DS_TWR, "TimerClock %llu Hz", Node->timer_clock);
        LOG_INFO(DS_TWR, "ContinuousMode %s", OnOff2Str(Node->continuous));
    }
    return res;
}

const char* DsTwrDiagNode2Str( DsTwr_t* const Node){
    const char* name = "?";
    if(Node) {
        snprintf(Node->text, sizeof(Node->text), "Proc:%u,iter:%u,%s,%s,Spin:%u,CupPollId %u",
                Node->proc_cnt,
                Node->iter_cnt,
                DsTwrState2Str(Node->state),
                DsTwrInput2Str(Node->cur_input),
                Node->spin_cnt,
                Node->cur_id_index);
        name = Node->text;
    }
    return name;
}

bool DsTwrDiagNode(const DsTwr_t* const Node){
    bool res = false;
    if(Node) {
        LOG_INFO(DS_TWR, "%s", DsTwrDiagNode2Str((DsTwr_t* const)Node));
        res = true;
    }
    return res;
}

bool DsTwdDiagConfig(const DsTwrConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(DS_TWR, "StaticNodeCnt: %u", Config->known_nodes_cnt);
        uint8_t i = 0;
        for(i = 0; i < Config->known_nodes_cnt; i++) {
            LOG_INFO(DS_TWR, "0x%x", Config->known_nodes[i]);
        }
        res = true;
    }
    return res;
}

bool DsTwrDiagDistances(UwbIdInfo_t* Node, uint16_t cnt) {

    static const table_col_t cols[] = {
        {4, "No"},
        {8, "id"},
        {7, "valid"},
        {10, "distance"},
        {10, "dist_min"},
        {10, "dist_max"},
        {10, "Diff[m]"},
        {10, "ant_delay"},
    };
    char log_line[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    bool res = false;
    uint32_t i = 0;
    double delta_m = 0.0;
    for(i = 0; i < cnt; i++) {
        delta_m = Node[i].range_m.max-Node[i].range_m.min;
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, i + 1);
        snprintf(log_line, sizeof(log_line), "%s 0x%02x " TSEP, log_line, Node[i].id);
        snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node[i].valid);
        snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, UwbDistance2Str(Node[i].range_m.cur));
        snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, UwbDistance2Str(Node[i].range_m.min));
        snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, UwbDistance2Str(Node[i].range_m.max));
        snprintf(log_line, sizeof(log_line), "%s %8s " TSEP, log_line, BigVal2Str(delta_m) );
        snprintf(log_line, sizeof(log_line), "%s %8.2f " TSEP, log_line, Node[i].ant_delay_m);
        cli_printf("%s" CRLF, log_line);
        res = true;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}
