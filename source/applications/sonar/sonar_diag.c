#include "sonar_diag.h"

#include <stdio.h>
#include <string.h>

#include "float_diag.h"
#include "log.h"
#include "sonar.h"

bool sonar_diag_one(uint8_t num) {
    bool res = false;

    SonarHandle_t* Node = SonarGetNode(num);
    if(Node) {
        res = true;
    }

    return res;
}

bool sonar_diag(void) {
    bool res = true;
    return res;
}

const char* SonarBestCorrelationToStr(const SonarCorrelationInfo_t* const Info) {
    static char lText[300] = {0};
    strcpy(lText, "" CRLF);
    if(Info) {
        snprintf(lText, sizeof(lText), "%sSample:%u,", lText, Info->sample);
        snprintf(lText, sizeof(lText), "%s%s s,", lText, FloatToStr(Info->up_time_s, 2));
        snprintf(lText, sizeof(lText), "%sCorr:%s,", lText, FloatToStr(Info->correlation, 1));
        snprintf(lText, sizeof(lText), "%sCorPosLog:%s,", lText, FloatToStr(Info->correlation_positive_log, 2));
        snprintf(lText, sizeof(lText), "%sCorNegLog:%s,", lText, FloatToStr(Info->correlation_negative_log, 2));
        snprintf(lText, sizeof(lText), "%sPosCorr:%s,", lText, FloatToStr(Info->positive_correlation, 1));
        snprintf(lText, sizeof(lText), "%sNegCorr:%s,", lText, FloatToStr(Info->negative_correlation, 1));
        snprintf(lText, sizeof(lText), "%sDist:%s,", lText, FloatToStr(Info->dist_m, 2));
    }
    return lText;
}

const char* SonarConfigToStr(const SonarConfig_t* const Config) {
    static char lText[300] = {0};
    if(Config) {
        strcpy(lText, "");
    }
    return lText;
}

const char* SonarChirpParamToStr(const SonarChirpParam_t* const Node) {
    static char lText[300] = {0};
    strcpy(lText, "");
    if(Node) {
        float bandwith_hz = Node->frequency2-Node->frequency1;
        snprintf(lText, sizeof(lText), "%sSignalDur:%s s,", lText, FloatToStr(Node->signal_duration_s, 2));
        snprintf(lText, sizeof(lText), "%sA:%s,", lText, FloatToStr(Node->amplitude, 2));
        snprintf(lText, sizeof(lText), "%sF1:%s Hz,", lText, FloatToStr(Node->frequency1, 1));
        snprintf(lText, sizeof(lText), "%sF2:%s Hz,", lText, FloatToStr(Node->frequency2, 1));
        snprintf(lText, sizeof(lText), "%sBW:%s Hz,", lText, FloatToStr(bandwith_hz, 1));
    }
    return lText;
}

const char* SonarNodeToStr(const SonarHandle_t* const Node) {
    static char lText[300] = {0};
    strcpy(lText, "");
    if(Node) {
        snprintf(lText, sizeof(lText), "%sDDS_%u,", lText, Node->dds_num);
        snprintf(lText, sizeof(lText), "%sSignalDur:%s s,", lText, FloatToStr(Node->signal_duration_s, 2));
        snprintf(lText, sizeof(lText), "%scorrNum:%u,", lText, Node->correlator_num);
        snprintf(lText, sizeof(lText), "%scalcCorr:%u,", lText, Node->calc_correlation);
        snprintf(lText, sizeof(lText), "%sperPerChip:%u,", lText, Node->periods_per_chip);
        snprintf(lText, sizeof(lText), "%slooBackAudioN:%u,", lText, Node->loopback_audio_num);
        snprintf(lText, sizeof(lText), "%sA:%s,", lText, FloatToStr(Node->amplitude, 2));
        snprintf(lText, sizeof(lText), "%sF1:%s Hz,", lText, FloatToStr(Node->frequency1, 1));
        snprintf(lText, sizeof(lText), "%sF2:%s Hz,", lText, FloatToStr(Node->frequency2, 1));
        snprintf(lText, sizeof(lText), "%sVsnd:%s m/s,", lText, FloatToStr(Node->v_sound_m_pes_sec, 1));
    }
    return lText;
}

bool SonarDiag(const SonarHandle_t* const Node) {
    bool res = false;
    if(Node) {
        LOG_INFO(SONAR, "%s", SonarNodeToStr(Node));
        res = true;
    }
    return res;
}
