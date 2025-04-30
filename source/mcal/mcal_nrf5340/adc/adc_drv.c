#include "adc_drv.h"

#include "adc_diag.h"
#ifdef HAS_ADC_ISR
#include "adc_isr.h"
#endif
#include "adc_custom_types.h"
#include "clock.h"
#include "data_utils.h"
#include "debug_info.h"
#include "gpio_diag.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_saadc.h"
#include "time_mcal.h"
#include "utils_math.h"

#ifndef NRFX_SAADC_ENABLED
#error "+NRFX_SAADC_ENABLED"
#endif /*NRFX_SAADC_ENABLED*/

static const AdcRefInfo_t AdcRefInfo[] = {
    {
        .ref_nrf = NRF_SAADC_REFERENCE_INTERNAL,
        .volt = 0.6,
    },
    {
        .ref_nrf = NRF_SAADC_REFERENCE_VDD4, .volt = 0.825, /*3.3 / 4.0   */
    },
};

static const AdcChannelStaticInfo_t AdcChannelInfo[] = {
    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 4,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN0,
     .adc_channel = ADC_CHAN_0},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 5,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN1,
     .adc_channel = ADC_CHAN_1},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 6,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN2,
     .adc_channel = ADC_CHAN_2},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 7,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN3,
     .adc_channel = ADC_CHAN_3},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 25,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN4,
     .adc_channel = ADC_CHAN_4},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 26,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN5,
     .adc_channel = ADC_CHAN_5},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 27,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN6,
     .adc_channel = ADC_CHAN_6},

    {.valid = true,
     .pad =
         {
             .port = 0,
             .pin = 28,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_AIN7,
     .adc_channel = ADC_CHAN_7},

    {.valid = true,
     .pad =
         {
             .port = 2,
             .pin = 0,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_VDD,
     .adc_channel = ADC_CHAN_8},

    {.valid = true,
     .pad =
         {
             .port = 2,
             .pin = 0,
         },
     .adc_channel_nrf = NRF_SAADC_INPUT_VDDHDIV5,
     .adc_channel = ADC_CHAN_9},
};

static const AdcResolutionInfo_t AdcResolutionInfo[] = {
    {
        .resolution_nrf = NRF_SAADC_RESOLUTION_8BIT,
        .resolution = 8,
    },
    {
        .resolution_nrf = NRF_SAADC_RESOLUTION_10BIT,
        .resolution = 10,
    },
    {
        .resolution_nrf = NRF_SAADC_RESOLUTION_12BIT,
        .resolution = 12,
    },
    {
        .resolution_nrf = NRF_SAADC_RESOLUTION_14BIT,
        .resolution = 14,
    },
};

static const AdcGainInfo_t AdcGainInfo[] = {
    {
        .gain_nrf = NRF_SAADC_GAIN1_6,
        .gain = 1.0 / 6.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN1_5,
        .gain = 1.0 / 5.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN1_4,
        .gain = 1.0 / 4.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN1_3,
        .gain = 1.0 / 3.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN1_2,
        .gain = 1.0 / 2.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN1,
        .gain = 1.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN2,
        .gain = 2.0,
    },
    {
        .gain_nrf = NRF_SAADC_GAIN4,
        .gain = 4.0,
    },
};

static const double NrfRefCode2RefVoltage(nrf_saadc_reference_t ref) {
    double value = 0;
    uint32_t cnt = ARRAY_SIZE(AdcRefInfo);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        if(AdcRefInfo[i].ref_nrf == ref) {
            value = AdcRefInfo[i].volt;
            break;
        }
    }
    return value;
}

static const AdcResolutionInfo_t* AdcGetResolutionInfo(uint8_t resolution) {
    const AdcResolutionInfo_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcResolutionInfo); i++) {
        if(AdcResolutionInfo[i].resolution == resolution) {
            Node = &AdcResolutionInfo[i];
            break;
        }
    }
    return Node;
}

