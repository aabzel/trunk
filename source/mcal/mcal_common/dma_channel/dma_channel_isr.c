#include "dma_channel_isr.h"

#include "dma_channel_mcal.h"

static bool DmaChannelHalfIsrLL(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->half = true;
        Node->half_cnt++;
        Node->busy = true;
        Node->processed = false;
        res = true;
        if(Node->CallBackHalf) {
            res = Node->CallBackHalf();
        }
    }
    return res;
}

static bool DmaChannelDoneIsrLL(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->done = true;
        Node->done_cnt++;
        Node->busy = false;
        Node->processed = false;
        res = true;
        if(Node->CallBackDone) {
            res = Node->CallBackDone();
        }
    }
    return res;
}

static bool DmaChannelErrorIsrLL(DmaChannelHandle_t* const Node) {
    bool res = false;
    if(Node) {
        Node->error_done = true;
        Node->error_cnt++;
        Node->busy = false;
        Node->processed = false;
        res = true;
        // if(Node->CallBackError) {
        //     res = Node->CallBackError();
        // }
    }
    return res;
}

bool DmaChannelErrorIsr(Dma_t dma_num, DmaChannel_t channel) {
    bool res = false;
    DmaInfoChannel_t DmaPad = {
        .dma_num = dma_num,
        .stream = channel,
    };
    const DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        res = DmaChannelErrorIsrLL(Node);
    }
    return res;
}

bool DmaChannelHalfIsr(Dma_t dma_num, DmaChannel_t channel) {
    bool res = false;
    DmaInfoChannel_t DmaPad = {
        .dma_num = dma_num,
        .stream = channel,
    };
    const DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        res = DmaChannelHalfIsrLL(Node);
    }
    return res;
}

bool DmaChannelDoneIsr(Dma_t dma_num, DmaChannel_t channel) {
    bool res = false;
    DmaInfoChannel_t DmaPad = {
        .dma_num = dma_num,
        .stream = channel,
    };
    const DmaChannelHandle_t* Node = DmaChannelToNode(DmaPad);
    if(Node) {
        res = DmaChannelDoneIsrLL(Node);
    }
    return res;
}
