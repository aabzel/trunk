#ifndef DMA_DIAG_CUSTOM_H
#define DMA_DIAG_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "dma_custom_types.h"

#ifndef HAS_DMA
#error "+HAS_DMA"
#endif

const char* DmaDirToStr(uint8_t code);
const char* DmaHalStateToStr(const HAL_DMA_StateTypeDef state );
bool dma_custom_diag_one(uint8_t num);
bool dma_diag_low_level_diag(char* keyWord1, char* keyWord2);
bool dma_custom_diag(void);
bool dma_diag_low_level_command(int32_t argc, char* argv[]);

#ifdef __cplusplus
}
#endif

#endif /* DMA_DIAG_CUSTOM_H  */