static const double NrfGainCode2Value(nrf_saadc_gain_t gain) {
    double value = 0;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(AdcGainInfo);
    for(i = 0; i < cnt; i++) {
        if(AdcGainInfo[i].gain_nrf == gain) {
            value = AdcGainInfo[i].gain;
            break;
        }
    }
    return value;
}

uint32_t AdcResol2MaxValue(uint8_t resolution) {
    uint32_t value = 0;
    value = (uint32_t)int_pow(2, resolution);
    return value;
}

static const nrf_saadc_input_t AdcChannel2HalChan(AdcChannel_t adc_channel) {
    nrf_saadc_input_t nrf_channel = NRF_SAADC_INPUT_DISABLED;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].adc_channel == adc_channel) {
            nrf_channel = AdcChannelInfo[i].adc_channel_nrf;
            break;
        }
    }
    return nrf_channel;
}

static const nrf_saadc_resolution_t AdcResolution2NrfxResolCode(uint8_t resolution) {
    nrf_saadc_resolution_t res_code = NRF_SAADC_RESOLUTION_12BIT;
    const AdcResolutionInfo_t* Node = AdcGetResolutionInfo(resolution);
    if(Node) {
        res_code = Node->resolution_nrf;
    }

    return res_code;
}

static nrfx_saadc_channel_t AdcConfig2NrfAdcConfig(const AdcChannelConfig_t* const AdcChannelConfig,
                                                   AdcChannel_t adc_channel, uint8_t cfg_num) {
    nrfx_saadc_channel_t ch_cfg = {0};
    if(AdcChannelConfig) {
        ch_cfg.channel_config.resistor_p = NRF_SAADC_RESISTOR_DISABLED;
        ch_cfg.channel_config.resistor_n = NRF_SAADC_RESISTOR_DISABLED;
        ch_cfg.channel_config.gain = NRF_SAADC_GAIN1_6;
        ch_cfg.channel_config.reference = NRF_SAADC_REFERENCE_INTERNAL;
        ch_cfg.channel_config.acq_time = NRF_SAADC_ACQTIME_10US;
        ch_cfg.channel_config.mode = NRF_SAADC_MODE_SINGLE_ENDED;
        ch_cfg.channel_config.burst = NRF_SAADC_BURST_DISABLED;
        ch_cfg.pin_p = AdcChannel2HalChan(AdcChannelConfig->channel);
        ch_cfg.pin_n = NRF_SAADC_INPUT_DISABLED;
        ch_cfg.channel_index = cfg_num;
    }
    return ch_cfg;
}

bool adc_init_channel(AdcNum_t adc_num, AdcChannel_t adc_channel, uint8_t cfg_num) {
    cli_printf(CRLF);
    LOG_WARNING(LG_ADC, "ADC %u Chan %u Set", adc_num, adc_channel);
    bool res = false;

    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        const AdcChannelConfig_t* AdcChannelConfig = AdcChannelGetConfigNode(adc_num, adc_channel);
        if(AdcChannelConfig) {
            nrfx_saadc_channel_t ChanCfg = AdcConfig2NrfAdcConfig(AdcChannelConfig, adc_channel, cfg_num);
            AdcNode->ch_cfgs[cfg_num] = ChanCfg;

            AdcChannelHandle_t* AdcChannelNode = AdcChannelGetNode(adc_num, adc_channel);
            if(AdcChannelNode) {
                double ref_voltage = NrfRefCode2RefVoltage(ChanCfg.channel_config.reference);
                LOG_INFO(LG_ADC, "Ch%u RefVoltage %f", adc_channel, ref_voltage);
                double gain = NrfGainCode2Value(ChanCfg.channel_config.gain);
                LOG_INFO(LG_ADC, "Ch%u Gain %f", adc_channel, gain);
                if(0.001 < gain) {
                    AdcChannelNode->gained_ref_voltage = (ref_voltage / gain);
                    LOG_INFO(LG_ADC, "Ch%u GainedRefVoltage %f", adc_channel, AdcChannelNode->gained_ref_voltage);
                    AdcChannelNode->code_to_volt_factor = (AdcChannelNode->gained_ref_voltage / AdcNode->ref_code);
                    LOG_INFO(LG_ADC, "Ch%u Code2Voltage factor %f", adc_channel, AdcChannelNode->code_to_volt_factor);

                    AdcChannelNode->volts = (ref_voltage / gain);
                    LOG_INFO(LG_ADC, "Ch%u GainedVoltage %f", adc_channel, AdcChannelNode->volts);
                    res = true;
                }
            } else {
                LOG_ERROR(LG_ADC, "ADC%u Chan %u AdcChanNodeErr", adc_num, adc_channel);
            }
        } else {
            LOG_ERROR(LG_ADC, "ADC%u Chan %u AdcChanNodeErr", adc_num, adc_channel);
        }
    } else {
        LOG_ERROR(LG_ADC, "ADC%u NodeErr", adc_num);
    }
    return res;
}

