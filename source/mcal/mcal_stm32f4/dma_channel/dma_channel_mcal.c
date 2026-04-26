#include "dma_channel_mcal.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "array.h"
#include "mcal_common.h"
#include "dma_channel_types.h"
#include "dma_custom_bindings.h"
#include "dma_custom_types.h"
#include "dma_custom_misc.h"
#include "hal_diag.h"
#include "log.h"
#include "stm32f4xx_hal.h"

#define DMA_INT_PRIORITY 0

#define DMA1_CHANNEL_INFO                                                                                              \
    {                                                                                                                  \
        .dma_num = 1,                                                                                                  \
        .channel = 0,                                                                                                  \
        .DMA_STREAMx = DMA1_Stream0,                                                                                   \
        .irq_n = DMA1_Stream0_IRQn,                                                                                    \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 1,                                                                                              \
            .DMA_STREAMx = DMA1_Stream1,                                                                               \
            .irq_n = DMA1_Stream1_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 2,                                                                                              \
            .DMA_STREAMx = DMA1_Stream2,                                                                               \
            .irq_n = DMA1_Stream2_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 3,                                                                                              \
            .DMA_STREAMx = DMA1_Stream3,                                                                               \
            .irq_n = DMA1_Stream3_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 4,                                                                                              \
            .DMA_STREAMx = DMA1_Stream4,                                                                               \
            .irq_n = DMA1_Stream4_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 5,                                                                                              \
            .DMA_STREAMx = DMA1_Stream5,                                                                               \
            .irq_n = DMA1_Stream5_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 6,                                                                                              \
            .DMA_STREAMx = DMA1_Stream6,                                                                               \
            .irq_n = DMA1_Stream6_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 1,                                                                                              \
            .channel = 7,                                                                                              \
            .DMA_STREAMx = DMA1_Stream7,                                                                               \
            .irq_n = DMA1_Stream7_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },

#define DMA2_CHANNEL_INFO                                                                                              \
    {                                                                                                                  \
        .dma_num = 2,                                                                                                  \
        .channel = 0,                                                                                                  \
        .DMA_STREAMx = DMA2_Stream0,                                                                                   \
        .irq_n = DMA2_Stream0_IRQn,                                                                                    \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 1,                                                                                              \
            .DMA_STREAMx = DMA2_Stream1,                                                                               \
            .irq_n = DMA2_Stream1_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 2,                                                                                              \
            .DMA_STREAMx = DMA2_Stream2,                                                                               \
            .irq_n = DMA2_Stream2_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 3,                                                                                              \
            .DMA_STREAMx = DMA2_Stream3,                                                                               \
            .irq_n = DMA2_Stream3_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 4,                                                                                              \
            .DMA_STREAMx = DMA2_Stream4,                                                                               \
            .irq_n = DMA2_Stream4_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 5,                                                                                              \
            .DMA_STREAMx = DMA2_Stream5,                                                                               \
            .irq_n = DMA2_Stream5_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 6,                                                                                              \
            .DMA_STREAMx = DMA2_Stream6,                                                                               \
            .irq_n = DMA2_Stream6_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .dma_num = 2,                                                                                              \
            .channel = 7,                                                                                              \
            .DMA_STREAMx = DMA2_Stream7,                                                                               \
            .irq_n = DMA2_Stream7_IRQn,                                                                                \
            .valid = true,                                                                                             \
        },

#define DMA_CHANNEL_INFO                                                                                               \
    DMA1_CHANNEL_INFO                                                                                                  \
    DMA2_CHANNEL_INFO

static const DmaChannelInfo_t DmaChannelInfo[] = {DMA_CHANNEL_INFO};

const DmaChannelInfo_t* DmaChannelGetInfo(uint8_t num, DmaChannel_t channel) {
    uint32_t cnt = ARRAY_SIZE(DmaChannelInfo);
    uint32_t i = 0;
    DmaChannelInfo_t* Node = NULL;
    for(i = 0; i < cnt; i++) {
        if(DmaChannelInfo[i].valid) {
            if(num == DmaChannelInfo[i].dma_num) {
                if(channel == DmaChannelInfo[i].channel) {
                    Node = &DmaChannelInfo[i];
                }
            }
        }
    }
    return Node;
}

DMA_Stream_TypeDef* DmaChannelToDMAx(uint8_t dma_num, DmaChannel_t channel) {
    DMA_Stream_TypeDef* DMA_STREAMx = NULL;
    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        DMA_STREAMx = ChannelInfo->DMA_STREAMx;
    }
    return DMA_STREAMx;
}

