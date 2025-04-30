#include "dds_drv.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "array.h"
#include "std_includes.h"
#ifdef HAS_AUDIO
#include "audio.h"
#endif
#include "bit_utils.h"
#include "byte_utils.h"
//#include "utils_math.h"
#include "code_generator.h"
#include "file_pc.h"
#include "convert.h"
#include "data_types.h"
#include "table_utils.h"
#include "time_mcal.h"
#include "log.h"
#ifdef HAS_TIME
#include "time_mcal.h"
#endif
#ifdef HAS_ALLOCATOR
#include "heap_allocator.h"
#endif

#ifdef HAS_WAV
#include "wav.h"
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
#include "code_generator.h"
#include "writer_config.h"

COMPONENT_GET_NODE(Dds, dds)
COMPONENT_GET_CONFIG(Dds, dds)

bool dds_proc_sample(uint8_t num, SampleType_t* out_dds_sample) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node && out_dds_sample) {
        uint64_t cur_time_us = time_get_us();
        switch(Node->dds_mode) {
        case DDS_MODE_STATIC: {
            (*out_dds_sample) = Node->amplitude;
            res = true;
        } break;
        case DDS_MODE_PWM: {
            (*out_dds_sample) = (SampleType_t)calc_pwm_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->duty_cycle, Node->offset);
            res = true;
        } break;
        case DDS_MODE_SIN: {
            (*out_dds_sample) = (SampleType_t)calc_sin_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->offset);
            res = true;

        } break;
        case DDS_MODE_SAW: {
            (*out_dds_sample) = (SampleType_t)calc_saw_sample(cur_time_us, Node->frequency, Node->phase_ms,
                                                              Node->amplitude, Node->offset);
            res = true;
        } break;
        case DDS_MODE_FENCE: {

            (*out_dds_sample) = (SampleType_t)calc_fence_sample(cur_time_us, Node->frequency, Node->phase_ms,
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

static double DDS_is_valid_freq(double frequency) {
    double out_freq = 0.0;
    if(0.0 < frequency) {
        out_freq = frequency;
    } else {
        out_freq = 1.0;
        LOG_ERROR(DDS, "FreqErr %f", frequency);
    }
    return out_freq;
}

static bool dds_init_common(const DdsConfig_t* const Config,
                            DdsHandle_t* const Node){
    bool res = false;
    if(Config) {
        if(Node) {
            Node->amplitude = Config->amplitude;
            Node->dds_mode = Config->dds_mode;
            Node->duty_cycle = Config->duty_cycle;
            Node->frame_pattern = Config->frame_pattern;
            Node->frequency = DDS_is_valid_freq(Config->frequency);
            Node->frequency2 = DDS_is_valid_freq(Config->frequency2);
            Node->name = Config->name;
            Node->offset = Config->offset;
            Node->phase_ms = Config->phase_ms;
            Node->player = Config->player;
            Node->sample_bitness = Config->sample_bitness;
            Node->array_size = Config->array_size;
            Node->sample_per_second = Config->sample_per_second;
            Node->signal_diration_s = Config->signal_diration_s;
            Node->sample_array = Config->sample_array;
            res = true;
        }
    }
    return res;
}

static bool  DdsIsValidConfig(const DdsConfig_t*const  Config){
    bool res = false;
    if(Config){
        res = true;
    }
    if(res){
        if(NULL==Config->sample_array){
            res = false;
            LOG_ERROR(DDS, "DDS,SampleArrErr");
        }else{
            res = true;
        }
    }

    if(res) {
        if(0==Config->array_size) {
            res = false;
            LOG_ERROR(DDS, "DDS,ArraySizeErr");
        }else{
            res = true;
        }
    }

    if(res){
        if(0<=Config->amplitude){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,AmpErr");
        }
    }

    if(res){
        if(0<=Config->frequency){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,FreqErr");
        }
    }

    if(res){
        if(0<=Config->frequency2){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,Freq2Err");
        }
    }

    if(res){
        if(0<Config->sample_bitness){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,SampleSizeErr");
        }
    }

    if(res){
        if(0<Config->sample_per_second){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,FpsErr");
        }
    }


    if(res){
        if(0<Config->signal_diration_s){
            res = true;
        }else{
            res = false;
            LOG_ERROR(DDS, "DDS,SigDurErr");
        }
    }




    return res;
}

bool dds_init_one(uint8_t num) {
    bool res = false;
    const DdsConfig_t* Config = DdsGetConfig(num);
    if(Config) {
        res = DdsIsValidConfig(Config);
        if(res) {
            LOG_WARNING(DDS, "%s",DdsConfigToStr(Config));
            DdsHandle_t* Node = DdsGetNode(num);
            if(Node) {
                res = dds_init_common(Config,Node);
                LOG_WARNING(DDS, "Init %u SampleSize %u byte", num, PCM_SAMPLE_SIZE);
                Node->init = true;
                res = true;
            }else{
                LOG_ERROR(DDS, "DDS%u,NodeErr", num);
            }
        }else{
            LOG_ERROR(DDS, "DDS%u,ConfigErr", num);
        }
    }
    return res;
}

bool dds_set_sample(uint8_t num, SampleType_t sample) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->cur_sample = sample;
        Node->dds_mode = DDS_MODE_STATIC;
        res = true;
    }
    return res;
}

