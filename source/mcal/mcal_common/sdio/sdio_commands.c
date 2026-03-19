#include "sdio_commands.h"

#include "convert.h"
#include "log.h"
#include "sdio_mcal.h"

bool sdio_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LG_SDIO, res, "Num");
    }

    if(res) {
        res = sdio_raw_reg_diag(num);
        log_info_res(LG_SDIO, res, "RegMap");
    } else {
        LOG_ERROR(LG_SDIO, "Usage: sdiorr num");
    }
    return res;
}

bool sdio_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = sdio_diag();
    } else {
        LOG_ERROR(LG_SDIO, "Usage: fdat");
    }

    return res;
}

bool sdio_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = sdio_mcal_init();
        if(false == res) {
            LOG_ERROR(LG_SDIO, "Init" LOG_ER);
        } else {
            LOG_INFO(LG_SDIO, "Init" LOG_OK);
        }
    }
    return res;
}
