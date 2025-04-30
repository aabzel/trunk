#include "pdm_drv.h"

#include <limits.h>
#include <math.h>
#include <stdlib.h>

#include "clock_utils.h"
#include "common_diag.h"
#include "data_utils.h"
#include "gpio_drv.h"
#include "hal_nrfx_diag.h"
#include "log.h"
#include "nrfx_pdm.h"
#include "pdm_custom_types.h"
#include "pdm_dep.h"
#include "pdm_diag.h"
#include "pdm_isr.h"
#include "pdm_types.h"

static const PdmFreqInfo_t PdmFreqInfo[] = {
    {
        .frequency_hz = KHZ_2_HZ(1000),
        .nrf_frequency_code = NRF_PDM_FREQ_1000K,
    },
    {
        .frequency_hz = KHZ_2_HZ(1032),
        .nrf_frequency_code = NRF_PDM_FREQ_1032K,
    },
    {
        .frequency_hz = KHZ_2_HZ(1067),
        .nrf_frequency_code = NRF_PDM_FREQ_1067K,
    },
    {
        .frequency_hz = MHZ_2_HZ(1231),
        .nrf_frequency_code = NRF_PDM_FREQ_1231K,
    },
    {
        .frequency_hz = MHZ_2_HZ(1280),
        .nrf_frequency_code = NRF_PDM_FREQ_1280K,
    },
    {
        .frequency_hz = MHZ_2_HZ(1333),
        .nrf_frequency_code = NRF_PDM_FREQ_1333K,
    },
};

static nrf_pdm_mclksrc_t PdmMasterClockSrc2NrfPdmMasterClockSrc(PdmMasterClk_t PdmMasterClockSrc) {
    nrf_pdm_mclksrc_t nrf_mclk_src = NRF_PDM_MCLKSRC_PCLK32M;
    switch((uint8_t)PdmMasterClockSrc) {
    case PDM_MASTER_CLK_CPU_PLL:
        nrf_mclk_src = NRF_PDM_MCLKSRC_PCLK32M;
        break;

    case PDM_MASTER_CLK_AUDIO_PLL:
        nrf_mclk_src = NRF_PDM_MCLKSRC_ACLK;
        break;

    default:
        nrf_mclk_src = NRF_PDM_MCLKSRC_PCLK32M;
        break;
    }
    return nrf_mclk_src;
}

nrf_pdm_ratio_t PdmRatio2NrfPdmRatio(uint8_t ratio) {
    nrf_pdm_ratio_t nrf_pdm_ratio = NRF_PDM_RATIO_64X;
    switch(ratio) {
    case 64:
        nrf_pdm_ratio = NRF_PDM_RATIO_64X;
        break;

    case 80:
        nrf_pdm_ratio = NRF_PDM_RATIO_80X;
        break;

    default:
        LOG_ERROR(PDM, "UndefRatio: %u", ratio);
        nrf_pdm_ratio = NRF_PDM_RATIO_64X;
        break;
    }
    return nrf_pdm_ratio;
}

static nrf_pdm_edge_t PdmEdge2NrfEdge(PdmEdge_t pdm_edge) {
    nrf_pdm_edge_t nrf_pdm_edge = NRF_PDM_EDGE_LEFTFALLING;
    switch((uint8_t)pdm_edge) {
    case PDM_EDGE_LEFT_FALLING:
        nrf_pdm_edge = NRF_PDM_EDGE_LEFTFALLING;
        break;

    case PDM_EDGE_LEFT_RISING:
        nrf_pdm_edge = NRF_PDM_EDGE_LEFTRISING;
        break;
    }
    return nrf_pdm_edge;
}

static nrf_pdm_freq_t PdfFrequency2NrfFrequency(uint32_t des_frequency_hz) {
    PdmFreqInfo_t FinalFreq = {
        .nrf_frequency_code = NRF_PDM_FREQ_1032K,
        .frequency_hz = KHZ_2_HZ(1032),
    };
    int32_t min_error = INT_MAX;
    int32_t cur_diff = 0;
    uint32_t cnt = ARRAY_SIZE(PdmFreqInfo);
    LOG_INFO(PDM, "%u Freq Options", cnt);
    uint32_t i = 0;
    for(i = 0; i < cnt; i++) {
        cur_diff = abs(((int32_t)PdmFreqInfo[i].frequency_hz) - ((int32_t)des_frequency_hz));
        if(cur_diff < min_error) {
            min_error = cur_diff;
            FinalFreq = PdmFreqInfo[i];
            // FinalFreq.nrf_frequency_code = PdmFreqInfo[i].nrf_frequency_code;
            // FinalFreq.frequency_hz = PdmFreqInfo[i].frequency_hz;
        }
    }
    LOG_INFO(PDM, "SetFreq %u Hz", FinalFreq.frequency_hz);
    return FinalFreq.nrf_frequency_code;
}

