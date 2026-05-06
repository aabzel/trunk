#include "quad_mix_4fs_diag.h"

#include <stdio.h>
#include <string.h>

#include "float_diag.h"
#include "quad_mix_4fs.h"
#include "log.h"
#include "circular_buffer_index.h"
#include "dsp_diag.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

#ifdef HAS_PC
#include "win_utils.h"
#endif

bool quad_mix_4fs_diag(uint8_t num) {
    bool res = false;
    QuadMix4fsHandle_t* Node = QuadMix4fsGetNode(num);
    if(Node) {
    }

    return res;
}

const char* QuadMix4fsShortNodeToStr(const  QuadMix4fsHandle_t* const Node){
    static char temp[300] = "?";
    strcpy(temp, "");
    if(Node) {
        float phase_error_deg = RAD_2_DEG(Node->phase_error_rad);
        snprintf(temp, sizeof(temp), "%sSam:%3d,", temp, Node->sample);
        snprintf(temp, sizeof(temp), "%sLoPha:%2d Sam,", temp, Node->lo_phase_n);
        snprintf(temp, sizeof(temp), "%sPhaErr:%s deg,", temp, FloatToStr(phase_error_deg,1));
        snprintf(temp, sizeof(temp), "%s(%3d)+j(%3d),", temp, Node->SdrI.AfterFilt,Node->SdrQ.AfterFilt);
    }
    return temp;
}


const char* QuadMix4fsAfterMuxNodeToStr(const  QuadMix4fsHandle_t* const Node){
    static char temp[300] = "?";
    strcpy(temp, "");
    if(Node) {
        snprintf(temp, sizeof(temp), "%sSam:%3d,", temp, Node->sample);
        snprintf(temp, sizeof(temp), "%sAM:(%3d)+j(%3d),", temp, Node->SdrI.AfterMux,Node->SdrQ.AfterMux);
    }
    return temp;
}


const char* QuadMix4fsNodeToStr(const  QuadMix4fsHandle_t* const Node){
    static char temp[300] = "?";
    strcpy(temp, "");
    if(Node) {
        float phase_error_deg = RAD_2_DEG(Node->phase_error_rad);
        snprintf(temp, sizeof(temp), "%sN:%3u,", temp, Node->num);
        snprintf(temp, sizeof(temp), "%sProcCnt:%4u,", temp, Node->proc_cnt);
        snprintf(temp, sizeof(temp), "%sSamN:%3u,", temp, Node->sam_num);
        snprintf(temp, sizeof(temp), "%sLoPha:%2d Sam,", temp, Node->lo_phase_n);
        snprintf(temp, sizeof(temp), "%sPhaErr:%s deg,", temp, FloatToStr(phase_error_deg,1));
        //snprintf(temp, sizeof(temp), "%sTime:%ss,", temp, FloatToStr(Node->time_s,3));
        snprintf(temp, sizeof(temp), "%sSam:%3d,", temp, Node->sample);
        snprintf(temp, sizeof(temp), "%s(%3d)+j(%3d),", temp, Node->SdrI.AfterFilt,Node->SdrQ.AfterFilt);
        snprintf(temp, sizeof(temp), "%sInit:%u,", temp, Node->init);
    }
    return temp;
}

const char* QuadMix4fsConfigToStr(const  QuadMix4fsConfig_t* const Config){
    static char temp[300] = "?";
    strcpy(temp, "");
    if(Config) {
        snprintf(temp, sizeof(temp), "%sN:%u,", temp, Config->num);
        snprintf(temp, sizeof(temp), "%s%s,", temp, Config->name);
        snprintf(temp, sizeof(temp), "%sFiltOrder:%u,", temp, Config->filter_order);
        snprintf(temp, sizeof(temp), "%sFiltNumI:%u,", temp, Config->filter_num_i);
        snprintf(temp, sizeof(temp), "%sFiltNumQ:%u,", temp, Config->filter_num_q);
        snprintf(temp, sizeof(temp), "%sFcut:%s Hz,", temp, FloatToStr(Config->cut_off_freq_hz,3));
    }
    return temp;
}


bool QuadMix4fsDiagConfig(const QuadMix4fsConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;
    }
    return res;
}
