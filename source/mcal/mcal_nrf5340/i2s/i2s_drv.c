#include "i2s_drv.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#ifdef HAS_ZEPHYR
#include <irq.h>
#include <nrfx_clock.h>
#include <zephyr/device.h>
#include <zephyr/drivers/pinctrl.h>
#include <zephyr/kernel.h>
#endif /*HAS_ZEPHYR*/

#ifdef HAS_I2S_VOLUME
#include "i2s_volume.h"
#endif

#include "board_config.h"
#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif /*HAS_DEBUGGER*/

#ifdef HAS_DIAG
#include "common_diag.h"
#endif /*HAS_DIAG*/

#include "clock.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "hal_nrfx_diag.h"
#include "i2s_config.h"
#include "i2s_diag.h"
#include "utils_math.h"

#ifdef HAS_I2S_ISR
#include "i2s_isr.h"
#endif /*HAS_I2S_ISR*/

#include "i2s_nrf_types.h"
#include "i2s_types.h"

#ifdef HAS_TEST_I2S
#include "test_i2s.h"
#endif /*HAS_TEST_I2S*/

#ifdef HAS_GPIO_DIAG
#include "gpio_diag.h"
#endif

#ifdef HAS_FDA801
#include "fda801_drv.h"
#endif /*HAS_FDA801*/

#include "log.h"
#include "nrfx_errors.h"
#include "nrfx_i2s.h"
#include "sys_config.h"
#ifdef HAS_SW_DAC
#include "sw_dac_drv.h"
#endif

static nrf_i2s_swidth_t I2sDataFormat2NrfSampleWidth(I2sDataFormat_t data_format) {
    nrf_i2s_swidth_t sample_width = NRF_I2S_SWIDTH_24BIT;
    switch((uint32_t)data_format) {
    case I2S_DATA_FORMAT_8B:
        sample_width = NRF_I2S_SWIDTH_8BIT;
        break;
    case I2S_DATA_FORMAT_16B:
        sample_width = NRF_I2S_SWIDTH_16BIT;
        break;
    case I2S_DATA_FORMAT_16B_EXTENDED:
        sample_width = NRF_I2S_SWIDTH_16BIT;
        break;
    case I2S_DATA_FORMAT_24B:
        sample_width = NRF_I2S_SWIDTH_24BIT;
        break;
    case I2S_DATA_FORMAT_32B:
        sample_width = NRF_I2S_SWIDTH_32BIT;
        break;
    }
    return sample_width;
}

