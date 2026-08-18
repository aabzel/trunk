#include "sonar.h"

#include <complex.h>
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "audio_types.h"
#include "code_generator.h"
#include "dds_drv.h"
#include "debug_info.h"
#include "file_mcal.h"
#include "float_diag.h"
#include "log.h"
#include "wav.h"

#ifdef HAS_FFT
#include "fft_mcal.h"
#endif

#ifdef HAS_PROBING_PULSE
#include "probing_pulse_mcal.h"
#endif

#ifdef HAS_CORRELATOR_S16
#include "correlator_s16.h"
#endif

#ifdef HAS_BARKER_CODE
#include "barker_code.h"
#endif

#ifdef HAS_FIR
#include "fir.h"
#endif

#ifdef HAS_LOOPBACK_AUDIO
#include "loopback_audio_mcal.h"
#endif

#ifdef HAS_SCAN
#include "scan.h"
#endif

#ifdef HAS_DFT
#include "dft.h"
#endif

#ifdef HAS_FILE_PC
#include "file_pc.h"
#endif

#ifdef HAS_COMPLEX
#include "complex_math.h"
#endif

#ifdef HAS_WIN
#include "win_utils.h"
#endif

#ifdef HAS_M_SEQ
#include "m_seq_mcal.h"
#endif

#ifdef HAS_PHYSICS
#include "physics_const.h"
#endif

COMPONENT_GET_NODE(Sonar, sonar)

COMPONENT_GET_CONFIG(Sonar, sonar)

static bool sonar_calc_and_load_to_correlator(SonarHandle_t* const Node) {
    bool res = false;
    uint32_t min_abs_period_ns = SEC_2_NSEC(Node->signal_duration_s);
    res = dds_set_array(Node->dds_num, 0, min_abs_period_ns);
    if (res) {
        DdsHandle_t *Dds = DdsGetNode(Node->dds_num);
        if (Dds) {
#ifdef HAS_CORRELATOR_S16
            res = correlator_s16_write_ref_signal(Node->correlator_num, Dds->sample_array, Dds->sample_cnt);
            log_info_res(SONAR,res,"correlator_s16_write_ref_signal");
#endif
        } else {
            LOG_ERROR(SONAR, "DDS_%u,GetNode,Error", Node->dds_num);
        }
    } else {
        LOG_ERROR(SONAR, "ddsSetArray,Error");
    }
    return res;
}

bool sonar_zonding_signal(uint32_t num, char* rec_file_name) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        if(rec_file_name) {
            LOG_ERROR(SONAR, "SONAR_%u,SetName:[%s]",num, rec_file_name);
            strcpy(Node->sonar_signal_wav, rec_file_name);
            res = true;
        }
    }
    return res;
}

static bool sonar_init_common(const SonarConfig_t* const Config, SonarHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {

#ifdef HAS_PROBING_PULSE
            Node->zonding_impulse_type = Config->zonding_impulse_type;
#endif

            Node->amplitude = Config->amplitude;
            Node->signal_duration_s = Config->signal_duration_s;
            Node->v_sound_m_pes_sec = Config->v_sound_m_pes_sec;
            Node->frequency1 = Config->frequency1;
            Node->frequency2 = Config->frequency2;
            Node->correlator_num = Config->correlator_num;
            Node->m_seq_num = Config->m_seq_num;
            Node->num = Config->num;
            Node->loopback_audio_num = Config->loopback_audio_num;
            Node->dds_num = Config->dds_num;

            if(Config->correlation_file_name) {
                strcpy(Node->correlation_file, Config->correlation_file_name);
            }
#if 0
            ProbingPulseConfig_t* Pulse = ProbingPulseGetConfig(1);
            if(Pulse) {
                res = sonar_zonding_signal(Node->num, Pulse->sonar_signal_wav_name);
            }
#endif
            Node->chirp_sn = 0;
            res = true;
        }
    }
    return res;
}

static bool SonarIsValidConfig(SonarConfig_t* Config) {
    bool res = false;
    if(Config) {
        res = true;

        ifn(0.0 < Config->frequency1) {
            LOG_ERROR(SONAR, "Cfg,Error,frequency1:%u", Config->num);
            res = false;
        }

        ifn(0.0 < Config->frequency2) {
            LOG_ERROR(SONAR, "Cfg,Error,frequency2:%u", Config->num);
            res = false;
        }

        ifn(0.0 < Config->signal_duration_s) {
            res = false;
            LOG_ERROR(SONAR, "Cfg,Error,chirpDuration_s:%u", Config->num);
        }

        ifn(Config->correlation_file_name) {
            res = false;
            LOG_ERROR(SONAR, "Cfg,Error,convolutionFileName:%u", Config->num);
        }
    }
    return res;
}

bool sonar_config_correlator_chirp(uint32_t num, float signal_duration_s, float amplitude, float frequency1,
                                   float frequency2) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        Node->signal_duration_s = signal_duration_s;
        Node->amplitude = amplitude;
        Node->frequency1 = frequency1;
        Node->frequency2 = frequency2;
        res = dds_set_chirp(Node->dds_num, Node->amplitude, signal_duration_s, frequency1, frequency2);
        if(res) {
            res = sonar_calc_and_load_to_correlator(Node);
            log_info_res(SONAR, res, "LoadChirpCodeToCorrelator");
        }
    }
    return res;
}

