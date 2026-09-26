#include "dma_custom_isr.h"

#include "dma_mcal.h"
#include "microcontroller_const.h"

bool DMAxChannelyIRQHandler(uint8_t dma_num, DmaChannel_t channel) {
    bool res = false;
    DmaChannelHandle_t* Node = DmaChannelGetNodeItem(dma_num, channel);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        const DmaChannelInfo_t* Info = DmaChannelGetInfo(dma_num, channel);
        if(Info) {
        }
    }
    return res;
}
