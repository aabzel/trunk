#ifndef DAC_MCAL_ISR_H
#define DAC_MCAL_ISR_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#include "dac_custom_isr.h"
#include "dac_types.h"

/*tx*/
bool DacTxHalfCpltCallBack(DacHandle_t* const Node);
bool DacTxCpltCallBack(DacHandle_t* const Node);

/*Rx*/
bool DacRxHalfCpltCallBack(DacHandle_t* const Node);
bool DacRxCpltCallBack(DacHandle_t* const Node);

/*Err*/
bool DacErrorCallBack(DacHandle_t* const Node);

/*RxTx*/
bool DacTxRxHalfCpltCallBack(DacHandle_t* const Node);
bool DacTxRxCpltCallBack(DacHandle_t* const Node);

#ifdef __cplusplus
}
#endif

#endif /* DAC_MCAL_ISR_H */
