#include "dac_channel_diag.h"

#include <stdio.h>

#include "dac_channel_mcal.h"
#include "board_info.h"
#include "gpio_diag.h"
#include "log.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_DAC_CUSTOM
#include "dac_custom_types.h"
#endif

const char* DacChannelConfigToStr(const DacChannelConfig_t* const Config) {
    static char temp[150] = "";
    strcpy(temp, "");
    if(Config) {
        snprintf(temp, sizeof(temp), "%sN:%u", temp, Config->num);
        snprintf(temp, sizeof(temp), "%sDAC%u_OUT%u,", temp, Config->dac_num, Config->channel);
        snprintf(temp, sizeof(temp), "%sScale:%f,", temp, Config->scale);
        snprintf(temp, sizeof(temp), "%s%s,", temp, GpioPadToStr(Config->Pad));
        snprintf(temp, sizeof(temp), "%s[%s]", temp, Config->name);
    }
    return temp;
}

bool DacDiagConfigChannel(DacChannelConfig_t* const Config) {
    bool res = false;
    if(Config) {
        LOG_INFO(LG_DAC, "%s", DacChannelConfigToStr(Config));
        res = true;
    }
    return res;
}

const char* DacChannelToStr(uint8_t channel) {
    static char temp[40] = "";
    snprintf(temp, sizeof(temp), "Ch%u", channel);
    return temp;
}

#if 0
bool dac_channel_diag(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {
        {10, "DAC"}, {15, "Code"}, {13, "VoltagePin"}, {13, "GPIO"}, {6, "MCU"}, {6, "Scale"}, {13, "VoltageReal"},
    };

    static const table_col_t cols2[] = {
        {5, "Dac"},  {4, "Ch"},  {6, "DEC"}, {8, "HEX"},   {6, "mV"},           {6, "V"},
        {6, "Port"}, {6, "Pin"}, {6, "Pad"}, {6, "Scale"}, {13, "VoltageReal"},
    };

    table_cap(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));
    table_header(&(curWriterPtr->stream), cols2, ARRAY_SIZE(cols2));

    uint16_t num = 0;
    uint32_t chan_cnt = dac_channel_get_cnt();
    uint8_t i = 0;
    for(i = 0; i <= chan_cnt; i++) {
        DacChannelHandle_t* Node = DacChannelGetNode(i);
        if(Node) {

            // DacChannelHandle_t* Channel=DacChannelGetNodeV2(Node->dac_num, Node->channel);
            // float voltage = dac_channel_voltage_read_short(Node->dac_num, Node->channel);
            char log_line[120];
            strcpy(log_line, TSEP);
            snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->dac_num);
            snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->channel);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, Node->code);
            snprintf(log_line, sizeof(log_line), "%s 0x%04x " TSEP, log_line, Node->code);
            snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, ((uint32_t)(Node->voltage * 1000.0)));
            snprintf(log_line, sizeof(log_line), "%s %1.2f " TSEP, log_line, Node->voltage);
            // const DacChannelInfo_t* DacChannelToInfo(uint8_t dac_num, DacChannel_t channel)
#ifdef HAS_DAC_CHANNEL_CUSTOM
            DacChannelInfo_t* Info = DacChannelToInfo(Node->dac_num, Node->channel);
            if(Info) {
                Pad_t pad = Info->pad;
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.port);
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.pin);
                snprintf(log_line, sizeof(log_line), "%s %4u " TSEP, log_line, pad.byte);
            } else {
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
                snprintf(log_line, sizeof(log_line), "%s %4s " TSEP, log_line, "?");
            }
#endif
            snprintf(log_line, sizeof(log_line), "%s %1.2f " TSEP, log_line, Node->scale);
            snprintf(log_line, sizeof(log_line), "%s %2.2f " TSEP, log_line, Node->voltage_real);

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
#endif

bool dac_channel_diag(const char* const key_word1, const char* const key_word2) {
    bool res = false;
    static const table_col_t cols1[] = {
        {5, "DAC"}, {4, "cha"}, {7, "Code"}, {7, "Voltage"}, {7, "scale"}, {7, "VoltReal"}, {5, "Pad"}, {14, "wire"},
    };

    table_header(&(curWriterPtr->stream), cols1, ARRAY_SIZE(cols1));

    uint8_t num = 0;
    uint32_t channel_cnt = dac_channel_get_cnt();
    for(num = 0; num <= channel_cnt; num++) {
        const DacChannelConfig_t* Config = DacChannelGetConfig(num);
        if(Config) {
            DacChannelHandle_t* Node = DacChannelGetNode(num);
            if(Node) {
                float volt_real = Node->voltage * Node->scale;

                char log_line[220] = {0};
                strcpy(log_line, TSEP);
                snprintf(log_line, sizeof(log_line), "%s %3u " TSEP, log_line, Node->dac_num);
                snprintf(log_line, sizeof(log_line), "%s %2u " TSEP, log_line, Node->channel);
                snprintf(log_line, sizeof(log_line), "%s %5u " TSEP, log_line, Node->code);
                snprintf(log_line, sizeof(log_line), "%s %5.2f " TSEP, log_line, Node->voltage);
                snprintf(log_line, sizeof(log_line), "%s %5.1f " TSEP, log_line, Node->scale);
                snprintf(log_line, sizeof(log_line), "%s %5.2f " TSEP, log_line, volt_real);
#ifdef HAS_DAC_CHANNEL_CUSTOM
                const DacChannelInfo_t* Info = DacChannelToInfo(Node->dac_num, Node->channel);
                if(Info) {
                    snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, GpioPadToStr(Info->pad));
                    const Wire_t* Wire = Pad2WireInfio(Info->pad);
                    if(Wire) {
                        snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, Wire->wire_name);
                    }
                } else {
                    snprintf(log_line, sizeof(log_line), "%s %s " TSEP, log_line, "???");
                }
#endif
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

