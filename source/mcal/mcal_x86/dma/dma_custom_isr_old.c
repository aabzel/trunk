#include "dma_custom_isr.h"

#include "dma_mcal.h"
#include "sys_config.h"

bool DMAxChannelyIRQHandler(uint8_t dma_num, DmaChannel_t channel) {
    bool res = false;
    DmaChannelHandle_t* Node = DmaChannelGetNodeItem(dma_num, channel);
    if(Node) {
        const DmaChannelInfo_t* Info = DmaChannelGetInfo(dma_num, channel);
        if(Info) {
            res = true;
            flag_status ret = RESET;
            ret = dma_interrupt_flag_get(Info->Flag.tx_done);
            if(SET == ret) {
                Node->tx_done = true;
                Node->tx_done_cnt++;
                Node->busy = false;
                res = true;
                dma_flag_clear(Info->Flag.tx_done);
                dma_channel_enable(Info->dmax_channely, FALSE);
            }

            ret = dma_interrupt_flag_get(Info->Flag.half_tx_done);
            if(SET == ret) {
                Node->half_tx_done = true;
                Node->half_tx_done_cnt++;
                Node->busy = true;
                res = true;
                dma_flag_clear(Info->Flag.half_tx_done);
            }

            ret = dma_interrupt_flag_get(Info->Flag.error);
            if(SET == ret) {
                Node->error_cnt++;
                res = true;
                dma_flag_clear(Info->Flag.error);
            }

            ret = dma_interrupt_flag_get(Info->Flag.global);
            if(SET == ret) {
                Node->global_done = true;
                Node->global_cnt++;
                res = true;
                dma_flag_clear(Info->Flag.global);
            }
        }
    }
    return res;
}
