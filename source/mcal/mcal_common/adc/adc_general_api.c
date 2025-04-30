#include "adc_mcal.h"

#include <stdbool.h>
#include <stdint.h>

#include "adc_const.h"
#include "code_generator.h"
#include "log.h"
#include "sys_config.h"

COMPONENT_GET_NODE(Adc, adc)
COMPONENT_GET_CONFIG(Adc, adc)
COMPONENT_GET_CONFIG(AdcChannel, adc_channel)
COMPONENT_GET_NODE(AdcChannel, adc_channel)

double AdcChannelGetVoltageScale(uint8_t num) {
    double voltage_real = 0.0;
    AdcChannelHandle_t* Node = AdcChannelGetNode(num);
    if(Node) {
        voltage_real = Node->voltage_real;
    } else {
        LOG_INFO(LG_ADC, "InvalidNode %u", num);
    }
    return voltage_real;
}

bool AdcChannelGetVoltage(uint8_t node_num, double* const voltage_scale) {
    bool res = false;
    AdcChannelHandle_t* AdcNode = AdcChannelGetNode(node_num);
    if(AdcNode) {
        if(AdcNode->new_val) {
            *voltage_scale = AdcNode->voltage_real;
            AdcNode->new_val = false;
            res = true;
        } else {
            LOG_DEBUG(LG_ADC, "%u NoNews", node_num);
        }
    } else {
        LOG_INFO(LG_ADC, "InvalidNode %u", node_num);
    }
    return res;
}

const AdcChannelConfig_t* AdcChannelGetConfigV2(AdcNum_t adc_num, AdcChannel_t channel) {
    const AdcChannelConfig_t* ChConfig = NULL;
    uint32_t i = 0;
    uint32_t cnt = adc_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        // AdcDiagConfigChannel(&AdcChannelConfig[i]);
        if(adc_num == AdcChannelConfig[i].adc_num) {
            if(channel == AdcChannelConfig[i].channel) {
                if(AdcChannelConfig[i].valid) {
                    ChConfig = &AdcChannelConfig[i];
                    break;
                } else {
                    LOG_INFO(LG_ADC, "InvalidChan %u", i);
                }
            }
        }
    }
    return ChConfig;
}

AdcChannelHandle_t* AdcChannelGetNodeV2(AdcNum_t adc_num, AdcChannel_t channel) {
    AdcChannelHandle_t* Channel = NULL;
    uint32_t i = 0;
    uint32_t cnt = adc_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(adc_num == AdcChannelInstance[i].adc_num) {
            if(channel == AdcChannelInstance[i].channel) {
                if(AdcChannelInstance[i].valid) {
                    Channel = &AdcChannelInstance[i];
                    break;
                }
            }
        }
    }
    return Channel;
}

bool adc_channel_init_node(const AdcChannelConfig_t* const Config, AdcChannelHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->adc_num = Config->adc_num;
            Node->Pad = Config->Pad;
            Node->sequence = Config->sequence;
            Node->scale = Config->scale;
            Node->channel = Config->channel;
            Node->num = Config->num;
            Node->valid = true;
            Node->code = 0;
            Node->read_cnt = 0;
            Node->err_cnt = 0;
            Node->init_done = true;
            res = true;
        }
    }
    return res;
}

bool adc_wait_convert_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) {
    bool res = true;
    uint32_t start_ms = time_get_ms32();
    uint32_t cur_ms = start_ms;
    uint32_t diff_ms = 0;
    while(false == Node->conv_done) {
        cur_ms = time_get_ms32();
        diff_ms = cur_ms - start_ms;
        if(time_out_ms < diff_ms) {
            res = false;
            LOG_ERROR(LG_ADC, "ADC%u ConvTimeOut %u ms", Node->num, time_out_ms);
            break;
        }
    }
    return res;
}

COMPONENT_PROC_PATTERT(LG_ADC, ADC, adc)

COMPONENT_INIT_PATTERT(LG_ADC, ADC, adc)

COMPONENT_INIT_PATTERT_CNT(LG_ADC, ADC_CHAN, adc_channel, ADC_CHANNELS_COUNT)
