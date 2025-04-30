#include "spi_custom_diag.h"

#include <stdio.h>
#include <string.h>

#include "debugger.h"
#include "log.h"
#include "mcal_types.h"
#include "num_to_str.h"
#include "spi_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

static const char* SPI_CLKPHA_ToStr(SpiAtClockPhase_t CLKPHA) {
    const char* name = "?";
    switch((uint32_t)CLKPHA) {
    case SPI_AT32_CLOCK_PHASE_1ST:
        name = "1st";
        break;
    case SPI_AT32_CLOCK_PHASE_2ND:
        name = "2nd";
        break;
    }
    return name;
}

static const char* SPI_CLKPOL_ToStr(SpiAtClockPolarity_t CLKPO) {
    const char* name = "?";
    switch((uint32_t)CLKPO) {
    case SPI_AT32_CLOCK_POLARITY_LOW:
        name = "Low";
        break;
    case SPI_AT32_CLOCK_POLARITY_HIGH:
        name = "High";
        break;
    }
    return name;
}

static const char* SPI_MSTEN_ToStr(SpiAtBusRole_t MSTEN) {
    const char* name = "?";
    switch((uint32_t)MSTEN) {
    case SPI_AT32_BUS_ROLE_SLAVE:
        name = "Slave";
        break;
    case SPI_AT32_BUS_ROLE_MASTER:
        name = "Master";
        break;
    }
    return name;
}

static const char* SPI_SLBEN_ToStr(SpiAtSingleLineBiDir_t SLBEN) {
    const char* name = "?";
    switch((uint32_t)SLBEN) {
    case SPI_AT32_SINGLE_LINE_BI_DIR_OFF:
        name = "Dual line";
        break;
    case SPI_AT32_SINGLE_LINE_BI_DIR_ON:
        name = "Single line";
        break;
    }
    return name;
}

static const char* SPI_SLBTD_ToStr(SpiAtHalfDuplexMode_t SLBTD) {
    const char* name = "?";
    switch((uint32_t)SLBTD) {
    case SPI_AT32_HALF_DUPLEX_RX_ONLY:
        name = "RxOnly";
        break;
    case SPI_AT32_HALF_DUPLEX_TX_ONLY:
        name = "TxOnly";
        break;
    }
    return name;
}

static const char* SPI_LTF_ToStr(SpiAtFirstBit_t LTF) {
    const char* name = "?";
    switch((uint32_t)LTF) {
    case SPI_AT32_FIRST_BIT_MSB:
        name = "MSB";
        break;
    case SPI_AT32_FIRST_BIT_LSB:
        name = "LSB";
        break;
    }
    return name;
}

static const char* SPI_SPIEN_ToStr(SpiAtCtrl_t SPIEN) {
    const char* name = "?";
    switch((uint32_t)SPIEN) {
    case SPI_AT32_CTRL_DISABLED:
        name = "SpiOff";
        break;
    case SPI_AT32_CTRL_ENABLED:
        name = "SpiOn";
        break;
    }
    return name;
}

static const char* SPI_FBN_ToStr(SpiAtFrameSize_t FBN) {
    const char* name = "?";
    switch((uint32_t)FBN) {
    case SPI_AT32_FRAME_SIZE_8_BIT:
        name = "Frame8bit";
        break;
    case SPI_AT32_FRAME_SIZE_16_BIT:
        name = "Frame16bit";
        break;
    }
    return name;
}

static const char* SPI_ORA_ToStr(SpiAtTxMode_t ORA) {
    const char* name = "?";
    switch((uint32_t)ORA) {
    case SPI_AT32_MOVE_MODE_TX_AND_RX:
        name = "TxAndRx";
        break;
    case SPI_AT32_MOVE_MODE_RX_ONLY:
        name = "RxOnly";
        break;
    }
    return name;
}

static const char* SPI_SWCSIL_ToStr(SpiAtChipSelLevlel_t SWCSIL) {
    const char* name = "?";
    switch((uint32_t)SWCSIL) {
    case SPI_AT32_CHIP_SEL_LEVEL_LOW:
        name = "CsLow";
        break;
    case SPI_AT32_CHIP_SEL_LEVEL_HIGH:
        name = "CsHigh";
        break;
    }
    return name;
}

// Bit 9, Software CS enable, SWCSEN
static const char* SPI_SWCSEN_ToStr(SpiAtChipSelCtrl_t SWCSEN) {
    const char* name = "?";
    switch((uint32_t)SWCSEN) {
    case SPI_AT32_CHIP_SEL_SW:
        name = "SwChipSel";
        break;
    case SPI_AT32_CHIP_SEL_HW:
        name = "HwChipSel";
        break;
    }
    return name;
}

// Bit 12, Transmit CRC next, NTC
static const char* SPI_NTC_ToStr(SpiAtCrc_t NTC) {
    const char* name = "?";
    switch((uint32_t)NTC) {
    case SPI_AT32_CRC_OFF:
        name = "CrcOff";
        break;
    case SPI_AT32_CRC_ON:
        name = "CrcOn";
        break;
    }
    return name;
}

