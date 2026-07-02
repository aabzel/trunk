#ifndef DMA_CUSTOM_DRV_H
#define DMA_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif

#include "dma_mcal.h"
#include "dma_custom_types.h"
#include "std_includes.h"
#include "stm32fx_hal.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif



DMA_TypeDef* DmaNum2Instance(uint8_t num);
DMA_TypeDef* DmaNum2DMAx(uint8_t num);
DMA_HandleTypeDef* dma_get_handle(const uint8_t dma_num);

bool dma_init_ll(uint8_t num);
bool dma_init(void);
bool dma_stop(uint8_t num);
bool dma_start(uint8_t num, uint32_t src_address, uint32_t dst_address, uint32_t bytes);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_DRV_H  */
