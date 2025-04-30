#include "i2c_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "i2c_mcal.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "table_utils.h"
#include "writer_config.h"

const char* I2cConfigToStr(const I2cConfig_t* const Config) {
    static char text[80] = "";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sI2C%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sPri:%u,", text, Config->interrupt_priority);
        snprintf(text, sizeof(text), "%sClk:%u Hz,", text, Config->clock_speed);
        snprintf(text, sizeof(text), "%sINT:%u,", text, Config->interrupt_on);
        snprintf(text, sizeof(text), "%sSCL:%s,", text, GpioPadToStr(Config->PadScl));
        snprintf(text, sizeof(text), "%sSDA:%s,", text, GpioPadToStr(Config->PadSda));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

bool i2c_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},     {5, "I2C"},     {7, "done"},    {7, "ErrCnt"}, {7, "ErrBus"},
                                       {7, "ErrOvr"}, {7, "Errdata"}, {7, "ErrNack"}, {7, "TxCnt"},  {7, "RxCnt"},
                                       {7, "ItCnt"},  {6, "NACK"},    {17, "name"}};
    uint16_t num = 1;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for(i = 0; i <= I2C_COUNT; i++) {
        I2cHandle_t* Node = I2cGetNode(i);
        if(Node) {
            const I2cConfig_t* Config = I2cGetConfig(i);
            if(Config) {
                res = true;
                strcpy(temp_str, TSEP);
                snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, (unsigned int)i);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->done_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->error_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->error_bus_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->error_overrun_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->error_data_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->error_nack_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->tx_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->rx_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %5u " TSEP, temp_str, (unsigned int)Node->it_cnt);
                snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->ack_fail);
                snprintf(temp_str, sizeof(temp_str), "%s  %15s  " TSEP, temp_str, Config->name);
                cli_printf(TSEP " %3u ", num);
                cli_printf("%s" CRLF, temp_str);
            }
            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_scan_diag(uint8_t num) {
    bool res = false;
    LOG_INFO(I2C, "InterfaceNum %u", num);
    static const table_col_t cols[] = {
        {4, "--"}, {4, "x0"}, {4, "x1"}, {4, "x2"}, {4, "x3"}, {4, "x4"}, {4, "x5"}, {4, "x6"}, {4, "x7"},
        {4, "x8"}, {4, "x9"}, {4, "xA"}, {4, "xB"}, {4, "xC"}, {4, "xD"}, {4, "xE"}, {4, "xF"},
    };
    Type8Union_t un8;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t l = 0, h = 0;
    bool lres = false;
    for(h = 0; h <= 0xF; h++) {
        un8.nibble_h = h;
        cli_printf(TSEP);
        cli_printf(" %xx " TSEP, h);
        for(l = 0; l <= 0xF; l++) {
            un8.nibble_h = h;
            un8.nibble_l = l;
            lres = i2c_check_addr(num, un8.u8);
            if(lres) {
                cli_printf(" %02x " TSEP, un8.u8);
                res = true;
            } else {
                cli_printf(" -- " TSEP);
            }
#ifdef HAS_TIME
            wait_in_loop_ms(10);
#endif
        }
        cli_printf(CRLF);
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2s_diag_one(uint8_t num) {
    bool res = false;
    return res;
}
