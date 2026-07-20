#include "i2s_custom_diag.h"

#include "stm32fx_hal.h"
#include "i2s_mcal.h"
#include "i2s_custom_drv.h"
#include "i2s_custom_types.h"
#include "debugger.h"
#include "num_to_str.h"

#ifndef HAL_I2S_MODULE_ENABLED
#error "Add HAL_I2S_MODULE_ENABLED"
#endif

#ifndef HAS_I2S
#error "Add HAS_I2S"
#endif

const Reg32_t I2sRegs[] = {
    {.num = 1, .name = "SPI_CR2",     .offset = 0x4,  .size = 1, .access = ACCESS_READ_WRITE, .valid = true,},
    {.num = 2, .name = "SPI_SR",      .offset = 0x8,  .size = 2, .access = ACCESS_READ_ONLY,  .valid = true,},
    {.num = 3, .name = "SPI_DR",      .offset = 0xC,  .size = 2, .access = ACCESS_READ_WRITE, .valid = true,},
    {.num = 4, .name = "SPI_I2SCFGR", .offset = 0x1C, .size = 2, .access = ACCESS_READ_WRITE, .valid = true,},
    {.num = 5, .name = "SPI_I2SPR",   .offset = 0x20, .size = 2, .access = ACCESS_READ_WRITE, .valid = true,},
};


uint32_t i2s_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(I2sRegs);
    return cnt;
}

uint8_t I2s_DATLEN_ToNum(const Stm32I2sDatLen_t dat_len) {
    uint8_t sample_bittness = 0;
    switch(dat_len) {
        case I2S_DAT_LEN16_BIT:         sample_bittness = 16;        break;
        case I2S_DAT_LEN24_BIT:         sample_bittness = 24;        break;
        case I2S_DAT_LEN32_BIT:         sample_bittness = 32;        break;
        default : sample_bittness=0; break;
    }
    return  sample_bittness;
}

const char* I2s_I2SMOD_ToStr(Stm32I2sMode_t i2smsel) {
    const char* name = "?";
    switch(i2smsel) {
        case I2S_MODE_SPI:        name = "SPI";        break;
        case I2S_MODE_I2S:        name = "I2S";        break;
        default : name="??"; break;
    }
    return name;
}



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


const char* I2s_I2SSTD_ToStr(Stm32I2sStd_t standart) {
    const char* name = "?";
    switch(standart) {
        case I2S_STD_I2S_PHILIPS:           name = "I2S";       break;
        case I2S_STD_MSB_JUSTIFIED:         name = "MSB";       break;
        case I2S_STD_LSB_JUSTIFIED:         name = "LSB";       break;
        case I2S_STD_PCM:                   name = "PCM";        break;
        default : name="??"; break;
    }
    return name;
}

const char* I2s_PCMSYNC_ToStr(I2sPcmFrameSynchronization_t pcm_frame_sync) {
    const char* name = "?";
    switch(pcm_frame_sync) {
        case I2S_PCM_FRAME_SYNC_SHORT:       name = "Short";       break;
        case I2S_PCM_FRAME_SYNC_LONG:        name = "Long";       break;
        default : name="??"; break;
    }
    return name;
}


const char* I2s_I2SE_ToStr(I2sEnable_t enable) {
    const char* name = "?";
    switch(enable) {
        case I2S_PERIPHERAL_IS_DISABLED:         name = "disabled";       break;
        case I2S_PERIPHERAL_IS_ENABLED:        name = "enabled";        break;
        default : name="??"; break;
    }
    return name;
}



const char* I2s_I2SCLKPOL_ToStr(I2sClockPolatity_t i2s_clk_pol) {
    const char* name = "?";
    switch(i2s_clk_pol) {
        case I2S_CLKPOL_LOW:         name = "ClkPolLow";       break;
        case I2S_CLKPOL_HIGH:        name = "ClkPolHi";        break;
        default : name="??"; break;
    }
    return name;
}

const char* I2s_I2SCFG_ToStr(Stm32I2sCnfgMode_t cfg_mode){
    const char* name = "?";
    switch(cfg_mode) {
        case I2S_ROLE_SLAVE_TRANSMIT:         name = "SLAVE_TX";       break;
        case I2S_ROLE_SLAVE_RECEIVE:         name = "SLAVE_RX";       break;
        case I2S_ROLE_MASTER_TRANSMIT:         name = "MASTER_TX";       break;
        case I2S_ROLE_MASTER_RECEIVE:        name = "MASTER_RX";        break;
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
    uint16_t num = 0;
    static const table_col_t cols[] = {{5, "No"},  {12, "Base"}, {5, "mode"}, {5, "i2s"},    {4, "bit"}, {10, "Role"},
                                       {5, "Std"}, {6, "chlen"}, {5, "Psr"},  {6, "ClkOut"}, {12, "Odd"}};
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i2s_num = 0;
    for(i2s_num = 1; i2s_num <= I2S_COUNT; i2s_num++) {
        SPI_TypeDef* I2sBaseAddr = I2sGetBaseAddr(i2s_num);
        char temp_str[120]={0};
        if(I2sBaseAddr) {
            char suffix[50]={0};
            I2sReg_SPI_I2SPR_t RegPscPre;
            I2sReg_SPI_I2SCFGR_t SPI_I2SCFGR;
            SPI_I2SCFGR.dword = I2sBaseAddr->I2SCFGR;
            RegPscPre.dword = I2sBaseAddr->I2SPR;
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, i2s_num);

            strcpy(temp_str, TSEP);
            snprintf(suffix, sizeof(suffix), " 0x%08x " TSEP, (unsigned int)I2sBaseAddr);
            strcat(temp_str, suffix);

            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, SerialModeToStr(SPI_I2SCFGR.I2SMOD));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(SPI_I2SCFGR.I2SE));
            snprintf(temp_str, sizeof(temp_str), "%s %2s " TSEP, temp_str, I2sBitToStr(SPI_I2SCFGR.DATLEN));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, I2sRoleToStr(SPI_I2SCFGR.I2SCFG));
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, I2sStdToStr(SPI_I2SCFGR.I2SSTD));
            snprintf(temp_str, sizeof(temp_str), "%s %4s " TSEP, temp_str, I2sChlenToStr(SPI_I2SCFGR.CHLEN));
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, RegPscPre.I2SDIV);
            snprintf(temp_str, sizeof(temp_str), "%s %3s " TSEP, temp_str, OnOffToStr(RegPscPre.MCKOE));
            snprintf(temp_str, sizeof(temp_str), "%s %10s " TSEP, temp_str, I2sOddToStr(RegPscPre.ODD));
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
            state = HAL_I2S_GetState(Node->pHandle);
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


