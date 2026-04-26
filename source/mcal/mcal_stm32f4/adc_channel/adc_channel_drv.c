#include "adc_channel_channel_drv.h"

#include <stdint.h>

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

bool adc_init_ll(uint8_t adc_num) {
    LOG_INFO(LG_ADC, "Init %u", adc_num);
    bool res = false;
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        const AdcConfig_t* AdcConfNode = AdcGetConfigNode(adc_num);
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

bool adc_channel_init_one(void) {
    bool res = false;
    LOG_INFO(LG_ADC, "InitChannels");
    return res;
}

static bool adc_channel_init(void) {
    bool res = false;
    LOG_INFO(LG_ADC, "InitChannels");
    uint32_t adc_channel_cnt = adc_channel_get_cnt();
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    for(i = 0; i < adc_channel_cnt; i++) {
        uint8_t adc_num = AdcChannelConfig[i].num;
        AdcChannel_t adc_channel = AdcChannelConfig[i].channel;
        res = adc_init_channel(adc_num, adc_channel);
        if(res) {
            ok_cnt++;
        }
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

bool adc_channel_read(uint8_t adc_num, uint16_t adc_channel, uint32_t* code) {
    bool res = false;

    res = adc_init_channel(adc_num, (AdcChannel_t)adc_channel);
    if(res) {
        AdcHandle_t* AdcNode = AdcGetNode(adc_num);
        if(AdcNode) {
            AdcNode->conv_done = false;
            HAL_StatusTypeDef ret = HAL_ADC_Start_IT(&AdcNode->adc_h);
            if(HAL_OK == ret) {
                // uint32_t cnt = 0;
                while(false == AdcNode->conv_done) {
                    res = adc_wait_conv_done_ll(AdcNode, 1000);
                    if(res) {
                        *code = AdcNode->code;
                        LOG_DEBUG(LG_ADC, "ADC%u CH%u %u", adc_num, adc_channel, AdcNode->code);
                    } else {
                        LOG_ERROR(LG_ADC, "%u TimeOut", adc_num);
                    }
                }
            } else {
                LOG_ERROR(LG_ADC, "%u StartErr", adc_num);
            }
        } else {
            LOG_ERROR(LG_ADC, "%u NodeErr", adc_num);
        }
    } else {
        LOG_ERROR(LG_ADC, "init Adc %u Channel %u", adc_num, adc_channel);
    }

    return res;
}

bool adc_channel_proc(void) {
    LOG_DEBUG(LG_ADC, "Proc");
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    uint32_t ch_cnt = adc_channel_get_cnt();
    for(i = 0; i < ch_cnt; i++) {
        res = adc_channel_read(AdcChannels[i].num, AdcChannels[i].channel, &AdcChannels[i].code);
        if(res) {
            cnt++;
        } else {
            LOG_DEBUG(LG_ADC, "ReadErr Adc:%u Ch:%u", AdcChannels[i].num, AdcChannels[i].channel);
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


double AdcCode2Voltage(int32_t code) {
    double voltage_v = 0.0;
    voltage_v = (CROSS_CODE_VOLTAGE * ((double)code));
    return voltage_v;
}

bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t adc_channel, double* const voltage) {
    bool res = false;
    LOG_DEBUG(LG_ADC, "Read Adc:%u Ch:%u", adc_num, adc_channel);
    uint32_t code = 0;
    double val = 0.0;
    res = adc_channel_read(adc_num, adc_channel, &code);
    if(res) {
        val = AdcCode2Voltage(code);
        LOG_DEBUG(LG_ADC, "ADC%u CH%u Code:%u=0x%x ->%f V", adc_num, adc_channel, code, code, val);
        (*voltage) = val;
    }
    return res;
}

bool adc_pad_read_voltage(Pad_t pad, double* const voltage) {
    bool res = false;
    AdcChannel_t adc_channel = AdcPad2Channel(pad);
    AdcNum_t adc_num = AdcPad2AdcNum(pad);
    res = adc_channel_read_voltage(adc_num, adc_channel, voltage);
    return res;
}

double adc_pad_read_voltage_short(Pad_t pad) {
    bool res = false;
    AdcChannel_t chan_num = AdcPad2Channel(pad);
    AdcNum_t adc_num = AdcPad2AdcNum(pad);
    double voltage = 0.0;
    res = adc_channel_read_voltage(adc_num, chan_num, &voltage);
    if(res) {
        LOG_INFO(LG_ADC, "Read %s %f V", GpioPad2Str(pad.byte), voltage);
    } else {
        LOG_ERROR(LG_ADC, "ReadErr Adc:%u Ch:%u", adc_num, chan_num);
    }
    return voltage;
}
