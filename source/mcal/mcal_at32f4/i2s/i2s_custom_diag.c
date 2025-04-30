#include "i2s_custom_diag.h"

#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "i2s_custom_drv.h"
#include "i2s_mcal.h"
#include "i2s_register_types.h"
#include "log.h"
#include "num_to_str.h"
#include "spi_custom_diag.h"
#include "table_utils.h"
#include "writer_config.h"

bool i2s_diag_custom(void) {
    bool res = false;
    static const table_col_t cols[] = {
        {5, "No"},
        {5, "I2C"},

    };
    uint16_t num = 1;
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    uint8_t i = 0;
    char temp_str[120];
    for(i = 0; i <= I2C_COUNT; i++) {
        I2sHandle_t* Node = I2sGetNode(i);
        if(Node) {
            res = true;
            strcpy(temp_str, TSEP);
            cli_printf(TSEP " %3u ", num);
            cli_printf("%s" CRLF, temp_str);
            num++;
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
        res = debug_raw_reg_diag(I2S, (uint32_t)Info->I2Sx, I2sReg, reg_cnt);
    }
    return res;
}

static const char* I2s_I2SMSEL_ToStr(SpiI2sMode_t i2smsel) {
    const char* name = "?";
    switch((uint32_t)i2smsel) {
    case I2SMSEL_SPI:
        name = "SPI";
        break;
    case I2SMSEL_I2S:
        name = "I2S";
        break;
    }
    return name;
}

static const char* I2s_STDSEL_ToStr(I2sStandart_t stdsel) {
    const char* name = "?";
    switch((uint32_t)stdsel) {
    case STDSEL_PHILIPS:
        name = "PHILIPS";
        break;
    case STDSEL_LEFT_ALIGNE:
        name = "LeftAligne";
        break;
    case STDSEL_RIGHT_ALIGNED:
        name = "Right_Aligned";
        break;
    case STDSEL_PCM:
        name = "PCM";
        break;
    }
    return name;
}

static const char* I2s_I2SCLKPOL_ToStr(I2sClockPolatity_t i2s_clk_pol) {
    const char* name = "?";
    switch((uint32_t)i2s_clk_pol) {
    case I2SCLKPOL_LOW:
        name = "ClkPolLow";
        break;
    case I2SCLKPOL_HIGH:
        name = "ClkPolHi";
        break;
    }
    return name;
}

static const char* I2s_I2SODD_ToStr(I2sOddFactor_t I2SODD) {
    const char* name = "?";
    switch((uint32_t)I2SODD) {
    case I2SODD_EVEN:
        name = "I2SDIV*2";
        break;
    case I2SODD_ODD:
        name = "(I2SDIV*2)+1";
        break;
    }
    return name;
}

static const char* I2s_I2SMCLKOE_ToStr(I2sMasterClockOut_t I2SMCLKOE) {
    const char* name = "?";
    switch((uint32_t)I2SMCLKOE) {
    case I2SMCLKOE_OFF:
        name = "McklOff";
        break;
    case I2SMCLKOE_ON:
        name = "McklOn";
        break;
    }
    return name;
}

static const char* I2s_ACS_ToStr(I2sAudioChannel_t ACS) {
    const char* name = "?";
    switch((uint32_t)ACS) {
    case ACS_CHANNEL_LEFT:
        name = "ChLeft";
        break;
    case ACS_CHANNEL_RIGHT:
        name = "ChRight";
        break;
    }
    return name;
}

static const char* I2s_I2SCBN_ToStr(I2sChannelBitNum_t i2scbn) {
    const char* name = "?";
    switch((uint32_t)i2scbn) {
    case I2SCBN_16BIT_WIDE:
        name = "16-bit wide";
        break;
    case I2SCBN_32BIT_WIDE:
        name = "32-bit wide";
        break;
    }
    return name;
}

static const char* I2s_I2SDBN_ToStr(I2sBitLen_t I2SDBN) {
    const char* name = "?";
    switch((uint32_t)I2SDBN) {
    case I2SDBN_16BIT:
        name = "16bit";
        break;
    case I2SDBN_24BIT:
        name = "24bit";
        break;
    case I2SDBN_32BIT:
        name = "32bit";
        break;
    }
    return name;
}

static const char* I2s_I2SEN_ToStr(I2sEnable_t i2sen) {
    const char* name = "?";
    switch((uint32_t)i2sen) {
    case I2SEN_OFF:
        name = "Off";
        break;
    case I2SEN_ON:
        name = "On";
        break;
    }
    return name;
}

static const char* I2s_OPERSEL_ToStr(I2sOperation_t OPERSEL) {
    const char* name = "?";
    switch((uint32_t)OPERSEL) {
    case OPERSEL_SLAVE_TX:
        name = "SlaveTx";
        break;
    case OPERSEL_SLAVE_RX:
        name = "SlaveRx";
        break;
    case OPERSEL_MASTER_TX:
        name = "MasterTx";
        break;
    case OPERSEL_MASTER_RX:
        name = "MasterRx";
        break;
    }
    return name;
}

static bool I2sDiagRegCtrl2(SpiCtrl2_t* const Reg, char* keyword) {
    bool res = false;
    char text[150] = {0};
    snprintf(text, sizeof(text), "SPI_CTRL2,Value:0x%x=%s", Reg->qword, utoa_bin32(Reg->qword));
    log_print_conditional(LOG_LEVEL_WARNING, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "DMAREN:%u", Reg->DMAREN);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "DMATEN:%u", Reg->DMATEN);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "HWCSOE:%u", Reg->HWCSOE);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "TIEN:%u", Reg->TIEN);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "ERRIE:%u", Reg->ERRIE);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "RDBFIE:%u", Reg->RDBFIE);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "TDBEIE:%u", Reg->TDBEIE);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "MDIV:%u", Reg->MDIV);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "MDIV3EN:%u", Reg->MDIV3EN);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    res = true;
    return res;
}

