#include "sw_nor_flash_commands.h"

#include "convert.h"
#include "log.h"
#include "sw_nor_flash.h"
#include "sw_nor_flash_diag.h"

bool sw_nor_flash_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = sw_nor_flash_diag();
    } else {
        LOG_ERROR(SW_NOR_FLASH, "Usage: fdat");
    }

    return res;
}

bool sw_nor_flash_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = sw_nor_flash_mcal_init();
        if(false == res) {
            LOG_ERROR(SW_NOR_FLASH, "Init" LOG_ER);
        } else {
            LOG_INFO(SW_NOR_FLASH, "Init" LOG_OK);
        }
    }
    return res;
}
