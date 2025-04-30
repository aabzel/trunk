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

const char* AdcNum2Str(uint8_t adc_num) {
    static char name[40] = "";
    snprintf(name, sizeof(name), "ADC%u", adc_num);
    return name;
}

bool AdcDiagConfigChannel(AdcChannelConfig_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(LG_ADC, "0x%p ADC%u Chan%u %s Valid=%u", Node, Node->adc_num, Node->channel, Node->name, Node->valid);
        res = true;
    }
    return res;
}

const char* AdcChannel2Str(uint8_t channel) {
    static char name[40] = "";
    snprintf(name, sizeof(name), "Ch%u", channel);
    return name;
}

const char* AdcConfigToStr(const AdcConfig_t* const Config) {
    static char name[40] = "";
    if(Config) {
        snprintf(name, sizeof(name), "Resol:%u Bit,Ref:%f Vol", Config->resolution, Config->v_ref_voltage);
    }
    return name;
}

const char* AdcChannelConfigToStr(const AdcChannelConfig_t* const Config) {
    static char name[150] = "";
    if(Config) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sADC%u_IN%u,", name, Config->adc_num, Config->channel);
        snprintf(name, sizeof(name), "%sScale:%f,", name, Config->scale);
        snprintf(name, sizeof(name), "%s%s,", name, GpioPadToStr(Config->Pad));
        snprintf(name, sizeof(name), "%sSec:%u", name, Config->sequence);
        snprintf(name, sizeof(name), "%s%s", name, Config->name);
    }
    return name;
}

const char* AdcNodeToStr(const AdcHandle_t* const Node) {
    static char name[120] = "";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sCode:%u,", name, Node->code);
        snprintf(name, sizeof(name), "%sMax:%u,", name, Node->max_code);
        snprintf(name, sizeof(name), "%sResl:%uBit,", name, Node->resolution);
        snprintf(name, sizeof(name), "%sRef:%3.1f Vol,", name, Node->v_ref_voltage);
        snprintf(name, sizeof(name), "%sMax:%u", name, Node->max_code);
    }
    return name;
}

bool adc_diag(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {{10, "ADC"}, {15, "Code"}, {13, "Voltage"}, {13, "GPIO"}, {6, "MCU"}};

    static const table_col_t cols2[] = {
        {5, "Adc"}, {4, "Ch"}, {6, "DEC"}, {8, "HEX"}, {6, "mV"}, {6, "V"}, {6, "Port"}, {6, "Pin"}, {6, "Pad"},
    };

    table_cap(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));
    table_header(&(curWriterPtr->stream), cols2, ARRAY_SIZE(cols2));

    uint16_t num = 0;
    uint32_t chan_cnt = adc_channel_get_cnt();
    uint8_t i = 0;
    char log_line[120];
    for(i = 0; i < chan_cnt; i++) {
        AdcChannelHandle_t* Node = AdcChannelGetNode(i);
        if(Node) {
            double voltage = adc_channel_read_voltage_short(Node->adc_num, Node->channel);
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->adc_num);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->channel);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, Node->code);
            snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, Node->code);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, ((uint32_t)(voltage * 1000.0)));
            snprintf(log_line, sizeof(log_line), "%s %1.2f " TSEP, log_line, voltage);
#if 0
            AdcChannelStaticInfo_t* AdcChannelStaticInfo = AdcGetChannelInfo(Node->channel);
            if(AdcChannelStaticInfo) {
                Pad_t pad = AdcChannelStaticInfo->pad;
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.port);
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.pin);
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.byte);
            } else {
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
            }
#endif

            res = is_contain(log_line, key_word1, key_word2);
            if(res) {
                cli_printf("%s" CRLF, log_line);
                num++;
                res = true;
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols2, ARRAY_SIZE(cols2));
    return res;
}

bool adc_channel_diag(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {
        {5, "ADC"}, {4, "cha"}, {7, "Code"}, {7, "Voltage"}, {7, "scale"}, {7, "VoltReal"}, {5, "Pad"}, {14, "wire"},
    };

    table_header(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));

    uint8_t num = 0;
    char log_line[220];
    uint32_t channel_cnt = adc_channel_get_cnt();
    for(num = 0; num <= channel_cnt; num++) {
        const AdcChannelConfig_t* Config = AdcChannelGetConfig(num);
        if(Config) {
            AdcChannelHandle_t* Node = AdcChannelGetNode(num);
            if(Node) {
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->adc_num);
                snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->channel);
                snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->code);
                snprintf(log_line, sizeof(log_line), "%s %5.2f " TSEP, log_line, Node->voltage);
                double volt_real = Node->voltage * Node->scale;
                snprintf(log_line, sizeof(log_line), "%s %5.1f " TSEP, log_line, Node->scale);
                snprintf(log_line, sizeof(log_line), "%s %5.2f " TSEP, log_line, volt_real);
                const AdcChannelInfo_t* Info = AdcChannelToInfo(Node->adc_num, Node->channel);
                if(Info) {
                    snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, GpioPadToStr(Info->pad));
                    const Wire_t* Wire = Pad2WireInfio(Info->pad);
                    if(Wire) {
                        snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, Wire->wire_name);
                    }
                } else {
                    snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, "???");
                }
                snprintf(log_line, sizeof(log_line), "%s %12s " TSEP, log_line, Config->name);

                res = is_contain(log_line, key_word1, key_word2);
                if(res) {
                    cli_printf("%s" CRLF, log_line);
                    res = true;
                }
            }
        }
    }
    table_row_bottom(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));
    return res;
}

bool adc_diag_isr(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {
        {5, "ADC"},         {8, "Code"},   {7, "ItCnt"}, {7, "overflow"},  {7, "PreChConvEn"},
        {7, "PreChConvSt"}, {7, "ConvSt"}, {7, "Rdy"},   {7, "ChConvEnd"},
    };

    table_header(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));

    uint8_t num = 0;
    char log_line[120];
    uint32_t chan_cnt = adc_get_cnt();
    for(num = 0; num <= chan_cnt; num++) {
        AdcHandle_t* Node = AdcGetNode(num);
        if(Node) {

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
