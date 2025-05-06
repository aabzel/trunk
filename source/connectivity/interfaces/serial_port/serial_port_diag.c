#include "serial_port_diag.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "serial_port.h"

bool serial_port_diag(uint8_t num) {
    bool res = false;
    return res;
}

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
        snprintf(text, sizeof(text), "%sRate:%u Bit/s", text, Config->bit_rate);
        snprintf(text, sizeof(text), "%sPause:%u ms,", text, Config->byte_tx_pause_ms);
    }
    return text;
}
