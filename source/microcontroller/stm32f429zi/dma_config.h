#ifndef DMA_CONFIG_H
#define DMA_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dma_types.h"

#ifndef HAS_DMA
#error "+ HAS_DMA"
#endif /**/

#define DMA2_SDIO_RX 1
#define DMA2_SDIO_TX 2

extern const DmaConfig_t DmaConfig[];
extern DmaHandle_t DmaInstance[];

uint32_t dma_get_cnt(void);

#ifdef __cplusplus
}
#endif

#endif /* DMA_CONFIG_H  */
