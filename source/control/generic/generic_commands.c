#include "generic_commands.h"

#include "generic.h"
#include "log.h"

bool generic_jump_to_bootloader_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = generic_jump_to_bootloader();
        if(res) {
            LOG_ERROR(BOOT, "JumpBootOK");
        } else {
            LOG_ERROR(BOOT, "JumpBootErr");
        }
    }else {
        LOG_ERROR(BOOT, "Usage: jb");
    }
    return res;
}
