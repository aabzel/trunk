#include "boot_driver.h"

#include <stddef.h>

#include "std_includes.h"
#include "sys_config_common.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_NVIC
#include "nvic_drv.h"
#endif

#ifdef HAS_CRC32
#include "crc32.h"
#endif

#ifdef HAS_RISC_V
#include "rv32imc_driver.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif /*HAS_SYSTICK*/

#ifdef HAS_LED
//#include "led_drv.h"
#endif

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_FLASH_FS
#include "flash_fs.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_WATCHDOG
//#include "watchdog_mcal.h"
#endif
#include "sys_config.h"

BootData_t BootData = {0};
pFunction Jump_To_Code = NULL; /*Must not be in stack*/

#ifdef HAS_ARM
static bool bool_proc_stack_error(const uint32_t stack_top) {
    bool res = false;
#ifdef HAS_ARM
    LOG_ERROR(BOOT, "ErrorTopStackSizePointer:0x%08x lim: [0x%08x 0x%08x]", stack_top, RAM_START, RAM_START + RAM_SIZE);
#endif

#ifdef HAS_PARAM_SET
    res = false;
    uint8_t boot_cmd = BOOT_CMD_STACK_ERROR_STAY_ON;
    res = param_set(PAR_ID_BOOT_CMD, (uint8_t*)&boot_cmd);
    log_info_res(BOOT, res, "ParamSetBootStayStack");
#endif /*HAS_PARAM_SET*/
    return res;
}
#endif

#ifdef HAS_ARM
bool boot_jump_to_code_arm(const uint32_t app_start_address) {
    bool res = false;
    uint32_t reset_handler = 0;
    res = boot_check_reset_handler(app_start_address, &reset_handler);
    if(res) {
        uint32_t stack_top = 0;
        stack_top = read_addr_32bit(app_start_address);
        LOG_INFO(BOOT, "Stack_topAddress:0x%08x", stack_top);
        res = is_ram_addr(stack_top);
        if(res) {

#ifdef HAS_CLOCK
            // sw_pause_ms(500);
#endif

#ifdef USE_HAL_DRIVER
            HAL_SuspendTick();
#endif

#ifdef HAS_SYSTICK
            systick_disable();
#endif /*HAS_SYSTICK*/

#ifdef HAS_CMSIS
            __disable_irq();
#endif

#ifdef HAS_INTERRUPT
            res = interrupt_disable();
#endif /**/

#ifdef HAS_NVIC
            res = nvic_disable();
#endif /**/

#ifdef HAS_CMSIS
            SCB->VTOR = app_start_address;
#endif

            Jump_To_Code = (pFunction)reset_handler;
            /* Initialize user application's Stack Pointer */

#ifdef HAS_CMSIS
            __set_MSP(stack_top);
#endif
            // SCB->VTOR=(uint32_t)reset_handler;
#ifdef HAS_CLOCK
            clock_sw_pause_ms(500);
#endif
            Jump_To_Code();
            while(true) {
            }
        } else {
            res = bool_proc_stack_error(stack_top);
        }
    } else {
        res = bool_proc_start_error(reset_handler);
    }
    return res;
}
#endif

bool bool_proc_start_error(const uint32_t reset_handler) {
    bool res = false;
#ifdef HAS_LOG
    LOG_ERROR(BOOT, "AppResetHandlerAddress 0x%08x NotInFlash", reset_handler);
#endif

#ifdef HAS_PARAM_SET
    res = false;
    uint8_t boot_cmd = BOOT_CMD_START_ERROR_STAY_ON;
    res = param_set(PAR_ID_BOOT_CMD, (uint8_t*)&boot_cmd);
    log_info_res(BOOT, res, "ParamSetBootStayStart");
#endif /*HAS_PARAM_SET*/

    return res;
}

bool boot_check_reset_handler(const uint32_t app_start_address, uint32_t* const reset_handler) {
    bool res = false;
    if(reset_handler) {
#ifdef HAS_LOG
        LOG_WARNING(BOOT, "TryJumpToAddress:0x%08x...", app_start_address);
#endif

        uint32_t reset_addr = app_start_address;
        (void)reset_addr;
#ifdef HAS_ARM
        reset_addr += 4;
#endif

#ifdef HAS_DEBUGGER
        *reset_handler = read_addr_32bit(reset_addr);
        LOG_INFO(BOOT, "_start Addr:*(0x%08x)=0x%08x", reset_addr, *reset_handler);

#ifdef HAS_FLASH
        res = is_flash_addr(*reset_handler);
#endif
#endif // HAS_DEBUGGER
    }

    return res;
}

bool boot_jump_to_code(const uint32_t app_start_address) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(BOOT, "TryBoot 0x%08x", app_start_address);
#endif

#ifdef HAS_ARM
    res = boot_jump_to_code_arm(app_start_address);
#endif

#ifdef HAS_RISC_V
    res = rv32imc_boot_addr(app_start_address);
#endif
    return res;
}

bool boot_reboot(void) {
    bool res = false;
    res = boot_jump_to_code(BootConfig.fw_start_address);
    return res;
}
