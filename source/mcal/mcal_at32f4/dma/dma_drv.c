#include "dma_drv.h"

#include <stddef.h>
#include <stdint.h>
#include <string.h>

#include "dma_mcal.h"
#include "dma_config.h"
#include "dma_types.h"
#include "hal_diag.h"
#include "log.h"
#include "at32f435_437.h"

DMA_Stream_TypeDef* gma_stream_num_2_prt(uint8_t dma_num, uint8_t stream_num) {
    DMA_Stream_TypeDef* Instance = NULL;
    if(1 == dma_num) {
        switch((uint8_t)stream_num) {
        case 0:
            Instance = DMA1_Stream0;
            break;
        case 1:
            Instance = DMA1_Stream1;
            break;
        case 2:
            Instance = DMA1_Stream2;
            break;
        case 3:
            Instance = DMA1_Stream3;
            break;
        case 4:
            Instance = DMA1_Stream4;
            break;
        case 5:
            Instance = DMA1_Stream5;
            break;
        case 6:
            Instance = DMA1_Stream6;
            break;
        case 7:
            Instance = DMA1_Stream7;
            break;
        default:
            Instance = NULL;
            break;
        }
    }
    if(2 == dma_num) {
        switch(stream_num) {
        case 0:
            Instance = DMA2_Stream0;
            break;
        case 1:
            Instance = DMA2_Stream1;
            break;
        case 2:
            Instance = DMA2_Stream2;
            break;
        case 3:
            Instance = DMA2_Stream3;
            break;
        case 4:
            Instance = DMA2_Stream4;
            break;
        case 5:
            Instance = DMA2_Stream5;
            break;
        case 6:
            Instance = DMA2_Stream6;
            break;
        case 7:
            Instance = DMA2_Stream7;
            break;
        default:
            Instance = NULL;
            break;
        }
    }
    return Instance;
}

static uint32_t DmaGetChannel(uint8_t channel) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)channel) {
#ifdef DMA_CHANNEL_0
    case DMA_CHAN_0:
        code = DMA_CHANNEL_0;
        break;
#endif /**/

#ifdef DMA_CHANNEL_1
    case DMA_CHAN_1:
        code = DMA_CHANNEL_1;
        break;
#endif /**/

#ifdef DMA_CHANNEL_2
    case DMA_CHAN_2:
        code = DMA_CHANNEL_2;
        break;
#endif /**/

#ifdef DMA_CHANNEL_3
    case DMA_CHAN_3:
        code = DMA_CHANNEL_3;
        break;
#endif /**/

#ifdef DMA_CHANNEL_4
    case DMA_CHAN_4:
        code = DMA_CHANNEL_4;
        break;
#endif /**/

#ifdef DMA_CHANNEL_5
    case DMA_CHAN_5:
        code = DMA_CHANNEL_5;
        break;
#endif /**/

#ifdef DMA_CHANNEL_6
    case DMA_CHAN_6:
        code = DMA_CHANNEL_6;
        break;
#endif /**/

#ifdef DMA_CHANNEL_7
    case DMA_CHAN_7:
        code = DMA_CHANNEL_7;
        break;
#endif /**/
#ifdef DMA_CHANNEL_8
    case DMA_CHAN_8:
        code = DMA_CHANNEL_8;
        break;
#endif /**/

#ifdef DMA_CHANNEL_9
    case DMA_CHAN_9:
        code = DMA_CHANNEL_9;
        break;
#endif /**/

#ifdef DMA_CHANNEL_10
    case DMA_CHAN_10:
        code = DMA_CHANNEL_10;
        break;
#endif /**/

#ifdef DMA_CHANNEL_11
    case DMA_CHAN_11:
        code = DMA_CHANNEL_11;
        break;
#endif /**/

#ifdef DMA_CHANNEL_12
    case DMA_CHAN_12:
        code = DMA_CHANNEL_12;
        break;
#endif /**/

#ifdef DMA_CHANNEL_13
    case DMA_CHAN_13:
        code = DMA_CHANNEL_13;
        break;
#endif /**/

#ifdef DMA_CHANNEL_14
    case DMA_CHAN_14:
        code = DMA_CHANNEL_14;
        break;
#endif /**/

#ifdef DMA_CHANNEL_15
    case DMA_CHAN_15:
        code = DMA_CHANNEL_15;
        break;
#endif /**/
    }
    return code;
}

