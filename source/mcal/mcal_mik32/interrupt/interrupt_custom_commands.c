#include "interrupt_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "interrupt_custom_diag.h"
#include "interrupt_diag.h"
#include "log.h"
#include "mik32_hal.h"
#include "str_utils.h"
#include "sys_config.h"
#include "table_utils.h"
#include "writer_config.h"

#ifndef HAS_INTERRUPT_COMMANDS
#error "+HAS_INTERRUPT_COMMANDS"
#endif /*HAS_INTERRUPT_COMMANDS*/

bool interrupt_custom_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool interrupt_custom_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool interrupt_custom_enable_irq_command(int32_t argc, char* argv[]) {
    bool res = false;
    return res;
}

bool interrupt_custom_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    char keyWord1[20] = "";
    char keyWord2[20] = "";
    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }
    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }
    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(SYS, "Usage: id keyWord");
    }
    if(res) {
        res = interrupt_diag(keyWord1, keyWord2);
    }
    return res;
}

bool interrupt_custom_enable_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}

bool interrupt_raw_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = interrupt_raw_reg();
    return res;
}
