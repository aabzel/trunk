#include "quad_mix_4fs.h"

#include <complex.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "circular_buffer_index.h"
#include "code_generator.h"
#include "dsp.h"
#include "float_utils.h"
#include "local_oscillator_mcal.h"
#include "log.h"
#include "quad_mix_4fs_diag.h"
#include "sliding_integral.h"
#include "utils_math.h"
#include "vector_math.h"

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_DAC
#include "dac_channel_mcal.h"
#endif

#ifdef HAS_IIR
#include "iir.h"
#endif

#define PHA_ERR_LUT_LEN 50

#ifdef HAS_PHASE_ERR_LUT
static volatile float phaseErrRadLUT_iqPos[PHA_ERR_LUT_LEN][PHA_ERR_LUT_LEN] = {0};
static volatile float phaseErrRadLUT_iPosQNeg[PHA_ERR_LUT_LEN][PHA_ERR_LUT_LEN] = {0};
static volatile float phaseErrRadLUT_iNegQpos[PHA_ERR_LUT_LEN][PHA_ERR_LUT_LEN] = {0};
static volatile float phaseErrRadLUT_iNegQneg[PHA_ERR_LUT_LEN][PHA_ERR_LUT_LEN] = {0};
#endif

COMPONENT_GET_NODE(QuadMix4fs, quad_mix_4fs)
COMPONENT_GET_CONFIG(QuadMix4fs, quad_mix_4fs)

#ifdef HAS_PHASE_ERR_LUT
static bool phase_err_rad_lut_set(int32_t i, int32_t q, float phase_err_rad) {
    bool res = false;
    if(0 <= i) {
        if(0 <= q) {
            phaseErrRadLUT_iqPos[i][q] = phase_err_rad;
            res = true;
        } else {
            phaseErrRadLUT_iPosQNeg[i][-q] = phase_err_rad;
            res = true;
        }
    } else {
        if(0 <= q) {
            phaseErrRadLUT_iNegQpos[-i][q] = phase_err_rad;
            res = true;
        } else {
            phaseErrRadLUT_iNegQneg[-i][-q] = phase_err_rad;
            res = true;
        }
    }
    return res;
}
#endif

#ifdef HAS_PHASE_ERR_LUT
static bool quad_mix_4fs_init_phase_error_lut(void) {
    bool res = false;
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    int32_t i = 0;
    for(i = (-PHA_ERR_LUT_LEN + 1); i < PHA_ERR_LUT_LEN; i++) {
        int32_t q = 0;
        for(q = (-PHA_ERR_LUT_LEN + 1); q < PHA_ERR_LUT_LEN; q++) {
            float phase_err_rad = calc_carrier_phase_err_rad((float)i, (float)q);
            res = phase_err_rad_lut_set(i, q, phase_err_rad);
        }
    }
    return res;
}
#endif

static bool quad_mix_4fs_init_custom(void) {
    bool res = true;
#ifdef HAS_PHASE_ERR_LUT
    res = quad_mix_4fs_init_phase_error_lut();
#endif
    return res;
}

static bool quad_mix_4fs_is_valid_config(const QuadMix4fsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }

    if(res) {
        res = false;
        if(0 < Config->filter_num_q) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "Filter,Q,Err");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->filter_num_i) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "Filter,I,Err");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->filter_order) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "Filter,Order,Err");
        }
    }

    if(res) {
        res = false;
        if(0 < Config->cut_off_freq_hz) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "Cut,Off,Freq,Err");
        }
    }

    if(res) {
        res = false;
        if(Config->valid) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "ValidErr");
        }
    }

    if(res) {
        res = false;
        if(Config->name) {
            res = true;
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "NameErr");
        }
    }

    return res;
}

