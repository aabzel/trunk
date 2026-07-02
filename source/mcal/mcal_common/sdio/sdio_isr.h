#ifndef SDIO_ISR_H
#define SDIO_ISR_H

#include "std_includes.h"

bool SdioCallBackError(uint8_t num);
bool SdioCallBackRxHalfCplt(uint8_t num);
bool SdioCallBackTxHalfCplt(uint8_t num);



#endif /* SDIO_ISR_H */



