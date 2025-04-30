#include "boot_diag.h"

#include <stdio.h>

#include "boot_driver.h"
#include "core_driver.h"
#include "flash_mcal.h"
#include "log.h"

const char* BootCmdToStr(const BootCmd_t boot_cmd) {
    const char* name = "?";
    switch(boot_cmd) {
    case BOOT_CMD_LAUNCH_APP:
        name = "launch";
        break;
    case BOOT_CMD_LAUNCH_APP_CRC:
        name = "LaunchCrc";
        break;
    case BOOT_CMD_STAY_ON:
        name = "Stay";
        break;
    case BOOT_CMD_ENDEF:
        name = "UnDef";
        break;
    case BOOT_CMD_STACK_ERROR_STAY_ON:
        name = "StackStay";
        break;
    case BOOT_CMD_START_ERROR_STAY_ON:
        name = "StartStay";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

char* AppSize2str(uint32_t size) {
    snprintf(text, sizeof(text), "%6.2f kByte", ((double)(size)) / 1024.0);
    return text;
}

bool boot_diag(void) {
    bool res = false;
#ifdef HAS_ARM
    LOG_INFO(SYS, "BootAddr:0x%08x", BOOT_START_ADDRESS);
    uint32_t top_boot_stack_val = 0;
    top_boot_stack_val = *((uint32_t*)(BOOT_START_ADDRESS));
    res = is_ram_addr(top_boot_stack_val);
    if(res) {
        LOG_INFO(SYS, "BootStackEnd:0x%08x ", top_boot_stack_val);
    } else {
        LOG_ERROR(SYS, "BootStackEnd:0x%08x ", top_boot_stack_val);
    }
    uint32_t boot_reset_hand_addr = *((uint32_t*)(BOOT_START_ADDRESS + 4));
    res = is_flash_addr(boot_reset_hand_addr);
    if(res) {
        LOG_INFO(SYS, "BootResetHandler:0x%08x ", boot_reset_hand_addr);
    } else {
        LOG_ERROR(SYS, "BootResetHandler:0x%08x ", boot_reset_hand_addr);
    }
#endif
    return res;
}