static bool adc_do_conversion(AdcNum_t adc_num) {
    LOG_DEBUG(LG_ADC, "Conv ADC%u", adc_num);
    bool res = false;
    nrfx_err_t ret = NRFX_ERROR_INTERNAL;

    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        AdcNode->conv_done = false;
        ret = nrfx_saadc_mode_trigger();
        if(NRFX_SUCCESS == ret) {
#ifdef HAS_ADC_ISR
            res = adc_wait_convert_done(AdcNode, ADC_CONV_DONE_TIME_OUT_MS);
#else
            res = wait_ms(ADC_CONV_MAX_TIME_MS);
#endif
            if(false == res) {
                LOG_DEBUG(LG_ADC, "%u TimeOut", adc_num);
                AdcNode->err_cnt++;
            }
        } else {
            LOG_ERROR(LG_ADC, "ADC%u StartErr %u=%s", adc_num, ret, HalStatus2Str(ret));
        }
    } else {
        LOG_ERROR(LG_ADC, "ADC%u NodeErr", adc_num);
    }
    return res;
}

static bool adc_channels_init(AdcNum_t adc_num) {
    bool res = false;
    LOG_WARNING(LG_ADC, "ChannelsInit");
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    const AdcConfig_t* AdcConfig = AdcGetConfigNode(adc_num);
    nrfx_err_t ret = NRFX_ERROR_INTERNAL;
    uint32_t channels_mask = 0;
    uint8_t chan_cnt = adc_channel_get_cnt();
    if(AdcNode && AdcConfig) {
        uint32_t ok_cnt = 0;
        LOG_INFO(LG_ADC, "Channels %u", chan_cnt);

#ifdef ADC_ADV_CFG
        AdcNode->adv_config.oversampling = NRF_SAADC_OVERSAMPLE_DISABLED;
        AdcNode->adv_config.burst = NRF_SAADC_BURST_DISABLED;
        AdcNode->adv_config.internal_timer_cc = 0;
        AdcNode->adv_config.start_on_end = false;
#endif

        uint8_t i = 0;
        for(i = 0; i < chan_cnt; i++) {
            AdcChannel_t chan = AdcChannelConfig[i].channel;
            AdcNode->ch_cfgs[i].channel_index = chan;
            LOG_INFO(LG_ADC, "chan=%u", chan);
            res = adc_init_channel(adc_num, chan, i);
            if(res) {
                ok_cnt++;
                SET_BIT_NUM(channels_mask, i);
                LOG_INFO(LG_ADC, "CH%u InitOk", chan);
            } else {
                LOG_ERROR(LG_ADC, "CH%u InitError", chan);
            }
        }

        if(ok_cnt == chan_cnt) {
            if(AdcNode) {
                ret = nrfx_saadc_channels_config(AdcNode->ch_cfgs, chan_cnt);
                if(NRFX_SUCCESS == ret) {
                    LOG_INFO(LG_ADC, "ChanCfg %u Ok", chan_cnt);
                    res = true;
                } else {
                    res = false;
                    LOG_ERROR(LG_ADC, "ChanCfgErr %u=%s", ret, HalStatus2Str(ret));
                }
            }
        }
    }

    if(res) {
        nrf_saadc_resolution_t resolution = AdcResolution2NrfxResolCode(AdcConfig->resolution);
#ifdef ADC_ADV_CFG
        ret = nrfx_saadc_advanced_mode_set(channels_mask, resolution, &AdcNode->adv_config, AdcNode->event_handler);
#else  /*ADC_ADV_CFG*/
        ret = nrfx_saadc_simple_mode_set(channels_mask, resolution, AdcNode->oversampling, AdcNode->event_handler);
#endif /*ADC_ADV_CFG*/
        if(NRFX_SUCCESS == ret) {
            res = true;
            LOG_INFO(LG_ADC, "Nrf mode set Ok");
        } else {
            res = false;
            LOG_ERROR(LG_ADC, "NrfxModeSetErr Ret: 0x%x=%s", ret, HalStatus2Str(ret));
        }
    }

    if(res) {
        ret = nrfx_saadc_buffer_set(AdcNode->samples, chan_cnt);
        if(NRFX_SUCCESS == ret) {
            res = true;
            LOG_INFO(LG_ADC, "BufSetOk");
        } else {
            res = false;
            LOG_ERROR(LG_ADC, "BufSetErr %u = %s", ret, HalStatus2Str(ret));
        }
    }
    return res;
}

