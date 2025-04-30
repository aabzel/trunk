#include "quadrature_mixer_diag.h"

#include <stdio.h>
#include <string.h>

#include "quadrature_mixer.h"
#include "log.h"
#ifdef HAS_PC
#include "win_utils.h"
#endif
#include "circular_buffer_index.h"
#include "dsp_diag.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

bool quadrature_mixer_diag(uint8_t num) {
    bool res = false;
    QuadratureMixerHandle_t* Node = QuadratureMixerGetNode(num);
    if(Node) {
    }

    return res;
}


const char* QuadratureMixerNodeToStr(const  QuadratureMixerHandle_t* const Node){
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sTime:%ss,", text, DoubleToStr(Node->time_s));
        snprintf(text, sizeof(text), "%sSam:%s,", text, DoubleToStr(Node->sample));
        snprintf(text, sizeof(text), "%sPhaErr:%s rad,", text, DoubleToStr(Node->phase_error_rad));
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Node->sample_rate_hz));
        snprintf(text, sizeof(text), "%sLoFerq:%s Hz,", text, DoubleToStr(Node->lo_frequency_hz));
        snprintf(text, sizeof(text), "%sInCnt:%u,", text, Node->proc_cnt);
        snprintf(text, sizeof(text), "%sLoPha:%f rad,", text, Node->lo_phase_rad);
    }
    return text;
}

const char* QuadratureMixerConfigToStr(const  QuadratureMixerConfig_t* const Config){
    static char text[300] = "?";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%s%s,", text, Config->name);
        snprintf(text, sizeof(text), "%sFiltType:%s,", text, DspFilterTypeToStr(Config->filter_type));
        snprintf(text, sizeof(text), "%sFiltOrder:%u,", text, Config->filter_order);
        snprintf(text, sizeof(text), "%sFiltI:%u,", text, Config->filter_num[0]);
        snprintf(text, sizeof(text), "%sFiltQ:%u,", text, Config->filter_num[1]);
        snprintf(text, sizeof(text), "%sFsam:%s Hz,", text, DoubleToStr(Config->sample_rate_hz));
        snprintf(text, sizeof(text), "%sFcut:%s Hz,", text, DoubleToStr(Config->cut_off_freq_hz));
    }
    return text;
}

bool QuadratureMixerDiagConfig(const QuadratureMixerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }
    return res;
}