bool dds_set_pwm(uint8_t num, double frequency, SampleType_t amplitude, double duty_cycle, double phase_ms,
                 double offset) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->frequency = DDS_is_valid_freq(frequency);
        Node->amplitude = amplitude;
        Node->duty_cycle = duty_cycle;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dds_mode = DDS_MODE_PWM;
        res = true;
    }

    return res;
}


uint32_t DdsFramePatToNumChann(FramePattern_t frame_pattern){
    uint32_t channel_cnt = 0;
    switch(frame_pattern) {
        case CHANNEL_ONLY_RIGHT: channel_cnt = 2;break;
        case CHANNEL_ONLY_LEFT:channel_cnt = 2; break;
        case CHANNEL_BOTH: channel_cnt = 2;break;
        case CHANNEL_MONO: channel_cnt = 1;break;
        default:
            channel_cnt = 0;
            break;
    }
    return channel_cnt;
}

bool dds_shift_signal(uint8_t num, double phase_s){
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if (Node) {
    	double sample_dur_s = 1.0/((double)Node->sample_per_second);
    	int32_t offset_sam = phase_s/sample_dur_s;
        LOG_INFO(DDS, "AddFront:%u Samples,Dur:%f s", offset_sam,sample_dur_s);

    	res = audio_add_front_zeros(Node->sample_array,Node->array_size,offset_sam);
    }
    return res;
}

bool dds_set_phase_ms(uint8_t num, double phase_ms) {
    bool res = false;
    LOG_WARNING(DDS, "DDS%u,Set,Phase:%f ms", num, phase_ms);
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->phase_ms = phase_ms;
        res = true;
    }else {
        LOG_ERROR(DDS, "DDS%u,NodeErr", num);
    }
    return res;
}

bool dds_phase_set(uint8_t num, double phase_s) {
    bool res = false;
    double phase_ms = SEC_2_MSEC(phase_s);
	res = dds_set_phase_ms(  num,   phase_ms);
    return res;
}

bool dds_set_chirp(uint8_t num,
                   double chirp_duration_s,
                   double frequency1,
                   double frequency2) {
    bool res = false;
    LOG_WARNING(DDS, "Mode:Chirp,Freq1:%f Hz,Freq2:%f Hz,Duration:%f s", frequency1, frequency2, chirp_duration_s);

    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->frequency = frequency1;
        Node->frequency2 = frequency2;
        Node->signal_diration_s = chirp_duration_s;
        Node->dds_mode = DDS_MODE_CHIRP;
        res = true;
    }else {
        LOG_ERROR(DDS, "DDS%u,NodeErr", num);
    }
    return res;
}

