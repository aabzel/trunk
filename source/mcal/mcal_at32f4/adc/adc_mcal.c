#include "adc_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include "adc_custom_diag.h"
#include "adc_custom_types.h"
#include "artery_at32f4xx.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#include "utils_math.h"

#define ADC_CHANNEL_INFO(ADC_NUM, ADC_CHANNEL_X, ADC_CHAN_X, PORT_X, PIN_X)                                            \
    {                                                                                                                  \
        .valid = true,                                                                                                 \
        .adc_num = ADC_NUM,                                                                                            \
        .artery_channel = ADC_CHANNEL_X,                                                                               \
        .channel = ADC_CHAN_X,                                                                                         \
        .pad =                                                                                                         \
            {                                                                                                          \
                .port = PORT_X,                                                                                        \
                .pin = PIN_X,                                                                                          \
            },                                                                                                         \
    },

#define ADC1_CHANNEL_INFO_ALL                                                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_0, ADC_CHAN_0, PORT_A, 0)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_1, ADC_CHAN_1, PORT_A, 1)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_2, ADC_CHAN_2, PORT_A, 2)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_3, ADC_CHAN_3, PORT_A, 3)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_4, ADC_CHAN_4, PORT_A, 4)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_5, ADC_CHAN_5, PORT_A, 5)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_6, ADC_CHAN_6, PORT_A, 6)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_7, ADC_CHAN_7, PORT_A, 7)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_8, ADC_CHAN_8, PORT_B, 0)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_9, ADC_CHAN_9, PORT_B, 1)                                                          \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_10, ADC_CHAN_10, PORT_C, 0)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_11, ADC_CHAN_11, PORT_C, 1)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_12, ADC_CHAN_12, PORT_C, 2)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_13, ADC_CHAN_13, PORT_C, 3)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_14, ADC_CHAN_14, PORT_C, 4)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_15, ADC_CHAN_15, PORT_C, 5)                                                        \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_16, ADC_CHAN_16, 0, 0) /*Temp*/                                                    \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_17, ADC_CHAN_17, 0, 0) /*IntRef*/                                                  \
    ADC_CHANNEL_INFO(1, ADC_CHANNEL_18, ADC_CHAN_18, 0, 0) /*Vbat monitor*/

#define ADC2_CHANNEL_INFO_ALL                                                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_0, ADC_CHAN_0, PORT_A, 0)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_1, ADC_CHAN_1, PORT_A, 1)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_2, ADC_CHAN_2, PORT_A, 2)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_3, ADC_CHAN_3, PORT_A, 3)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_4, ADC_CHAN_4, PORT_A, 4)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_5, ADC_CHAN_5, PORT_A, 5)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_6, ADC_CHAN_6, PORT_A, 6)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_7, ADC_CHAN_7, PORT_A, 7)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_8, ADC_CHAN_8, PORT_B, 0)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_9, ADC_CHAN_9, PORT_B, 1)                                                          \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_10, ADC_CHAN_10, PORT_C, 0)                                                        \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_11, ADC_CHAN_11, PORT_C, 1)                                                        \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_12, ADC_CHAN_12, PORT_C, 2)                                                        \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_14, ADC_CHAN_14, PORT_C, 3)                                                        \
    ADC_CHANNEL_INFO(2, ADC_CHANNEL_15, ADC_CHAN_15, PORT_C, 5)

#define ADC3_CHANNEL_INFO_ALL                                                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_0, ADC_CHAN_0, PORT_A, 0)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_1, ADC_CHAN_1, PORT_A, 1)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_2, ADC_CHAN_2, PORT_A, 2)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_3, ADC_CHAN_3, PORT_A, 3)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_4, ADC_CHAN_4, PORT_F, 6)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_5, ADC_CHAN_5, PORT_F, 7)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_6, ADC_CHAN_6, PORT_F, 8)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_7, ADC_CHAN_7, PORT_F, 9)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_8, ADC_CHAN_8, PORT_F, 10)                                                         \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_9, ADC_CHAN_9, PORT_F, 3)                                                          \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_10, ADC_CHAN_10, PORT_C, 0)                                                        \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_11, ADC_CHAN_11, PORT_C, 1)                                                        \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_12, ADC_CHAN_12, PORT_C, 2)                                                        \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_13, ADC_CHAN_13, PORT_C, 3)                                                        \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_14, ADC_CHAN_14, PORT_F, 4)                                                        \
    ADC_CHANNEL_INFO(3, ADC_CHANNEL_15, ADC_CHAN_15, PORT_F, 5)

