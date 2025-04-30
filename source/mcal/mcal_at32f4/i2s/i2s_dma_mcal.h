#ifndef I2S_DMA_MCAL_H
#define I2S_DMA_MCAL_H

#include <stddef.h>

#include "audio_types.h"
#include "std_includes.h"
#include "i2s_types.h"

bool i2s_dma_ctrl_ll(I2sHandle_t* Node, bool on_off);
//bool i2s_dma_ctrl(uint8_t num, bool on_off);
bool i2s_init_dma(const I2sConfig_t* Config, I2sHandle_t* Node);
bool i2s_api_read_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode) ;
bool i2s_api_write_dma(uint8_t num, SampleType_t* const array, size_t size, DmaMode_t mode);
//bool i2s_dma_pause(uint8_t num) ;
bool i2s_dma_restart(uint8_t num);
//bool i2s_dma_stop(uint8_t num);

#endif /* I2S_DMA_MCAL_H */
