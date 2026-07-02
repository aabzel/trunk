#ifndef SPI_INTERRUPT_MCAL_H
#define SPI_INTERRUPT_MCAL_H

#include "std_includes.h"
#include "spi_types.h"

bool spi_read_interrupt(uint8_t num, uint8_t* const data, uint32_t size);
bool spi_write_interrupt(uint8_t num, const uint8_t* const data, uint32_t size);
bool spi_write_read_interrupt(uint8_t num, const uint8_t* const tx_array, uint8_t* const rx_array, uint32_t size);

#endif /* SPI_INTERRUPT_MCAL_H */
