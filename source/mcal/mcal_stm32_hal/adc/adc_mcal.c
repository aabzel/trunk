#include "adc_mcal.h"

#include <stddef.h>
#include <stdio.h>
#include <string.h>

#include "adc_config.h"
#include "adc_custom_diag.h"
#include "adc_custom_types.h"
#include "data_utils.h"
#include "gpio_diag.h"
#include "hal_mcal.h"
#include "std_includes.h"
#include "stm32fx_hal.h"
#include "time_mcal.h"
#include "interrupt_mcal.h"

#ifdef HAS_IQUEUE
#include "lib_iqueue.h"
#include "iqueue.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

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
        .irq_n = ADC_IRQn,
        .valid = true,
    },
#endif

#ifdef HAS_ADC2
    {
        .instance = ADC2,
        .adc_num = 2,
        .irq_n = ADC_IRQn,
        .valid = true,
    },
#endif

#ifdef HAS_ADC3
    {
        .instance = ADC3,
        .adc_num = 3,
        .irq_n = ADC_IRQn,
        .valid = true,
    },
#endif
};

AdcInfo_t* AdcGetInfo(uint32_t adc_num) {
    AdcInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(AdcInfo);
    for(i = 0; i < cnt; i++) {
        if(AdcInfo[i].adc_num == adc_num) {
            if(AdcInfo[i].valid) {
                Info = &AdcInfo[i];
                break;
            }
        }
    }
    return Info;
}

/*
Configures the sequencer of regular and injected groups.
This parameter can be associated to parameter 'DiscontinuousConvMode' to
have main sequence subdivided in successive parts.
 */
static uint32_t AdcScanModeToStmScanMode(const uint32_t num_of_conversion) {
    uint32_t stm32_scan_conv_mode = DISABLE;
    if(1 < num_of_conversion) {
        /* If enabled:
         Conversions are performed in sequence mode
         (multiple ranks defined by 'NbrOfConversion'/'InjectedNbrOfConversion' and each channel rank).
         Scan direction is upward: from rank1 to rank 'n'.         */
        stm32_scan_conv_mode = ENABLE;
    } else if(1==num_of_conversion) {
        /* If disabled: Conversion is performed in single mode (one channel converted, the one defined in rank 1).
        Parameters 'NbrOfConversion' and 'InjectedNbrOfConversion' are discarded (equivalent to set to 1). */
        stm32_scan_conv_mode = DISABLE;
    }
    return stm32_scan_conv_mode;
}

static FunctionalState AdcDmaModeToStmDmaMode(const MoveMode_t move_mode) {
    FunctionalState dma_continuous_requests = DISABLE;
    switch(move_mode) {
        case MOVE_MODE_POLLING:dma_continuous_requests = DISABLE; break;
        case MOVE_MODE_INTERRUPT:dma_continuous_requests = DISABLE; break;
        case MOVE_MODE_DMA: dma_continuous_requests = ENABLE;break;
        default: break;
    }
    return dma_continuous_requests;
}

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
    uint32_t code = ADC_RESOLUTION_12B;
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

static uint32_t AdcExternalTriggerSourceToExternalTrigConv(const AdcExternalTriggerSource_t trigger_source) {
    uint32_t ExternalTrigConv = ADC_SOFTWARE_START;
    switch (trigger_source) {
        case ADC_MCAL_TRIG_SRC_SOFTWARE_START:
            ExternalTrigConv = ADC_SOFTWARE_START;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER2_TRGO:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_TRGO;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER3_TRGO:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_TRGO;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER8_TRGO:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T8_TRGO;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH1:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC1;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH2:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC2;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER1_COM_CH3:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T1_CC3;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH2:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_CC2;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH3:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_CC3;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER2_COM_CH4:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T2_CC4;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER3_COM_CH1:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T3_CC1;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER4_COM_CH4:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T4_CC4;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH1:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T5_CC1;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH2:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T5_CC2;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER5_COM_CH3:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T5_CC3;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_TIRER8_COM_CH1:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_T8_CC1;
            break;
        case ADC_MCAL_TRIG_SRC_EXT_IT11:
            ExternalTrigConv = ADC_EXTERNALTRIGCONV_Ext_IT11;
            break;
        default:
            ExternalTrigConv = ADC_SOFTWARE_START;
            break;
    }
    return ExternalTrigConv;
}

static bool adc_compose_init(const AdcConfig_t* const Config, ADC_InitTypeDef* const pInit) {
    bool res = false;
    if(pInit) {
        pInit->NbrOfConversion = Config->num_of_conversion;
        pInit->ScanConvMode = AdcScanModeToStmScanMode(Config->num_of_conversion);
        pInit->DMAContinuousRequests = AdcDmaModeToStmDmaMode(Config->move_mode)   ;
        pInit->ExternalTrigConv = AdcExternalTriggerSourceToExternalTrigConv(Config->trigger_source);

        /* Specifies whether the conversion is performed in single mode (one conversion) or continuous mode for regular group,
           after the selected trigger occurred (software start or external trigger).
           This parameter can be set to ENABLE or DISABLE. */
        pInit->ContinuousConvMode = DISABLE;
        pInit->DataAlign = ADC_DATAALIGN_RIGHT;
        pInit->Resolution = AdcResolution2code(Config->resolution);
        pInit->ClockPrescaler = ADC_CLOCK_SYNC_PCLK_DIV2;
        pInit->ExternalTrigConvEdge = ADC_EXTERNALTRIGCONVEDGE_RISING;
        //--

        pInit->NbrOfDiscConversion = 1;
        pInit->DiscontinuousConvMode = DISABLE;
        pInit->EOCSelection = ADC_EOC_SEQ_CONV;
        res = true;
    }
    return res;
}

