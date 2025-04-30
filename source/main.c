
#include <stddef.h>

#ifdef HAS_PC
#include <stdio.h>
#include <string.h>
#endif

#include "std_includes.h"

#ifdef HAS_CLI
#include "cli_drv.h"
#endif

#ifdef USE_HAL_DRIVER
#include "stm32f4xx_hal.h"
#endif

#ifdef HAS_SYSTEM
#include "system.h"
#endif

#ifdef HAS_FREE_RTOS
#include "FreeRTOS.h"
#include "task.h"
#endif /*HAS_FREERTOS*/

#ifdef HAS_FLASH
#include "flash_config.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_NORTOS
/*mandatory space NoRTOS.h needs stdint.h*/
#include "sys_config.h"
#endif /*HAS_NORTOS*/

#ifdef HAS_CLOCK
#include "clock.h" //TODO DEL
#endif             /*HAS_CLOCK*/

#include "common_functions.h"

#ifdef HAS_SUPER_CYCLE
#include "super_cycle.h"
#endif

#ifdef HAS_STREAM
#include "debug_info.h"
#endif

#ifdef HAS_HEALTH_MONITOR
#include "health_monitor.h"
#endif /*HAS_HEALTH_MONITOR*/

#ifdef HAS_GPIO
#include "gpio_mcal.h"
#endif

#ifdef HAS_UART
#include "uart_mcal.h"
#endif

#ifdef HAS_CORTEX_M4
#include "cortex_m4_driver.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif /*HAS_LOG*/

#ifdef HAS_BOOTLOADER
#include "bootloader.h"
#endif /*HAS_BOOTLOADER */

#ifdef HAS_MBR
#include "mbr_drv.h"
#endif /* HAS_MBR*/

#if defined(HAS_BOOTLOADER) && defined(HAS_GENERIC)
#error "Firmware is unable to be bootloader and application simultaneously"
#endif /*HAS_BOOT and HAS_GENERIC*/

#ifdef HAS_PC
/*For DeskTop*/
int main(int argc, char* argv[])
#else /*HAS_PC*/
/*For MCU*/

int main(void)
#endif
{
    bool res = true;
    (void)res;

#ifdef HAS_SYS_INIT
    res = system_init();
    res = try_init(res, "SYS");
#endif

#ifdef HAS_LOG
    LOG_INFO(SYS, "init:%s" CRLF, (res) ? "OK!" : "Error!\a");
#endif

#ifdef HAS_HEALTH_MONITOR
    HealthMon.init_error = !res;
#endif /*HAS_HEALTH_MONITOR*/

#ifdef HAS_STREAM
    LOG_INFO(SYS, "ProgramLaunched!");
    print_version();
    print_sys_info();
#endif /*HAS_STREAM*/

#ifdef HAS_BOOTLOADER
    res = bootloader_proc();
#endif /*HAS_BOOTLOADER*/

#ifdef HAS_MBR
    res = mbr_proc();
#endif /*HAS_MBR*/

#ifdef HAS_PC
    LOG_DEBUG(SYS, "argc %u", argc);
    if(2 <= argc) {
        uint32_t i = 0;

        for(i = 0; i < argc; i++) {
            LOG_DEBUG(SYS, "Arg%u [%s]", i, argv[i]);
        }

        LOG_DEBUG(SYS, "FetchCLICommand...");
        char cmd_line[1000] = {0};
        LOG_DEBUG(SYS, "Arg1 [%s]", argv[1]);
        strcpy(cmd_line, argv[1]);
        for(i = 2; i < argc; i++) {
            LOG_DEBUG(SYS, "Arg%u [%s]", i, argv[i]);
            snprintf(cmd_line, sizeof(cmd_line), "%s %s", cmd_line, argv[i]);
        }

        LOG_NOTICE(SYS, "TryCmd [%s]...", cmd_line);
        res = cli_process_cmd(1, cmd_line);
        if(res) {
            LOG_INFO(SYS, "Cmd [%s] Ok", cmd_line);
        } else {
            LOG_ERROR(SYS, "Cmd [%s] Err", cmd_line);
        }
        return 0;
    }
#endif

#ifdef HAS_FREE_RTOS
    vTaskStartScheduler();
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_NORTOS
#ifdef HAS_SUPER_CYCLE
    super_cycle_start();
#endif /*HAS_SUPER_CYCLE*/
#endif /*HAS_NORTOS*/

#ifdef HAS_LOG
    LOG_ERROR(SYS, "Unreachable line!");
#endif
    /*Unreachable line*/
    while(true) {
    }
    return 0;
} // main
