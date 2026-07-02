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
#include "stm32fx_hal.h"

/*
  Table 42. DMA1 request mapping
  Table 43. DMA2 request mapping
 */
const DmaInfoChannel_t DmaBannedChannels[]={
        {.dma_num=1, .stream=1, .channel=0,},
        {.dma_num=1, .stream=6, .channel=0,},
        {.dma_num=1, .stream=1, .channel=1,},
        {.dma_num=1, .stream=3, .channel=1,},
        {.dma_num=1, .stream=1, .channel=2,},
        {.dma_num=1, .stream=5, .channel=6,},
        {.dma_num=1, .stream=7, .channel=6,},
        {.dma_num=1, .stream=0, .channel=7,},
        {.dma_num=2, .stream=7, .channel=0,},
        {.dma_num=2, .stream=0, .channel=1,},
        {.dma_num=2, .stream=2, .channel=2,},
        {.dma_num=2, .stream=1, .channel=3,},
        {.dma_num=2, .stream=4, .channel=3,},
        {.dma_num=2, .stream=6, .channel=3,},
        {.dma_num=2, .stream=7, .channel=3,},
        {.dma_num=2, .stream=4, .channel=4,},
        {.dma_num=2, .stream=0, .channel=5,},
        {.dma_num=2, .stream=5, .channel=5,},
        {.dma_num=2, .stream=7, .channel=6,},
        {.dma_num=2, .stream=0, .channel=7,},
};

const DmaInfoChannel_t DmaSpareChannels[]={
        {.dma_num=2, .stream=1, .channel=0,},
        {.dma_num=2, .stream=3, .channel=0,},
        {.dma_num=2, .stream=5, .channel=0,},
        {.dma_num=2, .stream=1, .channel=1,},
#if 0
        {.dma_num=2, .stream=4, .channel=1,},

        {.dma_num=2, .stream=7, .channel=1,},
        {.dma_num=2, .stream=5, .channel=2,},
        {.dma_num=2, .stream=6, .channel=2,},
        {.dma_num=2, .stream=7, .channel=2,},
#endif
};

uint32_t dma_channel_spare_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(DmaSpareChannels);
    return cnt;
}

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

static const DmaChannelInfo_t DmaChannelInfo[] = { DMA_CHANNEL_INFO };

const DmaChannelInfo_t* DmaChannelGetInfo(uint8_t num, DmaChannel_t stream) {
    uint32_t cnt = ARRAY_SIZE(DmaChannelInfo);
    uint32_t i = 0;
    DmaChannelInfo_t *Node = NULL;
    for (i = 0; i < cnt; i++) {
        if(DmaChannelInfo[i].valid) {
            if(num == DmaChannelInfo[i].dma_num) {
                if(stream == DmaChannelInfo[i].channel) {
                    Node = &DmaChannelInfo[i];
                }
            }
        }
    }
    return Node;
}

DMA_Stream_TypeDef* DmaChannelToDMAx(uint8_t dma_num, DmaChannel_t channel) {
    DMA_Stream_TypeDef *DMA_STREAMx = NULL;
    const DmaChannelInfo_t *ChannelInfo = DmaChannelGetInfo(dma_num, channel);
    if(ChannelInfo) {
        DMA_STREAMx = ChannelInfo->DMA_STREAMx;
    }
    return DMA_STREAMx;
}

