#include "param_config.h"

#include <inttypes.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifndef HAS_FLASH_FS
#error "Params need FLASH_FS"
#endif

#include "boot_driver.h"
#include "common_diag.h"
#include "data_utils.h"

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

#ifdef HAS_IWDG
#include "iwdg_params.h"
#else
#define IWDG_PARAMS
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

/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
    PARAMS_BOOT PARAMS_LIGHT_NAVIGATOR PARAMS_FLASH_FS PARAMS_GNSS PARAMS_GENERIC IWDG_PARAMS PARAMS_KEEPASS
        PARAMS_PASTILDA PARAMS_SDIO PARAMS_TIME PARAMS_BOOTLOADER{
            .facility = BOOT, .id = PAR_ID_BOOT_CMD, .len = 1, .type = TYPE_UINT8, .name = "BootCmd"}, /*num*/
    {.facility = BOOT, .id = PAR_ID_REBOOT_CNT, .len = 2, .type = TYPE_UINT16, .name = "ReBootCnt"},   /*num*/
    {.facility = SYS, .id = PAR_ID_SERIAL_NUM, .len = 4, .type = TYPE_UINT32, .name = "SerialNum"},    /**/
};

uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}
