#include "pc_commands.h"

#include <stdlib.h>

bool exit_command(int32_t argc, char* argv[]) {
    bool res = false;
    exit(1);
    res = true;
    return res;
}
