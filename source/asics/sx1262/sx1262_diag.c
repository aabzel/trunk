#include "sx1262_diag.h"

#include <inttypes.h>
#include <stdio.h>

#include "bit_utils.h"
#include "cli_utils.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "str_utils.h"
#include "sx1262_drv.h"

const OpCode_t OpCodeMap[] = {
    {.name = "resetStats", .op_code = 0x00},
    {.name = "clearIrqStatus", .op_code = 0x02},
    {.name = "clearDevice_errors", .op_code = 0x07},
    {.name = "SetDioIrqParams", .op_code = 0x08},
    {.name = "writeRegister", .op_code = 0x0d},
    {.name = "writeBuffer", .op_code = 0x0e},
    {.name = "GetStats", .op_code = 0x10},
    {.name = "GetPacketType", .op_code = 0x11},
    {.name = "GetIrqStatus", .op_code = 0x12},
    {.name = "GetRxBufferStatus", .op_code = 0x13},
    {.name = "GetPacketStatus", .op_code = 0x14},
    {.name = "GetRssiinst", .op_code = 0x15},
    {.name = "GetDeviceErrors", .op_code = 0x17},
    {.name = "readRegister", .op_code = 0x1d},
    {.name = "readBuffer", .op_code = 0x1e},
    {.name = "SetStandby", .op_code = 0x80},
    {.name = "SetRx", .op_code = 0x82},
    {.name = "SetTx", .op_code = 0x83},
    {.name = "SetSleep", .op_code = 0x84},
    {.name = "SetRfFrequency", .op_code = 0x86},
    {.name = "SetCadParam", .op_code = 0x88},
    {.name = "calibrate", .op_code = 0x89},
    {.name = "SetPacketType", .op_code = 0x8a},
    {.name = "SetModulationParams", .op_code = 0x8b},
    {.name = "SetPacketParams", .op_code = 0x8c},
    {.name = "SetTxParams", .op_code = 0x8e},
    {.name = "SetBufferBaseAddr", .op_code = 0x8f},
    {.name = "SetFallback_mode", .op_code = 0x93},
    {.name = "SetRxDuty_cycle", .op_code = 0x94},
    {.name = "SetPaConfig", .op_code = 0x95},
    {.name = "SetRegulatorMode", .op_code = 0x96},
    {.name = "SetDio3As_tcxo_ctrl", .op_code = 0x97},
    {.name = "calibrateImage", .op_code = 0x98},
    {.name = "SetDio2_asRfswitch", .op_code = 0x9d},
    {.name = "stop_timer_onPreamble", .op_code = 0x9f},
    {.name = "Set_loraSymbol_timeout", .op_code = 0xa0},
    {.name = "GetStatus", .op_code = 0xc0},
    {.name = "SetFs", .op_code = 0xc1},
    {.name = "SetCad", .op_code = 0xc5},
    {.name = "SetTxCarrier", .op_code = 0xd1},
    {.name = "SetTxPreamble", .op_code = 0xd2},

};

char* OpCodeToStr(uint8_t op_code) {
    char* name = "?";
    uint16_t i = 0;
    for(i = 0; i < ARRAY_SIZE(OpCodeMap); i++) {
        if(op_code == OpCodeMap[i].op_code) {
            name = OpCodeMap[i].name;
            break;
        }
    }
    return name;
}