static inline bool quad_mix_4fs_proc_sample_i(QuadMix4fsHandle_t* const Node, int32_t sam_num, int32_t sample) {
    bool res = false;
    Node->SdrI.LocalOcs = pwm_cos4_int(sam_num, Node->lo_phase_n);
    Node->SdrI.AfterMux = Node->SdrI.LocalOcs * sample;
    Node->SdrI.AfterFilt = 0;
    res = sliding_integral_proc_in_out_ll(Node->pNodeFilterI, Node->SdrI.AfterMux, &Node->SdrI.AfterFilt);
    if(res) {
    } else {
        LOG_ERROR(QUAD_MIX_4FS, "Filter,I,Err");
    }
    return res;
}

static inline bool quad_mix_4fs_proc_sample_q(QuadMix4fsHandle_t* const Node, int32_t sam_num, int32_t sample) {
    bool res = false;
    Node->SdrQ.LocalOcs = pwm_sin4_int(sam_num, Node->lo_phase_n);
    Node->SdrQ.AfterMux = Node->SdrQ.LocalOcs * sample;
    Node->SdrQ.AfterFilt = 0;

    res = sliding_integral_proc_in_out_ll(Node->pNodeFilterQ, Node->SdrQ.AfterMux, &Node->SdrQ.AfterFilt);
    if(res) {
    } else {
        LOG_ERROR(QUAD_MIX_4FS, "Filter,Q,Err");
    }
    return res;
}

#if 0
bool quad_mix_4fs_calc_phase_error_vector_angle(QuadMix4fsHandle_t* const Node) {
    bool res = false;
    VectorF_t x_axis = { 0 };
    VectorF_t phaseVector = { 0 };
    phaseVector.dx = (float) Node->SdrI.AfterFilt;
    phaseVector.dy = (float) Node->SdrQ.AfterFilt;
    phaseVector.dz = 0.0;
    x_axis.dx = 10.0f;
    x_axis.dy = 0.0f;
    x_axis.dz = 0.0f;
    Node->phase_error_rad = calc_angle_between_vectors_rad(&x_axis, &phaseVector);
    res = true;

    return res;
}
#endif

/*
            Q
            ^
    --------|++++++++
    --------|++++++++
  __--------|++++++++_______\I
    ++++++++|--------       /
    ++++++++|-----*--
    ++++++++|--------
 */
inline float calc_carrier_phase_err_approximate_rad(const float i_val, const float q_val) {
    float carr_phase_err_rad = 0.0f;
    if(0.0f < i_val) {
        // atan2f monotone increasing function
        carr_phase_err_rad = atan2f_approximate(q_val, i_val); // -pi/2......  pi/2
    } else {
        carr_phase_err_rad = atan2f_approximate(-q_val, -i_val); // -pi/2......  pi/2
    }
#ifdef HAS_BPSK_DEBUG
    LOG_DEBUG(QUAD_MIX_PHASE, "Pha,%f+j(%f),Err:%7.6f Rad", i_val, q_val, carr_phase_err_rad);
#endif
    return carr_phase_err_rad;
}

/*
            Q
            ^
    --------|++++++++
    --------|++++++++
  __--------|++++++++_______\I
    ++++++++|--------       /
    ++++++++|-----*--
    ++++++++|--------
 */
inline float calc_carrier_phase_err_rad(const float i_val, const float q_val) {
    float carr_phase_err_rad = 0.0f;
    if(0.0f < i_val) {
        // atan2f monotone increasing function
        carr_phase_err_rad = atan2f((float)q_val, (float)i_val); // -pi/2......  pi/2
    } else {
        carr_phase_err_rad = atan2f((float)-q_val, (float)-i_val); // -pi/2......  pi/2
    }
#ifdef HAS_BPSK_DEBUG
    LOG_DEBUG(QUAD_MIX_PHASE, "Pha,%f+j(%f),Err:%7.6f Rad", i_val, q_val, carr_phase_err_rad);
#endif
    return carr_phase_err_rad;
}

