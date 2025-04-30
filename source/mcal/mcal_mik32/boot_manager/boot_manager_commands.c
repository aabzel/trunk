#include "boot_manager_commands.h"

#include "boot_manager.h"
#include "log.h"

bool boot_manager_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_manager_diag();
    return res;
}
