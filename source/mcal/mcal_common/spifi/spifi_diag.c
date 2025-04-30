#include "spifi_diag.h"

#include <stdio.h>
#include <string.h>

#include "gpio_diag.h"
#include "log.h"
#include "spifi_mcal.h"
#include "table_utils.h"
#include "writer_config.h"
#include "shared_array.h"

const char* SpiFiConfigToStr(const SpiFiConfig_t* const Config) {
    if(Config) {
        sprintf(text, "SPI%u", Config->num);
        snprintf(text, sizeof(text), "%sRate:%u Hz,", text, Config->bit_rate_hz);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }

    return text;
}

bool SpiFiDiagConfig(const SpiFiConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(SPIFI, "%s", SpiFiConfigToStr(Config));
    }

    return res;
}

bool spifi_diag(void) {
    bool res = false;
    uint8_t num = 0;
    static const table_col_t cols[] = {{5, "No"},

    };
    char temp_str[120];
    table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    for(num = 0; num < SPIFI_COUNT; num++) {
        SpiFiHandle_t* Node = SpiFiGetNode(num);
        if(Node) {
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, num);
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" CRLF, temp_str);
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));

    return res;
}