bool i2s_api_read(uint8_t num, SampleType_t* array, size_t array_len) {
    bool res = false;
    (void)num;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        if(array && array_len) {
            Node->cur_rx_track = 0;
            nrfx_i2s_stop();
            Node->i2s_buffers[0].p_rx_buffer = (uint32_t*)array;
            Node->i2s_buffers[0].p_tx_buffer = NULL;

            Node->i2s_buffers[1].p_rx_buffer = (uint32_t*)array;
            Node->i2s_buffers[1].p_tx_buffer = NULL;
            nrfx_err_t ret = nrfx_i2s_start((nrfx_i2s_buffers_t const*)&Node->i2s_buffers[0], (uint16_t)array_len, 0);
            if(NRFX_SUCCESS == ret) {
                LOG_INFO(I2S, "StartReadOk");
                res = true;
            } else {
                LOG_ERROR(I2S, "StartErr %s", HalStatus2Str(ret));
            }
        } else {
            LOG_ERROR(I2S, "DataErr");
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

bool i2s_api_start(uint8_t num, size_t words) {
    bool res = false;
    LOG_INFO(I2S, "%u Start Words:%u", num, words);
    (void)num;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->frames = words;
        if(Node->i2s_buffers[0].p_rx_buffer && Node->i2s_buffers[0].p_tx_buffer && Node->i2s_buffers[1].p_rx_buffer &&
           Node->i2s_buffers[1].p_tx_buffer) {
            // nrfx_i2s_stop();
            LOG_INFO(I2S, "NrfxStart");
            nrfx_err_t ret = nrfx_i2s_start((nrfx_i2s_buffers_t const*)&Node->i2s_buffers[0], (uint16_t)words, 0);
            if(NRFX_SUCCESS == ret) {
                LOG_INFO(I2S, "%u StartOk", num);
                res = true;
            } else {
                LOG_ERROR(I2S, "StartErr %s", HalStatus2Str(ret));
            }
        } else {
            res = false;
            LOG_ERROR(I2S, "%u DataErr", num);
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

bool i2s_read_sample(uint8_t num, size_t size) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        res = i2s_api_read(num, (SampleType_t*)&Node->rx_sample.u32[0], size);
        if(res) {
            LOG_INFO(I2S, "Rx" LOG_OK);
            res = true;
        } else {
            Node->Err.read++;
            LOG_ERROR(I2S, "%u RxErr", num);
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

bool i2s_dma_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(I2S, "Stop %u", num);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->in_progress = false;
        nrfx_i2s_stop();
        LOG_INFO(I2S, "%u Stop", num);
        res = true;
    } else {
        LOG_ERROR(I2S, "%u NodeGetErr", num);
    }
    return res;
}

bool i2s_set_join_write(uint8_t num, uint32_t* array1, uint32_t* array2) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->stop_needed = false;
        if(array1) {
            Node->i2s_buffers[0].p_tx_buffer = (uint32_t*)array1;
            if(array2) {
                Node->i2s_buffers[1].p_tx_buffer = (uint32_t*)array2;
                res = true;
            }
        }
    } else {
        res = false;
    }
    return res;
}

bool i2s_api_write(uint8_t num, SampleType_t* array, size_t frames_to_send) {

    bool res = false;
    (void)num;
    LOG_INFO(I2S, "I2S%u Write %u Frames", num, frames_to_send);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        if(false == Node->in_progress) {
            Node->cur_tx_track = 0;
            nrfx_i2s_stop();
            Node->frames_to_send = frames_to_send;
            Node->i2s_buffers[0].p_rx_buffer = (uint32_t*)NULL;
            Node->i2s_buffers[0].p_tx_buffer = (uint32_t*)array;

            Node->i2s_buffers[1].p_rx_buffer = (uint32_t*)NULL;
            Node->i2s_buffers[1].p_tx_buffer = (uint32_t*)array;
            nrfx_err_t ret =
                nrfx_i2s_start((nrfx_i2s_buffers_t const*)&Node->i2s_buffers[0], (uint16_t)frames_to_send, 0);
            if(NRFX_SUCCESS == ret) {
                res = true;
                Node->in_progress = true;
                LOG_DEBUG(I2S, "%u WrOk %u Frames", num, frames_to_send);
            } else {
                Node->Err.start++;
                LOG_ERROR(I2S, "StartErr %s", HalStatus2Str(ret));
                res = false;
            }
        } else {
            LOG_ERROR(I2S, "I2S%u Busy", num);
            Node->Err.busy++;
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

static nrf_i2s_mode_t I2sMode2NrfMode(I2sRole_t i2s_mode) {
    nrf_i2s_mode_t nrf_i2s_mode = NRF_I2S_MODE_MASTER;
    switch((uint32_t)i2s_mode) {
    case I2SMODE_MASTER:
    case I2SMODE_MASTER_RX:
    case I2SMODE_MASTER_TX:
        nrf_i2s_mode = NRF_I2S_MODE_MASTER;
        break;
    case I2SMODE_SLAVE:
    case I2SMODE_SLAVE_TX:
    case I2SMODE_SLAVE_RX:
        nrf_i2s_mode = NRF_I2S_MODE_SLAVE;
        break;
    }
    return nrf_i2s_mode;
}

static const NrfI2sDiv_t I2sAvailableDiv[] = {{
                                                  .div_val = 2,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV2,
                                              },
                                              {
                                                  .div_val = 3,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV3,
                                              },
                                              {
                                                  .div_val = 4,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV4,
                                              },
                                              {
                                                  .div_val = 5,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV5,
                                              },
                                              {
                                                  .div_val = 6,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV6,
                                              },
                                              {
                                                  .div_val = 8,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV8,
                                              },
                                              {
                                                  .div_val = 10,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV10,
                                              },
                                              {
                                                  .div_val = 11,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV11,
                                              },
                                              {
                                                  .div_val = 15,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV15,
                                              },
                                              {
                                                  .div_val = 16,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV16,
                                              },
                                              {
                                                  .div_val = 21,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV21,
                                              },
                                              {
                                                  .div_val = 23,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV23,
                                              },
                                              {
                                                  .div_val = 30,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV30,
                                              },
                                              {
                                                  .div_val = 31,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV31,
                                              },
                                              {
                                                  .div_val = 32,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV32,
                                              },
                                              {
                                                  .div_val = 42,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV42,
                                              },
                                              {
                                                  .div_val = 63,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV63,
                                              },
                                              {
                                                  .div_val = 125,
                                                  .nrf_i2s_mck = NRF_I2S_MCK_32MDIV125,
                                              }};

static const NrfI2sLrDiv_t I2sAvailableLrRatio[] = {{
                                                        .ratio_val = 512,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_512X,
                                                    },
                                                    {
                                                        .ratio_val = 384,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_384X,
                                                    },
                                                    {
                                                        .ratio_val = 256,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_256X,
                                                    },
                                                    {
                                                        .ratio_val = 192,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_192X,
                                                    },
                                                    {
                                                        .ratio_val = 128,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_128X,
                                                    },
                                                    {
                                                        .ratio_val = 96,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_96X,
                                                    },
                                                    {
                                                        .ratio_val = 64,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_64X,
                                                    },
                                                    {
                                                        .ratio_val = 48,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_48X,
                                                    },
                                                    {
                                                        .ratio_val = 32,
                                                        .nrf_i2s_lrclk = NRF_I2S_RATIO_32X,
                                                    }

};

static bool I2sCalcFreq(uint32_t xtal_freq, uint8_t div_val, uint32_t des_sck_freq_hz, int32_t* freq_diff_hz,
                        uint32_t* calc_freq_hz, bool final) {
    bool res = false;
    if(freq_diff_hz && calc_freq_hz) {
        res = true;
        *calc_freq_hz = xtal_freq / div_val;
        double diff = ((double)(*calc_freq_hz)) - ((double)des_sck_freq_hz);
        double abs_diff = fabs(diff);
        *freq_diff_hz = (int32_t)abs_diff;
        log_level_t level = LOG_LEVEL_INFO;
        if(final) {
            level = LOG_LEVEL_WARNING;
        } else {
            level = LOG_LEVEL_DEBUG;
        }
        log_write(level, I2S, "Xtal:%u Hz DivVal %u Calc:%u Hz Des:%u Hz Diff:%d Hz", xtal_freq, div_val, *calc_freq_hz,
                  des_sck_freq_hz, *freq_diff_hz);
    }
    return res;
}

bool I2sCalcLrFreq(uint32_t master_clock_hz, uint32_t ratio, uint32_t des_audio_lr_freq_hz,
                   uint32_t* calc_audio_lr_freq_hz, bool final) {
    bool res = false;
    if(calc_audio_lr_freq_hz) {
        res = true;
        int32_t error_hz = 0;
        *calc_audio_lr_freq_hz = master_clock_hz / ratio;
        double diff = ((double)(*calc_audio_lr_freq_hz)) - ((double)des_audio_lr_freq_hz);
        double abs_diff = fabs(diff);
        error_hz = (int32_t)abs_diff;
        log_level_t level = LOG_LEVEL_INFO;
        if(final) {
            level = LOG_LEVEL_WARNING;
        } else {
            level = LOG_LEVEL_DEBUG;
        }
        log_write(level, I2S, "Clk:%u DesLR:%u Hz DesRatio %u Calc:%u Hz Err:%d Hz", master_clock_hz,
                  des_audio_lr_freq_hz, ratio, *calc_audio_lr_freq_hz, error_hz);
    }
    return res;
}

static const NrfI2sDiv_t* I2sCalcDiv(uint32_t des_sck_freq_hz, uint32_t xtal_freq) {
    const NrfI2sDiv_t* OptNrfI2sDiv = NULL;
    LOG_INFO(I2S, "DesSckFreq %u Hz Xtall:%u Hz", des_sck_freq_hz, xtal_freq);
    int32_t i = 0;
    uint32_t calc_freq_hz = 0;
    int32_t freq_diff_hz = 0;
    int32_t min_freq_diff_hz = INT_MAX;
    uint32_t cnt = ARRAY_SIZE(I2sAvailableDiv);
    for(i = (cnt - 1); 0 <= i; i--) {
        I2sCalcFreq(xtal_freq, I2sAvailableDiv[i].div_val, des_sck_freq_hz, &freq_diff_hz, &calc_freq_hz, false);
        if(freq_diff_hz < min_freq_diff_hz) {
            OptNrfI2sDiv = &I2sAvailableDiv[i];
            min_freq_diff_hz = freq_diff_hz;
            LOG_DEBUG(I2S, "NewMim Calc:%u Hz Diff:%d Hz", calc_freq_hz, freq_diff_hz);
        }
    }
    I2sCalcFreq(xtal_freq, OptNrfI2sDiv->div_val, des_sck_freq_hz, &freq_diff_hz, &calc_freq_hz, true);

    return OptNrfI2sDiv;
}

static const NrfI2sLrDiv_t* I2sCalcLrDiv(uint32_t des_audio_lr_freq_hz, uint32_t master_clock_hz) {
    const NrfI2sLrDiv_t* OptimalLrRatio = NULL;
#ifdef HAS_DEBUGGER
    ASSERT_DYNAMIC(0 != master_clock_hz);
    ASSERT_DYNAMIC(0 != des_audio_lr_freq_hz);
#endif
    double des_rato = ((double)master_clock_hz) / ((double)des_audio_lr_freq_hz);
    LOG_INFO(I2S, "CalcAudioFreq  DesLRCK %u Hz MCK:%u Hz DesRatio:%f", des_audio_lr_freq_hz, master_clock_hz,
             des_rato);
    int32_t i = 0;

    //    MCK/LRCK ratio
    uint32_t calc_audio_lr_freq_hz = 0;
    double ratio_error = 0.0;
    double ratio_cur = 0.0;
    double min_rat_error = 9999999.9;
    uint32_t cnt = ARRAY_SIZE(I2sAvailableLrRatio);
    for(i = 0; i < cnt; i++) {
        ratio_cur = (double)I2sAvailableLrRatio[i].ratio_val;
        ratio_error = fabs(ratio_cur - des_rato);
        I2sCalcLrFreq(master_clock_hz, OptimalLrRatio->ratio_val, des_audio_lr_freq_hz, &calc_audio_lr_freq_hz, false);
        if(ratio_error <= min_rat_error) {
            min_rat_error = ratio_error;
            OptimalLrRatio = &I2sAvailableLrRatio[i];
            LOG_DEBUG(I2S, "NewMim CalcAudioFreq:%u Hz Err:%f CurRatio:%u", calc_audio_lr_freq_hz, ratio_error,
                      OptimalLrRatio->ratio_val);
        }
    }
    I2sCalcLrFreq(master_clock_hz, OptimalLrRatio->ratio_val, des_audio_lr_freq_hz, &calc_audio_lr_freq_hz, true);
    return OptimalLrRatio;
}

bool i2s_read_write(uint8_t num, uint32_t tx_sample) {
    bool res = false;
    Type32Union_t un32;
    un32.u32 = tx_sample;
    LOG_DEBUG(I2S, "%u ReadWrite TxSample:0x%08x", num, tx_sample);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->cur_tx_track = 0;
        nrfx_i2s_stop();
        Node->tx_sample.u32[0] = un32.u16[0];
        Node->tx_sample.u32[1] = un32.u16[1];
        Node->i2s_buffers[0].p_tx_buffer = (uint32_t*)&Node->tx_sample;
        Node->i2s_buffers[0].p_rx_buffer = (uint32_t*)&Node->rx_sample;
        nrfx_err_t ret = nrfx_i2s_start((nrfx_i2s_buffers_t const*)&Node->i2s_buffers[0], (uint16_t)2, 0);
        if(NRFX_SUCCESS == ret) {
            res = true;
            LOG_INFO(I2S, "%u TxRxOk", num);
        } else {
            Node->Err.start++;
            res = false;
            LOG_ERROR(I2S, "%u TxRxErr %u %s", num, ret, HalStatus2Str(ret));
        }
    } else {
        LOG_ERROR(I2S, "%u NodeErr", num);
    }
    return res;
}

uint32_t i2s_get_sample_rate(uint8_t num) {
    uint32_t sample_rate = 0;
    const I2sConfig_t* Config = I2sGetConfig(num);
    if(Config) {
        sample_rate = Config->audio_freq;
    }
    return sample_rate;
}

bool i2s_play_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    LOG_INFO(I2S, "I2S%u PlayTx DAC%u %s", num, dac_num, OnOff2Str(status));
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_SW_DAC
        Node->dac_num = dac_num;
        SwDac_t* DacNode = SwDacGetNode(dac_num);
        if(DacNode) {
            LOG_DEBUG(I2S, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;

#ifdef HAS_DYNAMIC_SAMPLES
            if(DacNode->tx_sample_array) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_DAC, "TrackArrayErr");
            }
#endif /*HAS_DYNAMIC_SAMPLES*/
            if(DacNode->sample_cnt) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(LG_DAC, "TrackSampleCntErr");
            }

            if(res) {
                LOG_INFO(I2S, "SpotRecord %u", dac_num);
                Node->loopback = false;
                Node->play = status;
                if(Node->play) {
                    // i2s_dma_stop(num);
                    LOG_INFO(I2S, "Play %u samples", DacNode->sample_cnt);
                    LOG_DEBUG(I2S, "StartPlay");
#ifdef HAS_DYNAMIC_SAMPLES
                    res = i2s_api_write(num, &DacNode->tx_sample_array[0], DacNode->sample_cnt);
#else /*HAS_DYNAMIC_SAMPLES*/
#ifdef HAS_SW_DAC_STATIC_SAMPLES
                    res = i2s_api_write(num, &DacNode->tx_sample_static_array[0], DacNode->sample_cnt);
#endif /*HAS_SW_DAC_STATIC_SAMPLES*/
#endif /*HAS_DYNAMIC_SAMPLES*/
                    if(res) {
                        LOG_INFO(I2S, "TxOk %u Samples", DacNode->sample_cnt);
                    } else {
                        Node->Err.write++;
                        LOG_ERROR(I2S, "I2sWriteErr");
                    }
                } else {
                    res = true;
                }
            } else {
                LOG_ERROR(LG_DAC, "TrackErr");
            }
        } else {
            LOG_ERROR(LG_DAC, "HandleErr");
        }
