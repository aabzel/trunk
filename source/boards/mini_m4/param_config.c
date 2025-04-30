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

#ifdef HAS_IWDG
#include "iwdg_params.h"
#endif

#ifdef HAS_BOOT
#include "boot_diag.h"
#include "boot_params.h"
#endif /*HAS_BOOT*/


/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
#ifdef HAS_IWDG
                                  IWDG_PARAMS
#endif

#ifdef HAS_BOOT
                                  BOOT_PARAMS
#endif /*HAS_BOOT*/

                                  {BOOT, PAR_ID_REBOOT_CNT, 2, .type=TYPE_UINT16, "ReBootCnt"}, /*num*/
                                  {APP, PAR_ID_MAX_UP_TIME, 4, .type=TYPE_UINT32, "MaxUpTime"}, /*min*/
                                  {ASM, PAR_ID_SERIAL_NUM, 4, .type=TYPE_UINT32, "SerialNum"},  /**/
#ifdef HAS_BOOT
                                  {BOOT, PAR_ID_BOOT_CMD, 1, .type=TYPE_UINT8, "BootCmd"}, /*1-stay in boot 0-launch App*/
#endif /*HAS_BOOT*/
                                  {BOOT, PAR_ID_BOOT_CNT, 1, .type=TYPE_UINT8, "BootCnt"}, /*num*/
                                   };

uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}