static uint32_t DmaGetChannel(uint8_t channel) {
    uint32_t code = 0xFFFFFFFF;
    switch(channel) {
#ifdef DMA_CHANNEL_0
    case DMA_CHAN_0:
        code = DMA_CHANNEL_0;
        break;
#endif

#ifdef DMA_CHANNEL_1
    case DMA_CHAN_1:
        code = DMA_CHANNEL_1;
        break;
#endif

#ifdef DMA_CHANNEL_2
    case DMA_CHAN_2:
        code = DMA_CHANNEL_2;
        break;
#endif

#ifdef DMA_CHANNEL_3
    case DMA_CHAN_3:
        code = DMA_CHANNEL_3;
        break;
#endif

#ifdef DMA_CHANNEL_4
    case DMA_CHAN_4:
        code = DMA_CHANNEL_4;
        break;
#endif

#ifdef DMA_CHANNEL_5
    case DMA_CHAN_5:
        code = DMA_CHANNEL_5;
        break;
#endif

#ifdef DMA_CHANNEL_6
    case DMA_CHAN_6:
        code = DMA_CHANNEL_6;
        break;
#endif

#ifdef DMA_CHANNEL_7
    case DMA_CHAN_7:
        code = DMA_CHANNEL_7;
        break;
#endif

#ifdef DMA_CHANNEL_8
    case DMA_CHAN_8:
        code = DMA_CHANNEL_8;
        break;
#endif

#ifdef DMA_CHANNEL_9
    case DMA_CHAN_9:
        code = DMA_CHANNEL_9;
        break;
#endif

#ifdef DMA_CHANNEL_10
    case DMA_CHAN_10:
        code = DMA_CHANNEL_10;
        break;
#endif

#ifdef DMA_CHANNEL_11
    case DMA_CHAN_11:
        code = DMA_CHANNEL_11;
        break;
#endif

#ifdef DMA_CHANNEL_12
    case DMA_CHAN_12:
        code = DMA_CHANNEL_12;
        break;
#endif

#ifdef DMA_CHANNEL_13
    case DMA_CHAN_13:
        code = DMA_CHANNEL_13;
        break;
#endif

#ifdef DMA_CHANNEL_14
    case DMA_CHAN_14:
        code = DMA_CHANNEL_14;
        break;
#endif

#ifdef DMA_CHANNEL_15
    case DMA_CHAN_15:
        code = DMA_CHANNEL_15;
        break;
#endif
    default: break;
    }
    return code;
}

#define COPY_DMA_STREAM_BITS(BIT)                                                                                      \
    do {                                                                                                               \
        DmaStreamIntStatusReg.teif = Reg.tcif##BIT;                                                                    \
        DmaStreamIntStatusReg.tcif = Reg.tcif##BIT;                                                                    \
        DmaStreamIntStatusReg.feif = Reg.feif##BIT;                                                                    \
        DmaStreamIntStatusReg.dmeif = Reg.dmeif##BIT;                                                                  \
        DmaStreamIntStatusReg.htif = Reg.htif##BIT;                                                                    \
    } while(0);

DmaStreamIntStatusReg_t DmaGetStream(uint8_t dma_num, uint8_t channel_num) {
    DmaStreamIntStatusReg_t DmaStreamIntStatusReg;
    memset(&DmaStreamIntStatusReg, 0, sizeof(DmaStreamIntStatusReg_t));
    DMA_TypeDef* DMAx = DmaNum2DMAx(dma_num);
    if(DMAx) {
        if(channel_num <= 3) {
            DmaLowIntStatusReg_t Reg;
            Reg.reg_val = DMAx->LISR;
            switch(channel_num) {
            case 0: {
                COPY_DMA_STREAM_BITS(0)
            } break;
            case 1: {
                COPY_DMA_STREAM_BITS(1)
            } break;
            case 2: {
                COPY_DMA_STREAM_BITS(2)
            } break;
            case 3: {
                COPY_DMA_STREAM_BITS(3)
            } break;
            default: break;
            }
        }
        if((4 <= channel_num) && (channel_num <= 7)) {
            DmaHighIntStatusReg_t Reg;
            Reg.reg_val = DMAx->HISR;
            switch(channel_num) {
            case 4: {
                COPY_DMA_STREAM_BITS(4)
            } break;
            case 5: {
                COPY_DMA_STREAM_BITS(5)
            } break;
            case 6: {
                COPY_DMA_STREAM_BITS(6)
            } break;
            case 7: {
                COPY_DMA_STREAM_BITS(7)
            } break;
            default: break;
            }
        }
    }
    return DmaStreamIntStatusReg;
}

bool dma_channel_priority_get(DmaChannelPad_t DmaPad, uint8_t* priority){
    bool res = false;
    return res;
}