bool dds_set_sin(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, SampleType_t offset) {
    bool res = false;
    if(0 < amplitude) {
        LOG_WARNING(DDS, "Mode:Sin,Freq:%f Hz,Amp:%d,Phase:%f ms,OffSet:%d", frequency, amplitude, phase_ms, offset);
        DdsHandle_t* Node = DdsGetNode(num);
        if(Node) {
            Node->frequency = DDS_is_valid_freq(frequency);
            Node->amplitude = amplitude;
            Node->phase_ms = phase_ms;
            Node->offset = offset;
            Node->dds_mode = DDS_MODE_SIN;
            res = true;
        } else {
            LOG_ERROR(DDS, "DDS%u,NodeErr", num);
        }
    } else {
        LOG_ERROR(DDS, "DDS%u,AmpErr", num);
    }
    return res;
}

bool dds_init(void) {
    bool res = true;
    uint32_t cnt = dds_get_cnt();
    LOG_WARNING(DDS, "Init Cnt %u", cnt);
    uint8_t i = 0;
    uint32_t ok = 0;
    for(i = 1; i <= cnt; i++) {
        res = dds_init_one(i);
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

int16_t dds_calc_sin_sample_s16(double t_s, DdsHandle_t* const Node){
	int16_t sample = 0;
	if(Node) {
		if(0.0<t_s) {
    	    uint64_t time_us = (uint64_t) SEC_2_USEC(t_s);
        	double sample_d = calc_sin_sample(time_us,
                                             (double) Node->frequency,
                                             (double) Node->phase_ms,
                                             (double) Node->amplitude,
                                             (double) Node->offset);
        	sample = (int16_t) sample_d;
		}
	}

	return sample;
}


double  DdsPhaseMsToRad(double Fs, double phase_ms) {
	double phase_rad = 0.0;
	phase_rad = 4*M_PI*Fs*phase_ms/1000.0;
	return phase_rad;
}

int16_t dds_calc_sample_s16(double t_s, DdsHandle_t* const Node) {
	int16_t sample = 0;
	if(Node) {
		if(0.0<t_s) {
    	    uint64_t time_us = (uint64_t) SEC_2_USEC(t_s);
    	    double sample_d = 0.0;
    	    switch(Node->dds_mode) {
    	    case DDS_MODE_CHIRP: {
    	      double phase_rad = DdsPhaseMsToRad(Node->sample_per_second, Node->phase_ms);
      	      sample_d = calc_chirp_sample(time_us,
                                           (double) Node->frequency2,
                                           (double) Node->frequency,
                                                    phase_rad,
                                           (double) Node->amplitude,
                                           (double) Node->signal_diration_s);
    	    }break;
    	    case DDS_MODE_SIN: {
        	      sample_d = calc_sin_sample(time_us,
                                             (double) Node->frequency,
                                             (double) Node->phase_ms,
                                             (double) Node->amplitude,
                                             (double) Node->offset);

    	    }break;
    	    default: {}break;
    	    }
        	sample = (int16_t) sample_d;
		}
	}

	return sample;
}


static bool dds_calc_one_sample(DdsHandle_t* Node,
                                uint32_t cur_time_ns,
                                uint32_t i,
                                uint32_t s,
                                SampleType_t* tx_sample) {
    bool res = false;
    Node->tx_sample_d = 0.0;
    Node->tx_sample = 0;
    uint64_t time_us = NSEC_2_USEC_U(cur_time_ns);
    switch((uint8_t)Node->dds_mode) {
        case DDS_MODE_CHIRP: {
            Node->tx_sample_d = calc_chirp_sample(  time_us,
                                       Node->frequency2,
                                       Node->frequency,
                                       0.0,
                                       (double)  Node->amplitude,
                                          Node->signal_diration_s);
            res = true;
        } break;
        case DDS_MODE_SIN: {
            Node->tx_sample_d = calc_sin_sample(cur_time_ns / 1000,
                                                Node->frequency,
                                                Node->phase_ms,
                                                ((double)Node->amplitude),
                                                ((double)Node->offset));
            res = true;
        } break;

        case DDS_MODE_DTMF: {
            Node->tx_sample_d = calc_dtmf_sample(cur_time_ns / 1000,
                                                 Node->frequency,
                                                 Node->frequency2,
                                                 Node->phase_ms,
                                                 ((double)Node->amplitude),
                                                 ((double)Node->offset));
            res = true;
        } break;

    } // switch((uint8_t)Node->dds_mode)
    Node->tx_sample = (SampleType_t)Node->tx_sample_d;
    LOG_PARN(DDS, "%s", DdsSampleToStr(Node,s));
    *tx_sample =Node->tx_sample;

    return res;
}
bool dds_set_fence(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, double offset) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->frequency = DDS_is_valid_freq(frequency);
        Node->amplitude = (SampleType_t)amplitude;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dds_mode = DDS_MODE_FENCE;
        res = true;
    }
    return res;
}

