#include "sw_dac_drv.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#ifdef HAS_AUDIO
#include "audio.h"
#include "audio_types.h"
#endif
#include "bit_utils.h"
#include "byte_utils.h"
#include "code_generator.h"
#include "convert.h"
#include "data_types.h"
#include "table_utils.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif
#include "log.h"
#ifdef HAS_ALLOCATOR
#include "heap_allocator.h"
#endif

#ifdef HAS_WM8731
#include "wm8731_drv.h"
#endif

#ifdef HAS_TIMER
#include "timer_mcal.h"
#endif /*HAS_TIMER*/

#if HAS_MATH
#include "utils_math.h"
#endif /*HAS_MATH*/
#include "sw_dac_config.h"
#include "sw_dac_diag.h"
#include "writer_config.h"

SwDac_t* SwDacGetNode(uint8_t num) {
    SwDac_t* Node = NULL;
    /*TODO find with bin search*/
    uint32_t i = 0;
    for(i = 0; i < sw_dac_get_cnt(); i++) {
        if(num == SwDacItem[i].num) {
            Node = &SwDacItem[i];
            break;
        }
    }
    return Node;
}

const SwDacConfig_t* SwDacGetConfig(uint8_t num) {
    const SwDacConfig_t* ConfNode = 0;
    uint32_t i = 0;
    /*TODO find with bin search*/
    for(i = 0; i < sw_dac_get_cnt(); i++) {
        if(num == SwDacConfig[i].num) {
            ConfNode = &SwDacConfig[i];
            break;
        }
    }
    return ConfNode;
}

bool sw_dac_proc(uint8_t num, SampleType_t* out_dac_sample) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node && out_dac_sample) {
        uint64_t cur_time_us = time_get_us();
        switch(Node->dac_mode) {
        case DAC_MODE_STATIC: {
            (*out_dac_sample) = Node->amplitude;
            res = true;
        } break;
        case DAC_MODE_PWM: {
            (*out_dac_sample) = (SampleType_t)calc_pwm_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->duty_cycle, Node->offset);
            res = true;
        } break;
        case DAC_MODE_SIN: {
            (*out_dac_sample) = (SampleType_t)calc_sin_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->offset);
            res = true;

        } break;
        case DAC_MODE_SAW: {
            (*out_dac_sample) = (SampleType_t)calc_saw_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->offset);
            res = true;
        } break;
        case DAC_MODE_FENCE: {

            (*out_dac_sample) = (SampleType_t)calc_fence_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                                Node->amplitude, Node->offset);
            res = true;
        } break;
        default:
            res = false;
            break;
        }
    }
    return res;
}

static double dac_is_valid_freq(double frequency) {
    double out_freq = 0.0;
    if(0.0 < frequency) {
        out_freq = frequency;
    } else {
        out_freq = 1.0;
        LOG_ERROR(SW_DAC, "FreqErr %f", frequency);
    }
    return out_freq;
}

static bool sw_dac_init_one(uint8_t num) {
    bool res = false;
    const SwDacConfig_t* Config = SwDacGetConfig(num);
    if(Config) {
        SwDacConfigDiag(Config);
        SwDac_t* Node = SwDacGetNode(num);
        if(Node) {
            LOG_WARNING(SW_DAC, "Init %u SampleSize %u byte", num, PCM_SAMPLE_SIZE);
            Node->dac_mode = Config->dac_mode;
            Node->frequency = dac_is_valid_freq(Config->frequency);
            Node->amplitude = Config->amplitude;
            Node->frame_pattern = Config->frame_pattern;
            Node->duty_cycle = Config->duty_cycle;
            Node->sample_bitness = Config->sample_bitness;
            Node->sample_per_second = Config->sample_per_second;
            Node->phase_ms = Config->phase_ms;
            Node->offset = Config->offset;

#ifdef HAS_DYNAMIC_SAMPLES
            Node->tx_sample_array = NULL;
#endif

#ifdef HAS_I2S_RX
            Node->rx_sample_array = NULL;
#endif

#ifdef HAS_REAL_SAMPLE_ARRAY
            Node->real_sample_array = NULL;
#endif
            // Node->sample_size = PCM_SAMPLE_SIZE;
            Node->init = true;
            Node->sample_bitness = Config->sample_bitness;
            Node->sample_cnt = 0;
            Node->frame_pattern = CHANNEL_BOTH;
            Node->cur_sample = 0;
            res = true;
        }
    }
    return res;
}

