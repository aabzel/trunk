#include "dma_custom_bindings.h"
#include "mik32_hal.h"

uint32_t DmaDirToMik32DmaDir(DmaDir_t dir) {
    uint32_t code = 0xFFFFFFFF;
    switch(dir) {
    case DMA_MCAL_DIR_PERIPH_TO_MEMORY:
        code = DMA_PERIPH_TO_MEMORY;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_PERIPH:
        code = DMA_MEMORY_TO_PERIPH;
        break;
    case DMA_MCAL_DIR_MEMORY_TO_MEMORY:
        code = DMA_MEMORY_TO_MEMORY;
        break;
    default:
        code = DMA_MEMORY_TO_MEMORY;
        break;
    }
    return code;
}