bool dds_set_saw(uint8_t num, double frequency, SampleType_t amplitude, double phase_ms, double offset) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->frequency = DDS_is_valid_freq(frequency);
        Node->amplitude = (SampleType_t)amplitude;
        Node->phase_ms = phase_ms;
        Node->offset = (SampleType_t)offset;
        Node->dds_mode = DDS_MODE_SAW;
        res = true;
    }
    return res;
}
/*
 i - I2S left channel
 s - sample serial number
 */
static bool dds_save_sample(DdsHandle_t* Node,
                            uint32_t i,
                            uint32_t s,
                            SampleType_t tx_sample){
    bool res = false;

    if(i < Node->array_size) {
        switch((uint8_t)Node->frame_pattern) {
            case CHANNEL_ONLY_RIGHT: {
                Node->sample_array[i] = 0;
                Node->sample_array[i + 1] = tx_sample;
                res = true;
            } break;
            case CHANNEL_ONLY_LEFT: {
                Node->sample_array[i] = tx_sample;
                Node->sample_array[i + 1] = 0;
                res = true;
            } break;
            case CHANNEL_BOTH: {
                Node->sample_array[i] = tx_sample;
                Node->sample_array[i + 1] = tx_sample;
                res = true;res = true;
            } break;
            case CHANNEL_MONO: {
                Node->sample_array[s] = tx_sample;
                res = true;
            } break;
        }
    } else {
        LOG_ERROR(DDS, "StaticArrayOverflow:%u/%u", i, Node->array_size);
        res = false;
    }

    return res;
}

bool dds_set_static_period_48k_1000hz_word(uint8_t num) {
    bool res = false;
    LOG_INFO(DDS, "CalcArray:DDS:%u,Freq:48 kHz,1 Period,SampleSize 2 Byte,SampleTime 20833 ns", num);
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->sample_per_second = 48000;
        uint8_t sample_size = Node->sample_bitness / 8;
        LOG_INFO(DDS, "%s,Sample:%u byte,MaxTime:1ms,SampleCnt 48", DdsNodeToStr(Node), sample_size);
        Node->sample_cnt = 48;
        res = true;
    } else {
        LOG_ERROR(DDS, "NodeErr");
    }

    if(res) {
        uint32_t i = 0;
        uint32_t s = 0;
        uint32_t cur_time_ns = 0;
        for(cur_time_ns = 0, i = 0, s = 0; s < Node->sample_cnt; cur_time_ns += 20833, i += 2, s++) {
            SampleType_t tx_sample = 0;
            res = dds_calc_one_sample(Node, cur_time_ns, i, s, &tx_sample);
            res = dds_save_sample(Node, i, s, tx_sample);
        }
        res = true;
    }
    return res;
}

uint32_t dds_calc_max_time_ns(DdsHandle_t* Node, uint32_t periods) {
    uint32_t max_time_ns = 0;

    double min_freq_hz = Node->frequency;

#ifdef HAS_DTMF
    if(DDS_MODE_DTMF == Node->dds_mode) {
        min_freq_hz = MIN(Node->frequency, Node->frequency2);
    }
#endif
    max_time_ns = (uint32_t)((double)periods) * (1000000000.0 / min_freq_hz);
    LOG_INFO(DDS, "MinFreq:%f Hz,MaxPeriod %u us", min_freq_hz, NSEC_2_USEC_U(max_time_ns));
    return max_time_ns;
}