bool sw_dac_set_sample(uint8_t num, SampleType_t sample) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->cur_sample = sample;
        Node->dac_mode = DAC_MODE_STATIC;
        res = true;
    }
    return res;
}

bool sw_dac_set_pwm(uint8_t num, double frequency, SampleType_t amplitude, double duty_cycle, double phase_ms,
                    double offset) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->frequency = dac_is_valid_freq(frequency);
        Node->amplitude = amplitude;
        Node->duty_cycle = duty_cycle;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dac_mode = DAC_MODE_PWM;
        res = true;
    }

    return res;
}

bool sw_dac_set_sin(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, SampleType_t offset) {
    bool res = false;
    if(0 < amplitude) {
        LOG_WARNING(SW_DAC, "Mode:Sin, Freq %f Hz, Amp %d, Phase %f ms, OffSet %d", frequency, amplitude, phase_ms,
                    offset);
        SwDac_t* Node = SwDacGetNode(num);
        if(Node) {
            Node->frequency = dac_is_valid_freq(frequency);
            Node->amplitude = amplitude;
            Node->phase_ms = phase_ms;
            Node->offset = offset;
            Node->dac_mode = DAC_MODE_SIN;
            res = true;
        } else {
            LOG_ERROR(SW_DAC, "DAC%u NodeErr", num);
        }
    } else {
        LOG_ERROR(SW_DAC, "DAC%u AmpErr", num);
    }
    return res;
}

bool sw_dac_init(void) {
    bool res = true;
    uint32_t cnt = sw_dac_get_cnt();
    LOG_WARNING(SW_DAC, "Init Cnt %u", cnt);
    uint8_t i = 0;
    uint32_t ok = 0;
    for(i = 1; i <= cnt; i++) {
        res = sw_dac_init_one(i);
        if(res) {
            ok++;
        } else {
        }
    }

    if(ok) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool sw_dac_set_fence(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, double offset) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->frequency = dac_is_valid_freq(frequency);
        Node->amplitude = (SampleType_t)amplitude;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dac_mode = DAC_MODE_FENCE;
        res = true;
    }
    return res;
}

bool sw_dac_set_saw(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, double offset) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->frequency = dac_is_valid_freq(frequency);
        Node->amplitude = (SampleType_t)amplitude;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dac_mode = DAC_MODE_SAW;
        res = true;
    }
    return res;
}

