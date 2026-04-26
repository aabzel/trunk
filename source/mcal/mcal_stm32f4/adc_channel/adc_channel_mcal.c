#include "adc_channel_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "adc_config.h"
#include "adc_custom_diag.h"
#include "adc_custom_types.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "adc_mcal.h"
#include "hal_mcal.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

static const AdcChannelInfo_t AdcChannelInfo[] = {
    { .num = 1, .code = ADC_CHANNEL_0,  .adc_channel = ADC_CHAN_0,  .pad = { .port = PORT_A, .pin = 0, }, },
    { .num = 1, .code = ADC_CHANNEL_1,  .adc_channel = ADC_CHAN_1,  .pad = { .port = PORT_A, .pin = 1, }, },
    { .num = 1, .code = ADC_CHANNEL_2,  .adc_channel = ADC_CHAN_2,  .pad = { .port = PORT_A, .pin = 2, }, },
    { .num = 1, .code = ADC_CHANNEL_3,  .adc_channel = ADC_CHAN_3,  .pad = { .port = PORT_A, .pin = 3, }, },
    { .num = 1, .code = ADC_CHANNEL_4,  .adc_channel = ADC_CHAN_4,  .pad = { .port = PORT_A, .pin = 4, }, },
    { .num = 1, .code = ADC_CHANNEL_5,  .adc_channel = ADC_CHAN_5,  .pad = { .port = PORT_A, .pin = 5, }, },
    { .num = 1, .code = ADC_CHANNEL_6,  .adc_channel = ADC_CHAN_6,  .pad = { .port = PORT_A, .pin = 6, }, },
    { .num = 1, .code = ADC_CHANNEL_7,  .adc_channel = ADC_CHAN_7,  .pad = { .port = PORT_A, .pin = 7, }, },
    { .num = 1, .code = ADC_CHANNEL_8,  .adc_channel = ADC_CHAN_8,  .pad = { .port = PORT_B, .pin = 0, }, },
    { .num = 1, .code = ADC_CHANNEL_9,  .adc_channel = ADC_CHAN_9,  .pad = { .port = PORT_B, .pin = 1, }, },
    { .num = 1, .code = ADC_CHANNEL_10, .adc_channel = ADC_CHAN_10, .pad = { .port = PORT_C, .pin = 0, }, },
    { .num = 1, .code = ADC_CHANNEL_11, .adc_channel = ADC_CHAN_11, .pad = { .port = PORT_C, .pin = 1, }, },
    { .num = 1, .code = ADC_CHANNEL_12, .adc_channel = ADC_CHAN_12, .pad = { .port = PORT_C, .pin = 2, }, },
    { .num = 1, .code = ADC_CHANNEL_13, .adc_channel = ADC_CHAN_13, .pad = { .port = PORT_C, .pin = 3, }, },
    { .num = 1, .code = ADC_CHANNEL_14, .adc_channel = ADC_CHAN_14, .pad = { .port = PORT_C, .pin = 4, }, },
    { .num = 1, .code = ADC_CHANNEL_15, .adc_channel = ADC_CHAN_15, .pad = { .port = PORT_C, .pin = 5, }, },
};

const AdcChannelInfo_t* AdcChannelToInfo(uint8_t adc_num, AdcChannel_t channel) {
    const AdcChannelInfo_t *Info = NULL;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if (adc_num == AdcChannelInfo[i].num) {
            if (channel == AdcChannelInfo[i].adc_channel) {
                Info = &AdcChannelInfo[i];
                break;
            }
        }
    }
    return Info;
}

uint32_t AdcChannel2HalChan(AdcChannel_t adc_channel) {
    uint32_t code = 0;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if (AdcChannelInfo[i].adc_channel == adc_channel) {
            code = AdcChannelInfo[i].code;
            break;
        }
    }
    return code;
}


bool adc_channel_init(uint8_t adc_num, AdcChannel_t channel) {
    LOG_DEBUG(ADC_CHANNEL, "Init,Adc:%u,Channel:%u", adc_num, channel);
    bool res = false;
    const AdcChannelConfig_t *AdcCh = AdcChannelGetConfigV2(adc_num, channel);
    if (AdcCh) {
        AdcHandle_t *AdcNode = AdcGetNode(adc_num);
        if (AdcNode) {
            ADC_ChannelConfTypeDef sConfig = { 0 };
            sConfig.Channel = AdcChannel2HalChan(channel);
            sConfig.Rank = AdcCh->num;
            sConfig.SamplingTime = ADC_SAMPLETIME_56CYCLES;
            HAL_StatusTypeDef ret;
            ret = HAL_ADC_ConfigChannel(&AdcNode->adc_h, &sConfig);
            res = HAL_retToRes(ret);
        }
    }
    return res;
}

bool adc_channel_init_one(uint8_t num) {
    bool res = false;
    const AdcChannelConfig_t *Config = AdcChannelGetConfig(num);
    if (Config) {
        AdcChannelHandle_t *Node = AdcChannelGetNode(num);
        if (Node) {
            res = adc_channel_init_node(Config, Node);
            if(res) {
                res = adc_channel_init(Config->adc_num, Config-> channel);
                Node->valid = true;
            }
        }
    }
    return res;
}

