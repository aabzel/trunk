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

#ifdef HAS_SX1262
#include "sx1262_params.h"
#endif

#ifdef HAS_IWDG
#include "iwdg_params.h"
#endif
//#include "system.h" //Whats for

#ifdef HAS_BOOT
#include "boot_diag.h"
#include "boot_params.h"
#endif /*HAS_BOOT*/

/*TODO: Sort by index for bin search in future*/
const ParamItem_t ParamArray[] = {
#ifdef HAS_SX1262
		                          PARAMS_SX1262
#endif

#ifdef HAS_IWDG
                                  IWDG_PARAMS
#endif
#ifdef HAS_BOOT
                                  BOOT_PARAMS
#endif /*HAS_BOOT*/

                                  {.facility=TEST, .id=PAR_ID_TEST_ID1, .len=1, .type=TYPE_UINT8, .name="TestVal"},
                                  {.facility=BOOT, .id=PAR_ID_REBOOT_CNT, .len=2, .type=TYPE_UINT16, .name="ReBootCnt"}, /*num*/
                                  {.facility=APP, .id=PAR_ID_MAX_UP_TIME, .len=4, .type=TYPE_UINT32, .name="MaxUpTime"}, /*min*/
                                  {.facility=ASM, .id=PAR_ID_SERIAL_NUM, .len=4, .type=TYPE_UINT32, .name="SerialNum"},  /**/
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