static const uint8_t AdcChannel2SampleIndex(AdcNum_t adc_num, AdcChannel_t chan_num) {
    uint32_t ch_index = 0;
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        nrf_saadc_input_t nrf_saadc_input = AdcChannel2HalChan(chan_num);
        uint32_t i = 0;
        uint32_t ch_cnt = adc_channel_get_cnt();
        for(i = 0; i < ch_cnt; i++) {
            if(nrf_saadc_input == AdcNode->ch_cfgs[i].pin_p) {
                ch_index = AdcNode->ch_cfgs[i].channel_index;
                break;
            }
        }
    }
    return ch_index;
}

bool adc_is_valid_nrf_channel(AdcChannel_t chan_num) {
    bool res = false;
    if(ADC_CHAN_0 <= chan_num) {
        if(chan_num <= ADC_CHAN_7) {
            res = true;
        }
    }
    return res;
}

bool adc_is_valid_channel(AdcChannel_t chan_num) {
    bool res = false;
    uint32_t ch_cnt = adc_channel_get_cnt();
    uint32_t i = 0;
    for(i = 0; i < ch_cnt; i++) {
        if(AdcChannels[i].channel == chan_num) {
            if(AdcChannels[i].valid) {
                res = true;
                break;
            }
        }
    }
    return res;
}

bool adc_is_valid_num(AdcNum_t adc_num) {
    bool res = false;
    if(ADC_1 == adc_num) {
        res = true;
    }
    return res;
}

bool adc_channel_read_code(AdcNum_t adc_num, AdcChannel_t adc_channel, int32_t* const code) {
    bool res = true;
    LOG_DEBUG(LG_ADC, "Read ADC%u CH%u", adc_num, adc_channel);
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        res = adc_is_valid_channel(adc_channel);
        if(res) {
            uint8_t idx = AdcChannel2SampleIndex(adc_num, adc_channel);
            AdcNode->code = AdcNode->samples[idx];
            LOG_DEBUG(LG_ADC, "%d", AdcNode->code);
            if(code) {
                *code = AdcNode->code;
                AdcNode->read_cnt++;
            }
        } else {
            LOG_ERROR(LG_ADC, "CH%u Err", adc_channel);
        }
    } else {
        LOG_ERROR(LG_ADC, "%u NodeErr", adc_num);
    }
    return res;
}

double AdcCode2Voltage_v0(AdcNum_t adc_num, AdcChannel_t chan_num, int32_t code) {
    double voltage_v = 0.0;
    /*TODO to figure out*/
    AdcHandle_t* AdcNode = AdcGetNode(1);
    if(AdcNode) {

        // voltage_v = (double)(ADC_REF_VOLTAGE * ((double)code)) / ((double)MAX_VALUE_12BIT);
        voltage_v = ((AdcNode->v_ref_voltage / AdcNode->code_at_vref) * ((double)code));
    }
    return voltage_v;
}

