#include "iomux_custom_commands.h"

#include <stdint.h>

#include "convert.h"
#include "iomux_custom_diag.h"
#include "log.h"

bool iomux_diag_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = iomux_diag_reg_map();
    return res;
}
