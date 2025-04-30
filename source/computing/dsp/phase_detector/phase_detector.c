#include "phase_detector.h"

#include <string.h>

#include "wav.h"
#include "array.h"
#include "code_generator.h"
#include "table_utils.h"
#include "quadrature_mixer.h"
#include "log.h"
#include "debug_info.h"
#include "csv.h"

COMPONENT_GET_NODE(PhaseDetector, phase_detector)
COMPONENT_GET_CONFIG(PhaseDetector, phase_detector)

bool phase_detector_init_custom(void) {
    bool res = true;
    return res;
}

static bool phase_detector_proc_one_sample_ll(PhaseDetectorHandle_t* const Node,
                                              PhaseDetectorSample_t SampleRec,
                                              double freq_signal,
                                              FILE* const pFileWrite,
                                              uint32_t sample_num) {
    bool res = false;
    if(Node) {
        double time_s = ((double) sample_num) * Node->sample_time_s;
        QuadratureMixerHandle_t* QM = QuadratureMixerGetNode(2);
        if(QM) {
            res = quadrature_mixer_proc_sample_ll(QM, time_s, freq_signal, 0.0, (double) SampleRec) ;
            double distance_m = (Node->wavelength_m * QM->phase_error_rad)/(2.0*M_PI);
            res = csv_save_to_end("distance.csv", time_s, distance_m);
#if 0
            PhaseDetectorSample_t SampleToWr = 0.0;
            double distance_mm = distance_m*1000.0;
            SampleToWr = (PhaseDetectorSample_t) distance_mm;
            size_t write_cnt = fwrite((void *)&SampleToWr,
                                      sizeof(PhaseDetectorSample_t),
                                      1, pFileWrite);
            if( 1==write_cnt ) {
                res = true;
                LOG_DEBUG(WAV,"Write,Ok:%u",sample_num);
            } else {
                LOG_ERROR(WAV,"Write,Err:%u",sample_num);
            }
#endif
        }// QM
    }
    return res;
}

static bool phase_detector_proc_samples(PhaseDetectorHandle_t* const Node, const char* const  file_name, double  freq_signal) {
    bool res = false;
    LOG_INFO(PHASE_DETECTOR, "Proc,Sample,File:[%s]", file_name);
    if(file_name) {
        FILE* pFileRead = NULL;
        pFileRead = fopen(file_name, "rb");
        if(pFileRead) {
            FILE* pFileWrite = NULL;
            LOG_INFO(PHASE_DETECTOR, "Open,File:[%s]Ok", file_name);
            WavHeader_t WavHeader={0};
            size_t real_read = fread((void*)&WavHeader, sizeof(WavHeader_t),1, pFileRead);
            if(1==real_read) {
                LOG_INFO(PHASE_DETECTOR, "Read,Header,Ok,%s",WavHeaderToStr(&WavHeader));
                char file_write_name[80]={0};
                snprintf(file_write_name,sizeof(file_write_name),"PhaseDetect_%5.0f_Hz.wav",freq_signal);
                pFileWrite = fopen(file_write_name, "wb");
                if(pFileWrite) {
                    size_t write_cnt = fwrite((void *)&WavHeader, sizeof(WavHeader_t), 1, pFileWrite);
                    if(write_cnt) {
                        LOG_INFO(PHASE_DETECTOR, "Write,Header,Ok");
                    }else {
                        LOG_ERROR(PHASE_DETECTOR, "WriteHeaderErr");
                    }
                }
                cli_printf(CRLF);

                WavHandle_t WavHandle = {0};
                WavHandle.sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                WavHandle.sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;
                WavHandle.duration_s = WavHandle.sample_time_s*((double)WavHandle.sample_cnt);
                LOG_INFO(PHASE_DETECTOR, "%s",WavHandleToStr(&WavHandle));

                uint32_t s = 0;
                for(s=0; s<WavHandle.sample_cnt; s++) {
                    LOG_DEBUG(PHASE_DETECTOR,"proc Sample:%u",s);
                    PhaseDetectorSample_t Sample = {0};
                    real_read = fread((void*)&Sample, WavHeader.blockAlign,1, pFileRead);
                    if( 1 == real_read) {
                        res = phase_detector_proc_one_sample_ll(Node, Sample, freq_signal, pFileWrite,s);
                    }else{
                        res = false;
                        LOG_ERROR(PHASE_DETECTOR,"readDataErr:%u",real_read);
                    }
                    if(0==(s%(WavHandle.sample_cnt/100))){
                        cli_printf("\r%s",ProgressToStr(  s,   WavHandle.sample_cnt));
                    }
                }
                res = true;
            } else {
                LOG_ERROR(PHASE_DETECTOR,"readErr");
            }

            fclose(pFileWrite);
            fclose(pFileRead);
        } else {
            LOG_ERROR(PHASE_DETECTOR, "OpenFile:[%s] Err", file_name);
        }

    }
    return res;
}