double AdcCode2Voltage(AdcNum_t adc_num, AdcChannel_t chan_num, int32_t code) {
    double voltage_v = 0.0;
    AdcChannelHandle_t* AdcChannelNode = AdcChannelGetNode(adc_num, chan_num);
    if(AdcChannelNode) {
        voltage_v = AdcChannelNode->code_to_volt_factor * ((double)code);
    }
    return voltage_v;
}

uint32_t AdcCode2mV(AdcNum_t adc_num, AdcChannel_t chan_num, int32_t code) {
    uint32_t mvoltage_mv = 0;
    AdcChannelHandle_t* AdcChannelNode = AdcChannelGetNode(adc_num, chan_num);
    mvoltage_mv = (uint32_t)(AdcChannelNode->volts * code / MAX_VALUE_12BIT);
    return mvoltage_mv;
}

bool adc_proc(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = 0;
    uint32_t ch_cnt = adc_channel_get_cnt();
    LOG_DEBUG(LG_ADC, "Proc Cnt: %u", ch_cnt);
    if(ch_cnt) {
        res = adc_do_conversion(1);
        if(res) {
            for(i = 0; i < ch_cnt; i++) {
                res = adc_channel_read_code(AdcChannels[i].num, AdcChannels[i].channel, &AdcChannels[i].code);
                if(res) {
                    AdcChannels[i].read_cnt++;
                    cnt++;
                } else {
                    AdcChannels[i].err_cnt++;
                    LOG_ERROR(LG_ADC, "Read CH%u Err", AdcChannels[i].channel);
                }
            }

            if(cnt == ch_cnt) {
                res = true;
            } else {
                res = false;
            }
        }
    }
    return res;
}

static bool adc_init_channels_cache(void) {
    bool res = false;
    uint32_t cnt = adc_channel_get_cnt();
    LOG_INFO(LG_ADC, "InitCache %u entry", cnt);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        AdcChannels[i].num = AdcChannelConfig[i].num;
        AdcChannels[i].channel = AdcChannelConfig[i].channel;
        AdcChannels[i].valid = true;
        AdcChannels[i].code = 0;
    }
    return res;
}

bool adc_set_vref(uint8_t adc_num, double v_ref_voltage) {
    bool res = false;
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        LOG_INFO(LG_ADC, "ADC%u Vref %f V", adc_num, v_ref_voltage);
        AdcNode->v_ref_voltage = v_ref_voltage;
        res = true;
    } else {
        LOG_ERROR(LG_ADC, "Node ADC%u lacks", adc_num);
    }
    return res;
}

bool adc_init(void) {
    LOG_WARNING(LG_ADC, "Init...");
    bool res = false;
    AdcHandle_t* AdcNode = AdcGetNode(1);
    if(AdcNode) {
        AdcNode->init_done = false;
        AdcNode->it_cnt = 0;
        res = adc_init_channels_cache();

        const AdcConfig_t* AdcConfigNode = AdcGetConfigNode(1);
        if(AdcConfigNode) {

            res = adc_set_vref(1, AdcConfigNode->v_ref_voltage);
            AdcNode->code_at_vref = AdcResol2MaxValue(AdcConfigNode->resolution);
            nrfx_err_t ret = NRFX_ERROR_NULL;
            ret = nrfx_saadc_init(AdcConfigNode->irq_priority);
            if(NRFX_SUCCESS == ret) {
                LOG_INFO(LG_ADC, "SarADCinitOk");
#ifdef HAS_ADC_ISR
                AdcNode->event_handler = (nrfx_saadc_event_handler_t)nrfx_saadc_event_handler;
#endif
                AdcNode->oversampling = NRF_SAADC_OVERSAMPLE_DISABLED;
                const AdcResolutionInfo_t* AdcResolutionInfo = AdcGetResolutionInfo(AdcConfig->resolution);
                if(AdcResolutionInfo) {
                    AdcNode->ref_code = AdcResol2MaxValue(AdcResolutionInfo->resolution);
                } else {
                    AdcNode->ref_code = MAX_VALUE_12BIT;
                }
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_ADC, "Nrfx_saadc_init Err");
            }
        } else {
            res = false;
            LOG_ERROR(LG_ADC, "%u ConfigErr", 1);
        }

    } else {
        res = false;
        LOG_ERROR(LG_ADC, "%u NodeErr", 1);
    }

    if(res) {
        res = adc_channels_init(1);
        if(res) {
            AdcNode->init_done = true;
            LOG_INFO(LG_ADC, "ChannelInitOk");
        } else {
            res = false;
            LOG_ERROR(LG_ADC, "ChannelInitErr");
        }
    }
    set_log_level(LG_ADC, LOG_LEVEL_INFO);
    return res;
}

