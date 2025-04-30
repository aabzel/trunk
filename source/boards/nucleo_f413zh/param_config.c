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
#include "log.h"
#include "param_diag.h"
#include "param_types.h"

#ifdef HAS_IWDG
#include "iwdg_params.h"
#else
#define IWDG_PARAMS
#endif

#ifdef HAS_DECAWAVE
#include "decawave_params.h"
#else
#define DECAWAVE_PARAMS
#endif

#ifdef HAS_BOOT
#include "boot_diag.h"
#include "boot_params.h"
#else
#define BOOT_PARAMS
#endif

#ifdef HAS_TIME
#include "time_params.h"
#else
#define PARAMS_TIME
#endif


/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
    DECAWAVE_PARAMS
    IWDG_PARAMS
    BOOT_PARAMS
    PARAMS_TIME
                                  {BOOT, PAR_ID_REBOOT_CNT, 2, TYPE_UINT16, "ReBootCnt"}, /*num*/
                                  {SYS, PAR_ID_SERIAL_NUM, 4, TYPE_UINT32, "SerialNum"},  /**/
#ifdef HAS_BOOT
                                  {BOOT, PAR_ID_BOOT_CMD, 1, TYPE_UINT8, "BootCmd"}, /*1-stay in boot 0-launch App*/
#endif /*HAS_BOOT*/
#ifdef HAS_I2S
#ifdef HAS_I2S1
                                  {I2S, PAR_ID_I2S1_BUS_ROLE, 1, TYPE_UINT8, "I2s1BusRole"},
#endif /*HAS_I2S1*/
#ifdef HAS_I2S2
                                  {I2S, PAR_ID_I2S2_BUS_ROLE, 1, TYPE_UINT8, "I2s2BusRole"},
#endif /*HAS_I2S2*/

#ifdef HAS_I2S4
                                  {I2S, PAR_ID_I2S4_BUS_ROLE, 1, TYPE_UINT8, "I2s4BusRole"},
#endif /*HAS_I2S4*/
#ifdef HAS_BC127
                                  {BC127, PAR_ID_BC127_I2S_BUS_ROLE, 1, TYPE_UINT8, "Bc127I2sBusRole"},
#endif /*HAS_BC127*/
#ifdef HAS_WM8731
                                  {WM8731, PAR_ID_WM8731_I2S_BUS_ROLE, 1, TYPE_UINT8, "Wm8731i2sBusRole"},
#endif /*HAS_WM8731*/
#endif /*HAS_I2S*/
                                  {BOOT, PAR_ID_BOOT_CNT, 1, TYPE_UINT8, "BootCnt"}, /*num*/
                                   };


uint32_t param_get_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(ParamArray);
    return cnt;
}