bool i2s_raw_reg_diag(uint8_t num) {
    bool res = false;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info) {
        LOG_INFO(I2S, "I2S%u,Base:0x%p", num, Info->I2Sx);
        uint32_t reg_cnt = i2s_reg_cnt();
        res = debug_raw_reg_diag(I2S, (uint32_t)Info->I2Sx, I2sRegs, reg_cnt);
    }

    return res;
}

bool I2sDiagReg_CR2(const uint32_t reg_val) {
    bool res = false;
    I2sReg_SPI_CR2_t Reg;
    Reg.dword =reg_val;
    LOG_WARNING(I2S, "CR2:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(I2S, "RXDMAEN:%u", Reg.RXDMAEN);
    LOG_INFO(I2S, "TXDMAEN:%u", Reg.TXDMAEN);
    LOG_INFO(I2S, "ERRIE:%u", Reg.ERRIE);
    LOG_INFO(I2S, "RXNEIE:%u", Reg.RXNEIE);
    LOG_INFO(I2S, "TXEIE:%u", Reg.TXEIE);

    res = true;
    return res;
}



bool I2sDiagReg_SR(const uint32_t reg_val) {
    bool res = false;
    I2sReg_SPI_SR_t Reg;
    Reg.dword =reg_val;
    LOG_WARNING(I2S, "SPI_SR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(I2S, "RXNE:%u", Reg.RXNE);
    LOG_INFO(I2S, "TXE:%u", Reg.TXE);
    LOG_INFO(I2S, "CHSIDE:%u", Reg.CHSIDE);
    LOG_INFO(I2S, "UDR:%u", Reg.UDR);
    LOG_INFO(I2S, "OVR:%u", Reg.OVR);
    LOG_INFO(I2S, "BSY:%u", Reg.BSY);
    LOG_INFO(I2S, "FRE:%u", Reg.FRE);

    res = true;
    return res;
}


bool I2sDiagReg_DR(const uint32_t reg_val) {
    bool res = false;
    I2sReg_SPI_DR_t Reg;
    Reg.dword = reg_val;
    LOG_WARNING(I2S, "SPI_DR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(I2S, "DR:%u=0x%x", Reg.DR, Reg.DR);

    res = true;
    return res;
}
bool I2sDiagReg_I2SCFGR(const uint32_t reg_val) {
    bool res = false;
    I2sReg_SPI_I2SCFGR_t Reg;
    Reg.dword = reg_val;
    LOG_WARNING(I2S, "SPI_DR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(I2S, "CHLEN:%u", Reg.CHLEN);
    LOG_INFO(I2S, "DATLEN:%u=%u Bit", Reg.DATLEN, I2s_DATLEN_ToNum(    Reg.DATLEN));
    LOG_INFO(I2S, "CKPOL:%u=%s", Reg.CKPOL,I2s_I2SCLKPOL_ToStr(Reg.CKPOL));
    LOG_INFO(I2S, "I2SSTD:%u=%s", Reg.I2SSTD,I2s_I2SSTD_ToStr(Reg.I2SSTD));
    LOG_INFO(I2S, "PCMSYNC:%u=%s", Reg.PCMSYNC,I2s_PCMSYNC_ToStr(Reg.PCMSYNC));
    LOG_INFO(I2S, "I2SCFG:%u=%s", Reg.I2SCFG,I2s_I2SCFG_ToStr(Reg.I2SCFG));
    LOG_INFO(I2S, "I2SE:%u=%s", Reg.I2SE,I2s_I2SE_ToStr(Reg.I2SE));
    LOG_INFO(I2S, "I2SMOD:%u=%s", Reg.I2SMOD, I2s_I2SMOD_ToStr(Reg.I2SMOD));
    res = true;
    return res;
}

bool I2sDiagReg_I2SPR(const uint32_t reg_val) {
    bool res = false;
    I2sReg_SPI_I2SPR_t Reg;
    Reg.dword = reg_val;
    LOG_WARNING(I2S, "I2SPR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(I2S, "I2SDIV:%u", Reg.I2SDIV);
    LOG_INFO(I2S, "ODD:%u", Reg.ODD);
    LOG_INFO(I2S, "MCKOE:%u", Reg.MCKOE);
    res = true;
    return res;
}


bool i2s_diag_low_level(const uint8_t num) {
    bool res = false;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info) {
        LOG_INFO(I2S, "I2S%u,Base:0x%p", num, Info->I2Sx);
        I2sDiagReg_CR2(Info->I2Sx->CR2);
        I2sDiagReg_SR(Info->I2Sx->SR);
        I2sDiagReg_DR(Info->I2Sx->DR);
        I2sDiagReg_I2SCFGR(Info->I2Sx->I2SCFGR);
        I2sDiagReg_I2SPR(Info->I2Sx->I2SPR);
        res = true;
    }

    return res;
}
