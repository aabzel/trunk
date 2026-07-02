#ifndef SPI_DMA_CUSTOM_H
#define SPI_DMA_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spi_types.h"

bool spi_dma_init_rx(const uint8_t num);
bool spi_dma_init_tx(const uint8_t num);
bool spi_dma_write(const uint8_t num, const uint8_t* const data, const uint32_t size);
bool spi_dma_read(const uint8_t num, uint8_t* const data, const uint32_t size);
bool spi_dma_write_read(const uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, const uint32_t size);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DMA_CUSTOM_H  */
