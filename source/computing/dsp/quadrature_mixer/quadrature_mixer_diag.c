#include "quadrature_mixer_diag.h"

#include <stdio.h>
#include <string.h>

#include "float_diag.h"
#include "quadrature_mixer.h"
#include "log.h"
#include "circular_buffer_index.h"
#include "dsp_diag.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_PC
#include "win_utils.h"
#endif

bool quadrature_mixer_diag(uint8_t num) {
    bool res = false;
    QuadratureMixerHandle_t* Node = QuadratureMixerGetNode(num);
    if(Node) {
    }

    return res;
}


const char* QuadratureMixerNodeToStr(const  QuadratureMixerHandle_t* const Node){
    static char temp[300] = "?";
    if(Node) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sTime:%ss,", temp, FloatToStr(Node->time_s,3));
        snprintf(temp, sizeof(temp), "%sSam:%s,", temp, FloatToStr(Node->sample,3));
        snprintf(temp, sizeof(temp), "%sPhaErr:%s rad,", temp, FloatToStr(Node->phase_error_rad,3));
        snprintf(temp, sizeof(temp), "%sInit:%u,", temp, Node->init);
        snprintf(temp, sizeof(temp), "%sFsam:%s Hz,", temp, FloatToStr(Node->sample_rate_hz,3));
        snprintf(temp, sizeof(temp), "%sLoFerq:%s Hz,", temp, FloatToStr(Node->lo_frequency_hz,3));
        snprintf(temp, sizeof(temp), "%sInCnt:%u,", temp, Node->proc_cnt);
        snprintf(temp, sizeof(temp), "%sLoPha:%f rad,", temp, Node->lo_phase_rad);
    }
    return temp;
}

const char* QuadratureMixerConfigToStr(const  QuadratureMixerConfig_t* const Config){
    static char temp[300] = "?";
    if(Config) {
        strcpy(temp, "");
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
        snprintf(temp, sizeof(temp), "%sFiltType:%s,", temp, DspFilterTypeToStr(Config->filter_type));
        snprintf(temp, sizeof(temp), "%sFiltOrder:%u,", temp, Config->filter_order);
        snprintf(temp, sizeof(temp), "%sFiltI:%u,", temp, Config->filter_num[0]);
        snprintf(temp, sizeof(temp), "%sFiltQ:%u,", temp, Config->filter_num[1]);
        snprintf(temp, sizeof(temp), "%sFsam:%s Hz,", temp, FloatToStr(Config->sample_rate_hz,3));
        snprintf(temp, sizeof(temp), "%sFcut:%s Hz,", temp, FloatToStr(Config->cut_off_freq_hz,3));
    }
    return temp;
}

bool QuadratureMixerDiagConfig(const QuadratureMixerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }
    return res;
}
