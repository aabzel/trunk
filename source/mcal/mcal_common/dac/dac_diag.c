#include "dac_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"
#include "dac_mcal.h"
#include "table_utils.h"
#include "writer_config.h"

const char* DacConfigToStr(const DacConfig_t* const Config) {
    static char temp[200] = "";
    if(Config) {
        sprintf(temp, "DAC%u", Config->num);
        snprintf(temp, sizeof(temp), "%sChipSel:%s,", temp, GpioPadToStr(Config->Pad));
        snprintf(temp, sizeof(temp), "%sInt:%u,", temp, Config->interrupt_on);
        snprintf(temp, sizeof(temp), "%sIntPio:%u,", temp, Config->irq_priority);
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
    }

    return temp;
}

bool DacDiagConfig(const DacConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_DAC, "%s", DacConfigToStr(Config));
    }
    return res;
}

bool dac_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"},   {10, "clk"}, {5, "pha"}, {5, "plo"},
                                       {6, "bits"}, {8, "tx"},   {8, "rx"},  {10, "name"}
    };
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < DAC_COUNT; num++) {
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
            char temp_str[120];
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %8u " TSEP, temp_str, dac_get_clock(num));
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, Node->name);
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
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < DAC_COUNT; num++) {
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
            char temp_str[120]={0};
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->tx_done);
            snprintf(temp_str, sizeof(temp_str), "%s %2u " TSEP, temp_str, Node->it_cnt);
            snprintf(temp_str, sizeof(temp_str), "%s %s " TSEP, temp_str, Node->name);
            snprintf(temp_str, sizeof(temp_str), "%s", temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}
