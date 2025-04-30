#include "generic.h"

#include "std_includes.h"

#ifdef HAS_DEBUGGER
//#include "debugger.h"
#endif

#ifdef HAS_NVIC
//#include "nvic_drv.h"
#endif

#ifdef HAS_CRC32
//#include "crc32.h"
#endif

#ifdef HAS_CLOCK
//#include "clock.h"
#endif

#include "sys_config_common.h"

#ifdef HAS_SYSTICK
//#include "systick_general.h"
#endif /*HAS_SYSTICK*/

#ifdef HAS_LED
//#include "led_drv.h"
#endif

#ifdef HAS_INTERRUPT
//#include "interrupt_drv.h"
#endif

#ifdef HAS_CLOCK
//#include "clock.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_FLASH
//#include "flash_drv.h"
#endif

#include "log.h"

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_BOOT
#include "boot_const.h"
#endif

#ifdef HAS_WATCHDOG
//#include "watchdog_mcal.h"
#endif
//#include "sys_config.h"

static bool fine_start_event = false;

bool generic_jump_to_bootloader(void) {
    bool res = false;
#ifdef HAS_PARAM
    uint8_t boot_cmd = BOOT_CMD_STAY_ON;
    res = param_set(PAR_ID_BOOT_CMD, (uint8_t*)&boot_cmd);
    log_info_res(GENERIC, res, "SetBoot");
#endif

    core_reboot();
    LOG_ERROR(GENERIC, "ReBootErr");

    return res;
}

bool generic_proc(void) {
    bool res = false;
    uint32_t up_time_ms = time_get_ms32();
    if((2 * WDT_TIMEOUT_MS) < up_time_ms) {
        /* Watchdog did not reset board still.
           That means that everything all right!*/
        if(false == fine_start_event) {
            LOG_INFO(GENERIC, "AppLoadedFine!");
            /*Indicate boot that Application loaded fine*/
            res = true;
#ifdef HAS_PARAM
            uint8_t boot_cnt = 0;
            res = param_set(PAR_ID_BOOT_CNT, (uint8_t*)&boot_cnt);
#endif /*HAS_PARAM*/
            if(res) {
                LOG_INFO(GENERIC, "AppLoadedFineSave!");
                fine_start_event = true;
            } else {
                LOG_ERROR(GENERIC, "ErrResetBootCnt");
            }
        }
    }
    return res;
}