static nrf_pdm_mode_t PdmMode2NrfMode(PdmMode_t pdm_mode) {
    nrf_pdm_mode_t mode = NRF_PDM_MODE_STEREO;
    switch((uint8_t)pdm_mode) {
    case PDM_MODE_STEREO:
        mode = NRF_PDM_MODE_STEREO; ///< Sample and store one pair (Left + Right) of 16-bit samples per RAM word.
        break;
    case PDM_MODE_MONO:
        mode = NRF_PDM_MODE_MONO; ///< Sample and store two successive Left samples (16 bit each) per RAM word.
        break;
    }
    return mode;
};

const static PdmStaticInfo_t PdmStaticInfo[] = {
#ifdef HAS_PDM
    {
        .num = 0,
#ifdef HAS_PDM_ISR
        .event_handler = nrfx_pdm0_event_handler,
#endif                           /*HAS_PDM_ISR*/
        .registers = NRF_PDM0_S, /*TODO TRy NS*/
        .valid = true,
    },
#endif /*HAS_PDM*/
};

PdmStaticInfo_t* PdmGetStaticNode(uint8_t num) {
    PdmStaticInfo_t* Node = NULL;
    uint8_t i = 0;
    uint8_t pdm_cnt = ARRAY_SIZE(PdmStaticInfo);
    LOG_DEBUG(PDM, "Total: %u Need %u", pdm_cnt, num);
    for(i = 0; i < pdm_cnt; i++) {
        if(num == PdmStaticInfo[i].num) {
            LOG_DEBUG(PDM, "spotNum %u", num);
            if(PdmStaticInfo[i].valid) {
                LOG_DEBUG(PDM, "spotValid %u", num);
                Node = (PdmStaticInfo_t*)&PdmStaticInfo[i];
                break;
            }
        }
    }
    return Node;
}

static bool pdm_start(uint8_t num) {
    bool res = false;
    LOG_INFO(PDM, "PDM%u Start", num);
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        nrfx_err_t ret = nrfx_pdm_start();
        if(NRFX_SUCCESS == ret) {
            LOG_INFO(PDM, "PDM%u StartOk", num);
            res = true;
            Node->start_cnt++;
            Node->rx_done = false;
        } else {
            LOG_ERROR(PDM, "PDM%u StartErr %u=%s ", num, ret, HalStatus2Str(ret));
        }
    }
    return res;
}

static bool pdm_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(PDM, "PDM%u Stop", num);
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        nrfx_err_t ret = nrfx_pdm_stop();
        if(NRFX_SUCCESS == ret) {
            res = true;
            LOG_INFO(PDM, "PDM%u StopOk", num);
            Node->stop_cnt++;
        } else {
            LOG_ERROR(PDM, "PDM%u StopErr %u=%s", num, ret, HalStatus2Str(ret));
        }
    }
    return res;
}

bool pdm_buf_set(uint8_t num, const int16_t* const buf, uint16_t len) {
    bool res = false;
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        if(buf) {
            if(len) {
                nrfx_err_t ret = nrfx_pdm_buffer_set((int16_t*)buf, len);
                if(NRFX_SUCCESS == ret) {
                    if(false == Node->in_isr) {
                        LOG_DEBUG(PDM, "PDM%u BufSetOk", num);
                    }
                    res = true;
                } else {
                    Node->error_cnt++;
                    res = false;
                    if(false == Node->in_isr) {
                        LOG_ERROR(PDM, "PDM%u BufSetErr %u=%s", num, ret, HalStatus2Str(ret));
                    }
                }
            }
        }
    } else {
        if(false == Node->in_isr) {
            LOG_ERROR(PDM, "PDM%u BufSetErr ptr=%p len=%u", num, buf, len);
        }
    }
    return res;
}

