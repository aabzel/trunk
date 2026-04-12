#include "sw_sd_card_commands.h"

#include "convert.h"
#include "log.h"
#include "sw_sd_card.h"

bool sw_sd_card_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = sw_sd_card_diag();
    } else {
        LOG_ERROR(SW_SD_CARD, "Usage: fdat");
    }

    return res;
}

bool sw_sd_card_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = sw_sd_card_mcal_init();
        if(false == res) {
            LOG_ERROR(SW_SD_CARD, "Init" LOG_ER);
        } else {
            LOG_INFO(SW_SD_CARD, "Init" LOG_OK);
        }
    }
    return res;
}