#define ADC_CHANNEL_INFO_ALL                                                                                           \
    ADC1_CHANNEL_INFO_ALL                                                                                              \
    ADC2_CHANNEL_INFO_ALL                                                                                              \
    ADC3_CHANNEL_INFO_ALL

static const AdcChannelInfo_t AdcChannelInfo[] = {ADC_CHANNEL_INFO_ALL};

#if 0
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
#endif

static const AdcInfo_t AdcInfo[] = {
#ifdef HAS_ADC1
    {
        .ADCx = ADC1,
        .adc_num = 1,
        .valid = true,
        .clock_type = CRM_ADC1_PERIPH_CLOCK,
    },
#endif

#ifdef HAS_ADC2
    {
        .ADCx = ADC2,
        .adc_num = 2,
        .valid = true,
        .clock_type = CRM_ADC2_PERIPH_CLOCK,
    },
#endif

#ifdef HAS_ADC3
    {
        .ADCx = ADC3,
        .adc_num = 3,
        .valid = true,
        .clock_type = CRM_ADC3_PERIPH_CLOCK,
    },
#endif
};

const AdcInfo_t* AdcGetInfo(uint8_t adc_num) {
    AdcInfo_t* Info = NULL;
    uint8_t cnt = ARRAY_SIZE(AdcInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(AdcInfo[i].valid) {
            if(adc_num == AdcInfo[i].adc_num) {
                Info = &AdcInfo[i];
            }
        }
    }
    return Info;
}

const AdcChannelInfo_t* AdcChannelToInfo(uint8_t adc_num, AdcChannel_t channel) {
    AdcChannelInfo_t* ChannelInfo = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].channel == channel) {
            if(adc_num == AdcChannelInfo[i].adc_num) {
                ChannelInfo = &AdcChannelInfo[i];
                break;
            }
        }
    }
    return ChannelInfo;
}

bool adc_init_channel(uint8_t adc_num, AdcChannel_t channel) {
    LOG_DEBUG(LG_ADC, "InitAdc %u Channel %u", adc_num, channel);
    bool res = false;

    return res;
}
#if 0
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
#endif

