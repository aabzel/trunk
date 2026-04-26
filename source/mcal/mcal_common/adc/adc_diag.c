#include "adc_diag.h"

#include <stdio.h>

#include "adc_mcal.h"
#include "board_info.h"
#include "gpio_diag.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_ADC_CUSTOM
#include "adc_custom_types.h"
#endif

const char* AdcNumToStr(uint8_t adc_num) {
    static char name[40] = "";
    snprintf(name, sizeof(name), "ADC%u", adc_num);
    return name;
}

const char* AdcConfigToStr(const AdcConfig_t* const Config) {
    static char name[40] = "";
    if(Config) {
        snprintf(name, sizeof(name), "Resol:%u Bit,Ref:%f Vol", Config->resolution, Config->v_ref_voltage);
    }
    return name;
}

const char* AdcNodeToStr(const AdcHandle_t* const Node) {
    static char name[120] = "";
    strcpy(name, "");
    if(Node) {
        snprintf(name, sizeof(name), "%sCode:%u,", name, Node->code);
        snprintf(name, sizeof(name), "%sMax:%u,", name, Node->max_code);
        snprintf(name, sizeof(name), "%sResl:%uBit,", name, Node->resolution);
        snprintf(name, sizeof(name), "%sRef:%3.1f Vol,", name, Node->v_ref_voltage);
        snprintf(name, sizeof(name), "%sMax:%u", name, Node->max_code);
    }
    return name;
}

bool adc_diag_isr(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {
        {5, "ADC"},         {8, "Code"},   {7, "ItCnt"}, {7, "overflow"},  {7, "PreChConvEn"},
        {7, "PreChConvSt"}, {7, "ConvSt"}, {7, "Rdy"},   {7, "ChConvEnd"},
    };

    table_header(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));

    uint8_t num = 0;
    uint32_t chan_cnt = adc_get_cnt();
    for(num = 0; num <= chan_cnt; num++) {
        AdcHandle_t* Node = AdcGetNode(num);
        if(Node) {
            char log_line[120];
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->num);
            snprintf(log_line, sizeof(log_line), "%s %6u " TSEP, log_line, Node->code);

            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->it_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->overflow_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->preempt_chan_conv_end_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->preempt_chan_conv_start_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->conversion_start_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->ready_cnt);
            snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->chan_conv_end_cnt);

            res = is_contain(log_line, key_word1, key_word2);
            if(res) {
                cli_printf("%s" CRLF, log_line);
                num++;
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));
    return res;
}
