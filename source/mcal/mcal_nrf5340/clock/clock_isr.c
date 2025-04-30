#include "clock_isr.h"

#include "clock_config.h"

void NrfxClockEventHandler(nrfx_clock_evt_type_t event){
    ClockInstance.isr_cnt++;
    switch((uint8_t) event) {
        case NRFX_CLOCK_EVT_HFCLK_STARTED     : {
            ClockInstance.hfclk_started++;
        } break;
        case NRFX_CLOCK_EVT_LFCLK_STARTED     : {
            ClockInstance.lfclk_started++;
        } break;
        case NRFX_CLOCK_EVT_CTTO              : {
            ClockInstance.evt_ctto++;
        } break;
        case NRFX_CLOCK_EVT_CAL_DONE          : {
            ClockInstance.cal_done++;
        } break;
        case NRFX_CLOCK_EVT_HFCLKAUDIO_STARTED: {
            ClockInstance.hfclkaudio_started ++;
        } break;
        case NRFX_CLOCK_EVT_HFCLK192M_STARTED : {
            ClockInstance.hfclk192m_started++;
        } break;
        default : {
            ClockInstance.err_cnt++;
        } break;
    } ;

}