#ifdef HAS_PHASE_ERR_LUT
float calc_carrier_phase_err_lut_rad(const int32_t i_val, const int32_t q_val) {
    float phase_err_rad = 0.0f;
    if(0 <= i_val) {
        if(0 <= q_val) {
            phase_err_rad = phaseErrRadLUT_iqPos[i_val][q_val];
        } else {
            phase_err_rad = phaseErrRadLUT_iPosQNeg[i_val][-q_val];
        }
    } else {
        if(0 <= q_val) {
            phase_err_rad = phaseErrRadLUT_iNegQpos[-i_val][q_val];
        } else {
            phase_err_rad = phaseErrRadLUT_iNegQneg[-i_val][-q_val];
        }
    }
#ifdef HAS_BPSK_DEBUG
    LOG_PARN(QUAD_MIX_4FS, "Phase,%f+j(%f),Err:%7.6f Rad", i_val, q_val, phase_err_rad);
#endif
    return phase_err_rad;
}
#endif

bool is_valid_phase_err_rad(const float phase_error_rad) {
    bool res = false;
    if((-M_PI / 2) <= phase_error_rad) {
        if(phase_error_rad <= (M_PI / 2)) {
            res = true;
        }
    }
    return res;
}

inline bool quad_mix_4fs_is_valid_iq(const QuadMix4fsHandle_t* const Node) {
    bool res = true;
    if(0 == Node->SdrI.AfterFilt) {
        if(0 == Node->SdrQ.AfterFilt) {
            res = false;
        }
    }
    return res;
}

inline float quad_mix_4fs_calc_phase_error_atan(QuadMix4fsHandle_t* const Node) {
    float phase_error_rad = 0.0f;
    bool res = quad_mix_4fs_is_valid_iq(Node);
    if(res) {
        phase_error_rad = calc_carrier_phase_err_rad((float)Node->SdrI.AfterFilt, (float)Node->SdrQ.AfterFilt);
    }
    return phase_error_rad;
}

static inline bool quad_mix_4fs_calc_phase_error(QuadMix4fsHandle_t* const Node) {
    bool res = true;
    Node->phase_error_rad = quad_mix_4fs_calc_phase_error_atan(Node);
    // Node->phase_error_rad = calc_carrier_phase_err_lut_rad( Node->SdrI.AfterFilt, Node->SdrQ.AfterFilt);
#ifdef HAS_QUAD_MIX_DEBUG
#ifdef HAS_GPIO
    float abs_error_deg = RAD_2_DEG(fabsf(Node->phase_error_rad));
    if(abs_error_deg < COSTAS_LOOP_LOCK_PHA_ERR) {
        gpio_logic_level_set(Node->PadOkPhase, GPIO_LVL_HI);
    } else {
        gpio_logic_level_set(Node->PadOkPhase, GPIO_LVL_LOW);
    }
#endif
#endif
    return res;
}

#ifdef HAS_IQ_DIAG
#ifdef HAS_DAC
bool quad_mix_4fs_constellation_diagram(QuadMix4fsHandle_t* const Node) {
    bool res = false;
    uint16_t code;
    code =(uint16_t) ((int32_t)DAC_12BIT_HALF + (int32_t)Node->SdrI.AfterFilt);
    res = dac_channel_code_set(1, DAC_CHAN_1, code);
    code =(uint16_t) ((int32_t)DAC_12BIT_HALF + (int32_t) Node->SdrQ.AfterFilt);
    res = dac_channel_code_set(1, DAC_CHAN_2, code);
    return res;
}
#endif
#endif