bool dds_set_fps(uint8_t num, uint32_t fps) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        LOG_INFO(DDS, "DDS%u,PrewFPS:%u Hz", num, Node->sample_per_second);
        Node->sample_per_second = fps;
        LOG_INFO(DDS, "DDS%u,NewFPS:%u Hz", num, fps);
        res = true;
    } else {
        LOG_ERROR(DDS, "NoNode %u", num);
    }
    return res;
}


static bool dds_calc_and_save_one_sample(DdsHandle_t* Node,
                                         uint32_t cur_time_ns,
                                         uint32_t i,
                                         uint32_t s) {
    bool res = false;
    if(s<Node->array_size) {
        SampleType_t tx_sample = 0;
        res = dds_calc_one_sample(Node, cur_time_ns, i, s, &tx_sample);
        if(res) {
            res = dds_save_sample(  Node, i,s, tx_sample);
        }
    }
    return res;
}

bool dds_player_set(uint8_t num,DdsPlayer_t player) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->player = player;
        res = true;
    }
    return res;
}

bool dds_set_array(uint8_t num, uint32_t periods, uint32_t min_abs_period_ns) {
    bool res = false;
    LOG_INFO(DDS, "SetArray: Dac%u,Periods:%u,MinPeriod:%u ns", num, periods, min_abs_period_ns);
    uint32_t sample_period_ns = 0;
    uint32_t max_time_ns = 0;
    uint32_t cur_time_ns = 0;
    DdsHandle_t* Node = DdsGetNode(num);
    if(0 < Node->sample_per_second) {
        DdsNodeDiag(Node);
        LOG_INFO(DDS, "CalcArray: Dac:%u,Periods:%u", num, periods);
        LOG_INFO(DDS, "SampleSize %u Byte", sizeof(SampleType_t));
        sample_period_ns = 1000000000 / Node->sample_per_second;
        LOG_INFO(DDS, "SamplePeriod:%u us", NSEC_2_USEC_U(sample_period_ns));
        if(Node) {
            Node->sample_bitness = sizeof(SampleType_t) * 8;
            uint8_t sample_size = Node->sample_bitness / 8;
            LOG_INFO(DDS, "Amplutude: %u,Freq: %f Hz,Sample:%u Byte", Node->amplitude, Node->frequency, sample_size);
            if(0 == min_abs_period_ns) {
                max_time_ns = dds_calc_max_time_ns(Node, periods);
            } else {
                max_time_ns = min_abs_period_ns;
            }
            // max_time_ns = (uint32_t)((double)periods) * (1000000000.0 / Node->frequency);
            LOG_INFO(DDS, "MaxTime:%uns=%uus=%ums", max_time_ns, max_time_ns / 1000, max_time_ns / 1000000);
            // size_t size;
            Node->sample_cnt = max_time_ns / sample_period_ns;
            LOG_INFO(DDS, "SampleCnt %u", Node->sample_cnt);
            res = true;
        } else {
            LOG_ERROR(DDS, "NodeErr");
        }
    } else {
        LOG_ERROR(DDS, "FreqErr %u Hz", Node->sample_per_second);
    }

    if(res) {
        LOG_INFO(DDS, "SamCnt:%u samples", Node->sample_cnt);
        LOG_INFO(DDS, "SampleSize:%u byte", sizeof(SampleType_t));
        uint32_t i = 0;
        uint32_t s = 0;
        LOG_INFO(DDS, "SampleMode %s", DdsMode2Str(Node->dds_mode));

        for(cur_time_ns = 0, i = 0, s = 0;
            s < Node->sample_cnt;
            cur_time_ns += sample_period_ns, i += 2, s++) {
            res = dds_calc_and_save_one_sample(Node, cur_time_ns, i, s);
            if(false==res){
                break;
            }
        }
        res = true;
    }
    return res;
}

