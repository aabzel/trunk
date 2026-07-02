#include "clock_custom_commands.h"

#include <inttypes.h>
#include <stdio.h>

//#include "clock_diag.h"
#include "clock_custom_diag.h"
#include "clock_mcal.h"
#include "convert.h"
#include "ctype.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller.h"
#include "stm32fx_hal_rcc.h"
#include "str_utils.h"
#include "timer_utils.h"

bool clock_custom_periph_diag_command(int32_t argc, char* argv[]) {
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

    if(res) {
        res = true;
#ifdef HAS_CLOCK_DIAG
        res = periph_clock_diag(keyWord1, keyWord2);
#endif
    } else {
        LOG_ERROR(CLK, "Usage: ccpd keyWord");
    }
    return res;
}

bool clock_custom_core_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = clock_custom_diag();
    } else {
        LOG_ERROR(CLK, "Usage: cccd");
    }
    return res;
}
