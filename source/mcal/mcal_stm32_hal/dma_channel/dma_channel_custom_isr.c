#include "dma_channel_custom_isr.h"

#include "dma_channel_mcal.h"
#include "dma_channel_custom.h"

void DmaChannelTxDone(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node) {
        DmaChannelDoneIsrLL(Node);
    }
}

void DmaChannelTxHalf(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelHalfIsrLL(Node);
    }
}

void DmaChannelError(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelErrorIsrLL(Node);
    }
}

void DmaChannelAll(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelAllIsrLL(Node);
    }
}

void DmaChannelAbort(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelAbortIsrLL(Node);
    }
}

void DmaChannelM1HalfTx(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelM1HalfTxIsrLL(Node);
    }
}

void DmaChannelM1FullTx(DMA_HandleTypeDef *h_dma) {
    DmaChannelHandle_t* Node = DmaChannelHandleToNode(h_dma);
    if(Node){
        DmaChannelM1FullTxIsrLL(Node);
    }
}


