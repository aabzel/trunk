#ifndef SW_SD_CARD_MCAL_H
#define SW_SD_CARD_MCAL_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_sd_card_config.h"
#include "sw_sd_card_types.h"
#include "disk_const.h"
#ifdef HAS_SW_SD_CARD_DIAG
#include "sw_sd_card_diag.h"
#endif

/* API */
const SwSdCardConfig_t* SwSdCardGetConfig(uint8_t num);
SwSdCardHandle_t* SwSdCardGetNode(uint8_t num);
bool SwSdCardIsValidConfig(const SwSdCardConfig_t* const Config);

bool sw_sd_card_mcal_init(void);
bool sw_sd_card_init_custom(void);
bool sw_sd_card_init_one(uint8_t num);
bool sw_sd_card_init_common(const SwSdCardConfig_t* const Config,
                            SwSdCardHandle_t* const Node);


/*setters*/
DRESULT sd_sw_diskctl(uint8_t pdrv, uint8_t cmd, void* buff ) ;
bool disk_sw_write_sector(uint8_t pdrv, uint32_t sector, uint8_t* const buff);

/*getters*/
bool disk_sw_read_sector(uint8_t num, uint32_t sector, uint8_t* const buff);



#ifdef __cplusplus
}
#endif

#endif /* SW_SD_CARD_MCAL_H */