#ifdef HAS_BARKER_CODE
bool sonar_config_correlator_barker13(uint32_t num, float amplitude, float carrier_frequency_hz,
                                      uint32_t periods_per_chip) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        LOG_WARNING(SONAR, "SetRefSignal,Barker13,Amp:%f,CarFreq:%f Hz,PerPerChip:%u", amplitude, carrier_frequency_hz,
                    periods_per_chip);
        Node->amplitude = amplitude;
        Node->frequency1 = carrier_frequency_hz;
        Node->periods_per_chip = periods_per_chip;
        res = dds_set_barker13(Node->dds_num, Node->amplitude, carrier_frequency_hz, periods_per_chip);

        Node->signal_duration_s = barker13_signal_duration(carrier_frequency_hz, periods_per_chip);
        if(res) {
            res = sonar_calc_and_load_to_correlator(Node);
            log_info_res(SONAR, res, "LoadBarker13CodeToCorrelator");
        }
    }
    return res;
}
#endif

bool sonar_config_correlator_m_seq(uint8_t num, uint8_t m_seq_num, float amplitude, float carrier_frequency_hz,
                                   uint32_t periods_per_chip) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        LOG_WARNING(SONAR, "SetRefSignal,M-seq,Amp:%f,CarFreq:%f Hz,PerPerChip:%u", amplitude, carrier_frequency_hz,
                    periods_per_chip);
        Node->amplitude = amplitude;
        Node->frequency1 = carrier_frequency_hz;
        Node->periods_per_chip = periods_per_chip;
        res = dds_set_m_seq(Node->dds_num, m_seq_num, Node->amplitude, carrier_frequency_hz, periods_per_chip);
        Node->signal_duration_s = m_seq_signal_duration(m_seq_num, carrier_frequency_hz, periods_per_chip);
        if(res) {
            res = sonar_calc_and_load_to_correlator(Node);
            log_info_res(SONAR, res, "LoadMSeqCodeToCorrelator");
        }
    }
    return res;
}

bool sonar_config_correlator_mono(uint32_t num,
                                  float signal_duration_s,
                                  float amplitude,
                                  float carrier_frequency_hz) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        LOG_WARNING(SONAR, "SetRefSignal,Mono,Amp:%f,CarFreq:%f Hz,PerPerChip:%u", amplitude, carrier_frequency_hz);
        Node->amplitude = amplitude;
        Node->frequency1 = carrier_frequency_hz;
        Node->signal_duration_s = signal_duration_s;
        res = dds_signal_duration_set(Node->dds_num,   signal_duration_s);
        res = dds_set_sin(Node->dds_num, carrier_frequency_hz, (SampleType_t)amplitude, 0, 0);
        if(res) {
            res = sonar_calc_and_load_to_correlator(Node);
            log_info_res(SONAR, res, "LoadMonoCodeToCorrelator");
        }
    }
    return res;
}


bool sonar_init_one(uint32_t num) {
    bool res = false;
    LOG_WARNING(SONAR, "Init:%u", num);
    const SonarConfig_t* Config = SonarGetConfig(num);
    res = SonarIsValidConfig(Config);
    if(res) {
        if(res) {
            SonarHandle_t* Node = SonarGetNode(num);
            if(Node) {
                res = sonar_init_common(Config, Node);


                switch(Node->zonding_impulse_type) {
                case PROBING_PULSE_TYPE_MONO: {
                    res = sonar_config_correlator_mono(num, Node->signal_duration_s, Node->amplitude, Node->frequency1);
                } break;

                case PROBING_PULSE_TYPE_CHIRP: {
                    res = sonar_config_correlator_chirp(num, Node->signal_duration_s, Node->amplitude, Node->frequency1,
                                                        Node->frequency2);
                } break;
#ifdef HAS_BARKER_CODE
                case PROBING_PULSE_TYPE_BAKER13: {
                    res = sonar_config_correlator_barker13(num, Node->amplitude, Node->frequency1,
                                                           Node->periods_per_chip);

                } break;
#endif
                case PROBING_PULSE_TYPE_M_SEQ: {
                    res = sonar_config_correlator_m_seq(num, Node->m_seq_num, Node->amplitude, Node->frequency1,
                                                        Node->periods_per_chip);

                } break;
                default: {

                } break;
                }

                res = sonar_correlation_ctrl(num, Config->calc_correlation);
                Node->conv_sn = 0;
                Node->state = SONAR_STATE_IDLE;
                Node->valid = true;
                Node->init = true;
                res = true;
            }
        }
    }
    return res;
}

bool sonar_chirp_to_wav(uint32_t num) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        LOG_INFO(SONAR, "ZondingSignalToWav,[%s]", SonarNodeToStr(Node));
#if 0
        float signal_duration_s = dds_signal_duration_get(Node->dds_num);
        res = wav_duration_set(WAV_NUM_GENERATE, signal_duration_s);
        res = wav_generate_signal(WAV_NUM_GENERATE, Node->dds_num, "Zon");
#endif
        res = wav_generate(num, Node->sonar_signal_wav, Node->dds_num);
    }
    return res;
}

