#include "adc_mcal.h"

#include "adc_const.h"
#include "code_generator.h"
#include "compiler_const.h"
#include "log.h"
#include "microcontroller_const.h"
#include "std_includes.h"

COMPONENT_GET_NODE(Adc, adc)
COMPONENT_GET_CONFIG(Adc, adc)
COMPONENT_GET_CONFIG(AdcChannel, adc_channel)
COMPONENT_GET_NODE(AdcChannel, adc_channel)

_WEAK_FUN_
bool adc_proc(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_read(uint8_t adc_num, uint16_t adc_channel, uint32_t* code) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_mcal_init(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, float* const voltage) {
    bool res = false;
    LOG_DEBUG(LG_ADC, "Read,Adc:%u,Ch:%u", adc_num, channel);
    uint32_t code = 0;
    res = adc_channel_read(adc_num, channel, &code);
    if(res) {
        float val = 0.0;
        val = AdcCode2Voltage(code);
        LOG_PARN(LG_ADC, "ADC%u CH%u Code:%u=0x%x ->%f V", adc_num, channel, code, code, val);
        (*voltage) = val;
    }
    return res;
}

float AdcChannelGetVoltageScale(uint8_t num) {
    float voltage_real = 0.0;
    AdcChannelHandle_t* Node = AdcChannelGetNode(num);
    if(Node) {
        voltage_real = Node->voltage_real;
    } else {
        LOG_INFO(LG_ADC, "InvalidNode %u", num);
    }
    return voltage_real;
}

bool AdcChannelGetVoltage(uint8_t node_num, float* const voltage_scale) {
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
            Node->name = Config->name;
            Node->code = 0;
            Node->read_cnt = 0;
            Node->err_cnt = 0;
            Node->init_done = true;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool adc_set_vref(uint8_t adc_num, float v_ref_voltage) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code) {
    bool res = false;
    return res;
}

_WEAK_FUN_
float adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t channel) {
    float voltage = 0.0;
    return voltage;
}

_WEAK_FUN_
bool adc_proc_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_init_custom(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_init_one(uint8_t num) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_channel_proc(void) {
    bool res = false;
    return res;
}

_WEAK_FUN_
bool adc_init_one(uint8_t num) {
    bool res = false;
    return res;
}

// TODO add UTEST
float AdcCode2Voltage(const int32_t code) {
    float voltage_v = -100.0;
#ifdef CROSS_CODE_VOLTAGE
    voltage_v = (CROSS_CODE_VOLTAGE * ((float)code));
#endif
    return voltage_v;
}

bool adc_code_to_params(AdcChannelHandle_t* const Channel) {
    bool res = false;
    if(Channel) {
        Channel->voltage = AdcCode2Voltage(Channel->code);
        Channel->voltage_real = Channel->voltage * Channel->scale;
        res = true;
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

// COMPONENT_PROC_PATTERT(LG_ADC, ADC, adc)

COMPONENT_INIT_PATTERT(LG_ADC, ADC, adc)

// COMPONENT_INIT_PATTERT(LG_ADC, ADC_CHAN, adc_channel)
