#ifndef SPI_CUSTOM_H
#define SPI_CUSTOM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "spi_custom_isr.h"
#include "spi_custom_types.h"
#include "spi_types.h"

SPI_TypeDef* SpiNum2Base(const uint8_t num);
uint32_t spi_num_to_bus_clock(const uint8_t num) ;
uint8_t spi_base_2_num(SPI_TypeDef* Instance);
bool spi_proc_status(SpiHandle_t* const Node, const  SpiStm32RegStatus_t * const Status);

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_H  */
