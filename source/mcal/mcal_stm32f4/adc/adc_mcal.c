#include "adc_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "adc_config.h"
#include "adc_custom_diag.h"
#include "adc_custom_types.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "std_includes.h"
#include "stm32f4xx_hal.h"
#include "time_mcal.h"

#ifdef HAS_LOG
#include "log.h"
#endif

static const AdcChannelInfo_t AdcChannelInfo[] = {
    {
        .num = 1,
        .code = ADC_CHANNEL_0,
        .adc_channel = ADC_CHAN_0,
        .pad =
            {
                .port = PORT_A,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_1,
        .adc_channel = ADC_CHAN_1,
        .pad =
            {
                .port = PORT_A,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_2,
        .adc_channel = ADC_CHAN_2,
        .pad =
            {
                .port = PORT_A,
                .pin = 2,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_3,
        .adc_channel = ADC_CHAN_3,
        .pad =
            {
                .port = PORT_A,
                .pin = 3,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_4,
        .adc_channel = ADC_CHAN_4,
        .pad =
            {
                .port = PORT_A,
                .pin = 4,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_5,
        .adc_channel = ADC_CHAN_5,
        .pad =
            {
                .port = PORT_A,
                .pin = 5,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_6,
        .adc_channel = ADC_CHAN_6,
        .pad =
            {
                .port = PORT_A,
                .pin = 6,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_7,
        .adc_channel = ADC_CHAN_7,
        .pad =
            {
                .port = PORT_A,
                .pin = 7,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_8,
        .adc_channel = ADC_CHAN_8,
        .pad =
            {
                .port = PORT_B,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_9,
        .adc_channel = ADC_CHAN_9,
        .pad =
            {
                .port = PORT_B,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_10,
        .adc_channel = ADC_CHAN_10,
        .pad =
            {
                .port = PORT_C,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_11,
        .adc_channel = ADC_CHAN_11,
        .pad =
            {
                .port = PORT_C,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_12,
        .adc_channel = ADC_CHAN_12,
        .pad =
            {
                .port = PORT_C,
                .pin = 2,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_13,
        .adc_channel = ADC_CHAN_13,
        .pad =
            {
                .port = PORT_C,
                .pin = 3,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_14,
        .adc_channel = ADC_CHAN_14,
        .pad =
            {
                .port = PORT_C,
                .pin = 4,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_15,
        .adc_channel = ADC_CHAN_15,
        .pad =
            {
                .port = PORT_C,
                .pin = 5,
            },
    },

};

const AdcChannelInfo_t* AdcChannelToInfo(uint8_t adc_num, AdcChannel_t channel) {
    const AdcChannelInfo_t* Info = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(adc_num == AdcChannelInfo[i].num) {
            if(channel == AdcChannelInfo[i].adc_channel) {
                Info = &AdcChannelInfo[i];
                break;
            }
        }
    }
    return Info;
}

static const AdcResolutionInfo_t AdcResolutionInfo[] = {
    {
        .code = ADC_RESOLUTION_12B,
        .resolution = 12,
    },
    {
        .code = ADC_RESOLUTION_10B,
        .resolution = 10,
    },
    {
        .code = ADC_RESOLUTION_8B,
        .resolution = 8,
    },
    {
        .code = ADC_RESOLUTION_6B,
        .resolution = 6,
    },
};

static const AdcInfo_t AdcInfo[] = {
#ifdef HAS_ADC1
    {
        .instance = ADC1,
        .adc_num = 1,
        .valid = true,
    },
#endif

#ifdef HAS_ADC2
    {
        .instance = ADC2,
        .adc_num = 2,
        .valid = true,
    },
#endif

#ifdef HAS_ADC3
    {
        .instance = ADC3,
        .adc_num = 3,
        .valid = true,
    },
#endif
};

ADC_TypeDef* AdcGetInstance(uint8_t adc_num) {
    ADC_TypeDef* Instance = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(AdcInfo);
    for(i = 0; i < cnt; i++) {
        if(AdcInfo[i].adc_num == adc_num) {
            if(AdcInfo[i].valid) {
                Instance = AdcInfo[i].instance;
                break;
            }
        }
    }
    return Instance;
}

uint8_t AdcInstance2Num(ADC_TypeDef* ADCx) {
    uint8_t adc_num = 0;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(AdcInfo);
    for(i = 0; i < cnt; i++) {
        if(AdcInfo[i].instance == ADCx) {
            if(AdcInfo[i].valid) {
                adc_num = AdcInfo[i].adc_num;
                break;
            }
        }
    }
    return adc_num;
}

uint32_t AdcChannel2HalChan(AdcChannel_t adc_channel) {
    uint32_t code = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].adc_channel == adc_channel) {
            code = AdcChannelInfo[i].code;
            break;
        }
    }
    return code;
}

/*Hi load function*/
bool adc_init_channel(uint8_t adc_num, AdcChannel_t channel) {
    LOG_DEBUG(LG_ADC, "Init,Adc:%u,Channel:%u", adc_num, channel);
    bool res = false;
    HAL_StatusTypeDef ret;
    AdcHandle_t* Adc = AdcGetNode(adc_num);
    if(Adc) {
        ADC_ChannelConfTypeDef sConfig = {0};
        sConfig.Channel = AdcChannel2HalChan(channel);
        sConfig.Rank = 1;
        sConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
        ret = HAL_ADC_ConfigChannel(&Adc->adc_h, &sConfig);
        if(HAL_OK == ret) {
            res = true;
        } else {
            res = false;
        }
    }
    return res;
}

uint32_t AdcResolution2code(uint8_t resolution) {
    uint32_t code = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcResolutionInfo); i++) {
        if(AdcResolutionInfo[i].resolution == resolution) {
            code = AdcResolutionInfo[i].code;
            break;
        }
    }
    return code;
}

bool adc_init_custom(void) {
    bool res = false;
    LOG_INFO(LG_ADC, "ADC_REF_VOLTAGE %f V", ADC_REF_VOLTAGE);
    return res;
}

bool adc_init_one(uint8_t adc_num) {
    LOG_INFO(LG_ADC, "Init %u", adc_num);
    bool res = false;
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        const AdcConfig_t* AdcConfNode = AdcGetConfig(adc_num);
        if(AdcConfNode) {
            AdcNode->adc_h.Instance = AdcGetInstance(AdcConfNode->num);
            AdcNode->adc_h.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
            AdcNode->adc_h.Init.Resolution = AdcResolution2code(AdcConfNode->resolution);
            AdcNode->adc_h.Init.ScanConvMode = DISABLE;
            AdcNode->adc_h.Init.ContinuousConvMode = DISABLE;
            AdcNode->adc_h.Init.DiscontinuousConvMode = DISABLE;
            AdcNode->adc_h.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
            AdcNode->adc_h.Init.ExternalTrigConv = ADC_SOFTWARE_START;
            AdcNode->adc_h.Init.DataAlign = ADC_DATAALIGN_RIGHT;
            AdcNode->adc_h.Init.NbrOfConversion = 1;
            AdcNode->adc_h.Init.DMAContinuousRequests = DISABLE;
            AdcNode->adc_h.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
            HAL_StatusTypeDef ret;
            ret = HAL_ADC_Init(&AdcNode->adc_h);
            if(HAL_OK == ret) {
                res = true;
                LOG_INFO(LG_ADC, "Init %u Ok", adc_num);
            } else {
                res = false;
                LOG_ERROR(LG_ADC, "%u InitErr", adc_num);
            }
            if(res) {
                ret = HAL_ADC_Start(&AdcNode->adc_h);
                if(HAL_OK == ret) {
                    res = true;
                    LOG_INFO(LG_ADC, "%u StartOk", adc_num);
                } else {
                    res = false;
                    LOG_ERROR(LG_ADC, "%u StartErr", adc_num);
                }
            }
        } else {
            LOG_ERROR(LG_ADC, "%u ConfigErr", adc_num);
        }
    } else {
        LOG_ERROR(LG_ADC, "%u NodeErr", adc_num);
    }
    return res;
}

bool adc_channel_init_one(uint8_t num) {
    bool res = false;
    const AdcChannelConfig_t* Config = AdcChannelGetConfig(num);
    if(Config) {
        AdcChannelHandle_t* Node = AdcChannelGetNode(num);
        if(Node) {
            res = adc_channel_init_node(Config, Node);
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

bool adc_channel_mcal_init(void) {
    bool res = false;
    LOG_INFO(LG_ADC, "InitChannels");
    uint32_t adc_channel_cnt = adc_channel_get_cnt();
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    for(i = 0; i < adc_channel_cnt; i++) {
        adc_channel_init_one(i);
        uint8_t adc_num = AdcChannelConfig[i].num;
        AdcChannel_t channel = AdcChannelConfig[i].channel;
        res = adc_init_channel(adc_num, channel);
        ok_cnt = ok_cnt_update(ok_cnt, res);
    }

    if(ok_cnt) {
        res = true;
        LOG_INFO(LG_ADC, "InitChannelsOk");
    } else {
        LOG_ERROR(LG_ADC, "InitChannelsErr");
        res = false;
    }

    return res;
}

static bool adc_wait_conv_done_ll(AdcHandle_t* AdcNode, uint32_t time_out_ms) {
    uint32_t cnt = 0;
    bool res = true;
    uint32_t cur_time_ms = 0;
    uint32_t init_time_ms = time_get_ms32();
    uint32_t diff_time_ms = 0;
    while(false == AdcNode->conv_done) {
        cnt++;
        cur_time_ms = time_get_ms32();
        diff_time_ms = cur_time_ms - init_time_ms;
        if(time_out_ms < diff_time_ms) {
            res = false;
            break;
        }
    }
    return res;
}

bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code) {
    bool res = false;
    res = adc_init_channel(adc_num, (AdcChannel_t)channel);
    if(res) {
        AdcChannelHandle_t* Channel = AdcChannelGetNodeV2(adc_num, channel);
        AdcHandle_t* Adc = AdcGetNode(adc_num);
        if(Adc) {
            Adc->conv_done = false;
            HAL_StatusTypeDef ret = HAL_ADC_Start_IT(&Adc->adc_h);
            if(HAL_OK == ret) {
                // uint32_t cnt = 0;
                while(false == Adc->conv_done) {
                    res = adc_wait_conv_done_ll(Adc, 50);
                    if(res) {
                        Channel->code = Adc->code;
                        *code = (int32_t)Adc->code;
                        // LOG_DEBUG(LG_ADC, "ADC%u CH%u %u", adc_num, adc_channel, AdcNode->code);
                    } else {
                        //        LOG_ERROR(LG_ADC, "%u TimeOut", adc_num);
                    }
                }
            } else {
                //  LOG_ERROR(LG_ADC, "%u StartErr", adc_num);
            }
        } else {
            // LOG_ERROR(LG_ADC, "%u NodeErr", adc_num);
        }
    } else {
        // LOG_ERROR(LG_ADC, "init Adc %u Channel %u", adc_num, adc_channel);
    }

    return res;
}

bool adc_proc(void) {
    LOG_DEBUG(LG_ADC, "Proc");
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    uint32_t ch_cnt = adc_channel_get_cnt();
    for(i = 0; i < (ch_cnt); i++) {
        res = adc_channel_read_code(AdcChannelInstance[i].adc_num, (AdcChannel_t)AdcChannelInstance[i].channel,
                                    (int32_t*)&AdcChannelInstance[i].code);
        if(res) {
            adc_code_to_params(&AdcChannelInstance[i]);
            cnt++;
        } else {
            LOG_DEBUG(LG_ADC, "ReadErr,Adc:%u,Ch:%u", AdcChannelInstance[i].num, AdcChannelInstance[i].channel);
        }
    }
    if(cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle) {
#ifdef HAS_ADC1
    if(ADC1 == adcHandle->Instance) {
        __HAL_RCC_ADC1_CLK_ENABLE();
        HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        HAL_NVIC_EnableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC2
    if(ADC2 == adcHandle->Instance) {
        __HAL_RCC_ADC2_CLK_ENABLE();
        HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        HAL_NVIC_EnableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC3
    if(ADC3 == adcHandle->Instance) {
        __HAL_RCC_ADC3_CLK_ENABLE();
        HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        HAL_NVIC_EnableIRQ(ADC_IRQn);
    }
#endif
}

void HAL_ADC_MspDeInit(ADC_HandleTypeDef* adcHandle) {
#ifdef HAS_ADC1
    if(ADC1 == adcHandle->Instance) {
        __HAL_RCC_ADC1_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC2
    if(ADC2 == adcHandle->Instance) {
        __HAL_RCC_ADC2_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC3
    if(ADC3 == adcHandle->Instance) {
        __HAL_RCC_ADC3_CLK_DISABLE();
        HAL_NVIC_DisableIRQ(ADC_IRQn);
    }
#endif
}

static AdcHandle_t* AdcHalHandle2Handle(ADC_HandleTypeDef* hadc) {
    AdcHandle_t* AdcNode = NULL;
    uint8_t adc_num = AdcInstance2Num(hadc->Instance);
    AdcNode = AdcGetNode(adc_num);
    return AdcNode;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    AdcHandle_t* AdcNode = NULL;
    AdcNode = AdcHalHandle2Handle(hadc);
    if(AdcNode) {
        AdcNode->code = HAL_ADC_GetValue(&AdcNode->adc_h);
        AdcNode->conv_done = true;
        AdcNode->it_cnt++;
    }
}

AdcChannel_t AdcPad2Channel(Pad_t pad) {
    AdcChannel_t chan_num = ADC_CHAN_UNDEF;
    //  uint32_t code = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].pad.byte == pad.byte) {
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
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].pad.byte == pad.byte) {
            adc_num = AdcChannelInfo[i].num;
            break;
        }
    }
    return adc_num;
}

bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, float* const voltage) {
    bool res = false;
    LOG_DEBUG(LG_ADC, "Read Adc:%u Ch:%u", adc_num, channel);
    uint32_t code = 0;
    res = adc_channel_read_code(adc_num, channel, (int32_t*)&code);
    if(res) {
        float val = 0.0;
        val = AdcCode2Voltage(code);
        AdcChannelHandle_t* Channel = AdcChannelGetNodeV2(adc_num, channel);
        if(Channel) {
            Channel->voltage = val;
        }
        LOG_DEBUG(LG_ADC, "ADC%u CH%u Code:%u=0x%x ->%f V", adc_num, channel, code, code, val);
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
    if(res) {
        LOG_INFO(LG_ADC, "Read %s %f V", GpioPadToStr(pad), voltage);
    } else {
        // LOG_ERROR(LG_ADC, "ReadErr Adc:%u Ch:%u", adc_num, chan_num);
    }
    return voltage;
}

#if 0
bool adc_mcal_init(void) {
    bool res = false;
    LOG_INFO(LG_ADC, "Init");
    LOG_INFO(LG_ADC, "Version %u", ADC_CUSTOM_DRV_VER);
    uint32_t cnt = 0;
#ifdef HAS_ADC1
    res = adc_init_one(1);
    if(res) {
        cnt++;
    }
#endif

#ifdef HAS_ADC2
    res = adc_init_one(2);
    if(res) {
        cnt++;
    }
#endif

#ifdef HAS_ADC3
    res = adc_init_one(3);
    if(res) {
        cnt++;
    }
#endif

    res = adc_channel_init();
    if(res) {
        cnt++;
    }

    if(cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}
#endif