bool dds_rev_hwords(uint8_t num) {
    bool res = false;
    uint32_t cnt = 0;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        uint32_t i = 0;
        uint32_t s = 0;
        if(4 == sizeof(SampleType_t)) {
            for(s = 0, i = 0; s < Node->sample_cnt; s++, i += 2) {
                if(&Node->sample_array[i]) {
                    Node->sample_array[i] = reverse_half_word_order_uint32(Node->sample_array[i]);
                    Node->sample_array[i + 1] = reverse_half_word_order_uint32(Node->sample_array[i + 1]);
                }

#ifdef HAS_I2S_RX
                if(&Node->rx_sample_array[i]) {
                    Node->rx_sample_array[i] = reverse_half_word_order_uint32(Node->rx_sample_array[i]);
                    Node->rx_sample_array[i + 1] = reverse_half_word_order_uint32(Node->rx_sample_array[i + 1]);
                }
#endif
                cnt++;
            }
        } else {
            LOG_ERROR(DDS, "SamplseSize:%u byte", sizeof(SampleType_t));
        }
    }
    if(cnt == Node->sample_cnt) {
        res = true;
    } else {
        LOG_ERROR(DDS, "RevTrackErr Cnt:%u Samplse:%u", cnt, Node->sample_cnt);
    }
    return res;
}

bool dds_pattern_set(uint8_t num, FramePattern_t frame_pattern) {
    bool res = false;
    LOG_INFO(DDS, "%u SetFramePattern %u=%s", num, frame_pattern, FramePatternToStr(frame_pattern));
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->frame_pattern = frame_pattern;
        res = true;
    }
    return res;
}

bool dds_rev_bytes(uint8_t num) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        uint32_t sample_size = sizeof(SampleType_t);
        LOG_INFO(DDS, "SamplseSize:%u byte", sample_size);
        switch(sample_size) {
        case 2: {
            res = array_u16_item_reverse_bytes((uint16_t*)Node->sample_array, Node->sample_cnt * 2);

#ifdef HAS_I2S_RX
            res = array_u16_item_reverse_bytes((uint16_t*)Node->rx_sample_array, Node->sample_cnt * 2) && res;
#endif
        } break;
        case 4: {
            res = array_u32_item_reverse_bytes((uint32_t*)Node->sample_array, Node->sample_cnt * 2);

#ifdef HAS_I2S_RX
            res = array_u32_item_reverse_bytes((uint32_t*)Node->rx_sample_array, Node->sample_cnt * 2) && res;
#endif
        } break;
        default: {
            res = false;
            LOG_ERROR(DDS, "SamplseSize:%u byte", sample_size);
        } break;
        }
    }

    return res;
}

bool dds_match_sample_size(const DdsHandle_t* const Node, uint8_t sample_bitness) {
    bool res = false;
    if(sample_bitness == Node->sample_bitness) {
        res = true;
    } else {
        LOG_ERROR(DDS, "SamplseSize:Need:%u bit,real:%u bit", sample_bitness, Node->sample_bitness);
        res = false;
    }
    return res;
}

bool dds_set_array_ext(uint8_t num, uint32_t fps, SampleType_t* array, uint32_t sample_cnt) {
    bool res = false;
    res = dds_set_sin(num, 1000.0, 1000, 0.0, 0);
    if(res) {
        res = dds_set_fps(num, fps);
        if(res) {
            res = dds_set_array(num, 1, 0);
            if(res) {
                res = false;
                DdsHandle_t* Node = DdsGetNode(num);
                if(Node) {
                    size_t common_channel_cnt = MIN((2 * sample_cnt), DDS_STATIC_CHANNEL_CNT);
                    memcpy(array, Node->sample_array, sizeof(SampleType_t) * common_channel_cnt);
                    res = true;
                } else {
                    LOG_ERROR(DDS, "Node,Err");
                    res = false;
                }
            } else {
                LOG_ERROR(DDS, "Arr,Calc,Err");
                res = false;
            }
        } else {
            LOG_ERROR(DDS, "Fps,Set,Err");
            res = false;
        }
    } else {
        LOG_ERROR(DDS, "Sin,Set,Err");
        res = false;
    }
    return res;
}