bool sw_dac_set_static_period_48k_1000hz_word(uint8_t num) {
    bool res = false;

    LOG_INFO(SW_DAC, "CalcArray:Dac:%u,Freq:48 kHz,1 Period", num);
    LOG_INFO(SW_DAC, "SampleSize 2 Byte");
    LOG_INFO(SW_DAC, "SampleTime 20833 ns");
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->sample_per_second = 48000;
        uint8_t sample_size = Node->sample_bitness / 8;
        LOG_INFO(SW_DAC, "Amplutude: %u,Freq:1 kHz,Sample:%ubyte,Patt:%s", Node->amplitude, sample_size,
                 FramePattern2Str(Node->frame_pattern));

        LOG_INFO(SW_DAC, "MaxTime 1ms");
        // size_t size;
        Node->sample_cnt = 48;
        LOG_INFO(SW_DAC, "SampleCnt 48");
        res = true;

    } else {
        LOG_ERROR(SW_DAC, "NodeErr");
    }

    if(res) {
#ifdef HAS_SW_DAC_STATIC_SAMPLES
        memset(Node->tx_sample_static_array, 0, sizeof(Node->tx_sample_static_array));
#endif

        uint32_t i = 0;
        uint32_t s = 0;
        LOG_INFO(SW_DAC, "SampleMode %s", SwDacMode2Str(Node->dac_mode));
        SampleType_t tx_sample = 0;
        double tx_sample_d = 0.0;

        static const table_col_t cols[] = {
            {5, "No"},      {12, "UpTime"},  {12, "SampleReal"}, {12, "SampleInt"},
            {8, "SpleHex"}, {12, "SampleL"}, {12, "SampleR"},    {21, "SampleBin"},
        };

        table_header(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        uint32_t cur_time_ns = 0;
        double up_time_s = 0.0;
        for(cur_time_ns = 0, i = 0, s = 0; s < Node->sample_cnt; cur_time_ns += 20833, i += 2, s++) {
            cli_printf(TSEP);
            cli_printf(" %3u " TSEP, s + 1);

            switch((uint8_t)Node->dac_mode) {
            case DAC_MODE_SIN: {
                tx_sample_d = calc_sin_sample(cur_time_ns / 1000, 1000.0, Node->phase_ms, ((double)Node->amplitude),
                                              ((double)Node->offset));
                tx_sample = (SampleType_t)tx_sample_d;
            } break;
            case DAC_MODE_CHIRP: {
                // tx_sample = (SampleType_t)calc_chirp_sample(cur_time_ns/1000, Node->frequency, Node->amplitude
                // );
            } break;
            }
            up_time_s = ((double)(s + 1)) / ((double)Node->sample_per_second);
            cli_printf(" %10.8f " TSEP, up_time_s);

            cli_printf(" %10.1f " TSEP, tx_sample_d);
            cli_printf(" %10d " TSEP, tx_sample);
            cli_printf(" 0x%04x " TSEP, (uint16_t)tx_sample);
#ifdef HAS_SW_DAC_STATIC_SAMPLES
            switch((uint8_t)Node->frame_pattern) {
            case CHANNEL_ONLY_RIGHT: {
                Node->tx_sample_static_array[i] = 0;
                Node->tx_sample_static_array[i + 1] = tx_sample;
            } break;
            case CHANNEL_ONLY_LEFT: {
                Node->tx_sample_static_array[i] = tx_sample;
                Node->tx_sample_static_array[i + 1] = 0;
            } break;
            case CHANNEL_BOTH: {
                Node->tx_sample_static_array[i] = tx_sample;
                Node->tx_sample_static_array[i + 1] = tx_sample;
            } break;
            }
            cli_printf(" %10d " TSEP, Node->tx_sample_static_array[i]);
            cli_printf(" %10d " TSEP, Node->tx_sample_static_array[i + 1]);
#endif
            cli_printf(" %s " TSEP, utoa_bin16(tx_sample));
            cli_printf(CRLF);
        }
        table_row_bottom(&(curWriterPtr->stream), cols, ARRAY_SIZE(cols));
        res = true;
    }
    return res;
}

uint32_t sw_dac_calc_max_time_ns(SwDac_t* Node, uint32_t periods) {
    uint32_t max_time_ns = 0;

    double min_freq_hz = Node->frequency;

#ifdef HAS_DTMF
    if(DAC_MODE_DTMF == Node->dac_mode) {
        min_freq_hz = MIN(Node->frequency, Node->frequency2);
    }
#endif
    max_time_ns = (uint32_t)((double)periods) * (1000000000.0 / min_freq_hz);
    LOG_INFO(SW_DAC, "MinFreq:%f Hz,MaxPeriod %u us", min_freq_hz, NSEC_2_USEC_U(max_time_ns));
    return max_time_ns;
}

bool sw_dac_set_fps(uint8_t num, uint32_t fps) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        LOG_INFO(SW_DAC, "DAC%u PrewFPS: %u Hz", num, Node->sample_per_second);
        Node->sample_per_second = fps;
        LOG_INFO(SW_DAC, "DAC%u NewFPS: %u Hz", num, fps);
        res = true;
    } else {
        LOG_ERROR(SW_DAC, "NoNode %u", num);
    }
    return res;
}

