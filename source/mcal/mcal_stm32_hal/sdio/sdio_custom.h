#ifndef SDIO_CUSTOM_DRIVER_H
#define SDIO_CUSTOM_DRIVER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SDIO
#error "+HAS_SDIO"
#endif

#ifndef HAS_DMA
#warning "+HAS_DMA"
#endif

#include "std_includes.h"
#include "hal_diag.h"
#include "sdio_custom_const.h"
#include "sdio_types.h"
//#include "stm32fx.h"
//#include "stm32fx_hal_sd.h"

#ifdef HAS_SDIO_DIAG
#include "sdio_diag.h"
#endif /**/

#ifdef HAS_INTERRUPT
#endif

#ifdef HAS_DMA
#endif /*HAS_DMA*/

uint32_t sdio_reg_cnt(void);
uint8_t SdioInstance2num(const SD_TypeDef* const Instance);
bool SdioWaitTxDoneLl(SdioHandle_t* Node, uint32_t time_out, uint8_t num, uint32_t block_num) ;
bool SdioWaitRxDoneLl(SdioHandle_t* const Node, uint32_t time_out_ms, uint8_t num, uint32_t block_num) ;
bool sdio_proc_card_state(HAL_SD_CardStateTypeDef card_state);

#ifdef __cplusplus
}
#endif

#endif /* SDIO_CUSTOM_DRIVER_H */
