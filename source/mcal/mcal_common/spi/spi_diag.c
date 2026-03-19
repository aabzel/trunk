#include "spi_diag.h"

#include "common_diag.h"
#include "debugger.h"
#include "diag_inc.h"
#include "gpio_diag.h"
#include "interfaces_diag.h"
#include "log.h"
#include "mcal_diag.h"
#include "spi_custom_diag.h"
#include "spi_mcal.h"
#include "table_utils.h"
#include "writer_config.h"
#ifdef HAS_DMA_CHANNEL
#include "dma_channel_diag.h"
#endif

const char* ChipSelectSignalToStr(ChipSelectSignal_t state) {
    const char* name = "";
    switch(state) {
    case SPI_CHIP_ENABLE:
        name = "ENABLE";
        break;
    case SPI_CHIP_DISABLE:
        name = "DISABLE";
        break;
    default:
        break;
    }
    return name;
}

const char* SpiPolarityToStr(SpiPolarity_t polarity) {
    const char* name = "?";
    switch(polarity) {
    case SPI_POLARITY_LATCH_RISING:        name = "RISING";        break;
    case SPI_POLARITY_LATCH_FALING:        name = "FALING";        break;
    default:          name = "?";          break;
    }
    return name;
}

const char* SpiBitOrderToStr(IfBitOrder_t bit_order) {
    const char* name = "?";
    switch(bit_order) {
    case BIT_ORDER_MSB:        name = "Msb1st";        break;
    case BIT_ORDER_LSB:        name = "Lsb1st";        break;
    default:          name = "?";          break;
    }
    return name;
}

const char* SpiPhaseToStr(const SpiClkIdleLevel_t spi_phase) {
    const char* name = "?";
    switch(spi_phase) {
        case SPI_CLK_IDLE_LEVEL_0:        name = "0";        break;
        case SPI_CLK_IDLE_LEVEL_1:        name = "1";        break;
        default:          name = "?";          break;
    }
    return name;
}

const char* SpiTxModeToStr(const SpiTxMode_t tx_mode) {
    const char* name = "?";
    switch(tx_mode) {
    case SPI_TX_FULL_DUPLEX:        name = "TxFullDuplex";        break;
    case SPI_TX_SIMPLEX_RX:        name = "Tx";        break;
    case SPI_TX_HALF_DUPLEX_RX:        name = "TxHalfDuplexRx";        break;
    case SPI_TX_HALF_DUPLEX_TX:        name = "TxHalfDuplexTx";        break;
    default:        name = "TxHalfDuplexTx";        break;
    }
    return name;
}

const char* SpiChipSelModeToStr(ChipSelect_t chip_select) {
    const char* name = "?";
    switch(chip_select) {
    case SPI_CHIP_SEL_HW:        name = "HW";        break;
    case SPI_CHIP_SEL_SW:        name = "SW";        break;
    default:          name = "?";          break;
    }
    return name;
}

const char* SpiConfigToStr(const SpiConfig_t* const Config) {
    if(Config) {
        memset(text, 0, sizeof(text));
        strcpy(text, "");
        sprintf(text, "SPI%u,", Config->num);
        snprintf(text, sizeof(text), "%sRate:%u Hz,", text, Config->bit_rate_hz);
        snprintf(text, sizeof(text), "%sBitOrder:%s,", text, SpiBitOrderToStr(Config->bit_order));
        snprintf(text, sizeof(text), "%sFrameSize:%u bit,", text, Config->frame_size);
        snprintf(text, sizeof(text), "%sPha:%s,", text, SpiPhaseToStr(Config->phase));
        snprintf(text, sizeof(text), "%sPol:%s,", text, SpiPolarityToStr(Config->polarity));
        snprintf(text, sizeof(text), "%sChipSel:%s,", text, SpiChipSelModeToStr(Config->chip_select));
        snprintf(text, sizeof(text), "%sTxMode:%s,", text, SpiTxModeToStr(Config->tx_mode));
        snprintf(text, sizeof(text), "%sINT:%s,", text, OnOffToStr(Config->interrupt_on));
        snprintf(text, sizeof(text), "%sMvMode:%s,", text, McalMoveModeToStr(Config->move_mode));
        snprintf(text, sizeof(text), "%sIRQp:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sMOSI:%s,", text, GpioPadToStr(Config->PadMosi));
        snprintf(text, sizeof(text), "%sMISO:%s,", text, GpioPadToStr(Config->PadMiso));
        snprintf(text, sizeof(text), "%sCS:%s,", text, GpioPadToStr(Config->PadCs));
        snprintf(text, sizeof(text), "%sSCK:%s,", text, GpioPadToStr(Config->PadSck));
        snprintf(text, sizeof(text), "%sRole:%s,", text, IfBusRoleToStr(Config->bus_role));
#ifdef HAS_SPI_DMA
        snprintf(text, sizeof(text), "%sDmaTx:%s,", text, DmaPadToStr(Config->DmaTx));
        snprintf(text, sizeof(text), "%sDmaRx:%s,", text, DmaPadToStr(Config->DmaRx));
#endif
    }

    return text;
}

const char* SpiNodeToStr(const SpiHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
    }
    return text;
}

const char* SpiNodeIsrToStr(const SpiHandle_t* const Node) {
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sSPI%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sIt:%u,", text, Node->it_cnt);
        snprintf(text, sizeof(text), "%sRx:%u,", text, Node->rx_cnt);
        snprintf(text, sizeof(text), "%sTx:%u,", text, Node->tx_cnt);
        snprintf(text, sizeof(text), "%sTxRx:%u,", text, Node->txrx_cnt);
        snprintf(text, sizeof(text), "%sMov:%u,", text, Node->move_cnt);
        snprintf(text, sizeof(text), "%sErr:%u,", text, Node->error_cnt);
    }
    return text;
}

bool SpiDiagConfig(const SpiConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(SPI, "%s", SpiConfigToStr(Config));
    }

    return res;
}

bool spi_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"},   {10, "clk"}, {5, "pha"}, {5, "plo"},
                                       {6, "bits"}, {8, "tx"},   {8, "rx"},  {10, "name"}};
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < SPI_COUNT; num++) {
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, spi_get_clock(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, spi_get_phase(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, spi_get_polarity(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %2u " TSEP, temp_str, spi_get_data_size(num));
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->tx_byte_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->rx_byte_cnt);
            const SpiConfig_t* Config = SpiGetConfig(num);
            if(Config) {
                snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Config->name);
            }
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool spi_diag_int(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"}, {4, "rx"}, {4, "tx"}, {6, "it"}, {10, "name"}};
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < SPI_COUNT; num++) {
        SpiHandle_t* Node = SpiGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->rx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->tx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->it_cnt);
            const SpiConfig_t* Config = SpiGetConfig(num);
            if(Config) {
                snprintf(temp_str, sizeof(temp_str), "%s %s " TSEP, temp_str, Config->name);
            }
            snprintf(temp_str, sizeof(temp_str), "%s", temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

bool spi_raw_reg_diag(uint8_t num) {
    bool res = false;
    const SpiInfo_t* Info = SpiGetInfo(num);
    if(Info) {
        LOG_INFO(SPI, "SPI%u,Base:0x%p", num, Info->SPIx);
        uint32_t reg_cnt = spi_reg_cnt();
        res = debug_raw_reg_diag(SPI, (uint32_t)Info->SPIx, SpiRegs, reg_cnt);
    }

    return res;
}
