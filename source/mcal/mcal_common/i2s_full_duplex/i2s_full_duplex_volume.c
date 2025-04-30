#include "i2s_volume.h"

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "log.h"
#include "i2s_drv.h"
#include "i2s_diag.h"



static bool i2s_proc_off_ll(I2sHandle_t* const Node){
    bool res = true;

    return res;
}

static bool i2s_proc_run_ll(I2sHandle_t* const Node){
    bool res = true;
    return res;
}


static bool i2s_proc_amp_ll(I2sHandle_t* const Node){
    bool res = false;
    Node->pcm_max_get = i2s_calc_pcm_max_ll(Node);
    SampleType_t pcm_dif =Node->pcm_max_get-Node->pcm_max_set ;
    if(abs(pcm_dif) < I2S_VOLUME_SET_ACCURACY){
    	Node->state = I2S_STATE_RUN;
    	res = true;
    } else if (Node->pcm_max_get < Node->pcm_max_set) {
    	res = i2s_increase_pcms_ll(Node);
    } else if(Node->pcm_max_set<Node->pcm_max_get){
    	Node->state= I2S_STATE_DEC;
    	res = true;
    }
    return res;
}

static bool i2s_proc_dec_ll(I2sHandle_t* const Node){
    bool res = false;
    Node->pcm_max_get = i2s_calc_pcm_max_ll(Node);
    if(Node->pcm_max_get <= 0){
    	Node->state=I2S_STATE_OFF;
    	res = true;
    }else{
    	res = i2s_decrease_pcms_ll(Node);
    }
    return res;
}

bool i2s_volume_proc_ll(  I2sHandle_t* const Node) {
    bool res = true;
    if(Node) {
        if(Node->rx_tx_done) {
            LOG_DEBUG(I2S, "I2S%u RxTxDone +%u Sa", Node->samples_cnt);
        	LOG_DEBUG(I2S,"%s",I2sFsmDiag2Str(Node));
        	switch(Node->state) {
        	    case I2S_STATE_OFF: res= i2s_proc_off_ll(Node); break;
        	    case I2S_STATE_AMP: res= i2s_proc_amp_ll(Node); break;
        	    case I2S_STATE_RUN: res= i2s_proc_run_ll(Node); break;
        	    case I2S_STATE_DEC: res= i2s_proc_dec_ll(Node); break;
        	    default: {
                    LOG_DEBUG(I2S, "I2S%u UndefState",Node->num, Node->state);
        	    }break;
        	}

            Node->rx_tx_done = false;
        }
    }
    return res;
}

bool i2s_volume_init_ll(I2sHandle_t* const Node){
    bool res = false;
    if(Node) {
        LOG_WARNING(I2S, "I2S%u VolumeInit", Node->num);
        Node->state = I2S_STATE_OFF;
        Node->pcm_max_set = 100;
        Node->pcm_max_get = 0;

        Node->dec_numerator=9;
        Node->denominator=10;
        Node->inc_numerator=11;
        res = true;
    }
    return res;
}

