#include "ir_receiver_diag.h"

#include <stdio.h>
#include <string.h>

#include "array_diag.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "ext_int_diag.h"
#include "ir_samsung_mcal.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* IrReceiverConfigToStr(const IrReceiverConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sTIM%u,", text, Config->timer_num);
        snprintf(text, sizeof(text), "%sExpSZ:%u,", text, Config->exp_size);
        snprintf(text, sizeof(text), "%sSigSZ:%u,", text, Config->signal_size);
    }
    return text;
}

const char* IrReceiverNodeToStr(const IrReceiverHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%si:%u,", text, Node->event_i);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

bool ir_receiver_diag(void) {
    bool res = false;
    return res;
}

bool IrReceiverFrameDiag(const IrReceiverHandle_t* const Node) {
    bool res = false;
    LOG_INFO(IR_RECEIVER, "AllEvents");
    const table_col_t cols[] = {
        {5, "i"},
        {6, "event"},
        {8, "time"},
        {8, "diff"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    uint32_t diff_prev_us = 0;
    uint32_t i = 0;
    for(i = 0; i < Node->exp_size; i++) {
        uint32_t diff_us = Node->signal_fix[i].up_time_us - diff_prev_us;
        char log_line[150] = {0};
        strcpy(log_line, TSEP);
        snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
        snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, ExtIntEdgeToStr(Node->signal_fix[i].event));
        snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, Node->signal_fix[i].up_time_us);
        snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, diff_us);
        cli_printf("%s" CRLF, log_line);

        diff_prev_us = Node->signal_fix[i].up_time_us;
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool IrReceiverFrameRisingDiag(const IrReceiverHandle_t* const Node) {
    bool res = false;
    LOG_INFO(IR_RECEIVER, "RisingEvents");
    const table_col_t cols[] = {
        {5, "bit"}, {5, "i"}, {8, "time"}, {8, "diff"}, {7, "bit"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t diff_prev_us = 0;
    uint32_t i = 0;
    uint32_t num = 0;
    for(i = 0; i < Node->exp_size; i++) {
        if(PIN_INT_EDGE_RISING == Node->signal_fix[i].event) {
            num++;
            uint32_t diff_us = Node->signal_fix[i].up_time_us - diff_prev_us;
            IrSamsungBit_t bit_val = IrSamsungRisingDiffToBitValue(diff_us);
            char log_line[150] = {0};
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, num);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, i);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, Node->signal_fix[i].up_time_us);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, diff_us);
            snprintf(log_line, sizeof(log_line), "%s %5s " TSEP, log_line, IrSamsungBitValToStr(bit_val));
            cli_printf("%s" CRLF, log_line);
            diff_prev_us = Node->signal_fix[i].up_time_us;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
