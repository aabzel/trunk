#ifndef SPI_CUSTOM_DIAG_H
#define SPI_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "spi_custom_types.h"

extern const Reg32_t SpiRegs[];

uint32_t spi_reg_cnt(void);
const char* SpiInfoToStr(const SpiInfo_t* const Info);

#ifdef __cplusplus
}
#endif

#endif /* SPI_CUSTOM_DIAG_H */