static bool sonar_compose_rx_file_name_ll(SonarHandle_t* Node) {
    bool res = false;
    if(Node) {
        if(Node->reflected_radar_signal_wav) {
            uint32_t up_time_ms = time_get_ms32();
            uint32_t signal_duration_ms = SEC_2_MSEC_U32(Node->signal_duration_s);

            strcpy(Node->reflected_radar_signal_wav, "");
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_Rx_%u", Node->reflected_radar_signal_wav,   Node->play_cnt );
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_UT%uus", Node->reflected_radar_signal_wav,   up_time_ms);
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_%s", Node->reflected_radar_signal_wav,   ProbingPulseToStr(Node->zonding_impulse_type) );
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_fs_%u", Node->reflected_radar_signal_wav,     (uint32_t)Node->frequency1);
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_A%u", Node->reflected_radar_signal_wav,   (uint32_t)Node->amplitude);
            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_dt%ums", Node->reflected_radar_signal_wav,   signal_duration_ms);

            switch(Node->zonding_impulse_type) {
                case PROBING_PULSE_TYPE_CHIRP: {
                    snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_fe_%u", Node->reflected_radar_signal_wav,     (uint32_t)Node->frequency2);
                } break;

                case PROBING_PULSE_TYPE_BAKER13: {
                    snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_fe_%u", Node->reflected_radar_signal_wav,Node->periods_per_chip);
                } break;

                case PROBING_PULSE_TYPE_M_SEQ: {
                    snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s_fe_%u", Node->reflected_radar_signal_wav,Node->periods_per_chip);
                } break;

                default: {
                } break;
            }

            snprintf(Node->reflected_radar_signal_wav, sizeof(Node->reflected_radar_signal_wav), "%s.wav", Node->reflected_radar_signal_wav);
            LOG_INFO(SONAR, "RxFile:[%s]", Node->reflected_radar_signal_wav);
            res = true;
        }
    }
    return res;
}

static bool sonar_init_tx_pulse(SonarHandle_t* Node, ProbingPulseHandle_t* Pulse) {
    bool res = false;
    if(Pulse) {
        if(Node) {
            Node->frequency1 = Pulse->frequency1;
            Node->frequency2 = Pulse->frequency2;
            Node->amplitude = Pulse->amplitude;
            Node->zonding_impulse_type = Pulse->zonding_impulse_type;
            Node->periods_per_chip = Pulse->periods_per_chip;
            Node->signal_duration_s = Pulse->signal_duration_s;
            res = true;
        }
    }
    return res;
}

static bool sonar_proc_idle_ll(SonarHandle_t* Node) {
    bool res = false;
    uint32_t pulse_cnt = probing_pulse_get_cnt();
    ProbingPulseHandle_t* Pulse=ProbingPulseGetNode(Node->next_play%pulse_cnt);
    if(Pulse) {
        res = sonar_init_tx_pulse(Node, Pulse);
        res = sonar_compose_rx_file_name_ll(Node);
#ifdef HAS_LOOPBACK_AUDIO
        res = loopback_audio_play_rec_file(Node->loopback_audio_num, Pulse->sonar_signal_wav_name,
                                           Node->reflected_radar_signal_wav);
        if(res) {
            Node->state = SONAR_STATE_PLAY_PROBING_SIGNAL;
            Pulse->tx_cnt++;
            Node->play_cnt++;
            Node->next_play++;
        }
#endif
    }
    return res;
}

static bool sonar_proc_play_probing_signal_ll(SonarHandle_t* Node) {
    bool res = false;
#ifdef HAS_LOOPBACK_AUDIO
    res = loopback_audio_is_idle(Node->loopback_audio_num);
    if(res) {
        Node->state = SONAR_STATE_CALC_CORRELATION;
    }
#endif
    return res;
}

static bool sonar_proc_calc_correlation_ll(SonarHandle_t* Node) {
    bool res = false;
    if(Node->calc_correlation) {
#ifdef HAS_SONAR_CORRELATION
        res = sonar_calc_correlation(Node->num, Node->reflected_radar_signal_wav);
#endif
        Node->state = SONAR_STATE_IDLE;
    } else {
        Node->start_ms = time_get_ms32();
        Node->state = SONAR_STATE_TIMEOUT;
    }
    return res;
}

static bool sonar_proc_time_out_ll(SonarHandle_t* Node) {
    bool res = false;
    uint32_t duration_ms = time_get_ms32() - Node->start_ms;
    if(SONAR_TIMEOUT_MS < duration_ms) {
        Node->start_ms = time_get_ms32();
        Node->state = SONAR_STATE_IDLE;
        res = false;
    }
    return res;
}

bool sonar_correlation_ctrl(uint32_t num, bool on_off) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        Node->calc_correlation = on_off;
        res = true;
    }
    return res;
}

bool sonar_proc_one(uint32_t num) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        switch(Node->state) {
        case SONAR_STATE_IDLE: {
            res = sonar_proc_idle_ll(Node);
        } break;

        case SONAR_STATE_PLAY_PROBING_SIGNAL: {
            res = sonar_proc_play_probing_signal_ll(Node);
        } break;

        case SONAR_STATE_CALC_CORRELATION: {
            res = sonar_proc_calc_correlation_ll(Node);
        } break;

        case SONAR_STATE_TIMEOUT: {
            res = sonar_proc_time_out_ll(Node);
        } break;

        default: {
            res = false;
        } break;
        }
    }

    return res;
}

static bool sonar_init_custom(void) {
    bool res = true;
    return res;
}

#ifdef HAS_CORRELATOR_S16
static bool sonar_proc_sample(SonarHandle_t* const Node, int16_t sample, int64_t* const correlation) {
    bool res = false;
    if(Node) {
        if(correlation) {
            *correlation = correlator_s16_proc_in_out_short(Node->correlator_num, sample);
            // LOG_DEBUG(SONAR, "%d->%d",sample, *correlation );
            res = true;
        }
    }
    return res;
}
#endif



#ifdef HAS_DFT
double complex RecSpectrum[SONAR_MAX_SPEC] = {0};
double complex PulseSpectrum[SONAR_MAX_SPEC] = {0};
double complex MuxSpectrum[SONAR_MAX_SPEC] = {0};
#endif


