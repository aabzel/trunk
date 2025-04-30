#include "dac_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"
#include "dac_mcal.h"
#include "table_utils.h"
#include "writer_config.h"



const char* DacPolarity2Str(DacPolarity_t polarity) {
    const char* name = "?";
    switch((uint8_t)polarity) {
    case DAC_POLARITY_LATCH_RISING:
        name = "RISING";
        break;
    case DAC_POLARITY_LATCH_FALING:
        name = "FALING";
        break;
    }
    return name;
}

const char* DacBitOrder2Str(BitOrder_t bit_order) {
    const char* name = "?";
    switch((uint8_t)bit_order) {
    case DAC_MOST_SIGNIFICANT_BIT_FIRST:
        name = "Msb1st";
        break;
    case DAC_LEAST_SIGNIFICANT_BIT_FIRST:
        name = "Lsb1st";
        break;
    }
    return name;
}

const char* DacPhase2Str(DacPhase_t phase) {
    const char* name = "?";
    switch((uint8_t)phase) {
    case DAC_PHASE_0:
        name = "0";
        break;
    case DAC_PHASE_1:
        name = "1";
        break;
    }
    return name;
}

const char* DacChipSelMode2Str(ChipSelect_t chip_select) {
    const char* name = "?";
    switch((uint8_t)chip_select) {
    case DAC_CHIP_SEL_HW:
        name = "HW";
        break;
    case DAC_CHIP_SEL_SW:
        name = "SW";
        break;
    }
    return name;
}

const char* DacConfigToStr(const DacConfig_t* const Config) {
    static char text[200] = "";
    if(Config) {
        sprintf(text, "DAC%u", Config->num);
        snprintf(text, sizeof(text), "%sRate:%u Hz,", text, Config->bit_rate_hz);
        snprintf(text, sizeof(text), "%sBitOrder:%s,", text, DacBitOrder2Str(Config->bit_order));
        snprintf(text, sizeof(text), "%sPha:%s", text, DacPhase2Str(Config->phase));
        snprintf(text, sizeof(text), "%sPol:%s,", text, DacPolarity2Str(Config->polarity));
        snprintf(text, sizeof(text), "%sChipSel:%s,", text, DacChipSelMode2Str(Config->chip_select));
        snprintf(text, sizeof(text), "%sIRQp:%u,", text, Config->irq_priority);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sMOSI:%s,", text, GpioPad2Str(Config->PadMosi.byte));
        snprintf(text, sizeof(text), "%sMISO:%s,", text, GpioPad2Str(Config->PadMiso.byte));
        snprintf(text, sizeof(text), "%sCS:%s,", text, GpioPad2Str(Config->PadCs.byte));
        snprintf(text, sizeof(text), "%sSCK:%s,", text, GpioPad2Str(Config->PadSck.byte));
    }

    return text;
}

bool DacDiagConfig(const DacConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(DAC, "%s", DacConfigToStr(Config));
    }

    return res;
}

bool dac_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"},   {10, "clk"}, {5, "pha"}, {5, "plo"},
                                       {6, "bits"}, {8, "tx"},   {8, "rx"},  {10, "name"}};
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < DAC_COUNT; num++) {
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, dac_get_clock(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, dac_get_phase(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %1u  " TSEP, temp_str, dac_get_polarity(num));
            snprintf(temp_str, sizeof(temp_str), "%s  %2u " TSEP, temp_str, dac_get_data_size(num));
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->tx_byte_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %6u " TSEP, temp_str, Node->rx_byte_cnt);
            const DacConfig_t* Config = DacGetConfig(num);
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

bool dac_diag_int(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"}, {4, "rx"}, {4, "tx"}, {6, "it"}, {10, "name"}};
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < DAC_COUNT; num++) {
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->rx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->tx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->it_cnt);
            const DacConfig_t* Config = DacGetConfig(num);
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