bool adc_init_custom(void) {
    bool res = true;
    LOG_WARNING(LG_ADC, "ArteryADCInit");
    adc_common_config_type adc_common_struct = {0};
    nvic_irq_enable(ADC1_2_3_IRQn, 2, 2);

    adc_common_default_para_init(&adc_common_struct);

    /* config combine mode */
    adc_common_struct.combine_mode = ADC_INDEPENDENT_MODE;

    /* config division,adcclk is division by hclk */
    adc_common_struct.div = ADC_HCLK_DIV_4;

    /* config common dma mode,it's not useful in independent mode */
    adc_common_struct.common_dma_mode = ADC_COMMON_DMAMODE_DISABLE;

    /* config common dma request repeat */
    adc_common_struct.common_dma_request_repeat_state = FALSE;

    /* config adjacent adc sampling interval,it's useful for ordinary shifting mode */
    adc_common_struct.sampling_interval = ADC_SAMPLING_INTERVAL_5CYCLES;

    /* config inner temperature sensor and vintrv */
    adc_common_struct.tempervintrv_state = FALSE;

    /* config voltage battery */
    adc_common_struct.vbat_state = FALSE;
    adc_common_config(&adc_common_struct);
    res = true;

    log_level_get_set(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

static adc_resolution_type AdcResolutionToArteryResol(AdcResolution_t resolution) {
    adc_resolution_type artery_resol = ADC_RESOLUTION_12B;
    switch((uint32_t)resolution) {
    case ADC_RESOLUTION_6BIT:
        artery_resol = ADC_RESOLUTION_6B;
        break;
    case ADC_RESOLUTION_8BIT:
        artery_resol = ADC_RESOLUTION_8B;
        break;
    case ADC_RESOLUTION_10BIT:
        artery_resol = ADC_RESOLUTION_10B;
        break;
    case ADC_RESOLUTION_12BIT:
        artery_resol = ADC_RESOLUTION_12B;
        break;
    case ADC_RESOLUTION_14BIT:
        artery_resol = ADC_RESOLUTION_12B;
        break;
    default:
        artery_resol = ADC_RESOLUTION_12B;
        break;
    }
    return artery_resol;
}

bool adc_init_one(uint8_t num) {
    LOG_WARNING(LG_ADC, "Init ADC%u", num);
    bool res = false;
    const AdcConfig_t* Config = AdcGetConfig(num);
    if(Config) {
        LOG_WARNING(LG_ADC, "%s", AdcConfigToStr(Config));
        AdcHandle_t* Node = AdcGetNode(num);
        if(Node) {
            Node->resolution = Config->resolution;
            Node->v_ref_voltage = Config->v_ref_voltage;
            Node->is_idle = true;
            const AdcInfo_t* Info = AdcGetInfo(num);
            if(Info) {
                LOG_WARNING(LG_ADC, "ADC%u SpotInfo", num);
                Node->ADCx = Info->ADCx;

                crm_periph_clock_enable(Info->clock_type, TRUE);

                adc_base_config_type AdcBaseConfig = {0};

                adc_base_default_para_init(&AdcBaseConfig);

                AdcBaseConfig.sequence_mode = FALSE; //!!
                AdcBaseConfig.repeat_mode = FALSE;
                AdcBaseConfig.data_align = ADC_RIGHT_ALIGNMENT;
                AdcBaseConfig.ordinary_channel_length = 3;

                adc_base_config(Info->ADCx, &AdcBaseConfig);

                Node->max_code = ipow(2, Config->resolution) - 1;
                adc_resolution_set(Info->ADCx, AdcResolutionToArteryResol(Config->resolution));

                /* config ordinary trigger source and trigger edge */
                adc_ordinary_conversion_trigger_set(Info->ADCx, ADC_ORDINARY_TRIG_TMR1CH1, ADC_ORDINARY_TRIG_EDGE_NONE);

                /* config dma mode,it's not useful when common dma mode is use */
                adc_dma_mode_enable(Info->ADCx, FALSE);

                /* config dma request repeat,it's not useful when common dma mode is use */
                adc_dma_request_repeat_enable(Info->ADCx, FALSE);

                /* each ordinary channel conversion set occe flag */
                adc_occe_each_conversion_enable(Info->ADCx, TRUE);

                /* enable adc overflow interrupt */
                adc_interrupt_enable(Info->ADCx, ADC_OCCO_INT, TRUE);

                /* enable voltage monitoring out of range interrupt */
                adc_interrupt_enable(Info->ADCx, ADC_VMOR_INT, TRUE);

                /*!< preempt channels conversion end interrupt */
                adc_interrupt_enable(Info->ADCx, ADC_PCCE_INT, TRUE);

                /*!< ordinary channels conversion end interrupt */
                adc_interrupt_enable(Info->ADCx, ADC_OCCE_INT, TRUE);

                adc_enable(Info->ADCx, TRUE);
                while(adc_flag_get(Info->ADCx, ADC_RDY_FLAG) == RESET) {
                }

                /* adc calibration */
                adc_calibration_init(Info->ADCx);
                while(adc_calibration_init_status_get(Info->ADCx)) {
                }

                adc_calibration_start(Info->ADCx);
                while(adc_calibration_status_get(Info->ADCx)) {
                }

                adc_ordinary_software_trigger_enable(Node->ADCx, TRUE);
                res = true;
                LOG_INFO(LG_ADC, "ADC%u Start", num);

                LOG_WARNING(LG_ADC, "%s", AdcNodeToStr(Node));
                Node->init_done = true;
                log_level_get_set(LG_ADC, LOG_LEVEL_INFO);
            } else {
                LOG_ERROR(LG_ADC, "ADC%u InfoErr", num);
                res = false;
            }
            LOG_INFO(LG_ADC, "%s", AdcNodeToStr(Node));

        } else {
            LOG_ERROR(LG_ADC, "ADC%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(LG_ADC, "ADC%u ConfigErr", num);
        res = true;
    }
    log_level_get_set(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

static adc_channel_select_type AdcChannelToArteryChannel(AdcChannel_t channel) {
    adc_channel_select_type artery_channel = ADC_CHANNEL_4;

    const AdcChannelInfo_t* ChannelInfo = AdcChannelToInfo(1, channel);
    if(ChannelInfo) {
        artery_channel = ChannelInfo->artery_channel;
    }

    return artery_channel;
}

bool adc_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_ADC, "InitChannel %u", num);

    const AdcChannelConfig_t* Config = AdcChannelGetConfig(num);
    if(Config) {
        LOG_WARNING(LG_ADC, "%s", AdcChannelConfigToStr(Config));
        AdcChannelHandle_t* Node = AdcChannelGetNode(num);
        if(Node) {
            res = adc_channel_init_node(Config, Node);
            log_level_get_set(LG_ADC, LOG_LEVEL_INFO);
        } else {
            LOG_ERROR(LG_ADC, "ChNodeErr");
        }
    }

    return res;
}

static bool adc_channel_start(uint8_t adc_num, uint16_t channel) {
    bool res = false;
    const AdcChannelConfig_t* Config = AdcChannelGetConfigV2(adc_num, channel);
    if(Config) {
        AdcHandle_t* Node = AdcGetNode(adc_num);
        if(Node) {
            if(Node->fetch_done) {
                Node->fetch_done = false;
                Node->chan_conv_end = false;
                adc_channel_select_type artery_channel = AdcChannelToArteryChannel(channel);
                adc_ordinary_channel_set(Node->ADCx, artery_channel, 1, ADC_SAMPLETIME_47_5);
                adc_ordinary_software_trigger_enable(Node->ADCx, TRUE);
                Node->channel_cur = channel;
                res = true;
            } else {
                res = true;
            }
        }
    }
    return res;
}

bool adc_channel_proc(void) {
    static uint8_t i = 0;
    bool res = false;
    uint32_t channel_cnt = adc_channel_get_cnt();
    uint8_t num = 1 + i % (channel_cnt);
    AdcChannelHandle_t* Node = AdcChannelGetNode(num);
    if(Node) {
        res = adc_channel_start(Node->adc_num, Node->channel);
        if(res) {
            Node->is_reading = true;
            LOG_DEBUG(LG_ADC, "%u,Proc,ADC%u_CH%u", Node->spin_cnt, Node->adc_num, Node->channel);
            AdcHandle_t* AdcNode = AdcGetNode(Node->adc_num);
            if(AdcNode) {
                AdcNode->cur_channel_node = num;
            }
            res = true;
            Node->spin_cnt++;
        } else {
            Node->err_cnt++;
            LOG_WARNING(LG_ADC, "StartErr,ADC%u_Ch%u", Node->adc_num, Node->channel);
            res = false;
        }
    } else {
        LOG_ERROR(LG_ADC, "%u ChNodeErr", num);
    }
    i++;
    return res;
}

double adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t channel) { return 0.0; }

void AdcConvCpltCallback(AdcHandle_t* Node) {
    if(Node) {
        Node->conv_done = true;
        Node->it_cnt++;
    }
}

AdcChannel_t AdcPad2Channel(Pad_t pad) {
    AdcChannel_t chan_num = ADC_CHAN_UNDEF;
    //  uint32_t code = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].pad.byte == pad.byte) {
            chan_num = AdcChannelInfo[i].channel;
            break;
        }
    }
    return chan_num;
}

static AdcNum_t AdcPad2AdcNum(Pad_t pad) {
    AdcNum_t adc_num = ADC_UNDEF;
    // uint32_t code = 0;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].pad.byte == pad.byte) {
            adc_num = AdcChannelInfo[i].adc_num;
            break;
        }
    }
    return adc_num;
}