inline bool quad_mix_4fs_proc_sample_ll(QuadMix4fsHandle_t* const Node, int32_t sam_num, int32_t sample) {
    bool res = false;

#ifdef HAS_BPSK_DEBUG
    LOG_PARN(QUAD_MIX_SAMPLE, "samp:[%d]=%d", sam_num, sample);
#endif
    Node->proc_cnt++;
    Node->sample = sample;
    Node->sam_num = sam_num;

    bool ires = quad_mix_4fs_proc_sample_i(Node, sam_num, sample);
    bool qres = quad_mix_4fs_proc_sample_q(Node, sam_num, sample);
    (void)ires;
    (void)qres;
#ifdef HAS_IQ_DIAG
    quad_mix_4fs_constellation_diagram(Node);
#endif

#ifdef HAS_BPSK_DEBUG
    LOG_DEBUG(QUAD_MIX, "Sam:%d,%s", sample, QuadMix4fsAfterMuxNodeToStr(Node));
#endif

    res = quad_mix_4fs_calc_phase_error(Node);
#ifdef HAS_BPSK_DEBUG
    if(qres && ires) {
    } else {
        LOG_ERROR(QUAD_MIX_4FS, "MixError");
    }
    LOG_DEBUG(QUAD_MIX_4FS, "%s", QuadMix4fsShortNodeToStr(Node));
#endif

    return res;
}

bool quad_mix_4fs_proc_sample(uint8_t num, int32_t sam_num, int32_t sample) {
    bool res = false;
    QuadMix4fsHandle_t* Node = QuadMix4fsGetNode(num);
    if(Node) {
        res = quad_mix_4fs_proc_sample_ll(Node, sam_num, sample);
    }
    return res;
}

#ifdef HAS_IIR
bool quad_mix_4fs_lpf_iir(uint8_t num, int32_t k) {
    bool res = false;
    QuadMix4fsHandle_t* Node = QuadMix4fsGetNode(num);
    if(Node) {
        LOG_WARNING(QUAD_MIX_4FS, "QM%u,Set,IIR,LPF,K:%f", num, k);
        res = iir_lowpas_1st_order(Node->filter_num_i, k);
        if(res) {
            res = iir_lowpas_1st_order(Node->filter_num_q, k);
        }
    }
    return res;
}
#endif

static bool quad_mix_4fs_init_common(const QuadMix4fsConfig_t* const Config, QuadMix4fsHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->filter_order = Config->filter_order;
            Node->cut_off_freq_hz = Config->cut_off_freq_hz;
            Node->filter_num_i = Config->filter_num_i;
            Node->filter_num_q = Config->filter_num_q;
#ifdef HAS_GPIO
            Node->PadOkPhase = Config->PadOkPhase;
#endif
            res = true;
        }
    }
    return res;
}

bool quad_mix_4fs_init_one(uint8_t num) {
    bool res = false;

#ifdef HAS_PHASE_ERR_LUT
    res = quad_mix_4fs_init_phase_error_lut();
#endif
    LOG_WARNING(QUAD_MIX_4FS, "%u,Init", num);
    const QuadMix4fsConfig_t* Config = NULL;
    Config = QuadMix4fsGetConfig(num);
    res = quad_mix_4fs_is_valid_config(Config);
    if(res) {
        LOG_WARNING(QUAD_MIX_4FS, "%s", QuadMix4fsConfigToStr(Config));
        if(res) {
            QuadMix4fsHandle_t* Node = QuadMix4fsGetNode(num);
            if(Node) {
                res = quad_mix_4fs_init_common(Config, Node);
                Node->pNodeFilterI = SlidingIntegralGetNode(Node->filter_num_i);
                if(Node->pNodeFilterI) {
                    Node->pNodeFilterQ = SlidingIntegralGetNode(Node->filter_num_q);
                    if(Node->pNodeFilterQ) {
                        Node->valid = true;
                        Node->init = true;
                        LOG_INFO(QUAD_MIX_4FS, "Init,Ok");
                    }
                }

            } else {
                LOG_ERROR(QUAD_MIX_4FS, "NodeErr");
            }
        } else {
            LOG_ERROR(QUAD_MIX_4FS, "Absurd,Config,Err");
        }
    } else {
        LOG_DEBUG(QUAD_MIX_4FS, "Conf,Node,Err");
    }

    return res;
}

COMPONENT_INIT_PATTERT(QUAD_MIX_4FS, QUAD_MIX_4FS, quad_mix_4fs)