static uint32_t DmaGetDir(uint8_t dir) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)dir) {
    case DMA_DIR_PERIPH_TO_MEMORY:
        code = DMA_PERIPH_TO_MEMORY;
        break;
    case DMA_DIR_MEMORY_TO_PERIPH:
        code = DMA_MEMORY_TO_PERIPH;
        break;
    case DMA_DIR_MEMORY_TO_MEMORY:
        code = DMA_MEMORY_TO_MEMORY;
        break;
    }
    return code;
}

static uint32_t DmaGetPeriphInc(uint8_t per_inc) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)per_inc) {
    case DMA_INC_OFF:
        code = DMA_PINC_DISABLE;
        break;
    case DMA_INC_ON:
        code = DMA_PINC_ENABLE;
        break;
    }
    return code;
}

static uint32_t DmaGetMemInc(uint8_t mem_inc) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)mem_inc) {
    case DMA_INC_OFF:
        code = DMA_MINC_DISABLE;
        break;
    case DMA_INC_ON:
        code = DMA_MINC_ENABLE;
        break;
    }
    return code;
}

static uint32_t DmaGetPeriphDataAlignment(uint8_t aligment_per) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)aligment_per) {
    case DMA_ALIG_BYTE:
        code = DMA_PDATAALIGN_BYTE;
        break;
    case DMA_ALIG_HALF_WORD:
        code = DMA_PDATAALIGN_HALFWORD;
        break;
    case DMA_ALIG_WORD:
        code = DMA_PDATAALIGN_WORD;
        break;
    }
    return code;
}

static uint32_t MemoryBurst2StmMemoryBurst(uint8_t mem_burst) {
    uint32_t stm32_code = 0xFFFFFFFF;
    switch((uint8_t)mem_burst) {
    case DMA_BURST_SINGLE:
        stm32_code = DMA_MBURST_SINGLE;
        break;
    case DMA_BURST_INC4:
        stm32_code = DMA_MBURST_INC4;
        break;
    case DMA_BURST_INC8:
        stm32_code = DMA_MBURST_INC8;
        break;
    case DMA_BURST_INC16:
        stm32_code = DMA_MBURST_INC16;
        break;
    }
    return stm32_code;
}

static uint32_t PeriphBurst2StmPeriphBurst(DmaBurst_t periph_burst) {
    uint32_t stm32_code = 0xFFFFFFFF;
    switch((uint8_t)periph_burst) {
    case DMA_BURST_SINGLE:
        stm32_code = DMA_PBURST_SINGLE;
        break;
    case DMA_BURST_INC4:
        stm32_code = DMA_PBURST_INC4;
        break;
    case DMA_BURST_INC8:
        stm32_code = DMA_PBURST_INC8;
        break;
    case DMA_BURST_INC16:
        stm32_code = DMA_PBURST_INC16;
        break;
    }
    return stm32_code;
}

static uint32_t DmaGetMemDataAlignment(DmaAligmant_t aligment_mem) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)aligment_mem) {
    case DMA_ALIG_BYTE:
        code = DMA_MDATAALIGN_BYTE;
        break;
    case DMA_ALIG_HALF_WORD:
        code = DMA_MDATAALIGN_HALFWORD;
        break;
    case DMA_ALIG_WORD:
        code = DMA_MDATAALIGN_WORD;
        break;
    }
    return code;
}

