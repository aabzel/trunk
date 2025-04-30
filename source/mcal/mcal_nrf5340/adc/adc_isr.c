#include "adc_isr.h"

#include "adc_drv.h"

static bool ProcNrfxSaadcEventHandler(AdcHandle_t* AdcNode, nrfx_saadc_evt_t const* p_event) {
    bool res = false;
    if(AdcNode) {
        if(p_event) {
            switch(p_event->type) {
            case NRFX_SAADC_EVT_DONE:
                AdcNode->conv_done = true;
                break;
            case NRFX_SAADC_EVT_LIMIT:
                break;
            case NRFX_SAADC_EVT_CALIBRATEDONE:
                break;
            case NRFX_SAADC_EVT_BUF_REQ:
                break;
            case NRFX_SAADC_EVT_READY:
                break;
            case NRFX_SAADC_EVT_FINISHED:
                break;
            default:
                break;
            }
        }
    }
    return res;
}

void nrfx_saadc_event_handler(nrfx_saadc_evt_t const* p_event) {
    AdcHandle_t* AdcNode = AdcGetNode(1);
    if(AdcNode) {
        ProcNrfxSaadcEventHandler(AdcNode, p_event);
        AdcNode->it_cnt++;
    }
}
