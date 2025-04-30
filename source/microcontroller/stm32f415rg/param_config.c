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
#include "boot_diag.h"
#include "boot_params.h"
#endif /*HAS_BOOT*/

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

#ifdef HAS_FLASH_FS
#include "flash_fs_params.h"
#else
#define FLASH_FS_PARAMS
#endif /*HAS_FLASH_FS*/


/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
	    FLASH_FS_PARAMS
	    PARAMS_KEEPASS
	    PARAMS_PASTILDA
	    PARAMS_SDIO

                                  IWDG_PARAMS



                                  BOOT_PARAMS





                                  {BOOT, PAR_ID_REBOOT_CNT, 2, .type=TYPE_UINT16, "ReBootCnt"}, /*num*/
                                  {SYS, PAR_ID_MAX_UP_TIME, 4, .type=TYPE_UINT32, "MaxUpTime"}, /*min*/
                                  {SYS, PAR_ID_SERIAL_NUM, 4, .type=TYPE_UINT32, "SerialNum"},  /**/
#ifdef HAS_BOOT
                                  {BOOT, PAR_ID_BOOT_CMD, 1, .type=TYPE_UINT8, "BootCmd"}, /*1-stay in boot 0-launch App*/
#endif /*HAS_BOOT*/
                                  {BOOT, PAR_ID_BOOT_CNT, 1, .type=TYPE_UINT8, "BootCnt"}, /*num*/
                                   };

uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}


