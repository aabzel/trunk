#include "i2s_full_duplex_diag.h"

#include <stdio.h>
#include <string.h>

#include "i2s_full_duplex.h"
#include "log.h"
#include "table_utils.h"
#include "writer_config.h"

const char* I2sFullDuplexToStr(const I2sFullDuplexConfig_t* const Config) {
    static char line[120] = "";
    if(Config) {
        strncpy(line, "", sizeof(line) - 1);
        snprintf(line, sizeof(line), "%sN:%u,", line, Config->num);
        snprintf(line, sizeof(line), "%sI2sTx:%u,", line, Config->i2s_tx_num);
        snprintf(line, sizeof(line), "%sI2sRx:%u,", line, Config->i2s_rx_num);
        snprintf(line, sizeof(line), "%sRxBuff:%s", line, Config->name);
        LOG_INFO(I2S, "%s", line);
    }
    return line;
}

bool I2sFullDuplexDiagConfig(const I2sFullDuplexConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(I2S, "%s", I2sFullDuplexToStr(Config));
        res = true;
    }

    return res;
}

const char* I2sFullDuplexStateToStr(I2sFullDuplexState_t state) {
    const char* name = "?";
    switch((uint32_t)state) {
    case I2S_FULL_DUPLEX_STATE_IDLE:
        name = "Idle";
        break;
    case I2S_FULL_DUPLEX_STATE_TX:
        name = "Tx";
        break;
    case I2S_FULL_DUPLEX_STATE_RX:
        name = "Rx";
        break;
    case I2S_FULL_DUPLEX_STATE_RX_TX:
        name = "RxTx";
        break;
    }
    return name;
}

const char* I2sFullDuplexInputToStr(I2sFullDuplexInputs_t input) {
    const char* name = "?";
    switch((uint32_t)input) {
    case I2S_FULL_DUPLEX_INPUTS_RX_HALF:
        name = "RxHalf";
        break;
    case I2S_FULL_DUPLEX_INPUTS_RX_DONE:
        name = "RxDone";
        break;
    case I2S_FULL_DUPLEX_INPUTS_TX_HALF:
        name = "TxHalf";
        break;
    case I2S_FULL_DUPLEX_INPUTS_TX_DONE:
        name = "TxDone";
        break;
    case I2S_FULL_DUPLEX_INPUTS_START:
        name = "Start";
        break;
    case I2S_FULL_DUPLEX_INPUTS_STOP:
        name = "Stop";
        break;
    }
    return name;
}

bool i2s_full_duplex_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "Num"},    {9, "PrCnt"},  {8, "State"},  {8, "Input"}, {9, "RxHalf"},
        {9, "RxDone"}, {9, "TxHalf"}, {9, "TxDone"}, {7, "Start"}, {6, "stop"},
    };
    uint16_t cnt = 0;
    cnt = i2s_full_duplex_get_cnt();
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t num = 0;
    char text[200];
    for(num = 0; num <= cnt; num++) {
        I2sFullDuplexHandle_t* Node = I2sFullDuplexGetNode(num);
        if(Node) {
            strcpy(text, TSEP);
            snprintf(text, sizeof(text), "%s %3u " TSEP, text, Node->num);
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->proc_cnt);
            snprintf(text, sizeof(text), "%s %6s " TSEP, text, I2sFullDuplexStateToStr(Node->state));
            snprintf(text, sizeof(text), "%s %6s " TSEP, text, I2sFullDuplexInputToStr(Node->input));
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->rx_half_cnt);
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->rx_done_cnt);
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->tx_half_cnt);
            snprintf(text, sizeof(text), "%s %7u " TSEP, text, Node->tx_done_cnt);
            snprintf(text, sizeof(text), "%s %5u " TSEP, text, Node->start_cnt);
            snprintf(text, sizeof(text), "%s %4u " TSEP, text, Node->stop_cnt);
            cli_printf("%s" CRLF, text);

            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