bool phase_detector_half_cos(double freq_signal, const char* const file_name){
    bool res = false;
    return res;
}


bool phase_detector_proc_file(double freq_signal, const char* const file_name){
    bool res = false ;
    PhaseDetectorHandle_t* Node=PhaseDetectorGetNode(1);
    if(Node) {
        if(file_name) {
            LOG_INFO(PHASE_DETECTOR, "Fsignal:%f Hz,File:[%s]", freq_signal,file_name);
            WavHeader_t WavHeader={0};
            res = wav_info_ll(&WavHeader, file_name);
            if (res) {
                Node->signal_frequency_hz = freq_signal;
                Node->sample_freq_hz = WavHeader.sampleRate;
                Node->channel_cnt = WavHeader.numChannels;
                Node->bitsPerSample = WavHeader.bitsPerSample;
                Node->sample_time_s = 1.0 / ((double)WavHeader.sampleRate);
                Node->sample_cnt = WavHeader.subchunk2Size/WavHeader.blockAlign;

                Node->wavelength_m = Node->speed_of_sound_m_per_s/Node->signal_frequency_hz ;
                Node->duration_s = Node->sample_time_s*((double)Node->sample_cnt);
                LOG_INFO(PHASE_DETECTOR, "%s", PhaseDetectorNodeToStr(Node));
            }
            if (0.0 < freq_signal) {
                res = phase_detector_proc_samples(Node, file_name,  freq_signal);
            }
        }
    }
    return res;
}

static bool phase_detector_is_valid_config(const PhaseDetectorConfig_t * const Config ){
    bool res = false;
    if(Config) {
        if(0.0 < Config->signal_frequency_hz) {
                if(0.0 < Config->quadrature_mixer_num) {
                    if(100 < Config->filter_order) {
                        res = true;
                    }else{
                        LOG_ERROR(PHASE_DETECTOR, "FirOrder,Err");
                    }
                }else{
                    LOG_ERROR(PHASE_DETECTOR, "FirNum,Err");
                }
        }else{
            LOG_ERROR(PHASE_DETECTOR, "Config,Signal,Freq,Err");
        }
    }else{
        LOG_ERROR(PHASE_DETECTOR, "Config,Err");
    }
    return res;
}

bool phase_detector_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(PHASE_DETECTOR, "%u,Init", num);
    const PhaseDetectorConfig_t *Config = PhaseDetectorGetConfig(num);
    if (Config) {
        LOG_WARNING(PHASE_DETECTOR, "Config:%s", PhaseDetectorConfigToStr(Config));
        res = phase_detector_is_valid_config(Config);
        if (res) {
            PhaseDetectorHandle_t *Node = PhaseDetectorGetNode(num);
            if (Node) {
                LOG_INFO(PHASE_DETECTOR, "Spot,Node");
                Node->num = Config->num;
                Node->quadrature_mixer_num = Config->quadrature_mixer_num;
                Node->cut_off_frequency_hz = Config->cut_off_frequency_hz;
                Node->speed_of_sound_m_per_s = Config->speed_of_sound_m_per_s;
                Node->signal_frequency_hz = Config->signal_frequency_hz;
                Node->channel_cnt = Config->channel_cnt;
                Node->filter_order = Config->filter_order;
                Node->sample_freq_hz = Config->sample_freq_hz;
                Node->bitsPerSample = Config->bitsPerSample;
                Node->valid = true;

                Node->wavelength_m = Node->speed_of_sound_m_per_s/Node->signal_frequency_hz ;

                res = quadrature_mixer_init_one(Node->quadrature_mixer_num);
#if 0
                res = fir_synthesize(Node->fir_num,
                                     Node->filter_order,
                                     (FirSample_t) Node->cut_off_frequency_hz,
                                     (FirSample_t) Node->sample_freq_hz );
#endif
                if (res) {
                    Node->init = true;
                    LOG_WARNING(PHASE_DETECTOR, "Node:%s", PhaseDetectorNodeToStr(Node));
                }
            } else {
                LOG_ERROR(PHASE_DETECTOR, "NodeErr");
            }
        } else {
            LOG_ERROR(PHASE_DETECTOR, "AbsurdConfigErr");
        }
    } else {
        LOG_ERROR(PHASE_DETECTOR, "ConfNodeErr");
    }

    return res;
}

COMPONENT_INIT_PATTERT(PHASE_DETECTOR, PHASE_DETECTOR, phase_detector)
