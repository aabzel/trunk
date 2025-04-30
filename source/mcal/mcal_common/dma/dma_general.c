#include "dma_mcal.h"

#include "code_generator.h"
#include "dma_config.h"
#include "log.h"
#include "std_includes.h"
#include "sys_config.h"
#include "time_mcal.h"

COMPONENT_GET_CONFIG(Dma, dma)
COMPONENT_GET_NODE(Dma, dma)

COMPONENT_GET_CONFIG(DmaChannel, dma_channel)
COMPONENT_GET_NODE(DmaChannel, dma_channel)

bool dma_channel_init_common_one(DmaChannelConfig_t* Config, DmaChannelHandle_t* Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->CallBackDone = Config->CallBackDone;
            Node->CallBackHalf = Config->CallBackHalf;
            Node->aligment_mem = Config->aligment_mem;
            Node->aligment_per = Config->aligment_per;
            Node->buffer_size = Config->buffer_size;
            Node->channel = Config->channel;
            Node->dir = Config->dir;
            Node->dma_num = Config->dma_num;
            Node->dma_num = Config->dma_num;
            Node->fifo = Config->fifo;
            Node->mem_inc = Config->mem_inc;
            Node->memory_base_addr = Config->memory_base_addr;
            Node->memory_burst = Config->memory_burst;
            Node->mode = Config->mode;
            Node->mux = Config->mux;
            Node->num = Config->num;
            Node->per_inc = Config->per_inc;
            Node->periph_burst = Config->periph_burst;
            Node->peripheral_base_addr = Config->peripheral_base_addr;
            Node->priority = Config->priority;

            Node->busy = false;
            // Node->error_cnt = 0;
            // Node->global_cnt = 0;
            Node->global_done = false;
            Node->half = false;
            // Node->half_cnt = 0;
            Node->done = false;
            // Node->done_cnt = 0;
            Node->valid = true;

            res = true;
        }
    }
    return res;
}

DmaChannelHandle_t* DmaChannelGetNodeItem(uint8_t dma_num, DmaChannel_t channel) {
    DmaChannelHandle_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = dma_channel_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(DmaChannelInstance[i].valid) {
            if(dma_num == DmaChannelInstance[i].dma_num) {
                if(channel == DmaChannelInstance[i].channel) {
                    Node = &DmaChannelInstance[i];
                    break;
                }
            }
        }
    }

    return Node;
}

DmaChannelHandle_t* DmaPadGetNodeItem(DmaPad_t DmaPad) {
    DmaChannelHandle_t* Node = NULL;
    Node = DmaChannelGetNodeItem(DmaPad.dma_num, (DmaChannel_t)DmaPad.channel);
    return Node;
}

bool dma_wait_done(uint8_t num, DmaChannel_t channel) {
    bool res = false;

    DmaChannelHandle_t* Node = DmaChannelGetNodeItem(num, channel);
    if(Node) {
        bool loop = true;
#ifdef HAS_DMA_TIME_OUT
        uint32_t cur_ms = 0;
        uint32_t diff_ms = 0;
        uint32_t start_ms = time_get_ms32();
#endif
        while(loop) {
            if(Node->done) {
                res = true;
                loop = false;
            }
#ifdef HAS_DMA_TIME_OUT
            cur_ms = time_get_ms32();
            diff_ms = cur_ms - start_ms;
            if(DMA_TRANSFER_TIMEOUT_MS < diff_ms) {
                loop = false;
                res = false;
                LOG_ERROR(DMA, "DmaTxTimeOut");
            }
            wait_us(100);
#endif
        }
    }
    return res;
}

__attribute__((weak)) bool dma_mux_get(uint8_t dma_num, DmaChannel_t channel, uint8_t* const dmamux) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

__attribute__((weak)) bool dma_channel_init_custom(void) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

__attribute__((weak)) bool dma_channel_init_one(uint8_t num) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

__attribute__((weak)) bool dma_init_one(uint8_t num) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

__attribute__((weak)) bool dma_init_custom(void) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

__attribute__((weak)) bool dma_mux_set(uint8_t dma_num, DmaChannel_t channel, uint8_t dmamux) {
    LOG_ERROR(DMA, "%s NotInplemented", __FUNCTION__);
    return false;
}

COMPONENT_INIT_PATTERT_CNT(DMA, DMA, dma_channel, DMA_CHANNEL_COUNT)
COMPONENT_INIT_PATTERT_CNT(DMA, DMA, dma, DMA_COUNT)