static uint32_t DmaGetMode(DmaMode_t mode) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)mode) {
    case DMA_MODE_NORMAL:
        code = DMA_NORMAL;
        break;
    case DMA_MODE_CIRCULAR:
        code = DMA_CIRCULAR;
        break;
    case DMA_MODE_PFCTRL:
        code = DMA_PFCTRL;
        break;
    }
    return code;
}

static uint32_t DmaGetPriority(DmaPriority_t priority) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)priority) {
    case DMA_PRIOR_LOW:
        code = DMA_PRIORITY_LOW;
        break;
    case DMA_PRIOR_MED:
        code = DMA_PRIORITY_MEDIUM;
        break;
    case DMA_PRIOR_HIGH:
        code = DMA_PRIORITY_HIGH;
        break;
    case DMA_PRIOR_VERY_HIGH:
        code = DMA_PRIORITY_VERY_HIGH;
        break;
    }
    return code;
}

static uint32_t DmaGetFiFoNode(DmaFifo_t fifo) {
    uint32_t code = 0xFFFFFFFF;
    switch((uint8_t)fifo) {
    case DMA_FIFO_OFF:
        code = DMA_FIFOMODE_DISABLE;
        break;
    case DMA_FIFO_ON:
        code = DMA_FIFOMODE_ENABLE;
        break;
    }
    return code;
}

DMA_TypeDef* DmaNum2Instance(uint8_t num) {
    DMA_TypeDef* Instance = NULL;
    switch((uint8_t)num) {
    case 1:
        Instance = DMA1;
        break;
    case 2:
        Instance = DMA2;
        break;
    }
    return Instance;
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
    DMA_TypeDef* Instance = DmaNum2Instance(dma_num);
    if(Instance) {
        if(stream_num <= 3) {
            DmaLowIntStatusReg_t Reg;
            Reg.reg_val = Instance->LISR;
            switch(stream_num) {
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
            }
        }
        if((4 <= stream_num) && (stream_num <= 7)) {
            DmaHighIntStatusReg_t Reg;
            Reg.reg_val = Instance->HISR;
            switch(stream_num) {
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
            }
        }
    }
    return DmaStreamIntStatusReg;
}

bool dma_init_ll(uint8_t dma_id) {
    bool res = false;
    LOG_INFO(DMA, "%u Init", dma_id);

    const DmaConfig_t* DmaConfig = NULL;
    DMA_Stream_TypeDef* Instance = NULL;

    DmaConfig = DmaGetCongigNode(dma_id);
    if(DmaConfig) {
        uint8_t dma_num = DmaConfig->dma_num;
        uint8_t stream_num = DmaConfig->stream_num;
        Instance = gma_stream_num_2_prt(dma_num, stream_num);
        if(Instance) {
            DmaHandle_t* DmaNode = DmaGetNode(dma_id);
            if(DmaNode) {
                DmaNode->dma_h.Instance = Instance;
                DmaNode->dma_h.Init.Channel = DmaGetChannel(DmaConfig->channel);
                DmaNode->dma_h.Init.Direction = DmaGetDir(DmaConfig->dir);
                DmaNode->dma_h.Init.PeriphInc = DmaGetPeriphInc(DmaConfig->per_inc);
                DmaNode->dma_h.Init.MemInc = DmaGetMemInc(DmaConfig->mem_inc);
                DmaNode->dma_h.Init.PeriphDataAlignment = DmaGetPeriphDataAlignment(DmaConfig->aligment_per);
                DmaNode->dma_h.Init.MemDataAlignment = DmaGetMemDataAlignment(DmaConfig->aligment_mem);
                DmaNode->dma_h.Init.Mode = DmaGetMode(DmaConfig->mode);
                DmaNode->dma_h.Init.Priority = DmaGetPriority(DmaConfig->priority);
                DmaNode->dma_h.Init.FIFOMode = DmaGetFiFoNode(DmaConfig->fifo);
                DmaNode->dma_h.Init.FIFOThreshold = DMA_FIFO_THRESHOLD_FULL;
                DmaNode->dma_h.Init.MemBurst = MemoryBurst2StmMemoryBurst(DmaConfig->memory_burst);
                DmaNode->dma_h.Init.PeriphBurst = PeriphBurst2StmPeriphBurst(DmaConfig->periph_burst);
                // DmaNode->dma_h.XferAbortCallback=;
                HAL_StatusTypeDef ret = HAL_DMA_Init(&DmaNode->dma_h);
                if(HAL_OK == ret) {
                    LOG_INFO(DMA, "Init Id:%u Dma:%u Stream:%u " LOG_OK, dma_id, dma_num, stream_num);
                    res = true;
                } else {
                    LOG_ERROR(DMA, "%u Stream %u InitErr %s", dma_num, stream_num, HalStatus2Str(ret));
                    res = false;
                }
            } else {
                LOG_ERROR(DMA, "NodeErr");
            }
        } else {
            LOG_ERROR(DMA, "InstErr");
        }
    } else {
        LOG_ERROR(DMA, "ConfigErr");
    }
    return res;
}