static bool dsp_array_zero(SampleType_t* const Signal, const uint32_t size) {
    bool res = false;
    if(Signal) {
        uint32_t i = 0;
        for (i = 0; i < size; i++) {
            Signal[i] = 0;
        }
        res = true;
    }
    return res;
}

static bool dsp_array_cpy(SampleType_t* const SignalDst,
                          const SampleType_t* const SignalSrc,
                          const uint32_t channels,
                          const uint32_t size) {
    bool res = false;
    if(SignalDst) {
        if(SignalSrc) {
            LOG_INFO(SONAR, "CopySamples,Channels:%u,Size:%u Sam", channels,size);
            if(size) {
                if(channels) {
                    uint32_t i = 0;
                    for (i = 0; i < size; i++) {
                        LOG_DEBUG(SONAR,"S[%u]=WAV[%u]=%d=0x%04x", i,i * channels,SignalSrc[i * channels],SignalSrc[i * channels]);
                        SignalDst[i] = SignalSrc[i * channels];
                    }
                    res = true;
                }
            }
        }
    }
    return res;
}

/*
 */
bool sonar_dft_convolution(const char* const pulse_file_name, const char* const rec_file_name) {
    bool res = false;
    if(rec_file_name) {
        if(pulse_file_name) {
            LOG_INFO(SONAR, "SampleSize:%u Byte", sizeof(SampleType_t));
            LOG_INFO(SONAR, "RecFile:[%s]", rec_file_name);
            LOG_INFO(SONAR, "PulseFile:[%s]", pulse_file_name);
            res = wav_load(1, rec_file_name);
            if(res) {
                res = wav_load(2, pulse_file_name);
                if(res) {
                    res = false;
                    WavHandle_t* Rec = WavGetNode(1);
                    if(Rec) {
                        uint32_t start_ms = time_get_ms32();
                        SampleType_t* signal_rec = NULL;
                        SampleType_t* signal_pulse_ptr = NULL;

                        uint32_t size_sig = 0;
                        uint32_t max_sample_cnt = 0;
                        WavHandle_t* Pulse = WavGetNode(2);
                        if(Pulse) {
                            //max_sample_cnt = MAX(Rec->sample_cnt, Pulse->sample_cnt);
                            max_sample_cnt = ( Rec->sample_cnt+ Pulse->sample_cnt-1);
                            LOG_INFO(SONAR, "max_sample_cnt:%u sample", max_sample_cnt);
                            size_sig = max_sample_cnt * sizeof(SampleType_t);
                            LOG_INFO(SONAR, "size_sig:%u Byte", size_sig);
                            signal_rec = (SampleType_t*)malloc(size_sig);
                            if(signal_rec) {
                                signal_pulse_ptr = (SampleType_t*)malloc(size_sig);
                                if(signal_pulse_ptr) {
                                    res = true;
                                    dsp_array_zero(signal_rec,     max_sample_cnt) ;
                                    dsp_array_zero(signal_pulse_ptr,     max_sample_cnt) ;
                                }
                            }
                        }else {
                            LOG_ERROR(SONAR, "Wav2GetNode");
                        }

                        LOG_INFO(SONAR, "Fs:%u Hz", Pulse->sampling_frequency_hz);
                        LOG_INFO(SONAR, "SONAR_MAX_SPEC:%u ", SONAR_MAX_SPEC);
                        double sampling_period_s = 1.0 / ((double)Pulse->sampling_frequency_hz);
                        (void)sampling_period_s;
                        LOG_INFO(SONAR, "SamTime:%f s", sampling_period_s);
                        double measured_interval_s = ((double) max_sample_cnt) * sampling_period_s;
                        (void)measured_interval_s;
                        //uint32_t max_garmotic = dft_freq_to_garmonic( 48000, measured_interval_s);
                        uint32_t max_garmotic = max_sample_cnt;
                        LOG_INFO(SONAR, "maxGarmotic:%u", max_garmotic);
                        if(res) {


                            //SampleType_t* RecSam = (SampleType_t*)Rec->data;
                            //SampleType_t* PulseSam = (SampleType_t*)Pulse->data;
                            LOG_INFO(SONAR, "CopyPulse:");
                            res = dsp_array_cpy( signal_pulse_ptr, (SampleType_t*)Pulse->data, Pulse->channels, Pulse->sample_cnt);
                            log_res(SONAR,res,"SignalPulseFill");

                            LOG_INFO(SONAR, "CopyRec:");
                            res = dsp_array_cpy( signal_rec, (SampleType_t*)Rec->data, Rec->channels, Rec->sample_cnt);
                            log_res(SONAR,res,"signalRecFill");

                            // Up ok
#ifdef HAS_DFT
                            if(max_sample_cnt < SONAR_MAX_SPEC) {
                                res = dft_calc(signal_rec, max_sample_cnt, RecSpectrum, sampling_period_s, max_garmotic);
                                log_res(SONAR,res,"dft_calcRec");
                                if(res) {
                                    res = dft_calc(signal_pulse_ptr, max_sample_cnt, PulseSpectrum, sampling_period_s, max_garmotic);
                                    log_res(SONAR,res,"dft_calcPulse");
                                }
                            } else {
                                LOG_ERROR(SONAR, "MAX:%u,Need:%u", SONAR_MAX_SPEC, max_sample_cnt);
                            }
#endif
                        }
                        // untested code \/
#ifdef HAS_DFT
                        if(res) {
                            res = complex_array_conjugate( PulseSpectrum,  max_garmotic);
                            log_res(SONAR,res,"complex_array_conjugate");
                            res = complex_array_mux(RecSpectrum, PulseSpectrum, MuxSpectrum, max_garmotic);
                            log_res(SONAR,res,"complex_array_mux");
                        }else {
                            LOG_ERROR(SONAR, "dft_calc,ERROR!");
                        }
#endif

                        double complex* iSignal = (double complex*)malloc(sizeof(double complex) * max_sample_cnt);
                        if(iSignal) {
                            res = true;
                        } else {
                            res = false;
                            LOG_ERROR(SONAR, "MallocErr,Need:%u", max_sample_cnt);
                        }
#ifdef HAS_DFT
                        if(res) {
                            if(iSignal) {
                                res = idft_calc(MuxSpectrum, max_garmotic, max_sample_cnt, iSignal);
                            }
                        }
#endif

                        uint32_t duration_ms = time_calc_duration_ms(start_ms);
                        LOG_INFO(SONAR, "DFT,Calc,Convolution,Duration:%s s", FloatToStr(MSEC_2_SEC(duration_ms),3)  );

                        if(res) {
                            res = complex_signal_save("convolutionDFT.csv", iSignal, max_sample_cnt, sampling_period_s);
                        }
#if 0 // next buggy code
#endif
                    }else {
                        LOG_ERROR(SONAR, "WavGetNode");
                    }
                } else {
                    LOG_ERROR(SONAR, "Wav2PulseLoad");
                }
            }else {
                LOG_ERROR(SONAR, "Wav1RecLoad");
            }
        }else {
            LOG_ERROR(SONAR, "PulseFileName");
        }
    } else {
        LOG_ERROR(SONAR, "RecFileName");
    }
    return res;
}