bool dma_channel_init_stm_init(const DmaChannelConfig_t* const ChannelConfig,
                               DMA_InitTypeDef* const pInit) {
    bool res = false;
    if (pInit) {
        pInit->Channel = DmaGetChannel(ChannelConfig->DmaPad.channel);
        pInit->Direction = DmaDirToStm32DmaDir(ChannelConfig->dir);
        pInit->PeriphInc = DmaGetPeriphInc(ChannelConfig->per_inc);
        pInit->MemInc = DmaGetMemInc(ChannelConfig->mem_inc);
        pInit->PeriphDataAlignment = DmaGetPeriphDataAlignment(ChannelConfig->aligment_per);
        pInit->MemDataAlignment = DmaGetMemDataAlignment(ChannelConfig->aligment_mem);
        pInit->Mode = DmaGetMode(ChannelConfig->mode);
        pInit->Priority = DmaGetPriority(ChannelConfig->priority);
        pInit->FIFOMode = DmaGetFiFoNode(ChannelConfig->fifo);
        pInit->FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
        pInit->MemBurst = MemoryBurst2StmMemoryBurst(ChannelConfig->memory_burst);
        pInit->PeriphBurst = PeriphBurst2StmPeriphBurst(ChannelConfig->periph_burst);
        res = true;
    }
    return res;
}

bool dma_channel_init_one(uint8_t num) {
    bool res = false;
    const DmaChannelConfig_t* ChannelConfig = DmaChannelGetConfig(num);
    if(ChannelConfig) {
        DmaChannelHandle_t* DmaChNode = DmaChannelGetNode(num);
        if(DmaChNode){
            res = dma_channel_init_common(ChannelConfig, DmaChNode);
        }

        uint8_t dma_num = ChannelConfig->DmaPad.dma_num;
        uint8_t channel_num = ChannelConfig->DmaPad.channel;
        LOG_WARNING(LG_DMA, "%u,DMA%u,Channel%u,Init", num, dma_num, channel_num);
        DMA_Stream_TypeDef* DMAx = NULL;
        DMAx = DmaChannelToDMAx(dma_num, channel_num);
        if(DMAx) {
            const DmaInfo_t* Info = DmaGetInfo(dma_num);
            if(Info) {
                DmaHandle_t* Node = DmaGetNode(dma_num);
                if(Node) {
                    Node->DMAx = Info->DMAx;
                    const DmaChannelInfo_t* ChannelInfo = DmaChannelGetInfo(dma_num, (DmaChannel_t)channel_num);
                    if(ChannelInfo) {
                        HAL_NVIC_SetPriority(ChannelInfo->irq_n, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
                        HAL_NVIC_EnableIRQ(ChannelInfo->irq_n);
                        Node->dma_h.Instance = ChannelInfo->DMA_STREAMx; // DMA_Stream_TypeDef
                        res= dma_channel_init_stm_init(ChannelConfig, &Node->dma_h.Init);
                        // Node->dma_h.XferAbortCallback=;
                        HAL_StatusTypeDef ret = HAL_DMA_Init(&Node->dma_h);
                        if(HAL_OK == ret) {
                            LOG_INFO(LG_DMA, "Init Id:%u Dma:%u Stream:%u " LOG_OK, num, dma_num, channel_num);
                            res = true;
                            AdcHandle_t* Adc = AdcGetNode(1);
                            if(Adc) {
                                Adc->adc_h.DMA_Handle = &(Node->dma_h);
                                Node->dma_h.Parent = &(Adc->adc_h);
                            }
                            // res = dma_start(dma_num, ChannelConfig->base_addr_source, ChannelConfig->base_addr_destination, ChannelConfig->move_size);
                        } else {
                            LOG_ERROR(LG_DMA, "%u Stream %u InitErr %s", dma_num, channel_num, HalStatusToStr(ret));
                            res = false;
                        }
                    }
                }
            }

        } else {
            LOG_ERROR(LG_DMA, "InstErr");
        }
    } else {
        LOG_ERROR(LG_DMA, "ConfigErr");
    }
    return res;
}

bool dma_channel_init_interrupts(void) {
#if 0
    LOG_WARNING(LG_DMA, "DMA1 ISR init");
    HAL_NVIC_SetPriority(DMA1_Stream0_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream0_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream1_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream1_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream2_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream2_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream3_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream3_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream4_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream4_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream5_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream5_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream6_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream6_IRQn);

    HAL_NVIC_SetPriority(DMA1_Stream7_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA1_Stream7_IRQn);
#endif /*HAS_DMA1*/

#if 0
    LOG_WARNING(LG_DMA, "DMA2 ISR init");
    HAL_NVIC_SetPriority(DMA2_Stream0_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream0_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream1_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream1_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream2_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream2_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream3_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream3_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream4_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream4_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream5_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream5_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream6_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream6_IRQn);

    HAL_NVIC_SetPriority(DMA2_Stream7_IRQn, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
    HAL_NVIC_EnableIRQ(DMA2_Stream7_IRQn);
#endif /*HAS_DMA2*/
    return true;
}

bool dma_channel_priority_set(DmaChannelPad_t DmaPad, uint8_t priority){
    bool res = false;
    return res;
}
