#include "boot_commands.h"

#include "boot_driver.h"

bool boot_reboot_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_reboot();
    return res;
}

bool boot_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = boot_diag();
    return res;
}