#ifdef HAS_CORRELATOR_S16
static bool sonar_update_best_correlation(const SonarCorrelationInfo_t* const Cur,
                                          SonarCorrelationInfo_t* const Best) {
    bool res = false;
    if(Best->positive_correlation < Cur->positive_correlation) {
        // memcpy((void *)Best, (void *)Cur, sizeof(SonarCorrelationInfo_t));
        Best->dist_m = Cur->dist_m;
        Best->positive_correlation = Cur->positive_correlation;
        Best->negative_correlation = Cur->negative_correlation;
        Best->correlation_positive_log = Cur->correlation_positive_log;
        Best->correlation_negative_log = Cur->correlation_negative_log;
        Best->correlation = Cur->correlation;
        Best->up_time_s = Cur->up_time_s;
        Best->sample = Cur->sample;
        res = true;
    }
    return res;
}
#endif

#ifdef HAS_CORRELATOR_S16
static bool sonar_compose_line(char* temp, uint32_t size,  const SonarCorrelationInfo_t* const Info) {
    bool res = false;
    if(Info) {
        strcpy(temp, "");
        snprintf(temp, size, "%s s,%4d,", temp, Info->sample);
        // snprintf(temp, size, "%s offset,%4d,", temp, offset);
        snprintf(temp, size, "%s t,%7.5f,", temp, Info->up_time_s);
        snprintf(temp, size, "%s Cor,%" PRId64 ",", temp, Info->correlation);
        snprintf(temp, size, "%s PosCor,%" PRId64 ",", temp, Info->positive_correlation);
        snprintf(temp, size, "%s NegCor,%" PRId64 ",", temp, Info->negative_correlation);
        snprintf(temp, size, "%s CorPosLog,%f,", temp, Info->correlation_positive_log);
        snprintf(temp, size, "%s CorNegLog,%f,", temp, Info->correlation_negative_log);
        snprintf(temp, size, "%s D,%8.6f,", temp, Info->dist_m);
        snprintf(temp, size, "%s \n", temp);
        // snprintf(temp, size, "%s ST,%s,", temp, ScanStateToStr(Scan->state));
        res = true;
    }
    return res;
}
#endif

static bool sonar_plot_convolution_ll(SonarHandle_t* Node, uint8_t x, uint8_t y) {
    bool res = false;
    if(Node) {
#ifdef HAS_WIN
        char command[120] = {0};
        snprintf(command, sizeof(command), "python %s %s %u %u", SONAR_PLOT_CONVOLUTION_SCRIPT, Node->correlation_file,
                 x, y);
        res = win_cmd_run(command);
#endif
    }
    return res;
}

bool sonar_plot_convolution(uint8_t num, uint8_t x_col, uint8_t y_col) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        res = sonar_plot_convolution_ll(Node, x_col, y_col);
    } else {
        LOG_ERROR(SONAR, "%u,NodeErr", num);
    }
    return res;
}

