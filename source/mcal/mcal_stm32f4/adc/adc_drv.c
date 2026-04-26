

#include <stdint.h>

 

 
 
static const AdcChannelInfo_t AdcChannelInfo[] = {
    {
        .num = 1,
        .code = ADC_CHANNEL_0,
        .channel = ADC_CHAN_0,
        .pad =
            {
                .port = PORT_A,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_1,
        .channel = ADC_CHAN_1,
        .pad =
            {
                .port = PORT_A,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_2,
        .channel = ADC_CHAN_2,
        .pad =
            {
                .port = PORT_A,
                .pin = 2,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_3,
        .channel = ADC_CHAN_3,
        .pad =
            {
                .port = PORT_A,
                .pin = 3,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_4,
        .channel = ADC_CHAN_4,
        .pad =
            {
                .port = PORT_A,
                .pin = 4,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_5,
        .channel = ADC_CHAN_5,
        .pad =
            {
                .port = PORT_A,
                .pin = 5,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_6,
        .channel = ADC_CHAN_6,
        .pad =
            {
                .port = PORT_A,
                .pin = 6,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_7,
        .channel = ADC_CHAN_7,
        .pad =
            {
                .port = PORT_A,
                .pin = 7,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_8,
        .channel = ADC_CHAN_8,
        .pad =
            {
                .port = PORT_B,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_9,
        .channel = ADC_CHAN_9,
        .pad =
            {
                .port = PORT_B,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_10,
        .channel = ADC_CHAN_10,
        .pad =
            {
                .port = PORT_C,
                .pin = 0,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_11,
        .channel = ADC_CHAN_11,
        .pad =
            {
                .port = PORT_C,
                .pin = 1,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_12,
        .channel = ADC_CHAN_12,
        .pad =
            {
                .port = PORT_C,
                .pin = 2,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_13,
        .channel = ADC_CHAN_13,
        .pad =
            {
                .port = PORT_C,
                .pin = 3,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_14,
        .channel = ADC_CHAN_14,
        .pad =
            {
                .port = PORT_C,
                .pin = 4,
            },
    },
    {
        .num = 1,
        .code = ADC_CHANNEL_15,
        .channel = ADC_CHAN_15,
        .pad =
            {
                .port = PORT_C,
                .pin = 5,
            },
    },

};









 



bool adc_init_ll(uint8_t adc_num) {
    LOG_INFO(LG_ADC, "Init %u", adc_num);
    bool res = false;
    AdcHandle_t* Node = AdcGetNode(adc_num);
    if(Node) {
        const AdcConfig_t* AdcConfNode = AdcGetConfigNode(adc_num);
        if(AdcConfNode) {
            Node->adc_h.Instance = AdcGetInstance(AdcConfNode->num);
            Node->adc_h.Init.ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV4;
            Node->adc_h.Init.Resolution = AdcResolution2code(AdcConfNode->resolution);
            Node->adc_h.Init.ScanConvMode = DISABLE;
            Node->adc_h.Init.ContinuousConvMode = DISABLE;
            Node->adc_h.Init.DiscontinuousConvMode = DISABLE;
            Node->adc_h.Init.ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_NONE;
            Node->adc_h.Init.ExternalTrigConv = ADC_SOFTWARE_START;
            Node->adc_h.Init.DataAlign = ADC_DATAALIGN_RIGHT;
            Node->adc_h.Init.NbrOfConversion = 1;
            Node->adc_h.Init.DMAContinuousRequests = DISABLE;
            Node->adc_h.Init.EOCSelection = ADC_EOC_SINGLE_CONV;
            HAL_StatusTypeDef ret;
            ret = HAL_ADC_Init(&Node->adc_h);
            if(HAL_OK == ret) {
                res = true;
                LOG_INFO(LG_ADC, "Init %u Ok", adc_num);
            } else {
                res = false;
                LOG_ERROR(LG_ADC, "%u InitErr", adc_num);
            }
            if(res) {
                ret = HAL_ADC_Start(&Node->adc_h);
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


bool adc_proc(void) {
    LOG_DEBUG(LG_ADC, "Proc");
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    uint32_t ch_cnt = channel_get_cnt();
    for(i = 0; i < ch_cnt; i++) {
        res = channel_read(AdcChannels[i].num, AdcChannels[i].channel, &AdcChannels[i].code);
        if(res) {
            cnt++;
        } else {
            LOG_DEBUG(LG_ADC, "ReadErr Adc:%u Ch:%u", AdcChannels[i].num, AdcChannels[i].channel);
        }
    }
    if (cnt) {
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



static AdcHandle_t* AdcHalHandle2Handle(ADC_HandleTypeDef* hadc) {
    AdcHandle_t* Node = NULL;
    uint8_t adc_num = AdcInstance2Num(hadc->Instance);
    Node = AdcGetNode(adc_num);
    return Node;
}


float AdcCode2Voltage(int32_t code) {
    float voltage_v = 0.0;
    voltage_v = (CROSS_CODE_VOLTAGE * ((float)code));
    return voltage_v;
}
