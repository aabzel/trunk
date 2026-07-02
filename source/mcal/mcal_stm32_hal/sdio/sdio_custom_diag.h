#ifndef SDIO_CUSTOM_DIAG_H
#define SDIO_CUSTOM_DIAG_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>

#include "stm32fx_hal.h"
//#include "stm32fx_hal_sd.h"

#include "sdio_custom_types.h"
#include "mcal_types.h"
#include "sdio_register_types.h"

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifndef HAS_DIAG
#error "+HAS_DIAG"
#endif

#ifndef HAS_SDIO_DIAG
#error "+HAS_SDIO_DIAG"
#endif

extern const Reg32_t SdioReg[];

bool SdioStatusDiag(const uint32_t dword);
bool ParseSdCardInfo(const HAL_SD_CardInfoTypeDef* const CardInfo); // error
bool ParseSdCardCSD(const HAL_SD_CardCSDTypeDef* const CSD);
bool ParseSdCardCID(const HAL_SD_CardCIDTypeDef* const CIDp);
bool ParseSdCardStatus(const HAL_SD_CardStatusTypeDef* const Status);
bool sdio_scan(uint8_t num);

//bool ParseSdCardStatus(const HAL_SD_CardStatusTypeDef* const Status);
const char* HalSdioErrCode2Str(uint32_t ErrorCode);
const char* SdState2Str(HAL_SD_StateTypeDef code);
const char* CardState2Str(HAL_SD_CardStateTypeDef code);
const char* ManufaturerId2Str(uint8_t mid);
const char* au_size_str(uint8_t au_size);
char* size_of_prot_area2Str(uint32_t size_of_prot_area);

#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_DIAG_H */
