#include "bootloader.h"

#include "std_includes.h"
#include "flash_config.h"

#ifdef HAS_RISC_V
#include "rv32imc_driver.h"
#endif

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_NVIC
#include "nvic_drv.h"
#endif

#ifdef HAS_CRC32
#include "crc32.h"
#endif

#ifdef HAS_CLOCK
#include "clock.h"
#endif

#include "boot_diag.h"
#include "boot_driver.h"
#include "sys_config_common.h"

#ifdef HAS_SYSTICK
#include "systick_mcal.h"
#endif /*HAS_SYSTICK*/

#ifdef HAS_LED
#include "led_drv.h"
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
#include "watchdog_mcal.h"
#endif
#include "sys_config.h"

static bool is_valid_bootloader_cmd(uint8_t command) {
    bool res = false;
    switch(command) {
    case BOOT_CMD_LAUNCH_APP:
    case BOOT_CMD_LAUNCH_APP_CRC:
    case BOOT_CMD_STAY_ON:
        res = true;
        break;
    default:
        res = false;
        break;
    }
    return res;
}

static bool bootloader_try_app_plane(void) {
    bool res = false;
    bool out_res = true;
    (void)out_res;
    BootLoaderInstance.app_start_address = APP_START_ADDRESS;
#ifdef HAS_PARAM
    LOAD_PARAM(BOOTLOADER, PAR_ID_APP_START, BootLoaderInstance.app_start_address, APP_START_ADDRESS);
#endif

#ifdef HAS_LOG
    LOG_INFO(BOOTLOADER, "TryBootAddr 0x%08x", BootLoaderInstance.app_start_address);
#endif

    res = is_flash_addr(BootLoaderInstance.app_start_address);
    if(res) {
        res = boot_jump_to_code(BootLoaderInstance.app_start_address);
    } else {
#ifdef HAS_LOG
        LOG_ERROR(BOOTLOADER, "NotFlashAddr 0x%08x", BootLoaderInstance.app_start_address);
#endif
    }

    return res;
}

static bool bootloader_try_app_crc(void) {
    bool res = false, out_res = true;
    // uint32_t app_crc32_calc = 0;

    BootLoaderInstance.app_start_address = APP_START_ADDRESS;
    BootLoaderInstance.app_len = 0;
    BootLoaderInstance.app_crc32.read = 0;
    BootLoaderInstance.app_crc32.calc = 0;

#ifdef HAS_PARAM
    LOAD_PARAM(BOOTLOADER, PAR_ID_APP_START, BootLoaderInstance.app_start_address, APP_START_ADDRESS);
    LOAD_PARAM(BOOTLOADER, PAR_ID_APP_LEN, BootLoaderInstance.app_len, 0);
    LOAD_PARAM(BOOTLOADER, PAR_ID_APP_CRC32, BootLoaderInstance.app_crc32.read, 0);
#endif /*HAS_PARAM*/

    if(BootLoaderInstance.app_len) {
        if(is_flash_addr(BootLoaderInstance.app_start_address)) {
#ifdef HAS_LOG
            LOG_INFO(BOOTLOADER, "AppAddr:0x%08x,Len:%u byte", BootLoaderInstance.app_start_address,
                     BootLoaderInstance.app_len);
#endif
            BootLoaderInstance.app_crc32.calc =
                crc32_calc((uint8_t*)(BootLoaderInstance.app_start_address), BootLoaderInstance.app_len);
        }

        if(out_res) {
            if(BootLoaderInstance.app_crc32.read == BootLoaderInstance.app_crc32.calc) {
#ifdef HAS_LOG
                LOG_INFO(BOOTLOADER, "AppCRC32Ok! 0x%08x", BootLoaderInstance.app_crc32.read);
#endif
                res = bootloader_try_app_plane();
            } else {
#ifdef HAS_LOG
                LOG_ERROR(BOOTLOADER, "AppCRC32_UnMatch,read:0x%08x,calc:0x%08x", BootLoaderInstance.app_crc32.read,
                          BootLoaderInstance.app_crc32.calc);
#endif
            }
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(BOOTLOADER, "ZeroAppLen");
#endif
    }

    return res;
}

bool bootloader_proc(void) {
    bool res = false;
    BootCmd_t command = BOOT_CMD_ENDEF;
#ifdef HAS_LOG
    LOG_DEBUG(BOOTLOADER, "TryBootApp...");
#endif

    res = false;
#ifdef HAS_PARAM
    res = param_get(PAR_ID_BOOT_CMD, (uint8_t*)&command);
    if(false == res) {
        command = BOOT_CMD_LAUNCH_APP;
        LOG_ERROR(BOOTLOADER, "LackOfBootCmd ParamId: %u", PAR_ID_BOOT_CMD);
    }
#endif /*HAS_PARAM*/
#ifdef HAS_BOOTLOADER_DIAG
    LOG_DEBUG(BOOTLOADER, "BootCmd:%u=%s", command, BootCmdToStr(command));
#endif

    switch(command) {
    case BOOT_CMD_STACK_ERROR_STAY_ON:
    case BOOT_CMD_START_ERROR_STAY_ON:
    case BOOT_CMD_STAY_ON:
        res = true;
        break;
    case BOOT_CMD_LAUNCH_APP_CRC:
        res = bootloader_try_app_crc();
        break;
    case BOOT_CMD_LAUNCH_APP:
        res = bootloader_try_app_plane();
        break;
    default:
        res = false;
        break;
    }

    return res;
}

bool bootloader_launch_app(BootCmd_t command) {
    bool res = false;
    res = is_valid_bootloader_cmd(command);
    if(res) {
#ifdef HAS_FLASH_FS
        res = flash_fs_set(PAR_ID_BOOT_CMD, (uint8_t*)&command, sizeof(command));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(BOOTLOADER, "Error set boot cmd");
#endif
        }
#endif /*HAS_FLASH_FS*/
#ifdef HAS_FLASH_FS
        uint8_t bootloader_cnt = 0;
        res = flash_fs_set(PAR_ID_BOOT_CNT, (uint8_t*)&bootloader_cnt, sizeof(bootloader_cnt));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(BOOTLOADER, "ErrorResetBootCnt");
#endif
        }
#endif /*HAS_FLASH_FS*/

#ifdef HAS_FLASH_FS
        uint32_t start_addr = APP_START_ADDRESS;
        res = flash_fs_set(PAR_ID_APP_START, (uint8_t*)&start_addr, sizeof(start_addr));
        if(false == res) {
#ifdef HAS_LOG
            LOG_ERROR(BOOTLOADER, "ErrorSetStartAddr");
#endif
        }
#endif /*HAS_FLASH_FS*/

        core_reboot();
#ifdef HAS_LOG
        log_res(BOOTLOADER, res, "ReBoot");
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(BOOTLOADER, "InvalidBootCmd");
#endif
    }
    return res;
}

