#ifndef DMA_CUSTOM_TYPES_H
#define DMA_CUSTOM_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_const.h"
#include "stm32f4xx_hal.h"
#include "dma_const.h"

#define DMA_CUSTOM_TYPES           \
    DMA_TypeDef* DMAx;             \
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
