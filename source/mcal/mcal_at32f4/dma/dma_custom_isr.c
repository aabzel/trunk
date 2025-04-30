#include "dma_custom_isr.h"

#include "dma_mcal.h"
#include "microcontroller_const.h"

bool DMAxChannelyIRQHandler(uint8_t dma_num, DmaChannel_t channel) {
    bool res = false;
    // __disable_irq();
    DmaChannelHandle_t* Node = DmaChannelGetNodeItem(dma_num, channel);
    if(Node) {
        Node->it_cnt++;
        Node->it_done = true;
        const DmaChannelInfo_t* Info = DmaChannelGetInfo(dma_num, channel);
        if(Info) {
            res = true;
            flag_status ret = RESET;

            ret = dma_interrupt_flag_get(Info->Flag.half);
            if(SET == ret) {
                dma_flag_clear(Info->Flag.half);
                res = DmaChannelHalfIsrLL(Node);
            }

            ret = dma_interrupt_flag_get(Info->Flag.done);
            if(SET == ret) {
                dma_flag_clear(Info->Flag.done);
                res = DmaChannelDoneIsrLL(Node);
                // dma_channel_enable(Info->dmax_channely, FALSE);
            }

            ret = dma_interrupt_flag_get(Info->Flag.error);
            if(SET == ret) {
                dma_flag_clear(Info->Flag.error);
                res = DmaChannelErrorIsr_ll(Node);
            }

            ret = dma_interrupt_flag_get(Info->Flag.global);
            if(SET == ret) {
                dma_flag_clear(Info->Flag.global);
                Node->global_done = true;
                Node->global_cnt++;
                res = true;
            }
        }
    }
    // __enable_irq();
    return res;
}