#else
        LOG_ERROR(I2S, "Add SW_DAC component");
#endif /*HAS_SW_DAC*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}

bool i2s_config_tx(uint8_t num, uint8_t word_size, uint8_t channels, uint32_t audio_freq) {
    bool res = false;
    return res;
}

bool i2s_send(uint8_t num, bool status) {
    bool res = true;
    return res;
}

static bool i2s_gpio_init(const I2sConfig_t* const Config, nrfx_i2s_config_t* const config_prt) {
    bool res = false;
    LOG_WARNING(I2S, "InitI2Sgpio");
    if(Config) {
        if(config_prt) {
            config_prt->sck_pin = pad_assign(Config->PadSck.byte, "SCK");
            config_prt->lrck_pin = pad_assign(Config->PadLrCk.byte, "LR_CLK");
            config_prt->sdout_pin = pad_assign(Config->PadSdOut.byte, "SDOUT");
            config_prt->sdin_pin = pad_assign(Config->PadSdIn.byte, "SDIN");
            config_prt->mck_pin = pad_assign(Config->PadMClk.byte, "Mclk");
            if(I2S_MCLKOUT_OFF == Config->mclk_out) {
                config_prt->mck_pin = NRFX_I2S_PIN_NOT_USED;
                LOG_INFO(I2S, "MCLKOUT_OFF");
            }
            res = true;
        }
    }
    return res;
}
#ifdef HAS_ZEPHYR
static bool i2s_extra_init(void) {
    bool res = false;
    LOG_INFO(I2S, "I2sExtraInit");

    nrfx_err_t ret;

    nrfx_clock_hfclkaudio_config_set(HFCLKAUDIO_12_288_MHZ);

    NRF_CLOCK->TASKS_HFCLKAUDIOSTART = 1;

    /* Wait for ACLK to start */
    while(!NRF_CLOCK_EVENT_HFCLKAUDIOSTARTED) {
        k_sleep(K_MSEC(1));
    }

    // ret = pinctrl_apply_state(PINCTRL_DT_DEV_CONFIG_GET(I2S_NL), PINCTRL_STATE_DEFAULT);
    //__ASSERT_NO_MSG(ret == 0);

    // IRQ_CONNECT(DT_IRQN(I2S_NL), DT_IRQ(I2S_NL, priority), nrfx_isr, nrfx_i2s_irq_handler, 0);
    // irq_enable(DT_IRQN(I2S_NL));
    res = true;
}
#endif

