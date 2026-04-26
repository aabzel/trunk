#include "gpio_dac_commands.h"

#include "convert.h"
#include "log.h"
#include "gpio_dac_mcal.h"


bool gpio_dac_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0 ;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GPIO_DAC, res, "Num");
    }

    if(res) {
        res = gpio_dac_diag_one(num);
        log_info_res(GPIO_DAC, res, "Diag");

        res = gpio_dac_diag();
        log_info_res(GPIO_DAC, res, "Diag");
    } else {
        LOG_ERROR(GPIO_DAC, "Usage: fdat");
    }

    return res;
}

bool gpio_dac_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0 ;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GPIO_DAC, res, "Num");
    }

    if(0 == argc) {
        res = gpio_dac_mcal_init();
        log_info_res(GPIO_DAC, res, "Init");
    }
    return res;
}
