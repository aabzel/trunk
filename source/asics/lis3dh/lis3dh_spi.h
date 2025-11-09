#ifndef LIS3DH_SPI_H
#define LIS3DH_SPI_H

#include "std_includes.h"
#include "lis3dh_types.h"

bool lis3dh_spi_reg_read_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t reg_addr, uint8_t* const rx_byte) ;
bool lis3dh_spi_reg_write_ll(Lis3dhHandle_t* Node, Lis3dhRegAddr_t addr, uint8_t byte) ;

#endif /* LIS3DH_SPI_H */
