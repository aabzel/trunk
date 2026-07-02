#include "i2s_custom_diag.h"

#include "stm32fx_hal.h"
#include "i2s_mcal.h"
#include "i2s_custom_drv.h"
#include "i2s_custom_types.h"

#ifndef HAL_I2S_MODULE_ENABLED
#error "Add HAL_I2S_MODULE_ENABLED"
#endif

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif


const char* HalI2sStateToStr(HAL_I2S_StateTypeDef state){
    const char* name="?";
    switch(state){
        case HAL_I2S_STATE_RESET:     name="Reset"; break;
        case HAL_I2S_STATE_READY:     name="Ready"; break;
        case HAL_I2S_STATE_BUSY:      name="Busy"; break;
        case HAL_I2S_STATE_BUSY_TX:   name="BusyTx"; break;
        case HAL_I2S_STATE_BUSY_RX:   name="BusyRx"; break;
        case HAL_I2S_STATE_BUSY_TX_RX:name="BusyTxRx"; break;
        case HAL_I2S_STATE_TIMEOUT:   name="TimeOut"; break;
        case HAL_I2S_STATE_ERROR:     name="Error";break;
        default : name="??"; break;
    }
    return name;
}
#if 0

const char* I2sStdToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_STD_I2S_PHILIPS:   name="I2S"; break;
        case I2S_STD_MSB_JUSTIFIED: name="MSB"; break;
        case I2S_STD_LSB_JUSTIFIED: name="LSB"; break;
        case I2S_STD_PCM:   name="PCM"; break;

        default : name="??"; break;
    }
    return name;
}


const char* I2sBitToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_DAT_LEN16_BIT:     name="16"; break;
        case I2S_DAT_LEN24_BIT:     name="24"; break;
        case I2S_DAT_LEN32_BIT:      name="32"; break;
        case I2S_DAT_NOT_ALLOWED:   name="?"; break;

        default : name="??"; break;
    }
    return name;
}

const char* I2sOddToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case 0:     name="I2SDIV*2"; break;
        case 1:     name="(I2SDIV*2)+1"; break;

        default : name="??"; break;
    }
    return name;
}


const char* I2sChlenToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_CHLEN_16:   name="16"; break;
        case I2S_CHLEN_32:    name="32"; break;

        default : name="??"; break;
    }
    return name;
}

const char* SerialModeToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_MODE_SPI:   name="SPI"; break;
        case I2S_MODE_I2S:    name="I2S"; break;
        default : name="??"; break;
    }
    return name;
}

#endif

const char* I2sRoleToStr(uint8_t code){
    const char* name="?";
    switch(code){
        case I2S_ROLE_SLAVE_TRANSMIT:   name="SlaveTx"; break;
        case I2S_ROLE_SLAVE_RECEIVE:    name="SlaveRx"; break;
        case I2S_ROLE_MASTER_TRANSMIT:  name="MasterTx"; break;
        case I2S_ROLE_MASTER_RECEIVE:   name="MasterRx"; break;

        default : name="??"; break;
    }
    return name;
}


bool i2s_custom_diag_low_level(void) {
    bool res = false;
    static const table_col_t cols[] = {{5, "No"},  {12, "Base"}, {5, "mode"}, {5, "i2s"},    {4, "bit"}, {10, "Role"},
                                       {5, "Std"}, {6, "chlen"}, {5, "Psr"},  {6, "ClkOut"}, {12, "Odd"}};
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    char temp_str[120];
    char suffix[50];
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        SPI_TypeDef* I2sBaseAddr = I2sGetBaseAddr(i2s_num);
        strcpy(temp_str, TSEP);
        RegI2sConfig_t Reg;
        RegI2sPsc_t RegPscPre;
        if(I2sBaseAddr) {
            Reg.reg_val = I2sBaseAddr->I2SCFGR;
            RegPscPre.reg_val = I2sBaseAddr->I2SPR;
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, i2s_num);

            snprintf(suffix, sizeof(suffix), " 0x%08x " TSEP, (unsigned int)I2sBaseAddr);
            strcat(temp_str, suffix);

            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, SerialModeToStr(Reg.i2smod));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(Reg.i2se));
            snprintf(temp_str, sizeof(temp_str), "%s %2s " TSEP, temp_str, I2sBitToStr(Reg.datlen));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, I2sRoleToStr(Reg.i2scfg));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2sStdToStr(Reg.i2sstd));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, I2sChlenToStr(Reg.chlen));
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, RegPscPre.i2sdiv);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(RegPscPre.mckoe));
            snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, I2sOddToStr(RegPscPre.odd));
        }
        cli_printf("%s" CRLF, temp_str);
        num++;
        res = true;
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}


bool i2s_custom_diag(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},        {5, "num"},       {6, "echo"},  {6, "loop"},  {6, "iir"},    {6, "Err"},
        {9, "rxHalfCnt"}, {9, "txHalfCnt"}, {9, "rxCnt"}, {9, "txCnt"}, {10, "state"}, {8, "name"},
    };
    uint16_t num = 0;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    HAL_I2S_StateTypeDef state;
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        I2sHandle_t* Node = I2sGetNode(i2s_num);
        //#define __HAL_I2S_GET_IT_SOURCE(__HANDLE__, __INTERRUPT__)
        // __HAL_I2S_GET_FLAG(__HANDLE__, __FLAG__)
        // TODO: get bittness
        if(Node) {
            char temp_str[120]={0};
            strcpy(temp_str, TSEP);
            state = HAL_I2S_GetState(&Node->handle);
            snprintf(temp_str, sizeof(temp_str), "%s %1u   " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOffToStr(Node->echo));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOffToStr(Node->loopback));
            snprintf(temp_str, sizeof(temp_str), "%s %3s  " TSEP, temp_str, OnOffToStr(Node->iir));
            snprintf(temp_str, sizeof(temp_str), "%s %4u " TSEP, temp_str, (unsigned int)Node->error_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32valToStr(Node->rx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32valToStr(Node->tx_half_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32valToStr(Node->rx_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %7s " TSEP, temp_str, u32valToStr(Node->tx_cnt));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, HalI2sStateToStr(state));
            I2sConfig_t* I2sConfNode = I2sGetConfig(i2s_num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}



bool i2s_custom_diag_sample(void) {
    bool res = false;
    static const table_col_t cols0[] = {
        {9, ""},
        {35, "left"},
        {35, "right"},
        {8, ""},
    };

    static const table_col_t cols[] = {
        {5, "No"}, {3, "#"},  {8, "Rx"},    {8, "Tx"},    {8, "RxFix"}, {8, "TxFix"},
        {8, "Rx"}, {8, "Tx"}, {8, "RxFix"}, {8, "TxFix"}, {8, "name"},
    };
    uint16_t num = 0;
    table_cap(&(curWriterPtr->stream), cols0, ARRAY_SIZE(cols0));
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    // HAL_I2S_StateTypeDef state;
    char temp_str[120];
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        I2sHandle_t* Node = I2sGetNode(i2s_num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %u " TSEP, temp_str, Node->num);
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample_fixed.u32[0]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample_fixed.u32[0]));

            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->rx_sample_fixed.u32[1]));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str,
                     (unsigned int)(Node->tx_sample_fixed.u32[1]));
            I2sConfig_t* I2sConfNode = I2sGetConfig(i2s_num);
            if(I2sConfNode) {
                snprintf(temp_str, sizeof(temp_str), "%s %6s " TSEP, temp_str, I2sConfNode->name);
            }

            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
            res = true;
        }
    }

    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
