#include "param_config.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "std_includes.h"

#ifdef HAS_BOOT
//#include "boot_diag.h"
#include "boot_params.h"
#else
#define PARAMS_BOOT
#endif

#include "common_diag.h"
#include "data_utils.h"

#ifdef HAS_CLOCK
#include "clock_params.h"
#else
#define PARAMS_CLOCK
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifdef HAS_CLI
#include "log.h"
#endif

#include "param_diag.h"
#include "param_types.h"

#ifdef HAS_SDIO
#include "sdio_params.h"
#else
#define PARAMS_SDIO
#endif

#ifdef HAS_BOARD_CUSTOM
#include "board_params.h"
#else
#define BOARD_PARAMS
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
#endif /*HAS_FLASH_FS*/

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

#ifdef HAS_WATCHDOG
#include "watchdog_params.h"
#else
#define WATCHDOG_PARAMS
#endif

#define RARAM_ARRAY_ALL                                                                                                \
    BOARD_PARAMS                                                                                                       \
    PARAMS_BOOT                                                                                                        \
    PARAMS_BOOTLOADER                                                                                                  \
    PARAMS_CLOCK                                                                                                       \
    PARAMS_FLASH_FS                                                                                                    \
    PARAMS_GNSS                                                                                                        \
    PARAMS_GENERIC                                                                                                     \
    PARAMS_KEEPASS                                                                                                     \
    PARAMS_PASTILDA                                                                                                    \
    PARAMS_TIME                                                                                                        \
    WATCHDOG_PARAMS{.facility = SYS,                                                                                   \
                    .id = PAR_ID_SERIAL_NUM,                                                                           \
                    .len = 4,                                                                                          \
                    .type = TYPE_UINT32,                                                                               \
                    .default_value = "0",                                                                              \
                    .name = "SerialNum"}, /**/

/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {RARAM_ARRAY_ALL};

uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}
