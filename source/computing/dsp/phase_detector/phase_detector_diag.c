#include "phase_detector_diag.h"

#include <stdio.h>
#include <string.h>

#include "phase_detector.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

bool phase_detector_diag(uint8_t num) {
    bool res = false;
    return res;
}

const char* PhaseDetectorNodeToStr(const  PhaseDetectorHandle_t* const Node){
    static char text[300] = "?";
    if(Node) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Node->num);
        snprintf(text, sizeof(text), "%sCHs:%u,", text, Node->channel_cnt);
        snprintf(text, sizeof(text), "%sSamFreq:%u Hz,", text, Node->sample_freq_hz);
        snprintf(text, sizeof(text), "%sBitPerSam:%u Bit,", text, Node->bitsPerSample);
        snprintf(text, sizeof(text), "%sInit:%u,", text, Node->init);
        snprintf(text, sizeof(text), "%sSamCnt:%u,", text, Node->sample_cnt);
        snprintf(text, sizeof(text), "%sFs:%s Hz,", text, DoubleToStr(Node->signal_frequency_hz));
        snprintf(text, sizeof(text), "%sSamTime:%s s,", text, DoubleToStr(Node->sample_time_s));
        snprintf(text, sizeof(text), "%sDuration:%s s,", text, DoubleToStr(Node->duration_s));
        snprintf(text, sizeof(text), "%sWaveLen:%s m", text, DoubleToStr(Node->wavelength_m));
    }
    return text;
}

const char* PhaseDetectorConfigToStr(const  PhaseDetectorConfig_t* const Config){
    static char text[300] = "?";
    if(Config) {
        strcpy(text, "");
        snprintf(text, sizeof(text), "%sN:%u,", text, Config->num);
        snprintf(text, sizeof(text), "%sFirOrder:%u,", text, Config->filter_order);
        snprintf(text, sizeof(text), "%sQMixNum:%u,", text, Config->quadrature_mixer_num);
        snprintf(text, sizeof(text), "%sFsam:%u Hz,", text, Config->sample_freq_hz);
        snprintf(text, sizeof(text), "%sChan:%u,", text, Config->channel_cnt);
        snprintf(text, sizeof(text), "%sBit/sam:%u bit,", text, Config->bitsPerSample);
        snprintf(text, sizeof(text), "%sSpeed:%f m/s,", text, Config->speed_of_sound_m_per_s);
        snprintf(text, sizeof(text), "%sFs:%s Hz,", text, DoubleToStr(Config->signal_frequency_hz));

    }
    return text;
}