/*TODO make LUT*/
static uint32_t DmaGetChannel(uint8_t channel) {
    uint32_t code = 0xFFFFFFFF;
    switch (channel) {
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
    default:
        break;
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

DmaStreamIntStatusReg_t DmaGetStream(uint8_t dma_num, uint8_t stream_num) {
    DmaStreamIntStatusReg_t DmaStreamIntStatusReg;
    memset(&DmaStreamIntStatusReg, 0, sizeof(DmaStreamIntStatusReg_t));
    DMA_TypeDef *DMAx = DmaNum2DMAx(dma_num);
    if(DMAx) {
        if(stream_num <= 3) {
            DmaLowIntStatusReg_t Reg;
            Reg.reg_val = DMAx->LISR;
            switch (stream_num) {
            case 0: {
                COPY_DMA_STREAM_BITS(0)
            }
                break;
            case 1: {
                COPY_DMA_STREAM_BITS(1)
            }
                break;
            case 2: {
                COPY_DMA_STREAM_BITS(2)
            }
                break;
            case 3: {
                COPY_DMA_STREAM_BITS(3)
            }
                break;
            default:
                break;
            }
        }
        if((4 <= stream_num) && (stream_num <= 7)) {
            DmaHighIntStatusReg_t Reg;
            Reg.reg_val = DMAx->HISR;
            switch (stream_num) {
            case 4: {
                COPY_DMA_STREAM_BITS(4)
            }
                break;
            case 5: {
                COPY_DMA_STREAM_BITS(5)
            }
                break;
            case 6: {
                COPY_DMA_STREAM_BITS(6)
            }
                break;
            case 7: {
                COPY_DMA_STREAM_BITS(7)
            }
                break;
            default:
                break;
            }
        }
    }
    return DmaStreamIntStatusReg;
}

bool dma_channel_mux_get(DmaInfoChannel_t DmaPad, uint8_t* const mux) {
    * mux = 0xFF;
    return true;
}


bool dma_channel_priority_get(DmaInfoChannel_t DmaPad, uint8_t* priority) {
    bool res = false;
    return res;
}

bool dma_channel_init_stm_init(const DmaChannelConfig_t* const ChannelConfig, DMA_InitTypeDef* const pInit) {
    bool res = false;
    if(pInit) {
        pInit->FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
        pInit->FIFOMode = DmaGetFiFoNode(ChannelConfig->fifo);
        pInit->Channel = DmaGetChannel(ChannelConfig->DmaChPad.channel);
        pInit->Direction = DmaDirToStm32DmaDir(ChannelConfig->dir);
        pInit->PeriphInc = DmaGetPeriphInc(ChannelConfig->per_inc);
        pInit->MemInc = DmaGetMemInc(ChannelConfig->mem_inc);
        pInit->PeriphDataAlignment = DmaGetPeriphDataAlignment(ChannelConfig->aligment_per);
        pInit->MemDataAlignment = DmaGetMemDataAlignment(ChannelConfig->aligment_mem);
        pInit->Mode = DmaGetMode(ChannelConfig->mode);
        pInit->Priority = DmaGetPriority(ChannelConfig->priority);
        pInit->MemBurst = MemoryBurst2StmMemoryBurst(ChannelConfig->memory_burst);
        pInit->PeriphBurst = PeriphBurst2StmPeriphBurst(ChannelConfig->periph_burst);
        res = true;
    }
    return res;
}

bool dma_channel_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DMA_CHANNEL, "DMA_CHANNEL_%u=%s", num, DmaChannnelNumToStr(num));
    const DmaChannelConfig_t *ChannelConfig = DmaChannelGetConfig(num);
    if(ChannelConfig) {
        DmaChannelHandle_t *DmaChNode = DmaChannelGetNode(num);
        if(DmaChNode) {
            res = dma_channel_init_common(ChannelConfig, DmaChNode);
        }

        uint8_t dma_num = ChannelConfig->DmaChPad.dma_num;
        uint8_t stream_num = ChannelConfig->DmaChPad.stream;
        LOG_WARNING(LG_DMA, "%u,DMA%u,Channel%u,Init", num, dma_num, stream_num);
        DMA_Stream_TypeDef *DMAx = NULL;
        DMAx = DmaChannelToDMAx(dma_num, stream_num);
        if(DMAx) {
            const DmaInfo_t *Info = DmaGetInfo(dma_num);
            if(Info) {
                DmaHandle_t *Node = DmaGetNode(dma_num);
                if(Node) {
                    Node->DMAx = Info->DMAx;
                    const DmaChannelInfo_t *ChannelInfo = DmaChannelGetInfo(dma_num, (DmaChannel_t) stream_num);
                    if(ChannelInfo) {
                        HAL_NVIC_SetPriority(ChannelInfo->irq_n, DMA_INT_PRIORITY, DMA_INT_PRIORITY);
                        HAL_NVIC_EnableIRQ(ChannelInfo->irq_n);
                        DmaChNode->dma_h.Instance = ChannelInfo->DMA_STREAMx; // DMA_Stream_TypeDef
                        res = dma_channel_init_stm_init(ChannelConfig, &DmaChNode->dma_h.Init);
                        // Node->dma_h.XferAbortCallback=;
                        HAL_StatusTypeDef ret = HAL_DMA_Init(&DmaChNode->dma_h);
                        if(HAL_OK == ret) {
                            LOG_INFO(LG_DMA, "Init Id:%u Dma:%u Stream:%u " LOG_OK, num, dma_num, stream_num);
                            res = true;
#ifdef HAS_ADC
                            //AdcHandle_t* Adc = AdcGetNode(1);
                            //if(Adc) {
                            //    Adc->adc_h.DMA_Handle = &(Node->dma_h);
                            //    Node->dma_h.Parent = &(Adc->adc_h);
                            //}
#endif
                            // res = dma_start(dma_num, ChannelConfig->base_addr_source, ChannelConfig->base_addr_destination, ChannelConfig->move_size);
                        } else {
                            LOG_ERROR(LG_DMA, "%u Stream %u InitErr %s", dma_num, stream_num, HalStatusToStr(ret));
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

bool dma_channel_priority_set(DmaInfoChannel_t DmaPad, uint8_t priority) {
    bool res = false;
    return res;
}


bool dma_memcpy(void* const destination, const void* const source, uint32_t size) {
    bool res = false;
    if(destination && source && size) {
        __HAL_RCC_DMA2_CLK_ENABLE();
        static DMA_HandleTypeDef DmaHandleMemCpy;

        DmaHandleMemCpy.Instance = DMA2_Stream0;
        DmaHandleMemCpy.Init.Channel = DMA_CHANNEL_0;
        DmaHandleMemCpy.Init.Direction = DMA_MEMORY_TO_MEMORY;
        DmaHandleMemCpy.Init.PeriphInc = DMA_PINC_ENABLE;
        DmaHandleMemCpy.Init.MemInc = DMA_MINC_ENABLE;
        DmaHandleMemCpy.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
        DmaHandleMemCpy.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
        DmaHandleMemCpy.Init.Mode = DMA_NORMAL;
        DmaHandleMemCpy.Init.Priority = DMA_PRIORITY_HIGH;

        HAL_StatusTypeDef ret = HAL_DMA_Init(&DmaHandleMemCpy);
        if(HAL_OK == ret) {
            if(HAL_DMA_Start(&DmaHandleMemCpy, (uint32_t) source, (uint32_t) destination, size) == HAL_OK) {
                uint32_t timeout = 1000;
                uint32_t tickstart = HAL_GetTick();

                while((HAL_DMA_PollForTransfer(&DmaHandleMemCpy, HAL_DMA_FULL_TRANSFER, timeout)) != HAL_OK) {
                    if((HAL_GetTick() - tickstart) > timeout) {
                        // Таймаут - останавливаем DMA
                        HAL_DMA_Abort(&DmaHandleMemCpy);
                        break;
                    }
                }

                if(HAL_DMA_GetState(&DmaHandleMemCpy) == HAL_DMA_STATE_READY) {
                    res = true;
                }
            }
        }

        //HAL_DMA_DeInit(&DmaHandleMemCpy);

        //__HAL_RCC_DMA2_CLK_DISABLE();
    }

    return res;
}

bool dma_memcpy_custom_ll(void* const destination,
                          const void* const source,
                          uint32_t size,
                          uint8_t dma_num,
                          uint8_t stream,
                          uint8_t channel) {
    bool res = false;
    if(destination && source && size) {
        dma_init_clock(dma_num);
        static DMA_HandleTypeDef hdma_memcpy = {0};
        const DmaChannelInfo_t *Info = DmaChannelGetInfo(dma_num, stream);
        if(Info) {
            hdma_memcpy.Instance = Info->DMA_STREAMx;
            hdma_memcpy.Init.Channel = DmaGetChannel(channel);
            hdma_memcpy.Init.Direction = DMA_MEMORY_TO_MEMORY;
            hdma_memcpy.Init.PeriphInc = DMA_PINC_ENABLE;
            hdma_memcpy.Init.MemInc = DMA_MINC_ENABLE;
            hdma_memcpy.Init.PeriphDataAlignment = DMA_PDATAALIGN_BYTE;
            hdma_memcpy.Init.MemDataAlignment = DMA_MDATAALIGN_BYTE;
            hdma_memcpy.Init.Mode = DMA_NORMAL;
            hdma_memcpy.Init.Priority = DMA_PRIORITY_HIGH;
            hdma_memcpy.Init.PeriphBurst = DMA_PBURST_SINGLE ;
            hdma_memcpy.Init.MemBurst =  DMA_MBURST_SINGLE;
            hdma_memcpy.Init.FIFOMode =  DMA_FIFOMODE_DISABLE;
            hdma_memcpy.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_HALFFULL ;

            HAL_StatusTypeDef ret = HAL_DMA_Init(&hdma_memcpy);
            if(HAL_OK == ret) {
                ret = HAL_DMA_Start(&hdma_memcpy, (uint32_t) source,
                                               (uint32_t) destination,
                                               size) ;
                if( HAL_OK == ret ) {
                    uint32_t timeout = 1000;
                    uint32_t tickstart = HAL_GetTick();

                    while((HAL_DMA_PollForTransfer(&hdma_memcpy, HAL_DMA_FULL_TRANSFER, timeout)) != HAL_OK) {
                        if((HAL_GetTick() - tickstart) > timeout) {
                            HAL_DMA_Abort(&hdma_memcpy);
                            res = false;
                            break;
                        }
                    }

                    if(HAL_DMA_GetState(&hdma_memcpy) == HAL_DMA_STATE_READY) {
                        res = true;
                    }
                }
            }
        }
    }

    return res;
}

DMA_Stream_TypeDef* dma_stream_num_2_prt(const uint8_t dma_num,
                                         const uint8_t stream) {
    DMA_Stream_TypeDef* DMA_STREAMx = NULL;
    const DmaChannelInfo_t* Info = DmaChannelGetInfo(dma_num, stream) ;
    if (Info) {
        DMA_STREAMx = Info->DMA_STREAMx;
    }
    return DMA_STREAMx;
}