/*TODO split to small functions*/
bool sw_dac_set_array(uint8_t num, uint32_t periods, uint32_t min_abs_period_ns) {
    bool res = false;
    LOG_INFO(SW_DAC, "SetArray: Dac%u,Periods:%u,MinPeriod:%u ns", num, periods, min_abs_period_ns);
    uint32_t sample_period_ns = 0;
    uint32_t max_time_ns = 0;
    uint32_t cur_time_ns = 0;
    uint32_t malloc_size = 0;
    uint32_t malloc_base_size = 0;
    SwDac_t* Node = SwDacGetNode(num);
    if(0 < Node->sample_per_second) {
        SwDacNodeDiag(Node);
        LOG_INFO(SW_DAC, "CalcArray: Dac:%u,Periods:%u", num, periods);
        LOG_INFO(SW_DAC, "SampleSize %u Byte", sizeof(SampleType_t));
        sample_period_ns = 1000000000 / Node->sample_per_second;
        LOG_INFO(SW_DAC, "SamplePeriod:%u us", NSEC_2_USEC_U(sample_period_ns));
        if(Node) {
            Node->sample_bitness = sizeof(SampleType_t) * 8;
            uint8_t sample_size = Node->sample_bitness / 8;
            LOG_INFO(SW_DAC, "Amplutude: %u,Freq: %f Hz,Sample:%u Byte", Node->amplitude, Node->frequency, sample_size);
            if(0 == min_abs_period_ns) {
                max_time_ns = sw_dac_calc_max_time_ns(Node, periods);
            } else {
                max_time_ns = min_abs_period_ns;
            }
            // max_time_ns = (uint32_t)((double)periods) * (1000000000.0 / Node->frequency);
            LOG_INFO(SW_DAC, "MaxTime %u ns %u us %u ms", max_time_ns, max_time_ns / 1000, max_time_ns / 1000000);
            // size_t size;
#ifdef HAS_REAL_SAMPLE_ARRAY
#error ererer
            if(Node->real_sample_array) {
                LOG_WARNING(SW_DAC, "FreeRealTx...");
                // size = _msize(Node->tx_sample_array);
                // LOG_INFO(SW_DAC,"The size of the buffer is %d", size);
                FREE_FUN(Node->real_sample_array);
                Node->real_sample_array = NULL;
                LOG_WARNING(SW_DAC, "FreeRealTxOk");
            }
#endif

#ifdef HAS_DYNAMIC_SAMPLES
            if(Node->tx_sample_array) {
                LOG_WARNING(SW_DAC, "FreeTxArray...");
                // size = _msize(Node->tx_sample_array);
                // LOG_INFO(SW_DAC,"The size of the buffer is %d", size);
                FREE_FUN(Node->tx_sample_array);
                Node->tx_sample_array = NULL;
                LOG_WARNING(SW_DAC, "FreeTxArrayOk");
            }
#endif

#ifdef HAS_I2S_RX
            if(Node->rx_sample_array) {
                LOG_WARNING(SW_DAC, "FreeRxArray...");
                // size = _msize(Node->rx_sample_array);
                // LOG_INFO(SW_DAC,"The size of the buffer is %d", size);
                FREE_FUN(Node->rx_sample_array);
                Node->rx_sample_array = NULL;
                LOG_WARNING(SW_DAC, "FreeRxArrayOk");
            }
#endif
            Node->sample_cnt = max_time_ns / sample_period_ns;
            LOG_INFO(SW_DAC, "SampleCnt %u", Node->sample_cnt);

            malloc_base_size = Node->sample_cnt * sizeof(SampleType_t);
#ifdef HAS_REAL_SAMPLE_ARRAY
            Node->real_sample_array = (SampleType_t*)MALLOC_FUN(malloc_base_size);
            if(Node->real_sample_array) {
                LOG_INFO(SW_DAC, "MallocRealOk %u byte", malloc_base_size);
                res = true;
            } else {
                LOG_ERROR(SW_DAC, "MallocRealErr");
                res = false;
            }
#endif
            malloc_size = Node->sample_cnt * 2 * sizeof(sample_size);

#ifdef HAS_DYNAMIC_SAMPLES
            Node->tx_sample_array = (SampleType_t*)MALLOC_FUN(malloc_size);
            if(Node->tx_sample_array) {
                LOG_INFO(SW_DAC, "MallocTxOk %u Byte", malloc_size);
                res = true;
            } else {
                LOG_ERROR(SW_DAC, "MallocTxErr");
                res = false;
            }
#endif

#ifdef HAS_I2S_RX
            Node->rx_sample_array = (SampleType_t*)MALLOC_FUN(malloc_size);
            if(Node->rx_sample_array) {
                LOG_INFO(SW_DAC, "MallocRxOk %u byte", malloc_size);
                res = true;
            } else {
                LOG_ERROR(SW_DAC, "MallocRxErr");
                res = false;
            }
#endif

            res = true;

            if(res) {
                res = true;
                LOG_INFO(SW_DAC, "Malloc4Rx&Tx&Base Ok %u byte", malloc_size * 2 + malloc_base_size);
            } else {
                LOG_ERROR(SW_DAC, "MemoryErr");
            }

        } else {
            LOG_ERROR(SW_DAC, "NodeErr");
        }
    } else {
        LOG_ERROR(SW_DAC, "FreqErr %u Hz", Node->sample_per_second);
    }

    if(res) {
        // uint8_t sample_size = Node->sample_bitness/8;
#ifdef HAS_DYNAMIC_SAMPLES
        memset(Node->tx_sample_array, 0, malloc_size);
#endif

#ifdef HAS_I2S_RX
        memset(Node->rx_sample_array, 0, malloc_size);
#endif

#ifdef HAS_REAL_SAMPLE_ARRAY
        memset(Node->real_sample_array, 0, malloc_base_size);
#endif

        LOG_INFO(SW_DAC, "MallocOk:%u samples", Node->sample_cnt);
        LOG_INFO(SW_DAC, "SampleSize:%u byte", sizeof(SampleType_t));
        LOG_INFO(SW_DAC, "MallocOk:%u byte total", malloc_size);
        uint32_t i = 0;
        uint32_t s = 0;
        LOG_INFO(SW_DAC, "SampleMode %s", SwDacMode2Str(Node->dac_mode));
        SampleType_t tx_sample = 0;
        double tx_sample_d = 0.0;
        for(cur_time_ns = 0, i = 0, s = 0; s < Node->sample_cnt; cur_time_ns += sample_period_ns, i += 2, s++) {
            switch((uint8_t)Node->dac_mode) {
            case DAC_MODE_SIN: {
                tx_sample_d = calc_sin_sample(cur_time_ns / 1000, Node->frequency, Node->phase_ms,
                                              ((double)Node->amplitude), ((double)Node->offset));
                tx_sample = (SampleType_t)tx_sample_d;
            } break;
#ifdef HAS_DTMF
            case DAC_MODE_DTMF: {
                tx_sample_d = calc_dtmf_sample(cur_time_ns / 1000, Node->frequency, Node->frequency2, Node->phase_ms,
                                               ((double)Node->amplitude), ((double)Node->offset));
                tx_sample = (SampleType_t)tx_sample_d;
            } break;
#endif
            case DAC_MODE_CHIRP: {
                // tx_sample = (SampleType_t)calc_chirp_sample(cur_time_ns/1000, Node->frequency, Node->amplitude
                // );
            } break;
            } // switch

            LOG_DEBUG(SW_DAC, "[%3u/%3u]=CalcSample TxSample:%7.1f,TxSample:%5d", s, Node->sample_cnt, tx_sample_d,
                      tx_sample);
#ifdef HAS_REAL_SAMPLE_ARRAY
            if(&Node->real_sample_array[s]) {
                LOG_DEBUG(SW_DAC, "[%3u]=SetRealSample:%5d", s, tx_sample);
                Node->real_sample_array[s] = tx_sample;
            }
#endif

#ifdef HAS_PCM_16_BIT
            // uint16_t sample_data = tx_sample;
#endif

#ifdef HAS_PCM_32_BIT
            // uint32_t sample_data = tx_sample;
#ifdef HAS_MAX9860
            // sample_data = max9860_pcm_2_32bit_sample(tx_sample);
#endif /*HAS_MAX9860*/

#ifdef HAS_WM8731
            tx_sample = wm8731_pcm_2_32bit_sample(tx_sample);
#endif /* HAS_WM8731*/

#ifdef HAS_FDA801
            tx_sample = fda801_pcm_2_32bit_sample(tx_sample);
#endif /* HAS_FDA801*/

#endif /*HAS_PCM_32_BIT*/

#ifdef HAS_PCM_16_BIT

#ifdef HAS_WM8731
            tx_sample = wm8731_pcm_2_16bit_sample(tx_sample);
#endif /* HAS_WM8731*/

#ifdef HAS_FDA801
            tx_sample = fda801_pcm_2_16bit_sample(tx_sample);
#endif /* HAS_FDA801*/

#endif /*HAS_PCM_16_BIT*/

#ifdef HAS_DYNAMIC_SAMPLES
            switch((uint8_t)Node->frame_pattern) {
            case CHANNEL_ONLY_RIGHT: {
                LOG_DEBUG(SW_DAC, "SetTxSample_0X:%5d", tx_sample);
                Node->tx_sample_array[i] = 0;
                Node->tx_sample_array[i + 1] = tx_sample;
            } break;
            case CHANNEL_ONLY_LEFT: {
                LOG_DEBUG(SW_DAC, "SetTxSample_X0:%5d", tx_sample);
                Node->tx_sample_array[i] = tx_sample;
                Node->tx_sample_array[i + 1] = 0;
            } break;
            case CHANNEL_BOTH: {
                LOG_DEBUG(SW_DAC, "SetTxSample_XX:%5d", tx_sample);
                Node->tx_sample_array[i] = tx_sample;
                Node->tx_sample_array[i + 1] = tx_sample;
            } break;
            }
#endif

#ifdef HAS_SW_DAC_STATIC_SAMPLES
            if(i < ARRAY_SIZE(Node->tx_sample_static_array)) {
                switch((uint8_t)Node->frame_pattern) {
                case CHANNEL_ONLY_RIGHT: {
                    Node->tx_sample_static_array[i] = 0;
                    Node->tx_sample_static_array[i + 1] = tx_sample;
                } break;
                case CHANNEL_ONLY_LEFT: {
                    Node->tx_sample_static_array[i] = tx_sample;
                    Node->tx_sample_static_array[i + 1] = 0;
                } break;
                case CHANNEL_BOTH: {
                    Node->tx_sample_static_array[i] = tx_sample;
                    Node->tx_sample_static_array[i + 1] = tx_sample;
                } break;
                }
            } else {
                LOG_DEBUG(SW_DAC, "StaticArrayOverflow %u/%u", i, ARRAY_SIZE(Node->tx_sample_static_array));
            }
#endif

        } // for
        res = true;
    }
    return res;
}

