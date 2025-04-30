#include "i2c_custom_diag.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "artery_at32f4xx.h"
#include "debugger.h"
#include "i2c_custom_const.h"
#include "i2c_custom_drv.h"
#include "i2c_mcal.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

// 11.5 I2C registers

char* I2cMode2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case I2C_MODE_I2C:
        name = "I2C";
        break;
    case I2C_MODE_SMBUS:
        name = "SMBus";
        break;
    }
    return name;
}

char* I2cBusRole2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case I2C_BUS_ROLE_SLAVE:
        name = "Slave";
        break;
    case I2C_BUS_ROLE_MASTER:
        name = "Master";
        break;
    }
    return name;
}

char* I2cBusState2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case I2C_BUS_STATE_SPARE:
        name = "Spare";
        break;
    case I2C_BUS_STATE_BUSY:
        name = "Busy";
        break;
    }
    return name;
}

char* I2cDir2Str(uint8_t code) {
    char* name = "?";
    switch(code) {
    case I2C_DIR_RX:
        name = "Rx";
        break;
    case I2C_DIR_TX:
        name = "Tx";
        break;
    }
    return name;
}

const char* I2cErrToStr(i2c_status_type ret) {
    char* name = "?";
    switch((uint8_t)ret) {
    case I2C_OK:
        name = "Ok";
        break;
    case I2C_ERR_STEP_1:
        name = "Step1_BUSY";
        break;
    case I2C_ERR_STEP_2:
        name = "Step2TDIS";
        break;
    case I2C_ERR_STEP_3:
        name = "Step3";
        break;
    case I2C_ERR_STEP_4:
        name = "Step4_TDC"; // transmit data complete flag
        break;
    case I2C_ERR_STEP_5:
        name = "Step5";
        break;
    case I2C_ERR_STEP_6:
        name = "Step6";
        break;
    case I2C_ERR_STEP_7:
        name = "Step7";
        break;
    case I2C_ERR_STEP_8:
        name = "Step8";
        break;
    case I2C_ERR_STEP_9:
        name = "Step9";
        break;
    case I2C_ERR_STEP_10:
        name = "Step10";
        break;
    case I2C_ERR_STEP_11:
        name = "Step11";
        break;
    case I2C_ERR_STEP_12:
        name = "Step12";
        break;
    case I2C_ERR_TIMEOUT:
        name = "TIMEOUT";
        break;
#ifdef HAS_AT32F43X
    case I2C_ERR_TCRLD:
        name = "TCRLD";
        break;
    case I2C_ERR_TDC:
        name = "TDC";
        break;
#endif // HAS_AT32F43X
    case I2C_ERR_ACKFAIL:
        name = "ACKFAIL";
        break;
    case I2C_ERR_STOP:
        name = "STOP";
        break;
    case I2C_ERR_ADDR:
        name = "ADDR";
        break;
    case I2C_ERR_INTERRUPT:
        name = "INTERRUPT";
        break;
    }
    return name;
}

#ifdef HAS_AT32F43X
static const char* TxDirToStr(i2c_transfer_dir_type code) {
    const char* name = "?";
    switch(code) {
    case I2C_DIR_TRANSMIT:
        name = "Tx";
        break;
    case I2C_DIR_RECEIVE:
        name = "Rx";
        break;
    default:
        break;
    }
    return name;
}
#endif // HAS_AT32F43X

bool i2c_diag_custom(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},     {5, "I2C"},
#ifdef HAS_AT32F43X
        {8, "TxAddr"}, {5, "Dir"}, {7, "Match"},