bool sonar_calc_correlation_max(uint32_t num, char* const file_name, SonarCorrelationInfo_t* const pBestCorrelation) {
    bool res = false;
    if(file_name) {
        LOG_INFO(SONAR, "CalcMaxCorrelation,N:%u,File:[%s]", num, file_name);
        SonarHandle_t* Node = SonarGetNode(num);
        if(Node) {
            res = file_mcal_open_re(FILE_MCAL_READ, file_name);
            if(res) {
                LOG_INFO(SONAR, "OpenReadFileOk:[%s]", file_name);

                WavHeader_t WavHeader = {0};
                uint32_t real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
                if(sizeof(WavHeader_t) == real_read) {
                    LOG_NOTICE(SONAR, "Header:%s", WavHeaderToStr(&WavHeader));
                    // res = file_mcal_delete(FILE_MCAL_WRITE, Node->correlation_file);
                    WavHandle_t WavHandle = {0};
                    res = wav_header_to_handle(&WavHeader, &WavHandle);
                    uint32_t cur_sample = 0;
                    uint32_t sample_sn = 0;

                    SonarCorrelationInfo_t Cur = {0};
                    LOG_NOTICE(SONAR, "SampleCnt:%u", WavHandle.sample_cnt);

                    for(cur_sample = 0; cur_sample < WavHandle.sample_cnt; cur_sample++) {
                        Cur.sample = cur_sample;
                        Cur.positive_correlation = 0;
                        AudioStereoSample16bit_t StereoSample = {0};
                        real_read = file_mcal_read(FILE_MCAL_READ, StereoSample.buff, WavHeader.blockAlign);
                        if(WavHeader.blockAlign == real_read) {
                            res = sonar_proc_sample(Node, StereoSample.right, &Cur.correlation);
                            if(res) {
                                Cur.positive_correlation = math_diod_s64(Cur.correlation);
                                Cur.negative_correlation = math_diod_s64(-Cur.correlation);
                                Cur.correlation_positive_log = math_log10((float)Cur.positive_correlation);
                                Cur.correlation_negative_log = math_log10((float)Cur.negative_correlation);
                                Cur.up_time_s = ((float)cur_sample) * WavHandle.sample_time_s;
                                Cur.dist_m = (Node->v_sound_m_pes_sec * Cur.up_time_s) / 2.0;
                                sample_sn++;
                                sonar_update_best_correlation(&Cur, pBestCorrelation);
                                if(0 == (cur_sample % (WavHandle.sample_cnt / 50))) {
                                    cli_printf("\r %s", ProgressToStr(cur_sample, WavHandle.sample_cnt));
                                }
                            } else {
                                LOG_ERROR(SONAR, "ProcSampleError");
                            }
                        } else {
                            LOG_DEBUG(SONAR, "SampleReadErr,%u/%u,realRead:%u Byte", cur_sample, WavHandle.sample_cnt,
                                      real_read);
                        }
                    } //  for(cur_sample = 0; cur_sample < WavHandle.sample_cnt; cur_sample++) {
                    LOG_INFO(SONAR, CRLF "Best:%s", SonarBestCorrelationToStr(pBestCorrelation));
                } else {
                    LOG_ERROR(SONAR, "WavHeaderReadErr");
                    res = false;
                }
                res = file_mcal_close(FILE_MCAL_READ);
            } else {
                LOG_ERROR(SONAR, "OpenWav[%s]Err", file_name);
                res = false;
            }
        } else {
            LOG_ERROR(SONAR, "SONAR_%u,NodeErr", num);
            res = false;
        }
    }
    return res;
}



#ifdef HAS_CORRELATOR_S16
bool sonar_calc_correlation(uint32_t num, char* const file_name) {
    bool res = false;
    if(file_name) {
        SonarCorrelationInfo_t BestCorrelation = {0};
        res = sonar_calc_correlation_max(  num,  file_name, &BestCorrelation);
        LOG_INFO(SONAR, "ChirpCorrelation,N:%u,File:[%s]", num, file_name);
        SonarHandle_t* Node = SonarGetNode(num);
        if(Node) {
            res = file_mcal_open_re(FILE_MCAL_READ, file_name);
            if(res) {
                LOG_INFO(SONAR, "OpenReadFileOk:[%s]", file_name);

                WavHeader_t WavHeader = {0};
                uint32_t real_read = file_mcal_read(FILE_MCAL_READ, WavHeader.buff, sizeof(WavHeader_t));
                if(sizeof(WavHeader_t) == real_read) {
                    LOG_NOTICE(SONAR, "Header:%s", WavHeaderToStr(&WavHeader));

                    Node->conv_sn++;
                    snprintf(Node->correlation_file, sizeof(Node->correlation_file), "convolution_%u.csv",
                             Node->conv_sn);
                    // res = file_mcal_delete(FILE_MCAL_WRITE, Node->correlation_file);
                    WavHandle_t WavHandle = {0};
                    res = wav_header_to_handle(&WavHeader, &WavHandle);
                    uint32_t cur_sample = 0;
                    uint32_t sample_sn = 0;
                    SonarCorrelationInfo_t Cur = {0};

                    res = file_mcal_open_append(FILE_MCAL_WRITE, Node->correlation_file);
                    log_info_res(SONAR, res, "open_append");

                    LOG_NOTICE(SONAR, "SampleCnt:%u", WavHandle.sample_cnt);


                    uint32_t start_ms = time_get_ms32();


                    for(cur_sample = 0; cur_sample < WavHandle.sample_cnt; cur_sample++) {
                        Cur.sample = cur_sample;
                        Cur.positive_correlation = 0;
                        AudioStereoSample16bit_t StereoSample = {0};
                        real_read = file_mcal_read(FILE_MCAL_READ, StereoSample.buff, WavHeader.blockAlign);
                        if(WavHeader.blockAlign == real_read) {
                            res = sonar_proc_sample(Node, StereoSample.right, &Cur.correlation);
                            if(res) {

                                Cur.positive_correlation = math_diod_s64(Cur.correlation);
                                Cur.negative_correlation = math_diod_s64(-Cur.correlation);
                                Cur.correlation_positive_log = math_log10((float)Cur.positive_correlation);
                                Cur.correlation_negative_log = math_log10((float)Cur.negative_correlation);

                                // int32_t offset = ( (int32_t)sample_sn )-((int32_t)fir_order_get(Node->fir_num))+1 ;
                                Cur.up_time_s = ((float)cur_sample) * WavHandle.sample_time_s;
                                Cur.dist_m = (Node->v_sound_m_pes_sec * Cur.up_time_s) / 2.0;

                                Cur.up_time_s = Cur.up_time_s - BestCorrelation.up_time_s;
                                Cur.dist_m = Cur.dist_m- BestCorrelation.dist_m;
                                sample_sn++;

                                char temp[200] = {0};
                                res = sonar_compose_line(temp, sizeof(temp), &Cur);

                                if(0 == (cur_sample % (WavHandle.sample_cnt / 50))) {
                                    cli_printf("\r %s,%s", ProgressToStr(cur_sample, WavHandle.sample_cnt), temp);
                                    // LOG_INFO(SONAR, CRLF"Best:%s",SonarBestCorrelationToStr(&BestCorrelation));
                                }
                                res = file_mcal_write_line(FILE_MCAL_WRITE, temp, strlen(temp));
                            } else {
                                LOG_ERROR(SONAR, "ProcSampleError");
                            }
                        } else {
                            LOG_DEBUG(SONAR, "SampleReadErr,%u/%u,realRead:%u Byte", cur_sample, WavHandle.sample_cnt,
                                      real_read);
                        }
                    } //  for(cur_sample = 0; cur_sample < WavHandle.sample_cnt; cur_sample++) {
                    uint32_t duration_ms = time_calc_duration_ms(start_ms);
                    LOG_INFO(SONAR, "FIR,Calc,Convolution,Duration:%s s", FloatToStr(MSEC_2_SEC(duration_ms),3)  );


                    LOG_INFO(SONAR, CRLF "Best:%s", SonarBestCorrelationToStr(&BestCorrelation));
                    res = file_mcal_close(FILE_MCAL_WRITE);
                } else {
                    LOG_ERROR(SONAR, "WavHeaderReadErr");
                    res = false;
                }
                res = file_mcal_close(FILE_MCAL_READ);
            } else {
                LOG_ERROR(SONAR, "OpenWav[%s]Err", file_name);
                res = false;
            }
        } else {
            LOG_ERROR(SONAR, "SONAR_%u,NodeErr", num);
            res = false;
        }
    }
    return res;
}
#endif