const AdcChannelStaticInfo_t* AdcGetChannelInfo(AdcChannel_t adc_channel) {
    const AdcChannelStaticInfo_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].adc_channel == adc_channel) {
            Node = &AdcChannelInfo[i];
            break;
        }
    }
    return Node;
}

const AdcChannelStaticInfo_t* GpioPad2AdcChannelInfo(Pad_t pad) {
    const AdcChannelStaticInfo_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < ARRAY_SIZE(AdcChannelInfo); i++) {
        if(AdcChannelInfo[i].pad.byte == pad.byte) {
            Node = &AdcChannelInfo[i];
            break;
        }
    }
    return Node;
}

bool adc_channel_read_voltage(AdcNum_t adc_num, AdcChannel_t chan_num, double* const voltage) {
    bool res = false;
    int32_t code = 0;
    AdcHandle_t* AdcNode = AdcGetNode(adc_num);
    if(AdcNode) {
        res = adc_channel_read_code(adc_num, chan_num, &code);
        if(res) {
            if(voltage) {
                (*voltage) = AdcCode2Voltage(adc_num, chan_num, code);
            } else {
                res = false;
            }
        }
    } else {
        LOG_ERROR(LG_ADC, "%u NodeErr", adc_num);
    }
    return res;
}

double adc_channel_read_voltage_short(AdcNum_t adc_num, AdcChannel_t chan_num) {
    double voltage = 0;
    bool res = false;
    res = adc_channel_read_voltage(adc_num, chan_num, &voltage);
    if(false == res) {
        LOG_ERROR(LG_ADC, "ADC%u Ch%u ReadErrErr", adc_num, chan_num);
    }
    return voltage;
}

AdcChannel_t AdcPad2Channel(Pad_t pad) {
    AdcChannel_t chan_num = ADC_CHAN_UNDEF;
    const AdcChannelStaticInfo_t* AdcChannelInfo = GpioPad2AdcChannelInfo(pad);
    if(AdcChannelInfo) {
        chan_num = AdcChannelInfo->adc_channel;
    }
    return chan_num;
}

Pad_t AdcChannel2Pad(AdcNum_t adc_num, AdcChannel_t chan_num) {
    Pad_t pad = {0};
    const AdcChannelStaticInfo_t* AdcChannelStaticInfo = AdcGetChannelInfo(chan_num);
    if(AdcChannelStaticInfo) {
        pad = AdcChannelStaticInfo->pad;
    }
    return pad;
}

bool adc_pad_read_voltage(Pad_t pad, double* const voltage) {
    bool res = false;
    AdcChannel_t chan_num;
    chan_num = AdcPad2Channel(pad);
    res = adc_is_valid_channel(chan_num);
    if(res) {
        res = adc_channel_read_voltage(1, chan_num, voltage);
        if(false == res) {
            LOG_ERROR(LG_ADC, "Ch%u ReadErrErr", chan_num);
        } else {
            LOG_DEBUG(LG_ADC, "Read CH%u Ok", chan_num);
        }
    }
    return res;
}

double adc_pad_read_voltage_short(Pad_t pad) {
    double voltage = 0;
    bool res = false;
    res = adc_pad_read_voltage(pad, &voltage);
    if(false == res) {
        LOG_ERROR(LG_ADC, "Read %s Err", GpioPadToStr(pad));
    }
    return voltage;
}
