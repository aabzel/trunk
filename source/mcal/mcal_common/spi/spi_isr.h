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

/*tx*/
bool SpiTxHalfCpltCallBack(SpiHandle_t* const Node);
bool SpiTxCpltCallBack(SpiHandle_t* const Node);

/*Rx*/
bool SpiRxHalfCpltCallBack(SpiHandle_t* const Node);
bool SpiRxCpltCallBack(SpiHandle_t* const Node);

/*Err*/
bool SpiErrorCallBack(SpiHandle_t* const Node);

/*RxTx*/
bool SpiTxRxHalfCpltCallBack(SpiHandle_t* const Node);
bool SpiTxRxCpltCallBack(SpiHandle_t* const Node);


#ifdef __cplusplus
}
#endif

#endif /* SPI_MCAL_ISR_H */
