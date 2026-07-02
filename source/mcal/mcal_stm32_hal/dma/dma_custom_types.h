#ifndef DMA_CUSTOM_TYPES_H
#define DMA_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_custom_const.h"
#include "stm32fx_hal.h"
#include "dma_const.h"

#ifdef HAS_DMA_ROOT
#define DMA_CUSTOM_ROOT   DMA_HandleTypeDef dma_h;
#else
#define DMA_CUSTOM_ROOT
#endif

#define DMA_CUSTOM_VARIABLES               \
    DMA_TypeDef* DMAx;                     \
    DMA_HandleTypeDef dma_h;


typedef struct {
    uint8_t dma_num; /*DMA num*/
    volatile DMA_TypeDef* DMAx;
    bool valid;
} DmaInfo_t;

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_TYPES_H  */
