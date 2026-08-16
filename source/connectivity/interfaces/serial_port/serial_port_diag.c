#include "serial_port_diag.h"

#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "log.h"
#include "serial_port.h"
#include "table_utils.h"

const char* SerialPortNodeToStr(const SerialPortHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sCOM%u,", text, Node->com_port_num);
        snprintf(text, sizeof(text), "%sPause:%u ms,", text, Node->byte_tx_pause_ms);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Node->bit_rate);
        snprintf(text, sizeof(text), "%sRx:%u byte,", text, Node->rx_cnt);
        snprintf(text, sizeof(text), "%sTx:%u byte,", text, Node->tx_cnt);
        snprintf(text, sizeof(text), "%sErr:%u,", text, Node->rx_err_cnt);
        snprintf(text, sizeof(text), "%shComm:0x%p,", text, Node->hComm);
    }
    return text;
}

const char* SerialPortConfigToStr(const SerialPortConfig_t* const Config) {
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sCOM%u,", text, Config->com_port_num);
        snprintf(text, sizeof(text), "%sRate:%u Bit/s,", text, Config->bit_rate);
        snprintf(text, sizeof(text), "%sPause:%u ms,,", text, Config->byte_tx_pause_ms);
    }
    return text;
}

bool serial_port_scan(void) {
    bool res = false;
    const table_col_t cols[] = {
        {6, "COM"},
        {6, "Exist"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i = 0;
    for(i = 0; i < SERIAL_PORT_MAX_CNT; i++) {
        bool exist = serial_port_check(i);
        if(exist) {
            char temp[20] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s COM%u " TSEP, temp, i);
            snprintf(temp, sizeof(temp), "%s %4s " TSEP, temp, OnOffToStr(exist));
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

bool serial_port_diag(void) {
    bool res = false;
    const table_col_t cols[] = {
        {6, "COM"}, {8, "tx_cnt"}, {8, "rx_cnt"}, {6, "pause"}, {9, "baud"}, {8, "err"}, {8, "Name"}, {8, "Handle"},
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint32_t i = 0;
    for(i = 0; i < SERIAL_PORT_MAX_CNT; i++) {
        SerialPortHandle_t* Node = SerialPortNumToNode(i);
        if(Node) {
            char temp[200] = {0};
            strcpy(temp, TSEP);
            snprintf(temp, sizeof(temp), "%s COM%u " TSEP, temp, Node->com_port_num);
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, Node->tx_cnt);
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, Node->rx_cnt);
            snprintf(temp, sizeof(temp), "%s %4u " TSEP, temp, Node->byte_tx_pause_ms);

            snprintf(temp, sizeof(temp), "%s %7u " TSEP, temp, Node->bit_rate);
            snprintf(temp, sizeof(temp), "%s %6u " TSEP, temp, Node->rx_err_cnt);
            snprintf(temp, sizeof(temp), "%s %6s " TSEP, temp, Node->name);
            snprintf(temp, sizeof(temp), "%s 0x%p " TSEP, temp, Node->hComm);
            cli_printf("%s" CRLF, temp);
            res = true;
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    return res;
}

/*
https://learn.microsoft.com/en-us/windows/win32/debug/system-error-codes--0-499-
 */
const char* SerialPortErrorToStr(const uint32_t ret) {
    char* name = "?";
    switch(ret) {
    case ERROR_SEM_TIMEOUT:
        name = "ERROR_SEM_TIMEOUT";
        break;
    case ERROR_SUCCESS:
        name = "ERROR_SUCCESS";
        break;
    case ERROR_GEN_FAILURE:
        name = "ERROR_GEN_FAILURE";
        break;
    case ERROR_INVALID_HANDLE:
        name = "ERROR_INVALID_HANDLE";
        break;
    default:
        name = "?";
        break;
    }
    return name;
}