int16_t DdsPlayerToI2sNum(DdsPlayer_t player) {
    int16_t i2s_num = -1;
    switch((uint32_t)player) {
    case DDS_PLAYER_I2S0:
        i2s_num = 0;
        break;
    case DDS_PLAYER_I2S1:
        i2s_num = 1;
        break;
    case DDS_PLAYER_I2S2:
        i2s_num = 2;
        break;
    case DDS_PLAYER_I2S3:
        i2s_num = 3;
        break;
    case DDS_PLAYER_I2S4:
        i2s_num = 4;
        break;
    case DDS_PLAYER_I2S5:
        i2s_num = 5;
        break;
    case DDS_PLAYER_I2S6:
        i2s_num = 6;
        break;
    default:
        i2s_num = -1;
        break;
    }
    return i2s_num;
}

static DdsPlayer_t I2sNumToPlayer(uint8_t i2s_num) {
    DdsPlayer_t player = DDS_PLAYER_UNDEF;
    switch(i2s_num) {
    case 0:
        player = DDS_PLAYER_I2S0;
        break;
    case 1:
        player = DDS_PLAYER_I2S1;
        break;
    case 2:
        player = DDS_PLAYER_I2S2;
        break;
    case 3:
        player = DDS_PLAYER_I2S3;
        break;
    case 4:
        player = DDS_PLAYER_I2S4;
        break;
    case 5:
        player = DDS_PLAYER_I2S5;
        break;
    case 6:
        player = DDS_PLAYER_I2S6;
        break;
    default:
        break;
    }
    return player;
}

bool dds_play_stop(DdsHandle_t* Node) {
    bool res = false;
    switch(Node->player) {
        case DDS_PLAYER_WAV_FILE:
        case DDS_PLAYER_CSV_FILE:
            Node->state = DDS_STATE_IDLE;
            res = true;
            break;
        case DDS_PLAYER_I2S0:
        case DDS_PLAYER_I2S1:
        case DDS_PLAYER_I2S2:
        case DDS_PLAYER_I2S3:
        case DDS_PLAYER_I2S4: {
    #ifdef HAS_I2S
            int16_t i2s_num = DdsPlayerToI2sNum(Node->player);
            if(0 < i2s_num) {
                res = i2s_stop((uint8_t)i2s_num);
                if(res) {
                    Node->state = DDS_STATE_IDLE;
                }
            }
    #endif

        }break;
        default:
            res = false;
            break;
    }
    return res;
}



bool dds_stop(uint8_t num) {
    bool res = false;
    LOG_INFO(DDS, "DDS%u,Stop", num);
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        res=dds_play_stop(Node);
    }
    return res;
}

static bool dds_play_in_i2s_ll(DdsHandle_t* Node, uint8_t i2s_num) {
    bool res = false ;
#ifdef HAS_I2S
    int16_t i2s_num = DdsPlayerToI2sNum(Node->player);
    if(0 < i2s_num) {
        res = i2s_api_write((uint8_t)i2s_num, (SampleType_t*)Node->sample_array, Node->sample_cnt);
        if(res) {
            LOG_INFO(DDS, "I2s%u,Write,Ok", i2s_num);
        } else {
            LOG_ERROR(DDS, "I2s%u,Write,Err", i2s_num);
        }
    }
#endif
    return res;
}

