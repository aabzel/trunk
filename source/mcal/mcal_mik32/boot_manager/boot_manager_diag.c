#include "boot_manager_diag.h"

#include <stdbool.h>

#include "boot_manager_types.h"
#include "log.h"
#include "mcu32_memory_map.h"

const char* BootStrToStr(const BootManagerSrc_t boot_src) {
    const char* name = "?";
    switch(boot_src) {
    case BOOT_MANAGER_SRC_EEPROM:
        name = "EEPROM";
        break;
    case BOOT_MANAGER_SRC_RAM:
        name = "RAM";
        break;
    case BOOT_MANAGER_SRC_SPIFI:
        name = "SPIFI";
        break;
    default:
        name = "??";
        break;
    }
    return name;
}

bool BootManagerRegBootDiag(BootManagerRegBoot_t* const Reg) {
    bool res = false;
    if(Reg) {
        LOG_WARNING(BOOT, "BOOT:0x%x", Reg->dword);
        LOG_INFO(BOOT, "Src:0x%x=%s", Reg->boot_mode, BootStrToStr(Reg->boot_mode));
        res = true;
    }
    return res;
}

bool boot_manager_diag(void) {
    bool res = true;
    BootManagerRegBoot_t* RegBoot = (BootManagerRegBoot_t*)BOOT_MANAGER_BASE_ADDRESS;
    LOG_WARNING(BOOT, "BootSrc:%s", BootStrToStr(RegBoot->boot_mode));
    return res;
}