#if 0
bool adc_channel_mcal_init(void) {
    bool res = false;
    LOG_INFO(ADC_CHANNEL, "InitChannels");
    uint32_t adc_channel_cnt = adc_channel_get_cnt();
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    for (i = 0; i <= adc_channel_cnt; i++) {
        res = adc_channel_init_one(i);
        ok_cnt = ok_cnt_update(ok_cnt, res);
    }

    if (ok_cnt) {
        res = true;
        LOG_INFO(ADC_CHANNEL, "InitChannelsOk");
    } else {
        LOG_ERROR(ADC_CHANNEL, "InitChannelsErr");
        res = false;
    }

    return res;
}
#endif

bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code) {
    bool res = false;
    res = adc_channel_init(adc_num, (AdcChannel_t) channel);
    if (res) {
        AdcChannelHandle_t *Channel = AdcChannelGetNodeV2(adc_num, channel);
        AdcHandle_t *Adc = AdcGetNode(adc_num);
        if (Adc) {
            Adc->conv_done = false;
            HAL_StatusTypeDef ret = HAL_ADC_Start_IT(&Adc->adc_h);
            res = HAL_retToRes(ret);
            if (res) {
                // uint32_t cnt = 0;
                while (false == Adc->conv_done) {
                    res = adc_wait_conv_done_ll(Adc, 50);
                    if (res) {
                        Channel->code = Adc->code;
                        *code = (int32_t) Adc->code;
                        // LOG_DEBUG(ADC_CHANNEL, "ADC%u CH%u %u", adc_num, adc_channel, Node->code);
                    } else {
                        //        LOG_ERROR(ADC_CHANNEL, "%u TimeOut", adc_num);
                    }
                }
            } else {
                //  LOG_ERROR(ADC_CHANNEL, "%u StartErr", adc_num);
            }
        } else {
            // LOG_ERROR(ADC_CHANNEL, "%u NodeErr", adc_num);
        }
    } else {
        // LOG_ERROR(ADC_CHANNEL, "init Adc %u Channel %u", adc_num, adc_channel);
    }

    return res;
}

bool adc_channel_proc_one(uint8_t num) {
    LOG_PARN(ADC_CHANNEL, "Proc");
    bool res = false;
    AdcChannelHandle_t *AdcCh = AdcChannelGetNode(num);
    if (AdcCh) {
        AdcHandle_t *Adc = AdcGetNode(AdcCh->adc_num);
        if (Adc) {
            if (Adc->init_done) {
                if (MOVE_MODE_DMA != Adc->move_mode) {
                    res = adc_channel_read_code(AdcCh->adc_num,
                                                (AdcChannel_t) AdcCh->channel,
                                                (int32_t*) &AdcCh->code);
                    if (res) {
                        adc_code_to_params(AdcCh);
                    } else {
                        LOG_DEBUG(ADC_CHANNEL, "ReadErr,Adc:%u,Ch:%u",
                                  AdcCh->num,
                                  AdcCh->channel);
                    }
                }
            }
        }
    }

    return res;
}

AdcChannel_t AdcPad2Channel(Pad_t pad) {
    AdcChannel_t chan_num = ADC_CHAN_UNDEF;
    //  uint32_t code = 0;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if (AdcChannelInfo[i].pad.byte == pad.byte) {
            chan_num = AdcChannelInfo[i].adc_channel;
            break;
        }
    }
    return chan_num;
}

AdcNum_t AdcPad2AdcNum(Pad_t pad) {
    AdcNum_t adc_num = ADC_UNDEF;
    // uint32_t code = 0;
    uint32_t i = 0;
    for (i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if (AdcChannelInfo[i].pad.byte == pad.byte) {
            adc_num = AdcChannelInfo[i].num;
            break;
        }
    }
    return adc_num;
}

bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, float* const voltage) {
    bool res = false;
    LOG_DEBUG(ADC_CHANNEL, "Read Adc:%u Ch:%u", adc_num, channel);
    uint32_t code = 0;
    res = adc_channel_read_code(adc_num, channel, (int32_t*) &code);
    if (res) {
        float val = 0.0;
        val = AdcCode2Voltage(code);
        AdcChannelHandle_t *Channel = AdcChannelGetNodeV2(adc_num, channel);
        if (Channel) {
            Channel->voltage = val;
        }
        LOG_DEBUG(ADC_CHANNEL, "ADC%u CH%u Code:%u=0x%x ->%f V", adc_num, channel, code, code, val);
        (*voltage) = val;
    }
    return res;
}

float adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t channel) {
    float voltage = 0.0f;
    adc_channel_read_voltage(adc_num, channel, &voltage);
    return voltage;
}

bool adc_pad_read_voltage(Pad_t pad, float* const voltage) {
    bool res = false;
    AdcChannel_t channel = AdcPad2Channel(pad);
    AdcNum_t adc_num = AdcPad2AdcNum(pad);
    res = adc_channel_read_voltage(adc_num, channel, voltage);
    return res;
}

float adc_pad_read_voltage_short(Pad_t pad) {
    bool res = false;
    AdcChannel_t chan_num = AdcPad2Channel(pad);
    AdcNum_t adc_num = AdcPad2AdcNum(pad);
    float voltage = 0.0;
    res = adc_channel_read_voltage(adc_num, chan_num, &voltage);
    if (res) {
        LOG_INFO(ADC_CHANNEL, "Read %s %f V", GpioPadToStr(pad), voltage);
    } else {
        // LOG_ERROR(ADC_CHANNEL, "ReadErr Adc:%u Ch:%u", adc_num, chan_num);
    }
    return voltage;
}

