#ifndef DMA_DIAG_H
#define DMA__DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_custom_types.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

const char* DmaDir2Str(uint8_t code);

#ifdef __cplusplus
}
#endif

#endif /* DMA_DIAG_H  */
