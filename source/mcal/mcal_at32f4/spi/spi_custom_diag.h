#ifndef SPI_CUSTOM_DIAG_H
#define SPI_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spi_custom_types.h"

bool spi_raw_reg_diag(uint8_t num);
bool spi_diag_low_level(uint8_t num, const char* const keyword);
bool SpiDiagRegCtrl1(const SpiRegCtrl1_t* const Reg, const char* const keyword) ;

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_DIAG_H */
