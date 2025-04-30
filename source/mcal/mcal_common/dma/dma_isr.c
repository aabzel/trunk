#include "dma_isr.h"

bool DmaChannelHalfIsrLL(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->half = true;
        Node->half_cnt++;
        Node->busy = true;
        res = true;
        if(Node->CallBackHalf) {
            res = Node->CallBackHalf();
        }
    }
    return res;
}

bool DmaChannelDoneIsrLL(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->done = true;
        Node->done_cnt++;
        Node->busy = false;
        res = true;
        if(Node->CallBackDone) {
            res = Node->CallBackDone();
        }
    }
    return res;
}

bool DmaChannelErrorIsr_ll(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->it_error = true;
        Node->error_cnt++;
        Node->busy = false;
        res = true;
        if(Node->CallBackDone) {
            res = Node->CallBackDone();
        }
    }
    return res;
}
