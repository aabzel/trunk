#include "spi_drv.h"

bool ProcNrfxSpimEventHandler(SpiHandle_t* Node, nrfx_spim_evt_t const* p_event) {
    bool res = false;
    if(Node) {
        if(p_event) {
            switch(p_event->type) {
            case NRFX_SPIM_EVENT_DONE:
                Node->it_done = true;
                Node->it_cnt++;

                Node->txrx_int = true;
                Node->txrx_cnt++;

                Node->tx_int = true;
                Node->rx_int = true;
                break;
            default:
                break;
            }
        }
    }
    return res;
}

#ifdef NRFX_SPIM0_ENABLED
void nrfx_spim0_event_handler(nrfx_spim_evt_t const* p_event, void* p_context) {
    SpiHandle_t* Node = SpiGetNode(0);
    if(Node) {
        ProcNrfxSpimEventHandler(Node, p_event);
    }
}
#endif

#ifdef NRFX_SPIM1_ENABLED
void nrfx_spim1_event_handler(nrfx_spim_evt_t const* p_event, void* p_context) {
    SpiHandle_t* Node = SpiGetNode(1);
    if(Node) {
        ProcNrfxSpimEventHandler(Node, p_event);
    }
}
#endif

#ifdef NRFX_SPIM2_ENABLED
void nrfx_spim2_event_handler(nrfx_spim_evt_t const* p_event, void* p_context) {
    SpiHandle_t* Node = SpiGetNode(2);
    if(Node) {
        ProcNrfxSpimEventHandler(Node, p_event);
    }
}
#endif

#ifdef NRFX_SPIM3_ENABLED
void nrfx_spim3_event_handler(nrfx_spim_evt_t const* p_event, void* p_context) {
    SpiHandle_t* Node = SpiGetNode(3);
    if(Node) {
        ProcNrfxSpimEventHandler(Node, p_event);
    }
}
#endif

#ifdef NRFX_SPIM4_ENABLED
void nrfx_spim4_event_handler(nrfx_spim_evt_t const* p_event, void* p_context) {
    SpiHandle_t* Node = SpiGetNode(4);
    if(Node) {
        ProcNrfxSpimEventHandler(Node, p_event);
    }
}
#endif