bool i2s_init_config(I2sHandle_t* const Node, const I2sConfig_t* Config) {
    bool res = false;
    if(Node) {
        if(Config) {
            Node->audio_freq = Config->audio_freq;
            Node->data_format = Config->data_format;
            Node->debug_led1_num = Config->debug_led1_num;
            Node->debug_led2_num = Config->debug_led2_num;
            Node->sample_mode = Config->sample_mode;
            Node->samples_cnt = Config->samples_cnt;
            res = true;
        }
    }
    return res;
}

bool i2s_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(I2S, "%u Init", num);
    const I2sConfig_t* Config = I2sGetConfig(num);
    if(Config) {
        I2sDiagConfig(Config);
        LOG_INFO(I2S, "%u SpotConfig", num);
        I2sHandle_t* Node = I2sGetNode(num);
        if(Node) {
            res = i2s_init_config(Node, Config);
#ifdef HAS_DFT
            Node->dft_mem = (double complex*)Config->dft_mem;
#endif
            Node->stop_needed = false;
#ifdef HAS_I2S_VOLUME
            res = i2s_volume_init_ll(Node);
#endif

            Node->in_progress = false;
            // Node->debug_led1.byte = Config->debug_led1.byte;
            // Node->debug_led2.byte = Config->debug_led2.byte;
#ifdef HAS_SW_DAC
            Node->dac_num = 1;
#endif
            nrfx_i2s_config_t config = {0};
#ifdef HAS_GPIO
            res = i2s_gpio_init(Config, &config);
            if(res) {
                LOG_INFO(I2S, "%u GpioInitOk", num);
            } else {
                LOG_ERROR(I2S, "%u GpioInitErr", num);
            }
#endif /*HAS_GPIO*/
            uint32_t rec_sck_freq_hz = 64 * Config->audio_freq;
            LOG_WARNING(I2S, "ReComendedScl %u Hz ConfigScl %u Hz Diff:%u Hz", rec_sck_freq_hz, Config->sck_freq_hz,
                        labs(rec_sck_freq_hz - Config->sck_freq_hz));
#ifdef HAS_NORTOS
            const NrfI2sDiv_t* OptimalDiv = I2sCalcDiv(Config->sck_freq_hz, XTALL_FREQ);
#else
            LOG_INFO(I2S, "DEFAULT_CPU_CLOCK_HZ %u", DEFAULT_CPU_CLOCK_HZ);
            const NrfI2sDiv_t* OptimalDiv = I2sCalcDiv(Config->sck_freq_hz, DEFAULT_CPU_CLOCK_HZ);
#endif
            if(OptimalDiv) {
                config.mck_setup = OptimalDiv->nrf_i2s_mck; ///< Master clock setup.
            } else {
                LOG_ERROR(I2S, "SetDiv 125");
                config.mck_setup = NRF_I2S_MCK_32MDIV8; ///< Master clock setup.
            }

            config.channels = NRF_I2S_CHANNELS_STEREO; ///< Enabled channels.
            config.format = NRF_I2S_FORMAT_I2S;
            // config.skip_gpio_cfg = true;
            // config.skip_psel_cfg = true;
            config.alignment = NRF_I2S_ALIGN_RIGHT;      ///< Alignment of sample within a frame.
            config.mode = I2sMode2NrfMode(Config->mode); ///< Mode of operation.
#ifdef HAS_FDA801
            if(32 != Config->data_format) {
                LOG_ERROR(FDA801, "DacSupportsOnly 32bit mode %u", Config->data_format);
            }
#endif
            config.sample_width = I2sDataFormat2NrfSampleWidth(Config->data_format); ///< Sample width.
            // uint32_t des_lr_freq_hz = I2sAudioFreq2Hz(Config->audio_freq);

            uint32_t audio_freq = clock_audio_freq_get();
            const NrfI2sLrDiv_t* OptimalLrDiv = I2sCalcLrDiv(Config->audio_freq, audio_freq);
            if(OptimalLrDiv) {
                LOG_INFO(I2S, "SetLrRatio %u", OptimalLrDiv->ratio_val);
                config.ratio = OptimalLrDiv->nrf_i2s_lrclk; ///< MCK/LRCK ratio.
            } else {
                LOG_WARNING(I2S, "SetLrRatio 32x");
                config.ratio = NRF_I2S_RATIO_32X;
            }

            if(NRF_I2S_SWIDTH_24BIT == config.sample_width) {
                LOG_WARNING(I2S, "SetLrRatio 48x");
                config.ratio = NRF_I2S_RATIO_48X;
            }
#if 0
            if(NRF_I2S_SWIDTH_32BIT == config.sample_width) {
                LOG_WARNING(I2S, "SetLrRatio 96x");
                config.ratio = NRF_I2S_RATIO_96X;
            }
#endif
            config.clksrc = I2S_CONFIG_CLKCONFIG_CLKSRC_ACLK;
            /* HFCLKAUDIO.FREQUENCY
             * Audio PLL frequency in
             * 11.176 MHz - 11.402 MHz or
             * 12.165 MHz - 12.411 MHz
             * frequency bands
             *
             * We work at 12288330  Hz = 12.28833 MHz
             */
            // config.clksrc = NRF_I2S_CLKSRC_ACLK;
            config.enable_bypass = false;
#ifdef HAS_I2S_ISR
            config.irq_priority = 0;
            LOG_INFO(I2S, "I2sHandler 0x%08p", Config->I2sIsrHandler);
            LOG_INFO(I2S, "nrfx_i2s_irq_handler 0x%08p", nrfx_i2s_irq_handler);
#ifdef HAS_ZEPHYR
            IRQ_DIRECT_CONNECT(I2S0_IRQn, 0, nrfx_i2s_irq_handler, 0);
#endif /*HAS_ZEPHYR*/
#endif /*HAS_I2S_ISR*/

#ifndef HAS_I2S_POSTPONE_INIT
            nrfx_err_t ret = nrfx_i2s_init(&config, Config->I2sIsrHandler);
            if(NRFX_SUCCESS == ret) {
                res = true;
                LOG_INFO(I2S, "%u InitOk", num);
                Node->i2s_buffers[0].p_tx_buffer = NULL;
                Node->i2s_buffers[0].p_rx_buffer = NULL;
                Node->i2s_buffers[1].p_tx_buffer = NULL;
                Node->i2s_buffers[1].p_rx_buffer = NULL;
                Node->init_done = true;
#ifdef HAS_I2S0_LOOPBACK
                res = i2s_loopback(num, 256);
#endif /*HAS_I2S0_LOOPBACK*/
            } else {
                LOG_ERROR(I2S, "InitErr %s", HalStatus2Str(ret));
                res = false;
            }
#endif /*HAS_I2S_POSTPONE_INIT*/
        } else {
            LOG_ERROR(I2S, "LackNode %u", num);
        }
    } else {
        LOG_DEBUG(I2S, "%u NoConf", num);
    }
    return res;
}