#endif // HAS_AT32F43X
        {7, "Pec"},

    };
    uint16_t num = 1;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for(i = 0; i <= I2C_COUNT; i++) {
        I2cHandle_t* Node = I2cGetNode(i);
        if(Node) {
#ifdef HAS_AT32F43X
            uint16_t transfer_addr = i2c_transfer_addr_get(Node->I2Cx);
            i2c_transfer_dir_type tx_dir = i2c_transfer_dir_get(Node->I2Cx);
            uint8_t matched_addr = i2c_matched_addr_get(Node->I2Cx);
#endif // HAS_AT32F43X
            uint8_t pec_value = i2c_pec_value_get(Node->I2Cx);

            res = true;
            strcpy(temp_str, TSEP);

#if 0
                flag_status i2c_interrupt_get(Node->I2Cx, uint16_t source);
                flag_status i2c_flag_get(Node->I2Cx, uint32_t flag);
                flag_status i2c_interrupt_flag_get(Node->I2Cx, uint32_t flag);
#endif

#ifdef HAS_AT32F43X
            snprintf(temp_str, sizeof(temp_str), "%s  0x%04x " TSEP, temp_str, transfer_addr);
            snprintf(temp_str, sizeof(temp_str), "%s  %3s " TSEP, temp_str, TxDirToStr(tx_dir));
            snprintf(temp_str, sizeof(temp_str), "%s  0x%02x " TSEP, temp_str, matched_addr);
#endif // HAS_AT32F43X
            snprintf(temp_str, sizeof(temp_str), "%s  0x%02x " TSEP, temp_str, pec_value);

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);

            num++;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool i2c_raw_reg_diag(uint8_t num) {
    bool res = false;

    const I2cInfo_t* Info = I2cGetInfo(num);
    if(Info) {
        uint32_t reg_cnt = i2c_reg_cnt();
        res = debug_raw_reg_diag(I2C, (uint32_t)Info->I2Cx, I2cReg, reg_cnt);
    }

    return res;
}

const char* I2cClkCtrlToStr(const I2cClkCtrl_t* const Node) {
    static char text[150] = "";
    if(Node) {
        strcpy(text, "");
        ByteNimble_t Div;
        Div.byte = 0;
        Div.low = Node->divl;
        Div.high = Node->divh;
        // see page 175 Figure 11-3 Setup and hold time
        uint32_t clock_period = Node->sdad + Node->scld + Node->sclh + Node->scll;
        snprintf(text, sizeof(text), "%sDiv:%u,", text, Div.byte + 1);
        snprintf(text, sizeof(text), "%sPeriod:%u Tick,", text, clock_period);
        snprintf(text, sizeof(text), "%sSDAD:%u Tick,", text, Node->sdad); // SDA output delay
        snprintf(text, sizeof(text), "%sscld:%u Tick,", text, Node->scld); // SCL output delay
        snprintf(text, sizeof(text), "%ssclh:%u Tick,", text, Node->sclh); // SCL high level
        snprintf(text, sizeof(text), "%sscll:%u Tick", text, Node->scll);  // SCL low level
    }
    return text;
}

bool i2c_clkctrl_diag(double base_freq_hz, uint32_t qword) {
    bool res = false;
    I2cClkCtrl_t ClkCtrl;
    ClkCtrl.qword = qword;
    LOG_INFO(I2C, "APB1Freq:%f Hz,I2C_CLKCTRL:0x%08X=%s", base_freq_hz, ClkCtrl.qword, I2cClkCtrlToStr(&ClkCtrl));
    uint32_t clock_period = 0;
    Type8Union_t diviver = {
        .nibble_l = ClkCtrl.divl,
        .nibble_h = ClkCtrl.divh,
    };

    uint32_t real_divider = (uint32_t)(diviver.u8 + 1);
    double i2c_tick_freq_hz = base_freq_hz / ((double)real_divider);
    clock_period = ClkCtrl.sdad + ClkCtrl.scld + ClkCtrl.sclh + ClkCtrl.scll;
    double clock_period_s = ((double)(real_divider * clock_period)) * (1.0 / base_freq_hz);

    double freq_hz = 1.0 / clock_period_s;
    LOG_INFO(I2C, "Div:%u,I2cPHYclock:%f Hz,I2cPeriod:%u,Tick:%f s,I2cFreq:%f Hz", real_divider, i2c_tick_freq_hz,
             clock_period, clock_period_s, freq_hz);

    return res;
}