static bool dds_play_in_csv_ll(DdsHandle_t* const Node) {
    bool res = false;
    uint32_t i = 0;
    LOG_INFO(DDS, "PlayInCsv");
    char csv_file[200] = {0};
    snprintf(csv_file,sizeof(csv_file),"signal_%u.csv",Node->sample_cnt);
    res = file_pc_delete(csv_file);
    char text[400]={0};
    double sample_period_s = 1.0/((double)Node->sample_per_second);
    uint32_t cnt = MIN(Node->array_size,Node->sample_cnt);
    for(i=0; i<cnt; i++) {
        double up_time_s = ((double)i) * sample_period_s;
        strcpy(text,"");
        snprintf(text,sizeof(text),"%s%.5f,",text, up_time_s);
        snprintf(text,sizeof(text),"%s%u,",text, i);
        snprintf(text,sizeof(text),"%s%d,",text, Node->sample_array[i]);
        snprintf(text,sizeof(text),"%s",text);
        res = file_pc_print_line(csv_file, text, strlen(text));
    }
    return res;
}

static bool dds_play_in_wav_ll(DdsHandle_t* Node) {
    bool res = false ;
    LOG_INFO(DDS, "PlayInWav");
    res = wav_generate(1, Node->num);
    log_res(DDS,res,"WavGenerate");
    return res;
}

static bool dds_play_ll(DdsHandle_t* Node){
    bool res = false ;
    LOG_INFO(DDS, "Play");
    switch(Node->player) {
        case DDS_PLAYER_CSV_FILE: res = dds_play_in_csv_ll(Node); break;
        case DDS_PLAYER_WAV_FILE: res = dds_play_in_wav_ll(Node); break;
        case DDS_PLAYER_I2S0: res=dds_play_in_i2s_ll(Node,0); break;
        case DDS_PLAYER_I2S1: res=dds_play_in_i2s_ll(Node,1);break;
        case DDS_PLAYER_I2S2: res=dds_play_in_i2s_ll(Node,2);break;
        case DDS_PLAYER_I2S3:res=dds_play_in_i2s_ll(Node,3); break;
        case DDS_PLAYER_I2S4:res=dds_play_in_i2s_ll(Node,4); break;
        default:  LOG_ERROR(DDS, "UndefPlayerErr:%u",Node->player); break;
    }
    return res;
}

bool dds_play(uint8_t num, uint64_t duration_ms) {
    bool res = false;
    LOG_INFO(DDS, "DDS%u,Play,Duration:%llu ms", num, duration_ms);
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->duration_ms = duration_ms;
        Node->proc_on = true;
        LOG_INFO(DDS, "Play:%s", DdsNodeToStr(Node));
        res = dds_play_ll(Node);
        if(res) {
            uint32_t up_time = time_get_ms32();
            Node->play_off_time_stamp_ms = (uint64_t)up_time + duration_ms;
            Node->state = DDS_STATE_PLAY;
            res = true;
        }else {
            LOG_ERROR(DDS, "PlayErr");
        }
    } else {
        LOG_ERROR(DDS, "NodeErr");
    }
    return res;
}

bool dds_init_custom(void) {
    bool res = true;
    LOG_INFO(DDS, "InitCostom");
    return res;
}


bool dds_i2s_play1khz(uint8_t num, uint8_t i2s_num, SampleType_t amplitude, uint64_t duration_ms) {
    bool res = false;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        Node->player = I2sNumToPlayer(i2s_num);
        Node->amplitude = amplitude;
        res = dds_play(num, duration_ms);
    }
    return res;
}

bool dds_play1khz(uint8_t num, SampleType_t amplitude, double offset, double phase) {
    bool res = false;
    res = dds_set_sin(num, 1000.0, amplitude, phase, offset);
    if(res) {
        res = dds_play(num, 0xFFFFFFFF);
    }
    return res;
}

bool dds_proc_one(uint8_t num) {
    bool res = true;
    DdsHandle_t* Node = DdsGetNode(num);
    if(Node) {
        if(Node->proc_on) {
            uint64_t up_time = time_get_ms64();
            switch((uint8_t)Node->state) {
            case DDS_STATE_PLAY: {
                if(Node->play_off_time_stamp_ms < up_time) {
                    res = dds_stop(num);
                    LOG_DEBUG(DDS, "PlayStop");
                }

            } break;

            } // switch
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(DDS, DDS, dds)
COMPONENT_PROC_PATTERT(DDS, DDS, dds)
