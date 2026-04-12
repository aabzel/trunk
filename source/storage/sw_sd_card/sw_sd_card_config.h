#ifndef SW_SD_CARD_CONFIG_H
#define SW_SD_CARD_CONFIG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "sw_sd_card_types.h"
#include "sw_sd_card_dep.h"

extern const SwSdCardConfig_t SwSdCardConfig[];
extern SwSdCardHandle_t SwSdCardInstance[];

uint32_t sw_sd_card_get_cnt(void);



#ifdef __cplusplus
}
#endif

#endif /* SW_SD_CARD_CONFIG_H */
