#include "pll_sim_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "pll_sim.h"
#include "log.h"

//psd 1
bool pll_sim_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;


    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(PLL_SIM, "Arg1 FreqErr %s", argv[0]);
        }
    }


    if(res) {
        res = pll_sim_diag(num);
        if(res) {
        	LOG_INFO(PLL_SIM, "OK");
        } else {
            LOG_ERROR(PLL_SIM, "GenerateErr");
        }
    } else {
        LOG_ERROR(PLL_SIM, "Usage: psd Num");
    }
    return res;
}

/*
 * psn 1 1
 * psn 1 2
 * psn 1 3
 * psn 1 4
 */
bool pll_sim_n_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t divider = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &divider);
    }

    if(res) {
        LOG_INFO(PLL_SIM, "divider:%u", divider);
        res = pll_sim_divider_set(num,divider);
    }

    return res;
}
