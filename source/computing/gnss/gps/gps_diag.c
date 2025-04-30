#include "gps_diag.h"

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "float_utils.h"
#include "gps_misc_1.h"
#include "log.h"
#include "time_mcal.h"

const char* GpsNodeToStr(const GpsHandle_t* const Node) {
    static char name[300] = "?";
    if(Node) {
        snprintf(name, sizeof(name),
                 "IF:%d Hz,PRNlen:%u Sample,SampleDur:%f ns=FlyLen:%f m,SamPerChip:%3.1f,PRNseekStep:%u Sap",
                 Node->intermediate_freq_hz, Node->one_prn_sample_cnt, SEC_2_NSEC(Node->adc_sample_time_s),
                 Node->adc_sample_len_m, Node->sample_per_chip, Node->step_samples);
    }
    return name;
}

const char* GpsConfigToStr(const GpsConfig_t* const Config) {
    static char name[100] = "?";
    if(Config) {
        snprintf(name, sizeof(name), "[%s],GnssFrontEendLo:%7.2f Hz,ADC:%7.2f Hz", Config->file_name,
                 Config->gnss_front_end_lo_freq_hz, Config->adc_sample_rate_hz);
    }
    return name;
}

const char* CorrelationToStr(CorrelationResult_t* const CorrelationMin) {
    static char name[200] = "?";
    if(CorrelationMin) {
        snprintf(name, sizeof(name), "Dopp:%f Hz,Corr:%d,Offset:%u Sam", CorrelationMin->if_corr_hz,
                 CorrelationMin->mult_summ, CorrelationMin->offset_samples);
    }
    return name;
}

const char* PrnCorrelationToStr(PrnCorrelationResult_t* const Correlation) {
    static char name[200] = "?";
    if(Correlation) {
        snprintf(name, sizeof(name), "Corr:%d,Offset:%u Sam", Correlation->mult_summ, Correlation->offset_samples);
    }
    return name;
}

const char* PrnInfoToStr(const PrnInfo_t* const Node) {
    static char name[400] = "?";
    if(Node) {
        snprintf(name, sizeof(name), "PRN:%d,%s", Node->prn, PrnCorrelationToStr(&Node->Max));
    }
    return name;
}

#if 0
const char* GpsChanIToStr(ChannelIQ_t* ChI){
    static char name[550]="?";
    if(ChI){
        snprintf(name,sizeof(name),"I:Mi_%s",CorrelationToStr(&ChI->CorrelationMin));
        snprintf(name,sizeof(name),"%s,Ma_%s",name,CorrelationToStr(&ChI->CorrelationMax));
    }
    return name;
}
#endif

const char* GpsSatToStr(const GpsSat_t* const Node) {
    static char name[600] = "?";
    if(Node) {
        strcpy(name, "");
        snprintf(name, sizeof(name), "%sPRN:%d,", name, Node->prn);
        snprintf(name, sizeof(name), "%sDoppler:%d Hz,", name, Node->doppler_offset_hz);
        snprintf(name, sizeof(name), "%sPhase:%u Sam", name, Node->init_prn_phase_sample);
        // snprintf(name, sizeof(name), "%s%s" CRLF, name, CorrelationToStr(&Sat->CorrelationMax));
    }
    return name;
}