bool pdm_ctrl(uint8_t num, bool on_off, MicMode_t mode) {
    bool res = false;
    LOG_WARNING(PDM, "PDM%u, Ctrl %s, Mode:%s", num, OnOff2Str(on_off), MicMode2Str(mode));
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        Node->mic_mode = mode;
        if(on_off) {
            res = pdm_start(num);
        } else {
            res = pdm_stop(num);
        }
    } else {
        LOG_ERROR(PDM, "PDM%u NoNode", num);
    }
    return res;
}

bool pdm_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(PDM, "PDM%u Init", num);
    const PdmConfig_t* Config = PdmGetConfig(num);
    if(Config) {
        LOG_INFO(PDM, "PDM%u SpotConfig ", num);
        PdmDiagConfig(Config);
        res = PdmIsValidConfig(Config);
        PdmHandle_t* Node = PdmGetNode(num);
        if(Node && res) {
            if(Node->init_done) {
                LOG_WARNING(PDM, "PDM%u UnInit", num);
                nrfx_pdm_uninit();
            }
            Node->mic_mode = Config->mic_mode;
            Node->sample_rate_hz = Config->sample_rate_hz;
            Node->samples_cnt = Config->samples_cnt;

            Node->rx_done = false;
            Node->buf_toogle = 0;

            Node->in_isr = false;
            Node->rx_done = true;
            Node->error_cnt = 0;
            Node->int_cnt = 0;
            Node->rx_sample_cnt = 0;
            Node->buf_toogle = 0;
            if(Config->buf) {
                if(Config->sample_rate_hz) {
                    Node->buf = Config->buf;
                    Node->start_cnt = 0;
                    Node->stop_cnt = 0;

                    LOG_DEBUG(PDM, "PDM%u SpotNode", num);
                    const PdmStaticInfo_t* StaticNode = PdmGetStaticNode(num);
                    if(StaticNode) {
                        LOG_DEBUG(PDM, "PDM%u SpotStaticConfigFor", num);
                        nrfx_pdm_config_t if_config = {0};
                        if_config.gain_l =
                            (nrf_pdm_gain_t)uint8_limiter((uint8_t)Config->Gain.left, NRF_PDM_GAIN_MAXIMUM);
                        if_config.gain_r =
                            (nrf_pdm_gain_t)uint8_limiter((uint8_t)Config->Gain.right, NRF_PDM_GAIN_MAXIMUM);
                        if_config.mode = PdmMode2NrfMode(Config->pdm_mode);
                        if_config.edge = PdmEdge2NrfEdge(Config->edge);
                        if_config.pin_clk = Config->PadClk.byte;
                        if_config.pin_din = Config->PadDin.byte;
                        if_config.interrupt_priority = Config->irq_priority;
                        if_config.mclksrc = PdmMasterClockSrc2NrfPdmMasterClockSrc(Config->master_clk);
                        if_config.clock_freq = PdfFrequency2NrfFrequency(Config->frequency_hz);
                        if_config.ratio = PdmRatio2NrfPdmRatio(Config->ratio);

                        nrfx_err_t ret;
                        ret = nrfx_pdm_init(&if_config, StaticNode->event_handler);

                        if(NRFX_SUCCESS == ret) {
                            LOG_INFO(PDM, "PDM%u InitOk", num);
                            Node->init_done = true;
                            res = pdm_ctrl(num, Config->on, Config->mic_mode);
                        } else {
                            res = false;
                            LOG_ERROR(PDM, "PDM%u InitErr %u=%s", num, ret, HalStatus2Str(ret));
                        }
                    } else {
                        LOG_ERROR(PDM, "PDM%u NoStaticNode", num);
                    }
                }
            }
        } else {
            LOG_ERROR(PDM, "PDM%u NoNode", num);
        }
    } else {
        LOG_ERROR(PDM, "PDM%u NoConfig", num);
    }
    return res;
}

bool pdm_proc_one(uint8_t num) {
    bool res = false;
    LOG_PARN(PDM, "PDM%u Proc", num);
    PdmHandle_t* Node = PdmGetNode(num);
    if(Node) {
        if(Node->rx_done) {
            Node->rx_done = false;
            LOG_INFO(PDM, "PDM%u RxDone!", num);
            res = true;
        }
    }
    return res;
}
