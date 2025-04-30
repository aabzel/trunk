#ifndef DMA_CUSTOM_DIAG_H
#define DMA_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_types.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

const char* DmaReqSelToStr(uint8_t reqsel);
bool dma_diag_custom(uint8_t num);
bool dma_channel_diag_custom(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CUSTOM_DIAG_H  */
