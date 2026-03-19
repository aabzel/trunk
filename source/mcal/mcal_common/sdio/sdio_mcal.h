#ifndef SDIO_MCAL_H
#define SDIO_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sdio_types.h"
#include "sdio_config.h"
#include "sdio_custom.h"
#include "sdio_dma.h"
#include "sdio_int.h"
#include "sdio_poll.h"

#ifdef HAS_SDIO_DIAG
#include "sdio_diag.h"
#endif

/*API*/
SdioHandle_t* SdioGetNode(uint8_t num);
const SdioConfig_t* SdioGetConfig(uint8_t num);
const SdioInfo_t* SdioGetInfo(uint8_t num);

bool sdio_init_common(const SdioConfig_t* const Config, SdioHandle_t* const Node) ;
bool sdio_init_one(uint8_t num);
bool sdio_mcal_init(void);
bool sdio_proc_one(uint8_t num);
bool sdio_proc(void);
bool sdio_init_ll(uint32_t num);

/*setters*/
bool sdio_write_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, const uint8_t* const RxData);
uint8_t sdio_ioctl(uint8_t pdrv, uint8_t cmd, void* buff);

/*getters*/
bool SdioIsValid(uint8_t num);
bool SdioIsValidConfig(const SdioConfig_t* const Config);
bool sdio_read_sector(uint8_t num, uint32_t block_num, uint32_t block_cnt, uint8_t* const RxData);
bool sdio_card_info_get(uint32_t num);
bool sdio_init_test(SdioHandle_t* Node);
bool sdio_is_connected(uint32_t num);
uint16_t sdio_get_block_size(uint32_t num);
uint32_t sdio_get_block_num(uint32_t num);


#ifdef __cplusplus
}
#endif

#endif /* SDIO_MCAL_H */
