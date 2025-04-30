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

#include "system.h"

#ifdef HAS_BOOT
#include "boot_diag.h"
#endif /*HAS_BOOT*/

/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
                                  {BOOT, PAR_ID_REBOOT_CNT, 2, TYPE_UINT16, "ReBootCnt"}, /*num*/
                                  {APP, PAR_ID_MAX_UP_TIME, 4, TYPE_UINT32, "MaxUpTime"}, /*min*/
                                  {ASM, PAR_ID_SERIAL_NUM, 4, TYPE_UINT32, "SerialNum"},  /**/
#ifdef HAS_BOOTLOADER
                                  {BOOT, PAR_ID_APP_CRC32, 4, TYPE_UINT32_HEX, "AppCrc32"}, /**/
                                  {BOOT, PAR_ID_APP_LEN, 4, TYPE_UINT32, "AppLen"},         /**/
                                  {BOOT, PAR_ID_APP_START, 4, TYPE_UINT32_HEX, "StartApp"}, /*Flash Addr*/
                                  {BOOT, PAR_ID_APP_STATUS, 1, TYPE_UINT8, "AppStatus"},    /*Flash Addr*/
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_BOOT
                                  {BOOT, PAR_ID_BOOT_CMD, 1, TYPE_UINT8, "BootCmd"}, /*1-stay in boot 0-launch App*/
#endif /*HAS_BOOT*/
                                  {BOOT, PAR_ID_BOOT_CNT, 1, TYPE_UINT8, "BootCnt"}, /*num*/
                                   };


uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}