const char* StandbyToStr(StandbyMode_t standby_mode) {
    const char* name = "?";
    switch(standby_mode) {
    case STDBY_RC:
        name = "RC";
        break;
    case STDBY_XOSC:
        name = "XOSC";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

const char* cmd_stat2str(uint8_t cmd_stat) {
    const char* name = "undef";
    switch(cmd_stat) {
    case 0:
        name = "Rsvd";
        break;
    case 2:
        name = "DataAvailToHost";
        break;
    case 3:
        name = "timeout";
        break;
    case 4:
        name = "processingError";
        break;
    case 5:
        name = "FailureExecute";
        break;
    case 6:
        name = "TxDone";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}

const char* chip_mode2str(uint8_t chip_mode) {
    const char* name = "undef";
    switch(chip_mode) {
    case CHP_MODE_UNDEF:
        name = "unUsed";
        break;
    case CHP_MODE_STBY_RC:
        name = "STBY_RC";
        break;
    case CHP_MODE_STBY_XOSC:
        name = "STBY_XOSC";
        break;
    case CHP_MODE_FS:
        name = "FS";
        break;
    case CHP_MODE_RX:
        name = "RX";
        break;
    case CHP_MODE_TX:
        name = "TX";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}
// sx126x_convert_freq_in_hz_to_pll_step
bool parse_dev_stat(uint8_t dev_stat) {
    uint8_t code = 0;
    LOG_INFO(SX1262, "Status: 0x%02x 0b%s", dev_stat, utoa_bin8(dev_stat));
    code = extract_subval_from_8bit(dev_stat, 3, 1);
    LOG_INFO(SX1262, "CmdStat: [%u] %s", code, cmd_stat2str(code));

    code = extract_subval_from_8bit(dev_stat, 6, 4);
    LOG_INFO(SX1262, "ChipMode: [%u] %s", code, chip_mode2str(code));
    return true;
}

bool parse_op_error(uint16_t op_error) {
    bool res = false;
    LOG_INFO(SX1262, "op_error: 0x%04x 0b%s" CRLF, op_error, utoa_bin16(MASK_9BIT & op_error));
    if((1 << OP_ERR_BIT_RC64K_CALIB_ERR) == (op_error & (1 << OP_ERR_BIT_RC64K_CALIB_ERR))) {
        LOG_ERROR(LORA, "RC64k");
        res = true;
    }
    if((1 << OP_ERR_BIT_RC13M_CALIB_ERR) == (op_error & (1 << OP_ERR_BIT_RC13M_CALIB_ERR))) {
        LOG_ERROR(LORA, "RC13M");
        res = true;
    }
    if((1 << OP_ERR_BIT_PLL_CALIB_ERR) == (op_error & (1 << OP_ERR_BIT_PLL_CALIB_ERR))) {
        LOG_ERROR(LORA, "PLL");
        res = true;
    }
    if((1 << OP_ERR_BIT_ADC_CALIB_ERR) == (op_error & (1 << OP_ERR_BIT_ADC_CALIB_ERR))) {
        LOG_ERROR(LORA, "ADC calibration failed");
        res = true;
    }
    if((1 << OP_ERR_BIT_IMG_CALIB_ERR) == (op_error & (1 << OP_ERR_BIT_IMG_CALIB_ERR))) {
        LOG_ERROR(LORA, "IMG");
        res = true;
    }
    if((1 << OP_ERR_BIT_XOSC_START_ERR) == (op_error & (1 << OP_ERR_BIT_XOSC_START_ERR))) {
        LOG_ERROR(LORA, "XOSC");
        res = true;
    }
    if((1 << OP_ERR_BIT_PLL_LOCK_ERR) == (op_error & (1 << OP_ERR_BIT_PLL_LOCK_ERR))) {
        LOG_ERROR(LORA, "PLL lock");
        res = true;
    }
    if((1 << OP_ERR_BIT_PA_RAMP_ERR) == (op_error & (1 << OP_ERR_BIT_PA_RAMP_ERR))) {
        LOG_ERROR(LORA, "PA ramping");
        res = true;
    }
    return res;
}

const char* RxGainToStr(uint8_t rx_gain) {
    const char* name = "?";
    switch(rx_gain) {
    case RXGAIN_BOOSTED:
        name = "Boosted";
        break;
    case RXGAIN_POWER_SAVING:
        name = "PwrSave";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool parse_irq_stat(Sx1262IRQs_t irq_stat) {
    bool res = false;

    LOG_INFO(LORA, "irq_stat: 0x%04x 0b%s" CRLF, irq_stat.word, utoa_bin16(irq_stat.word));
    if(irq_stat.TxDone) {
        LOG_INFO(LORA, "0 TX done");
    }
    if(irq_stat.RxDone) {
        LOG_INFO(LORA, "1 RX done");
    }
    if(irq_stat.PreambleDetected) {
        LOG_INFO(LORA, "2 preambleDetected");
    }
    if(irq_stat.SyncWordValid) {
        LOG_INFO(LORA, "3 sync wordValid");
    }
    if(irq_stat.HeaderValid) {
        LOG_INFO(LORA, "4 LoRa headerReceived");
    }
    if(irq_stat.HeaderErr) {
        LOG_ERROR(LORA, "5 LoRa headerCRCError");
    }
    if(irq_stat.CrcErr) {
        LOG_INFO(LORA, "6 Wrong CRCreceived");
    }
    if(irq_stat.CadDone) {
        LOG_INFO(LORA, "7 ChannelActivityDetectionFinished");
    }
    if(irq_stat.CadDetected) {
        LOG_INFO(LORA, "8 ChannelActivityDetected");
    }
    if(irq_stat.Timeout) {
        LOG_WARNING(LORA, "9 RxOrTxTimeout");
    }

    return res;
}

bool print_int_diag(Sx1262IrqCnt_t* irq_cnt) {
    bool res = false;

    if(irq_cnt) {
        if(0 < irq_cnt->total) {
            LOG_INFO(SX1262, "total: %u", irq_cnt->total);
            res = true;
        }

        if(0 < irq_cnt->rx_done) {
            LOG_INFO(SX1262, "RxDone: %u", irq_cnt->rx_done);
            res = true;
        }
        if(0 < irq_cnt->tx_done) {
            LOG_DEBUG(SX1262, "TxDone: %u", irq_cnt->tx_done);
            res = true;
        }
        if(0 < irq_cnt->timeout) {
            LOG_DEBUG(SX1262, "TimeOut: %u", irq_cnt->timeout);
            res = true;
        }
        if(0 < irq_cnt->crc_err) {
            LOG_ERROR(SX1262, "CrcErr: %u", irq_cnt->crc_err);
            res = true;
        }
        if(0 < irq_cnt->preamble_detected) {
            LOG_INFO(SX1262, "PreambleDetected: %u", irq_cnt->preamble_detected);
            res = true;
        }
        if(0 < irq_cnt->header_valid) {
            LOG_INFO(SX1262, "header valid: %u", irq_cnt->header_valid);
            res = true;
        }
        if(0 < irq_cnt->cad_done) {
            LOG_INFO(SX1262, "CadDone: %u", irq_cnt->cad_done);
            res = true;
        }
        if(0 < irq_cnt->cad_detected) {
            LOG_DEBUG(SX1262, "CadDetected: %u", irq_cnt->cad_detected);
            res = true;
        }
        if(0 < irq_cnt->header_err) {
            LOG_ERROR(SX1262, "HeaderErr: %u", irq_cnt->header_err);
            res = true;
        }
        if(0 < irq_cnt->syncword_valid) {
            LOG_INFO(SX1262, "SyncWordValid: %u", irq_cnt->syncword_valid);
            res = true;
        }
        if(0 < irq_cnt->cad_done) {
            LOG_INFO(SX1262, "CadDone: %u ", irq_cnt->cad_done);
            res = true;
        }
    }
    return res;
}
#ifdef HAS_LORA
char* bandwidth2str(uint8_t bandwidth) {
    static char name[40] = "";
    uint32_t band_width = bandwidth2num((BandWidth_t)bandwidth);
    snprintf(name, sizeof(name), "%u Hz", (unsigned int)band_width);
    return name;
}
#endif

char* LinkDist2str(double meters) {
    static char name[30] = "";
    snprintf(name, sizeof(name), "%.1f Km", meters / 1000.0);
    return name;
}

char* dbm2wattsStr(int32_t dbm) {
    static char name[30] = "";
    float watts = dbm2watts(dbm);
    snprintf(name, sizeof(name), "%f W", watts);
    return name;
}

char* PreambleLenToStr(uint16_t pre_len) {
    static char name[30] = "";
    snprintf(name, sizeof(name), "%u Byte", pre_len);
    return name;
}

const char* IqSetUpToStr(uint8_t iq_setup) {
    const char* name = "undef";
    switch(iq_setup) {
    case IQ_SETUP_STANDARD:
        name = "Std";
        break;
    case IQ_SETUP_INVERTED:
        name = "Inv";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}

char* PayloadLenToStr(uint8_t size) {
    static char name[30] = "";
    snprintf(name, sizeof(name), "%u Byte", size);
    return name;
}
#ifdef HAS_LORA
const char* LowDataRateOptToStr(uint8_t packet_type) {
    const char* name = "?";
    switch(packet_type) {
    case LDRO_OFF:
        name = "Off";
        break;
    case LDRO_ON:
        name = "On";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}
#endif

const char* WireLessIfToStr(uint8_t packet_type) {
    const char* name = "?";
    switch(packet_type) {
    case PACKET_TYPE_GFSK:
        name = "GFSK";
        break;
    case PACKET_TYPE_LORA:
        name = "LoRa";
        break;
    case PACKET_TYPE_LR_FHSS:
        name = "RrFhss";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}
#ifdef HAS_LORA
const char* LoraHeaderTypeToStr(uint8_t header_type) {
    const char* name = "undef";
    switch(header_type) {
    case LORA_VAR_LEN_PACT:
        name = "VarLen";
        break;
    case LORA_FIX_LEN_PAC:
        name = "FixLen";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}
#endif
#ifdef HAS_LORA
const char* LoraCrcTypeToStr(uint8_t crc_type) {
    const char* name = "undef";
    switch(crc_type) {
    case LORA_CRC_OFF:
        name = "Off";
        break;
    case LORA_CRC_ON:
        name = "On";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}
#endif
#ifdef HAS_LORA
const char* coding_rate2str(uint8_t coding_rate) {
    const char* name = "?";
    switch(coding_rate) {
    case LORA_CR_4_5:
        name = "4/5";
        break;
    case LORA_CR_4_6:
        name = "4/6";
        break;
    case LORA_CR_4_7:
        name = "4/7";
        break;
    case LORA_CR_4_8:
        name = "4/8";
        break;
    default:
        name = "Er";
        break;
    }
    return name;
}
#endif
#ifdef HAS_LORA
uint32_t spreading_factor2num(SpreadingFactor_t spreading_factor) {
    uint32_t spreading_factors_num = ipow(2, spreading_factor);
    return spreading_factors_num;
}

const char* spreading_factor2str(uint8_t spreading_factor) {
    static char name[30] = "";
    uint32_t spread_factor = spreading_factor2num((SpreadingFactor_t)spreading_factor);
    snprintf(name, sizeof(name), "%u Chips/Symb", (unsigned int)spread_factor);
    return name;
}
#endif
