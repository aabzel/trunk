#include "boot_driver.h"

#include <stddef.h>

#include "code_generator.h"
#include "microcontroller_drv.h"
#include "std_includes.h"
#include "sys_config.h"
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
#include "clock_mcal.h"
#endif

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif

#ifdef HAS_INTERRUPT
#include "interrupt_mcal.h"
#endif

#ifdef HAS_CLOCK
#include "clock_mcal.h"
#endif

#ifdef HAS_CORE
#include "core_driver.h"
#endif

#ifdef HAS_FLASH
#include "flash_mcal.h"
#endif

#ifdef HAS_STORE_FS
#include "store_fs.h"
#endif

#ifdef HAS_LOG
#include "debug_info.h"
#include "log.h"
#endif

#ifdef HAS_TIME
#include "time_mcal.h"
#endif

#ifdef HAS_WATCHDOG
//#include "watchdog_mcal.h"
#endif

COMPONENT_GET_NODE(Boot, boot)
COMPONENT_GET_CONFIG(Boot, boot)

BootData_t BootData = {0};
pFunction Jump_To_Code = NULL; /*Must not be in stack*/

#ifdef HAS_ARM
static bool bool_proc_stack_error(const uint32_t stack_top) {
    bool res = false;
#ifdef HAS_LOG
    LOG_ERROR(BOOT, "ErrorTopStackSizePointer:0x%08x lim: [0x%08x 0x%08x]", stack_top, RAM_START, RAM_START + RAM_SIZE);
#endif

#ifdef HAS_STORE_FS_SET
    res = false;
    uint8_t boot_cmd = BOOT_CMD_STACK_ERROR_STAY_ON;
    res = store_fs_set(1, PAR_ID_BOOT_CMD, (uint8_t*)&boot_cmd);
    log_info_res(BOOT, res, "ParamSetBootStayStack");
#endif /* */
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
#ifdef HAS_LOG
        LOG_INFO(BOOT, "Stack_topAddress:0x%08x", stack_top);
#endif
        res = is_ram_addr(stack_top);
        if(res) {

#ifdef HAS_CLOCK
            // sw_pause_ms(500);
#endif

#ifdef USE_HAL_DRIVER
            HAL_SuspendTick();
#endif

#ifdef HAS_SYSTICK
            systick_mcal_stop();
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

#ifdef HAS_STORE_FS_SET
    res = false;
    uint8_t boot_cmd = BOOT_CMD_START_ERROR_STAY_ON;
    res = store_fs_set(PAR_ID_BOOT_CMD, (uint8_t*)&boot_cmd);
    log_info_res(BOOT, res, "ParamSetBootStayStart");
#endif /*HAS_STORE_FS_SET*/

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
#ifdef HAS_LOG
        LOG_INFO(BOOT, "_start Addr:*(0x%08x)=0x%08x", reset_addr, *reset_handler);
#endif

        res = is_flash_addr(*reset_handler);
#ifdef HAS_FLASH_EX
#endif

#endif
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
    res = boot_jump_to_code(BootConfig[0].fw_start_address);
    return res;
}

#ifdef HAS_STORE_FS
static bool boot_update_store_fs(uint8_t store_fs_num) {
    bool res = false;
    uint16_t cnt = 0;
    res = store_fs_get(store_fs_num, PAR_ID_REBOOT_CNT, &cnt);
    if(res) {
        cnt++;
        res = store_fs_set(store_fs_num, PAR_ID_REBOOT_CNT, &cnt);
    }
    return res;
}
#endif

static bool boot_init_custom(void) {
    bool res = false;
#ifdef HAS_STORE_FS
    res = boot_update_store_fs(1);
#endif
    return res;
}

bool boot_seek_vector_table(const uint32_t mem_start, const uint32_t size) {
    bool res = false;
#ifdef HAS_LOG
    LOG_INFO(BOOT, "SeekVectorTable,Start:0x%08X,Size:%u", mem_start, size);
#endif
    uint32_t cnt = 0;
    uint32_t offset = 0;
    uint32_t vt_size = sizeof(ArmCortexVectorTable_t);
    uint32_t end_size = size - vt_size;
    for(offset = 0; offset < end_size; offset++) {
        uint32_t phy_addr = mem_start + offset;
        res = arm_cortex_check_arm_vector_table(phy_addr);
        if(res) {
#ifdef HAS_LOG
            cli_printf(CRLF);
            LOG_INFO(BOOT, "%d,SpotVectorTable:0x%08x", cnt, phy_addr);
#endif
            cnt++;
        }
#ifdef HAS_LOG
        diag_progress_log(offset, end_size, 1000);
#endif
    }
#ifdef HAS_LOG
    cli_printf(CRLF);
#endif
    if(cnt) {
#ifdef HAS_LOG
        LOG_INFO(BOOT, "SpotVectorTable:%u", cnt);
#endif
        res = true;
    } else {
#ifdef HAS_LOG
        LOG_ERROR(BOOT, "NoVectorTables");
#endif
        res = false;
    }
    return res;
}

uint32_t boot_stack_top_addr_get(const uint8_t num) {
    uint32_t stack_top_addr = 0xFFFFFFFF;
    const BootConfig_t* Config = BootGetConfig(num);
    if(Config) {
        uint32_t* stack_top_addr_ptr = (uint32_t*)Config->fw_start_address;
        stack_top_addr = *stack_top_addr_ptr;
    }
    return stack_top_addr;
}

bool boot_proc_one(uint8_t num) { return true; }

static bool BootIsValidConfig(const BootConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = arm_cortex_check_arm_vector_table(Config->fw_start_address);
        if(res) {
        } else {
#ifdef HAS_LOG
            LOG_ERROR(BOOT, "NoVectorTable:0x%08x", Config->fw_start_address);
#endif
        }

        if(Config->name) {

        } else {
#ifdef HAS_LOG
            LOG_ERROR(BOOT, "Boot%u,NoName", Config->num);
#endif
        }
    }
    return res;
}

bool boot_stack_paint(const uint8_t num, FloatFixPoint_t* const stack_used) {
    bool res = false;
    BootHandle_t* Node = BootGetNode(num);
    if(Node) {
#ifdef HAS_CORE_EXT
        uint32_t exp_size = Node->stack_top_address - Node->stack_lim_address;
        if(stack_used) {
            *stack_used = core_stack_used(Node->stack_top_address, exp_size);
            res = true;
        }
#endif
    }
    return res;
}

bool boot_init_one(uint8_t num) {
    bool res = false;
    const BootConfig_t* Config = BootGetConfig(num);
    if(Config) {
#ifdef HAS_BOOT_DIAG
        LOG_WARNING(BOOT, "%s", BootConfigToStr(Config));
#endif
        res = BootIsValidConfig(Config);
        if(res) {
            BootHandle_t* Node = BootGetNode(num);
            if(Node) {
                Node->name = Config->name;
                Node->stack_top_address = Config->stack_top_address;
                Node->stack_lim_address = Config->stack_lim_address;
                Node->fw_start_address = Config->fw_start_address;
                Node->init = true;
#ifdef HAS_LOG
                LOG_INFO(BOOT, "INIT:%u ok", num);
#endif
            }
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(BOOT, BOOT, boot)
COMPONENT_PROC_PATTERT(BOOT, BOOT, boot)
