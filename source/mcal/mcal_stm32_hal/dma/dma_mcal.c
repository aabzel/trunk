#include "dma_mcal.h"

#include <stddef.h>
#include <string.h>

#include "array.h"
#include "dma_custom_bindings.h"
#include "dma_custom_types.h"
#include "hal_diag.h"
#include "hal_mcal.h"
#include "log.h"
#include "std_includes.h"
#include "stm32fx_hal.h"

#ifdef HAS_DMA_CHANNEL
#include "dma_channel_types.h"
#endif

#define DMA_INT_PRIORITY 0

static const DmaInfo_t DmaInfo[] = {
    {
        .dma_num = 1,
        .DMAx = DMA1,
        .valid = true,
    },
    {
        .dma_num = 2,
        .DMAx = DMA2,
        .valid = true,
    },
};

DMA_TypeDef* DmaNum2DMAx(uint8_t num) {
    DMA_TypeDef* DMAx = NULL;
    switch(num) {
    case 1:
        DMAx = DMA1;
        break;
    case 2:
        DMAx = DMA2;
        break;
    default:
        break;
    }
    return DMAx;
}

#define COPY_DMA_STREAM_BITS(BIT)                                                                                      \
    do {                                                                                                               \
        DmaStreamIntStatusReg.teif = Reg.tcif##BIT;                                                                    \
        DmaStreamIntStatusReg.tcif = Reg.tcif##BIT;                                                                    \
        DmaStreamIntStatusReg.feif = Reg.feif##BIT;                                                                    \
        DmaStreamIntStatusReg.dmeif = Reg.dmeif##BIT;                                                                  \
        DmaStreamIntStatusReg.htif = Reg.htif##BIT;                                                                    \
    } while(0);

const DmaInfo_t* DmaGetInfo(uint8_t dma_num) {
    DmaInfo_t* Info = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DmaInfo);
    for(i = 0; i < cnt; i++) {
        if(dma_num == DmaInfo[i].dma_num) {
            if(DmaInfo[i].valid) {
                Info = &DmaInfo[i];
                break;
            }
        }
    }
    return Info;
}

bool dma_init_clock(uint8_t num) {
    LOG_INFO(LG_DMA, "DMA%u,InitClk", num);
    bool res = false;
    switch(num) {
    case 1: {
#ifdef HAS_DMA1
        __HAL_RCC_DMA1_CLK_ENABLE();
        res = true;
#endif
    } break;
    case 2: {
#ifdef HAS_DMA2
        __HAL_RCC_DMA2_CLK_ENABLE();
        res = true;
#endif
    } break;
    default:
        res = false;
        break;
    }

    return res;
}

bool dma_init_custom(void) {
    bool res = true;
    LOG_INFO(LG_DMA, "Init,Custom");
    return res;
}

bool dma_stop(uint8_t num) {
    bool res = false;
    DmaHandle_t* DmaNode = DmaGetNode(num);
    if(DmaNode) {
        HAL_StatusTypeDef ret = HAL_ERROR;
        ret = HAL_DMA_Abort_IT(&DmaNode->dma_h);
        res = HAL_retToRes(ret);
        if(res) {
            __HAL_DMA_RESET_HANDLE_STATE(&DmaNode->dma_h);
        } else {
            LOG_ERROR(LG_DMA, "DmaAbort %s", HalStatusToStr(ret));
        }
    }
    return res;
}

#ifdef HAS_DMA_ROOT
DMA_HandleTypeDef* dma_get_handle(const uint8_t dma_num) {
    DMA_HandleTypeDef* pHandle = NULL;
    DmaHandle_t* Node = DmaGetNode(dma_num);
    if(Node) {
        pHandle = &Node->dma_h;
    }
    return pHandle;
}
#endif

bool dma_init_one(uint8_t num) {
    bool res = false;
    const DmaConfig_t* Config = DmaGetConfig(num);
    if(Config) {
        DmaHandle_t* Node = DmaGetNode(num);
        if(Node) {
            const DmaInfo_t* Info = DmaGetInfo(num);
            if(Info) {
                res = dma_init_clock(num);
            }
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
            LOG_ERROR(LG_DMA, "DmaStart %s", HalStatusToStr(ret));
        }
    }
    return res;
}
