#ifndef SPI_MCAL_ISR_H
#define SPI_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifdef HAS_SPI_CUSTOM
#include "spi_custom_isr.h"
#endif
#include "spi_types.h"

bool SpiCallBackError(uint8_t num);

bool SpiCallBackMoveStart(uint8_t num);
bool SpiCallBackMoveCplt(uint8_t num);

bool SpiCallBackRxHalfCplt(uint8_t num);
bool SpiCallBackRxCplt(uint8_t num);

bool SpiCallBackTxHalfCplt(uint8_t num);
bool SpiCallBackTxCplt(uint8_t num);

bool SpiCallBackTxRxHalfCplt(uint8_t num);
bool SpiCallBackTxRxCplt(uint8_t num);

#ifdef __cplusplus
}
#endif

#endif /* SPI_MCAL_ISR_H */
