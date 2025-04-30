#include "dma_custom_commands.h"

#include <stdio.h>

#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "dma_mcal.h"
#include "log.h"
#include "microcontroller_const.h"
#include "str_utils.h"

bool dma_diag_custom_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr adc %s", argv[0]);
        }
    }

    if(res) {
        res = dma_diag_custom(num);
    } else {
        LOG_ERROR(SYS, "Usage: ddc Num");
    }
    return res;
}

bool dma_channel_diag_custom_command(int32_t argc, char* argv[]) {
    bool res = true;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = dma_channel_diag_custom();
    } else {
        LOG_ERROR(SYS, "Usage: dcc");
    }
    return res;
}