bool bootloader_reboot(void) {
    bool res = false;
#ifdef HAS_ARM
    res = boot_jump_to_code_arm(ROM_START);
#endif

#ifdef HAS_RISC_V
    res = rv32imc_boot_addr(EXT_ROM_START);
#endif
    return res;
}

/*Application Hang on protection*/
bool bootloader_init(void) {
    bool res = false;
#ifdef HAS_FLASH_FS
    uint16_t real_len = 0;
    uint8_t bootloader_cnt = 0;
#ifdef HAS_GENERIC
    fine_start_event = false;
#endif

    res = false;
    res = flash_fs_get(PAR_ID_BOOT_CNT, (uint8_t*)&bootloader_cnt, sizeof(bootloader_cnt), &real_len);
    if(res && (sizeof(bootloader_cnt) == real_len)) {
        LOG_INFO(BOOTLOADER, "launch try %u", bootloader_cnt);

        bootloader_cnt++;
        res = flash_fs_set(PAR_ID_BOOT_CNT, (uint8_t*)&bootloader_cnt, sizeof(bootloader_cnt));
        if(false == res) {
            LOG_ERROR(BOOTLOADER, "Err update boot cnt");
        }

        if(APP_LAYNCH_TRY < bootloader_cnt) {
            LOG_ERROR(BOOTLOADER, "Application seems hang on");
            BootCmd_t command = BOOT_CMD_STAY_ON;
            res = flash_fs_set(PAR_ID_BOOT_CMD, (uint8_t*)&command, sizeof(command));
            if(false == res) {
                LOG_ERROR(BOOTLOADER, "Err send boot cmd");
            } else {
                LOG_DEBUG(BOOTLOADER, "Send boot StayOn OK");
                res = true;
            }
        }
    } else {
        res = true;
        bootloader_cnt = 0;
        res = flash_fs_set(PAR_ID_BOOT_CNT, (uint8_t*)&bootloader_cnt, sizeof(bootloader_cnt));
        if(false == res) {
            LOG_ERROR(BOOTLOADER, "Err init boot cnt");
        }
    }
    // res=bootloader_set_indicate() && res;
    // LOAD_PARAM(BOOTLOADER, PAR_ID_APP_START, , APP_START_ADDRESS) ;
#endif
    return res;
}

bool bootloader_erase_app(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_WARNING(BOOTLOADER, "ErraseApp");
#endif
    uint32_t cnt = flash_get_sector_cnt();
    uint32_t s = 0;
    for(s = 0; s < cnt; s++) {
        if(MEM_CONTENT_GENERIC == FlashSectorConfig[s].content) {
#ifdef HAS_FLASH_WRITE
            res = flash_mcal_erase(FlashSectorConfig[s].start, FlashSectorConfig[s].size);
            if(res) {
#ifdef HAS_LOG
                uint32_t end_addr = FlashSectorConfig[s].start + FlashSectorConfig[s].size;
                LOG_WARNING(BOOTLOADER, "EraseOk 0x%x...0x%x", FlashSectorConfig[s].start, end_addr);
#endif
            } else {
#ifdef HAS_LOG
                LOG_ERROR(BOOTLOADER, "EraseErr");
#endif
                res = false;
            }
#endif
        }
    }
    return res;
}