bool sonar_chirp_correlation_record(uint32_t num, float signal_duration_s, float amplitude, float frequency1,
                                    float frequency2, char* const file_name) {
    bool res = false;
    res = sonar_config_correlator_chirp(num, signal_duration_s, amplitude, frequency1, frequency2);
    if(res) {
#ifdef HAS_CORRELATOR_S16
        res = sonar_calc_correlation(num, file_name);
#endif
        // res = sonar_plot_convolution(num, 13, 7);
    }
    return res;
}

bool sonar_calc_correlation_mono_record(uint8_t num, float carrier_frequency_hz, float amplitude, float signal_duration,
                                        char*  rec_file_name) {
    bool res = false;
    LOG_NOTICE(SONAR, "calc_correlation_record,Mono");
    res = sonar_config_correlator_mono(num,  signal_duration, amplitude, carrier_frequency_hz);
    if(res) {
#ifdef HAS_CORRELATOR_S16
        res = sonar_calc_correlation(num, rec_file_name);
#endif
    }
    return res;
}

bool sonar_m_seq_calc_correlation_record(uint8_t num, uint8_t m_seq_num, float amplitude, float carrier_frequency_hz,
                                         uint32_t periods_per_chip, char* rec_file_name) {
    bool res = false;
    LOG_WARNING(SONAR, "m_seq_calc_correlation_record");
    res = sonar_config_correlator_m_seq(num, m_seq_num, amplitude, carrier_frequency_hz, periods_per_chip);
    if(res) {
#ifdef HAS_CORRELATOR_S16
        res = sonar_calc_correlation(num, rec_file_name);
#endif
    }
    return res;
}

#ifdef HAS_BARKER_CODE
bool sonar_barker_calc_correlation_record(uint8_t num, float amplitude, float carrier_frequency_hz,
                                          uint32_t periods_per_chip, char* file_name) {
    bool res = false;
    res = sonar_config_correlator_barker13(num, amplitude, carrier_frequency_hz, periods_per_chip);
    if(res) {
#ifdef HAS_CORRELATOR_S16
        res = sonar_calc_correlation(num, file_name);
#endif
        // res = sonar_plot_convolution(num, 13, 7);
    }
    return res;
}
#endif

bool sonar_v_sound(uint32_t num, float v_sound_m_pes_sec) {
    bool res = false;
    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        Node->v_sound_m_pes_sec = v_sound_m_pes_sec;
        res = true;
    }
    return res;
}

bool sonar_chirp_calc_bandwith(float v_sound_mps,
                               float resolution_m,
                               float f_central_hz,
                               SonarChirpParam_t* ChirpParam) {
    bool res = false;
    float band_with_hz = v_sound_mps/(2.0f*resolution_m);
    if(ChirpParam) {
        ChirpParam->frequency1 = f_central_hz - (band_with_hz/2.0f);
        ChirpParam->frequency2 = f_central_hz + (band_with_hz/2.0f);

        LOG_INFO(SONAR,"Vsound:%f m/s,Res:%f m,Fcentral:%f Hz,%s",v_sound_mps,resolution_m,f_central_hz,SonarChirpParamToStr(ChirpParam) );
        res = true;
    }

    return res;
}

/*
 */