bool i2s_init(void) {
    bool res = false;
    set_log_level(I2S, LOG_LEVEL_NOTICE);
    uint32_t i = 0;
    uint32_t cnt = 0;
    cnt = i2s_get_cnt();
    LOG_WARNING(I2S, "Init Cnt %u", cnt);
    if(1 == cnt) {
        for(i = 0; i < cnt; i++) {
            res = i2s_init_one(i);
            if(res) {
                cnt++;
            }
        }
        if(cnt) {
            res = true;
        } else {
            res = false;
        }
    } else {
        LOG_ERROR(I2S, "ConfigErr %u", cnt);
    }
    return res;
}

bool i2s_proc(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = i2s_get_cnt();
    for(i = 0; i <= cnt; i++) {
        res = i2s_proc_one(i);
    }
    return res;
}

bool i2s_loopback(uint8_t num, size_t words_num) {
    bool res = false;
    LOG_INFO(I2S, "%u LoopBack %u Byte", num, words_num);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->cur_tx_track = 0;
        Node->cur_rx_track = 1;

        Node->switch_needed = true;
        Node->stop_needed = false;
        uint8_t i = 0;
        for(i = 0; i < 2; i++) {
            memset((void*)&(Node->TxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
            memset((void*)&(Node->RxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
        }

        Node->i2s_buffers[0].p_rx_buffer = (uint32_t*)&Node->RxBuffer[0][0];
        Node->i2s_buffers[0].p_tx_buffer = (uint32_t*)&Node->RxBuffer[1][0];

        Node->i2s_buffers[1].p_rx_buffer = (uint32_t*)&Node->RxBuffer[1][0];
        Node->i2s_buffers[1].p_tx_buffer = (uint32_t*)&Node->RxBuffer[0][0];

        if(words_num <= I2S_BUFFER_SIZE) {
            res = i2s_api_start(num, words_num);
            if(res) {
                Node->loopback = true;
            }
        } else {
            LOG_ERROR(I2S, "NumOfWordsErr In:%u Max:%u", words_num, I2S_BUFFER_SIZE);
        }
    } else {
        res = false;
        LOG_ERROR(I2S, "%u NodeErr", words_num);
    }

    return res;
}

bool i2s_loopback_shared_memory(uint8_t num, size_t words_num) {
    bool res = false;
    LOG_INFO(I2S, "%u loopBackSharedMem Words:%u", num, words_num);
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
        Node->cur_tx_track = 0;
        Node->cur_rx_track = 1;
        Node->switch_needed = false;
        Node->stop_needed = false;
        uint8_t i = 0;
        for(i = 0; i < 2; i++) {
            memset((void*)&(Node->TxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
            memset((void*)&(Node->RxBuffer[i][0]), 0, I2S_BUFFER_SIZE * 4);
        }

        Node->i2s_buffers[0].p_rx_buffer = (uint32_t*)&Node->RxBuffer[0][0];
        Node->i2s_buffers[0].p_tx_buffer = (uint32_t*)&Node->RxBuffer[0][0];

        Node->i2s_buffers[1].p_rx_buffer = (uint32_t*)&Node->RxBuffer[0][0];
        Node->i2s_buffers[1].p_tx_buffer = (uint32_t*)&Node->RxBuffer[0][0];

        if(words_num <= I2S_BUFFER_SIZE) {
            res = i2s_api_start(num, words_num);
            if(res) {
                Node->loopback = true;
            }
        } else {
            LOG_ERROR(I2S, "NumOfWordsErr In:%u Max:%u", words_num, I2S_BUFFER_SIZE);
        }
    } else {
        res = false;
        LOG_ERROR(I2S, "%u NodeErr", words_num);
    }

    return res;
}

bool i2s_play_static_tx(uint8_t num, uint8_t dac_num, bool status) {
    bool res = false;
    I2sHandle_t* Node = I2sGetNode(num);
    if(Node) {
#ifdef HAS_SW_DAC
        Node->dac_num = dac_num;
        SwDac_t* DacNode = SwDacGetNode(dac_num);
        if(DacNode) {
            LOG_DEBUG(SW_DAC, "SpotDac %u", dac_num);
            Node->dac_num = dac_num;
            LOG_INFO(SW_DAC, "Play 48 samples");
            Node->loopback = false;
            Node->play = status;
            if(Node->play) {
                LOG_INFO(I2S, "StartPlay1KHz");
                res = false;
#ifdef HAS_SW_DAC_STATIC_SAMPLES
                res = i2s_api_write(num, DacNode->tx_sample_static_array, 48);
#endif
                if(res) {
                    LOG_INFO(I2S, "DmaTxOk %u Samples", DacNode->sample_cnt);
                    res = true;
                } else {
                    Node->error_cnt++;
                }
            } else {
                res = true;
            }
        } else {
            LOG_ERROR(SW_DAC, "HandleErr");
        }
#else  /**/
        LOG_ERROR(I2S, "Add SW_DAC component");
#endif /*HAS_SW_DAC*/
    } else {
        LOG_ERROR(I2S, "HandleErr");
    }
    return res;
}

#ifdef HAS_I2S_VOLUME
SampleType_t i2s_calc_pcm_max_ll(I2sHandle_t* const Node) {
    SampleType_t pcm_max = 0;
    bool res = false;
    size_t i = 0;
    size_t j = 0;
    Node->pcm_max_get = 0;
    for(i = 0; i < Node->frames_to_send; i++) {
        for(j = 0; j < 2; j++) {
            switch(sizeof(SampleType_t)) {
            case 2: {
                int16_t* word_ptr = (int16_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                Node->pcm_max_get = MAX(Node->pcm_max_get, abs(word_ptr[0]));
                Node->pcm_max_get = MAX(Node->pcm_max_get, abs(word_ptr[1]));
                i++;
                res = true;
            } break;
            case 4: {
                int32_t* qword_ptr = (int32_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                Node->pcm_max_get = MAX(Node->pcm_max_get, abs(qword_ptr[0]));
                res = true;
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;

    return pcm_max;
}
#endif

#ifdef HAS_I2S_VOLUME
bool i2s_decrease_pcms_ll(I2sHandle_t* const Node) {
    bool res = false;
    size_t i = 0;
    size_t j = 0;
    for(i = 0; i < Node->frames_to_send; i++) {
        for(j = 0; j < 2; j++) {
            switch(sizeof(SampleType_t)) {
            case 2: {
                int16_t* doubles16 = (int16_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                doubles16[0] = (doubles16[0] * Node->dec_numerator) / Node->denominator;
                doubles16[1] = (doubles16[1] * Node->dec_numerator) / Node->denominator;
                i++;
                res = true;
            } break;
            case 4: {
                int32_t* one32 = (int32_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                one32[0] = (one32[0] * Node->dec_numerator) / Node->denominator;
                res = true;
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}
#endif

#ifdef HAS_I2S_VOLUME
bool i2s_increase_pcms_ll(I2sHandle_t* const Node) {
    bool res = false;
    size_t i = 0;
    size_t j = 0;
    for(i = 0; i < Node->frames_to_send; i++) {
        for(j = 0; j < 2; j++) {
            switch(sizeof(SampleType_t)) {
            case 2: {
                int16_t* doubles16 = (int16_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                doubles16[0] = (doubles16[0] * Node->inc_numerator) / Node->denominator;
                doubles16[1] = (doubles16[1] * Node->inc_numerator) / Node->denominator;
                i++;
                res = true;
            } break;
            case 4: {
                int32_t* one32 = (int32_t*)&(Node->i2s_buffers[j].p_tx_buffer[i]);
                one32[0] = (one32[0] * Node->inc_numerator) / Node->denominator;
                res = true;
            } break;
            default:
                res = false;
                break;
            }
        }
    }
    return res;
}
#endif
