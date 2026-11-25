#ifndef POWER_DMA_MCAL_H
#define POWER_DMA_MCAL_H

#include <stddef.h>

#include "std_includes.h"
#include "power_types.h"

bool power_dma_ctrl_ll(PowerHandle_t* Node, bool on_off);
bool power_dma_ctrl(uint8_t num, bool on_off);
bool i2s_init_dma(const I2sConfig_t* Config, PowerHandle_t* Node);
bool i2s_api_read_dma(uint8_t num, uint8_t* const array, size_t size, DmaMode_t mode) ;
bool i2s_api_write_dma(uint8_t num, uint8_t* const array, size_t size, DmaMode_t mode);
bool power_dma_pause(uint8_t num);
bool power_dma_restart(uint8_t num);
bool power_dma_stop(uint8_t num);

#endif /* POWER_DMA_MCAL_H */