bool sonar_fft_convolution(const char* const pulse_file_name, const char* const rec_file_name) {
    bool res = false;
    if(rec_file_name) {
        if(pulse_file_name) {
            LOG_INFO(SONAR, "SampleSize:%u Byte", sizeof(SampleType_t));
            LOG_INFO(SONAR, "CalcFFT:Rec[%s],Pulse:[%s]", rec_file_name,pulse_file_name);
            res = wav_load(1, rec_file_name);
            if(res) {
                res = wav_load(2, pulse_file_name);
                if(res) {
                    res = false;
                    WavHandle_t* Rec = WavGetNode(1);
                    if(Rec) {
                        uint32_t start_ms = time_get_ms32();
                        SampleType_t* signal_rec = NULL;
                        SampleType_t* signal_pulse_ptr = NULL;

                        uint32_t size_sig = 0;
                        uint32_t max_sample_cnt = 0;
                        WavHandle_t* Pulse = WavGetNode(2);
                        if(Pulse) {
                            uint32_t init_sample_cnt=Rec->sample_cnt+ Pulse->sample_cnt-1;
                            max_sample_cnt = next_power_of_2( init_sample_cnt);
                            LOG_INFO(SONAR, "max_sample_cnt:%u sample",init_sample_cnt, max_sample_cnt);
                            size_sig = max_sample_cnt * sizeof(SampleType_t);
                            LOG_INFO(SONAR, "size_sig:%u Byte", size_sig);
                            signal_rec = (SampleType_t*)malloc(size_sig);
                            if(signal_rec) {
                                signal_pulse_ptr = (SampleType_t*)malloc(size_sig);
                                if(signal_pulse_ptr) {
                                    res = true;
                                    dsp_array_zero(signal_rec,     max_sample_cnt) ;
                                    dsp_array_zero(signal_pulse_ptr,     max_sample_cnt) ;
                                }
                            }
                        }else {
                            LOG_ERROR(SONAR, "Wav2GetNode");
                        }

                        LOG_INFO(SONAR, "Fs:%u Hz", Pulse->sampling_frequency_hz);
                        LOG_INFO(SONAR, "SONAR_MAX_SPEC:%u ", SONAR_MAX_SPEC);
                        double sampling_period_s = 1.0 / ((double)Pulse->sampling_frequency_hz);
                        (void)sampling_period_s;
                        LOG_INFO(SONAR, "SamTime:%f s", sampling_period_s);
                        double measured_interval_s = ((double) max_sample_cnt) * sampling_period_s;
                        (void)measured_interval_s;
                        //uint32_t max_garmotic = fft_freq_to_garmonic( 48000, measured_interval_s);
                        uint32_t max_garmotic = max_sample_cnt;
                        LOG_INFO(SONAR, "maxGarmotic:%u", max_garmotic);
                        if(res) {
                            LOG_INFO(SONAR, "CopyPulse:");
                            res = dsp_array_cpy( signal_pulse_ptr, (SampleType_t*)Pulse->data, Pulse->channels, Pulse->sample_cnt);
                            log_res(SONAR,res,"SignalPulseFill");

                            LOG_INFO(SONAR, "CopyRec:");
                            res = dsp_array_cpy( signal_rec, (SampleType_t*)Rec->data, Rec->channels, Rec->sample_cnt);
                            log_res(SONAR,res,"signalRecFill");

                            // Up ok
#ifdef HAS_FFT
                            if(max_sample_cnt < SONAR_MAX_SPEC) {
                                res = fft_calc(signal_rec, max_sample_cnt, RecSpectrum, sampling_period_s, max_garmotic);
                                log_res(SONAR,res,"fft_calcRec");
                                if(res) {
                                    res = fft_calc(signal_pulse_ptr, max_sample_cnt, PulseSpectrum, sampling_period_s, max_garmotic);
                                    log_res(SONAR,res,"fft_calcPulse");
                                }
                            } else {
                                LOG_ERROR(SONAR, "MAX:%u,Need:%u", SONAR_MAX_SPEC, max_sample_cnt);
                            }
#endif
                        }
                        // untested code \/
#ifdef HAS_FFT
                        if(res) {
                            res = complex_array_conjugate( PulseSpectrum,  max_garmotic);
                            log_res(SONAR,res,"complex_array_conjugate");
                            res = complex_array_mux(RecSpectrum, PulseSpectrum, MuxSpectrum, max_garmotic);
                            log_res(SONAR,res,"complex_array_mux");
                        }else {
                            LOG_ERROR(SONAR, "fft_calc,ERROR!");
                        }
#endif

                        double complex* iSignal = (double complex*)malloc(sizeof(double complex) * max_sample_cnt);
                        if(iSignal) {
                            res = true;
                        } else {
                            res = false;
                            LOG_ERROR(SONAR, "MallocErr,Need:%u", max_sample_cnt);
                        }
#ifdef HAS_FFT
                        if(res) {
                            if(iSignal) {
                                res = ifft_calc(MuxSpectrum, max_garmotic, max_sample_cnt, iSignal);
                            }
                        }
#endif

                        uint32_t duration_ms = time_calc_duration_ms(start_ms);
                        LOG_INFO(SONAR, "FFT,Calc,Convolution,Duration:%s s", FloatToStr(MSEC_2_SEC(duration_ms),3)  );
                        if(res) {
                            res = complex_signal_save("convolutionFFT.csv", iSignal, max_sample_cnt, sampling_period_s);
                        }
#if 0 // next buggy code
#endif
                    }else {
                        LOG_ERROR(SONAR, "WavGetNode");
                    }
                } else {
                    LOG_ERROR(SONAR, "Wav2PulseLoad");
                }
            }else {
                LOG_ERROR(SONAR, "Wav1RecLoad");
            }
        }else {
            LOG_ERROR(SONAR, "PulseFileName");
        }
    } else {
        LOG_ERROR(SONAR, "RecFileName");
    }
    return res;
}

COMPONENT_INIT_PATTERT(SONAR, SONAR, sonar)
COMPONENT_PROC_PATTERT(SONAR, SONAR, sonar)