static bool dma_check_const(void) {
    _Static_assert(2 == DMA_DIR_MEMORY_TO_MEMORY, "ValErr");
    _Static_assert(1 == DMA_DIR_MEMORY_TO_PERIPH, "ValErr");
    _Static_assert(0 == DMA_DIR_PERIPH_TO_MEMORY, "ValErr");
    return true;
}

#define DMA_INT_PRIORITY 0
static bool dma_init_interrupts(void) {
#ifdef HAS_DMA1
    LOG_WARNING(DMA, "DMA1 ISR init");
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

#ifdef HAS_DMA2
    LOG_WARNING(DMA, "DMA2 ISR init");
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

static bool dma_init_clock(void) {
    bool res = false;
#ifdef HAS_DMA1
    LOG_INFO(DMA, "DMA1InitClk");
    __DMA1_CLK_ENABLE();
    res = true;
#endif /*HAS_DMA1*/

#ifdef HAS_DMA2
    LOG_INFO(DMA, "DMA2InitClk");
    __DMA2_CLK_ENABLE();
    res = true;
#endif /*HAS_DMA2*/

    return res;
}

bool dma_init(void) {
    bool res = true;
    LOG_INFO(DMA, "Init..");
    res = dma_init_clock() && res;

    res = dma_init_interrupts() && res;

    res = dma_check_const() && res;
    uint8_t dma_id = 0;
    uint32_t cnt = dma_get_cnt();
    LOG_INFO(DMA, "Cnt:%u", cnt);
    for(dma_id = 1; dma_id <= cnt; dma_id++) {
        res = dma_init_ll((uint8_t)dma_id) && res;
    }
    LOG_INFO(DMA, "Init done");
    return res;
}

bool dma_stop(uint8_t num) {
    bool res = false;
    DmaHandle_t* DmaNode = DmaGetNode(num);
    if(DmaNode) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_DMA_Abort_IT(&DmaNode->dma_h);
        if(HAL_OK == ret) {
            res = true;
            __HAL_DMA_RESET_HANDLE_STATE(&DmaNode->dma_h);
        } else {
            LOG_ERROR(DMA, "DmaAbort %s", HalStatus2Str(ret));
        }
    }
    return res;
}

bool dma_start(uint8_t num, uint32_t src_address, uint32_t dst_address, uint32_t bytes) {
    bool res = false;
    DmaHandle_t* DmaNode = DmaGetNode(num);
    if(DmaNode) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_DMA_Start_IT(&DmaNode->dma_h, src_address, dst_address, bytes);
        if(HAL_OK == ret) {
            res = true;
        } else {
            LOG_ERROR(DMA, "DmaStart %s", HalStatus2Str(ret));
        }
    }
    return res;
}
