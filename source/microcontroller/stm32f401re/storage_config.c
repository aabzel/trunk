#include "storage_config.h"

#include "std_includes.h"
#include "array.h"
#include "storage_diag.h"
#include "storage_types.h"

#ifdef HAS_SDIO
#include "sdio_params.h"
#else
#define PARAMS_SDIO
#endif
#ifdef HAS_BOOT
#include "boot_params.h"
#else
#define PARAMS_BOOT
#endif
#ifdef HAS_KEEPASS
#include "keepass_params.h"
#else
#define PARAMS_KEEPASS
#endif

#ifdef HAS_PASTILDA
#include "pastilda_params.h"
#else
#define PARAMS_PASTILDA
#endif

#ifdef HAS_LIGHT_NAVIGATOR
#include "light_navigator_params.h"
#else
#define PARAMS_LIGHT_NAVIGATOR
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs_params.h"
#else
#define PARAMS_FLASH_FS
#endif /**/

#ifdef HAS_GNSS
#include "gnss_params.h"
#else
#define PARAMS_GNSS
#endif

#ifdef HAS_BOOTLOADER
#include "bootloader_params.h"
#else
#define PARAMS_BOOTLOADER
#endif


#ifdef HAS_GENERIC
#include "generic_params.h"
#else
#define PARAMS_GENERIC
#endif

#ifdef HAS_TIME
#include "time_params.h"
#else
#define PARAMS_TIME
#endif

/*TODO: Sort by index for bin search in future*/
const StorageItem_t StorageArray[] = {
    PARAMS_GENERIC
    PARAMS_KEEPASS
    PARAMS_PASTILDA
    PARAMS_TIME
};

uint32_t storage_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(StorageArray);
    return cnt;
}
