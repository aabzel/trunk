#include "pll_sim_diag.h"

#include <stdio.h>
#include <string.h>

#include "num_to_str.h"
#include "log.h"



const char* PllSinConfigToStr(const PllSimConfig_t* const Config){
	static char text[250] = "";
    if(Config){
    	strcpy(text,"");
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->num);
        snprintf(text, sizeof(text), "%sLo:%f Hz,", text,Config->lo_frequency_hz);
        snprintf(text, sizeof(text), "%sVCOp:%f,", text,Config->vco_p);
        snprintf(text, sizeof(text), "%sSamRate:%u Hz,", text,Config->sample_frequency_hz);
        snprintf(text, sizeof(text), "%sN:%u,", text,Config->divider);
        snprintf(text, sizeof(text), "%sFir:%u,", text,Config->fir_num);
    }
    return text;
}


const char* PllSinNodeToStr(const PllSimHandle_t* const Node){
    static char text[350] = "";
    if(Node) {
        strcpy(text,"");
        snprintf(text, sizeof(text), "%sS:%5u,", text,Node->sample_cnt);
        snprintf(text, sizeof(text), "%sT:%9.6f s,", text,Node->up_time_s);
        snprintf(text, sizeof(text), "%sOutFr:%6.1f Hz,", text,Node->out_frequency_hz);
        snprintf(text, sizeof(text), "%sPha_e:%6.1f deg,", text,Node->phase_err_deg);
        snprintf(text, sizeof(text), "%sVCOin:%6.1f deg,", text,Node->vco_in_deg);
        snprintf(text, sizeof(text), "%sFbFr:%6.1f Hz,", text,Node->fb_frequency_hz);
        snprintf(text, sizeof(text), "%sN:%1u,", text,Node->divider);
        snprintf(text, sizeof(text), "%sLoI:%6.1f,", text,Node->Lo.i);
        snprintf(text, sizeof(text), "%sFbI:%6.1f,", text,Node->SfbCur.i);
        snprintf(text, sizeof(text), "%sVCOp:%4.0f,", text,Node->vco_p);
        snprintf(text, sizeof(text), "%sLoFr:%6.1f Hz,", text,Node->lo_frequency_hz);
        //snprintf(text, sizeof(text), "%sSamTime:%f s,", text,Node->sample_time_s);
    }
    return text;
}


bool pll_sim_diag(uint8_t num){
	return false;
}