bool sw_dac_rev_hwords(uint8_t num) {
    bool res = false;
    uint32_t cnt = 0;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        if(4 == sizeof(SampleType_t)) {
            for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
#ifdef HAS_DYNAMIC_SAMPLES
                if(&Node->tx_sample_array[i]) {
                    Node->tx_sample_array[i] = reverse_half_word_order_uint32(Node->tx_sample_array[i]);
                    Node->tx_sample_array[i + 1] = reverse_half_word_order_uint32(Node->tx_sample_array[i + 1]);
                }
#endif

#ifdef HAS_I2S_RX
                if(&Node->rx_sample_array[i]) {
                    Node->rx_sample_array[i] = reverse_half_word_order_uint32(Node->rx_sample_array[i]);
                    Node->rx_sample_array[i + 1] = reverse_half_word_order_uint32(Node->rx_sample_array[i + 1]);
                }
#endif
                cnt++;
            }
        } else {
            LOG_ERROR(SW_DAC, "SamplseSize:%u byte", sizeof(SampleType_t));
        }
    }
    if(cnt == Node->sample_cnt) {
        res = true;
    } else {
        LOG_ERROR(SW_DAC, "RevTrackErr Cnt:%u Samplse:%u", cnt, Node->sample_cnt);
    }
    return res;
}

