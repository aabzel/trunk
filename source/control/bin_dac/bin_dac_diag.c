#include "bin_dac_diag.h"

#include "bin_dac_mcal.h"
#include "common_diag.h"
#include "diag_inc.h"
#include "num_to_str.h"
#include "diag_inc.h"
#include "float_diag.h"
#include "log.h"
#include "dma_channel_diag.h"
#include "gpio_diag.h"

/*
 Serializators
 */

const char* BinDacConfigToStr(const BinDacConfig_t* const Config) {
    strcpy(text, "");
    if(Config) {
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sTIM%u,", text, Config->timer_num);
        snprintf(text, sizeof(text), "%sFS:%u Hz,", text, Config->sample_freq_hz);
        snprintf(text, sizeof(text), "%sTxSz:%u Sam,", text, Config->data_array_size);
        snprintf(text, sizeof(text), "%sTxMem:0x%x,", text, Config->GpioPortDataArray);
        snprintf(text, sizeof(text), "%sOutPad:%s,", text, GpioPadToStr(Config->outPad));
        snprintf(text, sizeof(text), "%sDma:[%s],", text, DmaInfoPadToStr(&Config->DmaChPad));
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
    }
    return text;
}

const char* BinDacNodeToStr(const BinDacHandle_t* const Node) {
    strcpy(text, "");
    if(Node) {
        snprintf(text, sizeof(text), "%sSpin:%u,", text, Node->spin);
        snprintf(text, sizeof(text), "%sInit:%s,", text, OnOffToStr(Node->init));
        snprintf(text, sizeof(text), "%sTxSz:%u Sam,", text, Node->data_array_size);
        snprintf(text, sizeof(text), "%sTxMem:0x%x,", text, Node->GpioPortDataArray);
    }
    return text;
}

bool bin_dac_diag_one(uint8_t num) {
    bool res = false;
    const BinDacConfig_t *Config = BinDacGetConfig(num);
    if(Config) {
        LOG_INFO(BIN_DAC, "%s", BinDacConfigToStr(Config));
        BinDacHandle_t *Node = BinDacGetNode(num);
        if(Node) {
            LOG_INFO(BIN_DAC, "%s", BinDacNodeToStr(Node));
            res = true;
        }
    }

    return res;
}

bool bin_dac_diag(void) {
    bool res = false;
    res = bin_dac_diag_one(1);
    return res;
}



bool bin_dac_show_sample(uint8_t num) {
    bool res = false;
    bin_dac_diag_one(num);
    BinDacHandle_t *Node = BinDacGetNode(num);
    if(Node){
        LOG_INFO(BIN_ADC, "StartCnt:%u",Node->start_cnt);
        const table_col_t cols[] = {
                {5, "Num"},
                {10, "TS"},
                {10, "Sam"},
                {41, "BIN"},
        };
        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t i = 0 ;
        for(i=0;i<Node->data_array_size;i++){
            float ts = ((float)i) /   ((float)Node->sample_freq_hz);
            char temp_str[120];
            strcpy(temp_str, TSEP);
            snprintf(temp_str, sizeof(temp_str), "%s %3u " TSEP, temp_str, i);
            snprintf(temp_str, sizeof(temp_str), "%s %8s " TSEP, temp_str, FloatBigToStr(ts));
            snprintf(temp_str, sizeof(temp_str), "%s 0x%08x " TSEP, temp_str, Node->GpioPortDataArray[i]);
            snprintf(temp_str, sizeof(temp_str), "%s %s " TSEP, temp_str, utoa_bin32(Node->GpioPortDataArray[i]));
            snprintf(temp_str, sizeof(temp_str), "%s" CRLF, temp_str);
            cli_printf("%s" , temp_str);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
    }
    return res;
}
