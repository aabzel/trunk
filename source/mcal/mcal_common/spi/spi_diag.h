#ifndef SPI_DIAG_H
#define SPI_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_LOG
#error "+HAS_LOG"
#endif /*HAS_LOG*/

#ifndef HAS_SPI
#error "+HAS_SPI"
#endif /*HAS_SPI*/

#ifndef HAS_SPI_DIAG
#error "+HAS_SPI_DIAG"
#endif /*HAS_DIAG_SPI*/

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif /*HAS_DIAG*/

#include "std_includes.h"

#include "spi_types.h"

bool spi_diag_int(void);
bool spi_diag(void);
bool SpiDiagConfig(const SpiConfig_t* const Config);
bool spi_raw_reg_diag(uint8_t num);
const char* SpiTxModeToStr(const SpiTxMode_t tx_mode);
const char* SpiPhaseToStr(SpiClkIdleLevel_t phase) ;
const char* SpiChipSelModeToStr(ChipSelect_t chip_select) ;
const char* SpiBitOrderToStr(IfBitOrder_t bit_order) ;
const char* SpiPolarityToStr(SpiPolarity_t polarity) ;
const char* SpiConfigToStr(const SpiConfig_t* const Config);
const char* ChipSelectSignalToStr(ChipSelectSignal_t state);
const char* SpiNodeToStr(const SpiHandle_t* const Node);
const char* SpiNodeIsrToStr(const SpiHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* SPI_DIAG_H */