bool sw_dac_pattern_set(uint8_t num, FramePattern_t frame_pattern) {
    bool res = false;
    LOG_INFO(SW_DAC, "%u SetFramePattern %u=%s", num, frame_pattern, FramePattern2Str(frame_pattern));
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        Node->frame_pattern = frame_pattern;
        res = true;
    }
    return res;
}

bool sw_dac_rev_bytes(uint8_t num) {
    bool res = false;
    SwDac_t* Node = SwDacGetNode(num);
    if(Node) {
        uint32_t sample_size = sizeof(SampleType_t);
        LOG_INFO(SW_DAC, "SamplseSize:%u byte", sample_size);
        switch(sample_size) {
        case 2: {
#ifdef HAS_DYNAMIC_SAMPLES
            res = array_u16_item_reverse_bytes((uint16_t*)Node->tx_sample_array, Node->sample_cnt * 2);
#endif

#ifdef HAS_I2S_RX
            res = array_u16_item_reverse_bytes((uint16_t*)Node->rx_sample_array, Node->sample_cnt * 2) && res;
#endif
        } break;
        case 4: {
#ifdef HAS_DYNAMIC_SAMPLES
            res = array_u32_item_reverse_bytes((uint32_t*)Node->tx_sample_array, Node->sample_cnt * 2);
#endif

#ifdef HAS_I2S_RX
            res = array_u32_item_reverse_bytes((uint32_t*)Node->rx_sample_array, Node->sample_cnt * 2) && res;
#endif
        } break;
        default: {
            res = false;
            LOG_ERROR(SW_DAC, "SamplseSize:%u byte", sample_size);
        } break;
        }
    }

    return res;
}

bool sw_dac_match_sample_size(const SwDac_t* const Node, uint8_t sample_bitness) {
    bool res = false;
    if(sample_bitness == Node->sample_bitness) {
        res = true;
    } else {
        LOG_ERROR(SW_DAC, "SamplseSize: Need %u bit, real %u bit", sample_bitness, Node->sample_bitness);
        res = false;
    }
    return res;
}
