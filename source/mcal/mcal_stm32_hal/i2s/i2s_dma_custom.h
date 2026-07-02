#ifndef I2S_DMA_CUSTOM_H
#define I2S_DMA_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

bool i2s_dma_init(const uint8_t num);
bool i2s_dma_read(uint8_t num, uint16_t* array, uint32_t words);
bool i2s_dma_pause(uint8_t num) ;
bool i2s_dma_stop(uint8_t num) ;

#ifdef __cplusplus
}
#endif

#endif // I2S_DMA_CUSTOM_H





