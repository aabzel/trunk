#include "rtc_isr.h"

#include "rtc_drv.h"

static bool ProcNrfxRtcEventHandler(RtcHandle_t* const Node, nrfx_rtc_int_type_t interrupt_type) {
    bool res = false;
    if(Node) {
        switch(interrupt_type) {
        case NRFX_RTC_INT_TICK:
            Node->int_cnt++;
            if(0 == (Node->int_cnt % 8)) {
                Node->raw_sec++;
            }
            res = true;
            break;
        case NRFX_RTC_INT_COMPARE0:
            break;
        case NRFX_RTC_INT_COMPARE1:
            break;
        case NRFX_RTC_INT_COMPARE2:
            break;
        case NRFX_RTC_INT_COMPARE3:
            break;
        case NRFX_RTC_INT_OVERFLOW:
            Node->error_cnt++;
            break;
        default:
            break;
        }
    }
    return res;
}

#ifdef NRFX_RTC0_ENABLED
void nrfx_rtc0_event_handler(nrfx_rtc_int_type_t interrupt_type) {
    RtcHandle_t* Node = RtcGetNode(0);
    if(Node) {
        ProcNrfxRtcEventHandler(Node, interrupt_type);
    }
}
#endif

#ifdef NRFX_RTC1_ENABLED
void nrfx_rtc1_event_handler(nrfx_rtc_int_type_t interrupt_type) {
    RtcHandle_t* Node = RtcGetNode(1);
    if(Node) {
        ProcNrfxRtcEventHandler(Node, interrupt_type);
    }
}
#endif

#ifdef NRFX_RTC2_ENABLED
void nrfx_rtc2_event_handler(nrfx_rtc_int_type_t interrupt_type) {
    RtcHandle_t* Node = RtcGetNode(2);
    if(Node) {
        ProcNrfxRtcEventHandler(Node, interrupt_type);
    }
}
#endif
