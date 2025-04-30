#include "boot_manager.h"

#include "boot_manager_diag.h"
#include "log.h"

bool boot_manager_init(void) {
    bool res = true;
    LOG_WARNING(BOOT, "Init");
    res = boot_manager_diag();
    return res;
}