static bool I2sDiagRegSts(SpiStatus_t* const Reg, char* keyword) {
    bool res = false;
    char text[150] = {0};
    snprintf(text, sizeof(text), "SPI_STS,Value:0x%x=%s", Reg->qword, utoa_bin32(Reg->qword));
    log_print_conditional(LOG_LEVEL_WARNING, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "RDBF:%u", Reg->RDBF);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "TDBE:%u", Reg->TDBE);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "ACS:%u=%s", Reg->ACS, I2s_ACS_ToStr(Reg->ACS));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "TUERR:%u", Reg->TUERR);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "CCERR:%u", Reg->CCERR);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "MMERR:%u", Reg->MMERR);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "ROERR:%u", Reg->ROERR);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "BF:%u", Reg->BF);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "CSPAS:%u", Reg->CSPAS);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);
    res = true;

    return res;
}

static bool I2sDiagRegI2sCtrl(SpiI2sCtrl_t* const Reg, char* keyword) {
    bool res = false;
    char text[150] = {0};
    snprintf(text, sizeof(text), "SPI_I2SCTRL,Value:0x%x=%s", Reg->qword, utoa_bin32(Reg->qword));
    log_print_conditional(LOG_LEVEL_WARNING, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SCBN:%u=%s", Reg->I2SCBN, I2s_I2SCBN_ToStr(Reg->I2SCBN));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SDBN:%u=%s", Reg->I2SDBN, I2s_I2SDBN_ToStr(Reg->I2SDBN));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SCLKPOL:%u=%s", Reg->I2SCLKPOL, I2s_I2SCLKPOL_ToStr(Reg->I2SCLKPOL));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "STDSEL:%u=%s", Reg->STDSEL, I2s_STDSEL_ToStr(Reg->STDSEL));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "PCMFSSEL:%u", Reg->PCMFSSEL);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "OPERSEL:%u=%s", Reg->OPERSEL, I2s_OPERSEL_ToStr(Reg->OPERSEL));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SEN:%u=%s", Reg->I2SEN, I2s_I2SEN_ToStr(Reg->I2SEN));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SMSEL:%u=%s", Reg->I2SMSEL, I2s_I2SMSEL_ToStr(Reg->I2SMSEL));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);
    res = true;
    return res;
}

static bool I2sDiagRegI2sClkP(SpiI2sClkPrescaler_t* const Reg, char* keyword) {
    bool res = false;
    char text[150] = {0};
    snprintf(text, sizeof(text), "SPI_I2SCLKP,Value:0x%x=%s", Reg->qword, utoa_bin32(Reg->qword));
    log_print_conditional(LOG_LEVEL_WARNING, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SDIV1:%u", Reg->I2SDIV1);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SODD:%u=%s", Reg->I2SODD, I2s_I2SODD_ToStr(Reg->I2SODD));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SMCLKOE:%u=%s", Reg->I2SMCLKOE, I2s_I2SMCLKOE_ToStr(Reg->I2SMCLKOE));
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);

    snprintf(text, sizeof(text), "I2SDIV2:%u", Reg->I2SDIV2);
    log_print_conditional(LOG_LEVEL_INFO, I2S, text, keyword, NULL);
    res = true;
    return res;
}

bool i2s_diag_low_level(uint8_t num, char* keyword) {
    bool res = false;
    const I2sInfo_t* Info = I2sGetInfo(num);
    if(Info) {
        log_level_time_stamp(false);
        LOG_INFO(I2S, "I2S%u,Base:0x%p,key:[%s]", num, Info->I2Sx, keyword);
        res = SpiDiagRegCtrl1((SpiRegCtrl1_t*)&Info->I2Sx->ctrl1, keyword);
        res = I2sDiagRegCtrl2((SpiCtrl2_t*)&Info->I2Sx->ctrl2, keyword);
        res = I2sDiagRegSts((SpiStatus_t*)&Info->I2Sx->sts, keyword);
        res = I2sDiagRegI2sCtrl((SpiI2sCtrl_t*)&Info->I2Sx->i2sctrl, keyword);
        res = I2sDiagRegI2sClkP((SpiI2sClkPrescaler_t*)&Info->I2Sx->i2sclk, keyword);
        log_level_time_stamp(true);
    }
    return res;
}
