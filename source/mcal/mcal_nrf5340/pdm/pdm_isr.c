#include "pdm_isr.h"

#include "pdm_drv.h"

void nrfx_pdm0_event_handler(nrfx_pdm_evt_t const* p_event) {
    PdmHandle_t* Node = PdmGetNode(0);
    bool res = false;
    if(Node) {
        Node->int_cnt++;
        Node->in_isr = true;
        switch(p_event->error) {
        case NRFX_PDM_NO_ERROR: {
            if(p_event->buffer_requested) {
                Node->rx_done = true;
                Node->rx_sample_cnt += Node->samples_cnt;
                if(MIC_MODE_CONTINUOUS == Node->mic_mode) {
                    uint32_t offset = Node->samples_cnt * Node->buf_toogle;
                    res = pdm_buf_set(Node->num, Node->buf + offset, Node->samples_cnt);
                    if(res) {
                    } else {
                        Node->error_cnt++;
                    }
                }
            }
            if(p_event->buffer_released) {
                Node->buf_toogle = (0 == Node->buf_toogle) ? 1 : 0;
            }
        } break;
        case NRFX_PDM_ERROR_OVERFLOW: {
            Node->error_cnt++;
        } break;
        default:
            break;
        }
        Node->in_isr = false;
    }
}