// Bit 13, RC calculation enable, CCEN
static const char* SPI_CCEN_ToStr(SpiAtRc_t CCEN) {
    const char* name = "?";
    switch((uint32_t)CCEN) {
    case SPI_AT32_RC_OFF:
        name = "CrcOff";
        break;
    case SPI_AT32_RC_ON:
        name = "CrcOn";
        break;
    }
    return name;
}

static const char* SPI_MDIV_ToStr(SpiAtMasterClkFreqDiv_t MDIV) {
    const char* name = "?";
    switch((uint32_t)MDIV) {
    case SPI_AT32_MASTER_CLK_DIVIDER_2:
        name = "2";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_4:
        name = "4";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_8:
        name = "8";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_16:
        name = "16";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_32:
        name = "32";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_64:
        name = "64";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_128:
        name = "128";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_256:
        name = "256";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_512:
        name = "512";
        break;
    case SPI_AT32_MASTER_CLK_DIVIDER_1024:
        name = "1024";
        break;
    }
    return name;
}

bool SpiDiagRegCtrl1(const SpiRegCtrl1_t* const Reg, const char* const keyword) {
    bool res = false;
    if(Reg) {
        char text[150] = {0};
        snprintf(text, sizeof(text), "SPI_CTRL1,Value:0x%x=%s", Reg->qword, utoa_bin32(Reg->qword));
        log_print_conditional(LOG_LEVEL_WARNING, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "CLKPHA:%u=%s", Reg->CLKPHA, SPI_CLKPHA_ToStr(Reg->CLKPHA));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "CLKPOL:%u=%s", Reg->CLKPOL, SPI_CLKPOL_ToStr(Reg->CLKPOL));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "MSTEN:%u=%s", Reg->MSTEN, SPI_MSTEN_ToStr(Reg->MSTEN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "MDIV:%u=%s", Reg->MDIV, SPI_MDIV_ToStr(Reg->MDIV));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "SPIEN:%u=%s", Reg->SPIEN, SPI_SPIEN_ToStr(Reg->SPIEN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "LTF:%u=%s", Reg->LTF, SPI_LTF_ToStr(Reg->LTF));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "SWCSIL:%u=%s", Reg->SWCSIL, SPI_SWCSIL_ToStr(Reg->SWCSIL));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "SWCSEN:%u=%s", Reg->SWCSEN, SPI_SWCSEN_ToStr(Reg->SWCSEN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "ORA:%u=%s", Reg->ORA, SPI_ORA_ToStr(Reg->ORA));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "FBN:%u=%s", Reg->FBN, SPI_FBN_ToStr(Reg->FBN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "NTC:%u=%s", Reg->NTC, SPI_NTC_ToStr(Reg->NTC));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "CCEN:%u=%s", Reg->CCEN, SPI_CCEN_ToStr(Reg->CCEN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "SLBTD:%u=%s", Reg->SLBTD, SPI_SLBTD_ToStr(Reg->SLBTD));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        snprintf(text, sizeof(text), "SLBEN:%u=%s", Reg->SLBEN, SPI_SLBEN_ToStr(Reg->SLBEN));
        log_print_conditional(LOG_LEVEL_INFO, SPI, text, keyword, NULL);

        res = true;
    }
    return res;
}

bool spi_diag_low_level(uint8_t num, const char* const keyword) {
    bool res = false;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        res = SpiDiagRegCtrl1((SpiRegCtrl1_t*)&(Info->SPIx->ctrl1_bit), keyword);
    }
    return res;
}

static const Reg32_t SpiReg[] = {
    {
        .valid = true,
        .name = "SPI_CTRL1",
        .offset = 0x00,
    },
    {
        .valid = true,
        .name = "SPI_CTRL2",
        .offset = 0x04,
    },
    {
        .valid = true,
        .name = "SPI_STS",
        .offset = 0x08,
    },
    {
        .valid = true,
        .name = "SPI_DT",
        .offset = 0x0C,
    },
    {
        .valid = true,
        .name = "SPI_CPOLY",
        .offset = 0x10,
    },
    {
        .valid = true,
        .name = "SPI_RCRC",
        .offset = 0x14,
    },
    {
        .valid = true,
        .name = "SPI_TCRC",
        .offset = 0x18,
    },
    {
        .valid = true,
        .name = "SPI_SPICTRL",
        .offset = 0x1C,
    },
    {
        .valid = true,
        .name = "SPI_SPICLKP",
        .offset = 0x20,
    },

};

static uint32_t spi_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(SpiReg);
    return cnt;
}

bool spi_raw_reg_diag(uint8_t num) {
    bool res = false;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        LOG_INFO(SPI, "SPI%u,Base:0x%p", num, Info->SPIx);
        uint32_t reg_cnt = spi_reg_cnt();
        res = debug_raw_reg_diag(SPI, (uint32_t)Info->SPIx, SpiReg, reg_cnt);
    }

    return res;
}