static bool adc_start_ll(AdcHandle_t* Node) {
    bool res = false;
    HAL_StatusTypeDef ret;
    ret = HAL_ERROR;
    res = false;
    if (Node->RxSamples) {
        if (Node->RxSamplesCnt) {
            ret = HAL_ADC_Start_DMA(&Node->adc_h, (uint32_t*) Node->RxSamples, Node->RxSamplesCnt);
            res = HAL_retToRes(ret);
        }
    }
    // ret = HAL_ADC_Start(&Node->adc_h);
    if (res) {
        LOG_INFO(LG_ADC, "ADC%u,StartOk", Node->num);
    } else {
        LOG_ERROR(LG_ADC, "ADC%u,StartErr", Node->num);
    }

    return res;
}

uint8_t ADC_HandleTypeDefToNum(const ADC_HandleTypeDef* const hadc) {
    uint8_t adc_num = 0xFF;
    if(ADC1==hadc->Instance){
        adc_num = 1;
    }

    if(ADC2==hadc->Instance){
        adc_num = 2;
    }

    if(ADC3==hadc->Instance){
        adc_num = 3;
    }

    return adc_num;
}

bool adc_start(uint8_t num) {
    bool res = false;
    AdcHandle_t* Node = AdcGetNode(num);
    if (Node) {
        res = adc_start_ll(Node);
    }
    return res;
}

bool adc_interrupt_ctrl(uint8_t adc_num, bool on_off) {
    bool res = false;
    AdcInfo_t* Info = AdcGetInfo(adc_num);
    if(Info) {
        res = interrupt_control(Info->irq_n, on_off);
    }
    return res;
}

bool adc_init_one(uint8_t adc_num) {
    LOG_INFO(LG_ADC, "ADC%u,Init", adc_num);
    bool res = false;
    const AdcConfig_t* Config = AdcGetConfig(adc_num);
    res = AdcIsValidConfig(Config);
    if(res) {
        AdcHandle_t* Node = AdcGetNode(adc_num);
        if(Node) {
            res = adc_init_common(Config, Node);
            Node->adc_h.Instance = AdcGetInstance(Config->num);
            res = adc_compose_init(Config, &Node->adc_h.Init);
            HAL_StatusTypeDef ret;
            ret = HAL_ADC_Init(&Node->adc_h);
            res = HAL_retToRes(ret);
            res = adc_interrupt_ctrl(adc_num, Config->interrupt_on);
            log_info_res(LG_ADC, res, "Init");

#ifdef HAS_IQUEUE
            if(Config->SampleFifoMemCnt) {
                if(Config->SampleFifoMem) {
                    i_status status = iqueue_init(&Node->iQueue,
                                                  Config->SampleFifoMemCnt,
                                                  sizeof(uint16_t),
                                                  Config->SampleFifoMem);
                    res = iqueue_ret_res(status);
                }
            }
#endif
            Node->init_done = true;
        } else {
            LOG_ERROR(LG_ADC, "ADC%u,ConfigErr", adc_num);
        }
    } else {
        LOG_ERROR(LG_ADC, "ADC%u,NodeErr", adc_num);
    }
    return res;
}

bool adc_wait_conv_done_ll(AdcHandle_t* Node, uint32_t time_out_ms) {
    uint32_t cnt = 0;
    bool res = true;
    uint32_t cur_time_ms = 0;
    uint32_t init_time_ms = time_get_ms32();
    uint32_t diff_time_ms = 0;
    while(false == Node->conv_done) {
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

void HAL_ADC_MspInit(ADC_HandleTypeDef* adcHandle) {
#ifdef HAS_ADC1
    if(ADC1 == adcHandle->Instance) {
        __HAL_RCC_ADC1_CLK_ENABLE();
        // HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        // HAL_NVIC_EnableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC2
    if(ADC2 == adcHandle->Instance) {
        __HAL_RCC_ADC2_CLK_ENABLE();
        // HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        // HAL_NVIC_EnableIRQ(ADC_IRQn);
    }
#endif

#ifdef HAS_ADC3
    if(ADC3 == adcHandle->Instance) {
        __HAL_RCC_ADC3_CLK_ENABLE();
        // HAL_NVIC_SetPriority(ADC_IRQn, 4, 4);
        // HAL_NVIC_EnableIRQ(ADC_IRQn);
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

AdcHandle_t* AdcHalHandle2Handle(const ADC_HandleTypeDef* const hadc) {
    AdcHandle_t* Node = NULL;
    uint8_t adc_num = AdcInstance2Num(hadc->Instance);
    Node = AdcGetNode(adc_num);
    return Node;
}
