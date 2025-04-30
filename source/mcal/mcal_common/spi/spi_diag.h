#ifndef SPI_DIAG_H
#define SPI_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#include <stdint.h>

#include "spi_types.h"

bool spi_diag_int(void);
bool spi_diag(void);
bool SpiDiagConfig(const SpiConfig_t* const Config);
const char* SpiTxModeToStr(SpiTxMode_t phase);
const char* SpiConfigToStr(const SpiConfig_t* const Config);
const char* ChipSelectSignal2Str(ChipSelectSignal_t state);

#ifdef __cplusplus
}
#endif

#endif /* SPI_DIAG_H */
