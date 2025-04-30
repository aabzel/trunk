#ifndef SPIFI_CUSTOM_DRV_H
#define SPIFI_CUSTOM_DRV_H

#ifdef __cplusplus
extern "C" {
#endif


#ifndef HAS_SPIFI
#error "+HAS_SPIFI"
#endif

#include <stdbool.h>

#include "mik32_hal_spifi.h"

HAL_SPIFI_CacheEnableTypeDef SpiFiCacheCtrlToCacheEnable(bool cache_on_off) ;

#ifdef __cplusplus
}
#endif

#endif /* SPIFI_CUSTOM_DRV_H  */