static double AdcCode2Voltage(int32_t code) {
    double voltage_v = 0.0;
    voltage_v = (CROSS_CODE_VOLTAGE * ((double)code));
    return voltage_v;
}

bool adc_channel_read(uint8_t adc_num, uint16_t adc_channel, uint32_t* code) {
    bool res = false;
    return res;
}

bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t channel, double* const voltage) {
    bool res = false;
    LOG_DEBUG(LG_ADC, "Read Adc:%u Ch:%u", adc_num, channel);
    uint32_t code = 0;
    double val = 0.0;
    res = adc_channel_read(adc_num, channel, &code);
    if(res) {
        val = AdcCode2Voltage(code);
        LOG_PARN(LG_ADC, "ADC%u CH%u Code:%u=0x%x ->%f V", adc_num, channel, code, code, val);
        (*voltage) = val;
    }
    return res;
}

bool adc_pad_read_voltage(Pad_t pad, double* const voltage) {
    bool res = false;
    AdcChannel_t channel = AdcPad2Channel(pad);
    AdcNum_t adc_num = AdcPad2AdcNum(pad);
    res = adc_channel_read_voltage(adc_num, channel, voltage);
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

bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t channel, int32_t* const code) { return false; }

bool adc_channel_init_custom(void) { return true; }

