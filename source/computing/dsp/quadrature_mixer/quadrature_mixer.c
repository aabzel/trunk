#include "quadrature_mixer.h"

#include <complex.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "dsp.h"
#include "array.h"
#include "circular_buffer_index.h"
//#include "complex_diag.h"
#include "code_generator.h"
#include "table_utils.h"
#include "quadrature_mixer_diag.h"
#include "writer_config.h"
#include "float_utils.h"
#include "iir.h"
#include "log.h"
#include "vector_math.h"
#include "utils_math.h"

COMPONENT_GET_NODE(QuadratureMixer, quadrature_mixer)
COMPONENT_GET_CONFIG(QuadratureMixer, quadrature_mixer)

bool quadrature_mixer_init_custom(void) {
    bool res = true;
    return res;
}


static bool quadrature_mixer_is_valid_config(const QuadratureMixerConfig_t *const Config) {
    bool res = false;
    if (Config) {
        res = true;
    }

    if (res) {
        res = false;
        if (0 < Config->filter_type) {
            res = true;
        } else {
            LOG_ERROR(QUADRATURE_MIXER,"Filter,Type,Err");
        }
    }

    if (res) {
        res = false;
        if (0 < Config->filter_num[1]) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"Filter,Q,Err");
        }
    }

    if (res) {
        res = false;
        if (0 < Config->filter_num[0]) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"Filter,I,Err");
        }
    }

    if (res) {
        res = false;
        if (0 < Config->filter_order) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"Filter,Order,Err");
        }
    }

    if (res) {
        res = false;
        if (0 < Config->sample_rate_hz) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"SampeReteErr");
        }
    }

    if (res) {
        res = false;
        if (0 < Config->cut_off_freq_hz) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"Cut,Off,Freq,Err");
        }
    }

    if (res) {
        res = false;
        if ( Config->cut_off_freq_hz < (Config->sample_rate_hz/2)) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"Cut,Off,Big,Freq,Err");
        }
    }

    if (res) {
        res = false;
        if (Config->valid) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"ValidErr");
        }
    }

    if (res) {
        res = false;
        if (Config->name) {
            res = true;
        }else{
            LOG_ERROR(QUADRATURE_MIXER,"NameErr");
        }
    }

    return res;
}

bool quadrature_mixer_proc_sample_ll(QuadratureMixerHandle_t* const Node,
                                     double time_s,
                                     double carrier_frequency_hz,
                                     double lo_phase_rad,
                                     double sample) {
    bool res = false;
    if(Node) {
        LOG_DEBUG(QUADRATURE_MIXER, "sample:%f" ,sample);
        Node->proc_cnt++;
        Node->lo_phase_rad = lo_phase_rad;
        Node->sample = sample;
        Node->time_s = time_s;

        Node->lo_frequency_hz = carrier_frequency_hz;
        Node->SdrI.LocalOcs = lo_calc_cos_sample(time_s, carrier_frequency_hz, lo_phase_rad, 100.0, 0.0);
        Node->SdrI.AfterMux = Node->SdrI.LocalOcs * sample;
        Node->SdrI.AfterFilt = 0;
        bool ires = filter_proc_in_out(Node->filter_num[0], Node->filter_type ,(FilterSample_t) Node->SdrI.AfterMux, &Node->SdrI.AfterFilt);
        if(ires) {
            Node->SdrQ.LocalOcs = lo_calc_sin_sample(time_s, carrier_frequency_hz, lo_phase_rad, 100.0, 0.0);
            Node->SdrQ.AfterMux = Node->SdrQ.LocalOcs * sample;
            Node->SdrQ.AfterFilt = 0;
            bool qres = filter_proc_in_out(Node->filter_num[1], Node->filter_type, (FilterSample_t) Node->SdrQ.AfterMux, &Node->SdrQ.AfterFilt);
            if(qres) {
                Vector_t x_axis = {0};
                Vector_t phaseVector = { 0};
                phaseVector.dx = (double) Node->SdrI.AfterFilt;
                phaseVector.dy = (double) Node->SdrQ.AfterFilt;
                phaseVector.dz = 0.0;
                x_axis.dx = 10.0;
                x_axis.dy = 0;
                x_axis.dz = 0;
                Node->phase_error_rad = calc_angle_between_vectors_rad(&x_axis,&phaseVector);
                res = true;
            }else {
                LOG_ERROR(QUADRATURE_MIXER, "Filter,Q,Err" );
            }
        }else {
            LOG_ERROR(QUADRATURE_MIXER, "Filter,I,Err" );
        }
        LOG_DEBUG(QUADRATURE_MIXER, "%s", QuadratureMixerNodeToStr(Node));
    }
    return res;
}

bool quadrature_mixer_proc_sample(uint8_t num,
                                  double time_s,
                                  double carrier_frequency_hz,
                                  double lo_phase_rad,
                                  double sample) {
    bool res = false;
    QuadratureMixerHandle_t* Node = QuadratureMixerGetNode(num);
    if(Node) {
        res= quadrature_mixer_proc_sample_ll(Node, time_s, carrier_frequency_hz, lo_phase_rad, sample);
    }
    return res;
}

bool quadrature_mixer_lpf_iir(uint8_t num, double k){
    bool res = false;
    QuadratureMixerHandle_t *Node = QuadratureMixerGetNode(num);
    if(Node) {
        LOG_WARNING(QUADRATURE_MIXER, "QM%u,Set,IIR,LPF,K:%f", num, k);
    	res = iir_lowpas_1st_order(Node->filter_num[0],   k);
    	if(res){
        	res = iir_lowpas_1st_order(Node->filter_num[1],   k);
    	}
    }
    return res;
}

bool quadrature_mixer_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(QUADRATURE_MIXER, "%u,Init", num);
    const QuadratureMixerConfig_t *Config = NULL;
    Config = QuadratureMixerGetConfig(num);
    if (Config) {
        LOG_WARNING(QUADRATURE_MIXER, "%s", QuadratureMixerConfigToStr(Config));
        res = quadrature_mixer_is_valid_config(Config);
        if (res) {
            QuadratureMixerHandle_t *Node = QuadratureMixerGetNode(num);
            if (Node) {
                Node->num = Config->num;
                Node->sample_rate_hz = Config->sample_rate_hz;
                Node->filter_type = Config->filter_type;
                Node->filter_order = Config->filter_order;
                Node->cut_off_freq_hz = Config->cut_off_freq_hz;
                Node->filter_num[0] = Config->filter_num[0];
                Node->filter_num[1] = Config->filter_num[1];
                Node->valid = true;

                uint32_t i = 0;
                for(i=0;i<2;i++) {
                    res = filter_synthesize(Node->filter_num[i], Node->filter_type,
                            Node->filter_order,
                            Node->cut_off_freq_hz,
                            Node->sample_rate_hz);
                    if (res) {
                        LOG_INFO(QUADRATURE_MIXER, "Filter%u,SynthesizeOk",Node->filter_num[i]);
                    } else {
                        LOG_ERROR(QUADRATURE_MIXER, "Filter%u,SynthesizeErr",Node->filter_num[i]);
                    }
                }

                LOG_INFO(QUADRATURE_MIXER, "Init,Ok");
            } else {
                LOG_ERROR(QUADRATURE_MIXER, "NodeErr");
            }
        } else {
            LOG_ERROR(QUADRATURE_MIXER, "Absurd,Config,Err");
        }
    } else {
        LOG_DEBUG(QUADRATURE_MIXER, "Conf,Node,Err");
    }

    return res;
}

COMPONENT_INIT_PATTERT(QUADRATURE_MIXER, QUADRATURE_MIXER, quadrature_mixer)