bool adc_set_vref(uint8_t adc_num, double v_ref_voltage) { return false; }

bool adc_proc_one(uint8_t num) {
    bool res = false;
    const AdcConfig_t* Config = AdcGetConfig(num);
    if(Config) {
        AdcHandle_t* Node = AdcGetNode(num);
        if(Node) {
            LOG_DEBUG(LG_ADC, "p:%u,ADC%u Proc", Node->spin_cnt, num);

#if 0
            flag_status ret = 0;
            ret = adc_flag_get(Node->ADCx, ADC_OCCE_FLAG);
            if(SET==ret) {
                Node->data_word = adc_ordinary_conversion_data_get(Node->ADCx);
                LOG_NOTICE(LG_ADC, "ADC%u Code:%u", num, Node->data_word );
                adc_ordinary_software_trigger_enable(Node->ADCx, TRUE);
                res = true;
            }
#endif
            if(Node->it) {
                Node->it = false;
                LOG_DEBUG(LG_ADC, "ADC%u,ISR,Proc", num);
                /*Is ordinary channels conversion end ?*/
                if(Node->data_valid) {
                    Node->code = adc_ordinary_conversion_data_get(Node->ADCx);
                    LOG_PARN(LG_ADC, "ADC%u:Channel:%u,Code:%u", num, Node->channel_cur, Node->code);
                    AdcChannelHandle_t* ChNode = AdcChannelGetNodeV2(num, Node->channel_cur);
                    if(ChNode) {
                        ChNode->code = Node->code;
                        if(Node->max_code) {
                            ChNode->new_val = true;
                            ChNode->voltage = ((double)ChNode->code) * Config->v_ref_voltage / ((double)Node->max_code);
                            ChNode->voltage_real = ChNode->voltage * ChNode->scale;
                        }
                    }

                    Node->data_valid = false;
                    Node->is_idle = true;
                    Node->fetch_done = true;
                    res = true;
                }
            }
            /* adc1 software trigger start conversion */
            Node->spin_cnt++;
        } else {
            LOG_ERROR(LG_ADC, "ADC%u,NodeErr", num);
        }
    }
    return res;
}

bool adc_start(uint8_t num) {
    bool res = false;
    const AdcInfo_t* Info = AdcGetInfo(num);
    if(Info) {
        adc_ordinary_software_trigger_enable(Info->ADCx, TRUE);
        res = true;
    }
    return res;
}
