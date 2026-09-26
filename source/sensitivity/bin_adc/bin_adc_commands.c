#include "bin_adc_commands.h"

#include "convert.h"
#include "log.h"
#include "bin_adc_mcal.h"

bool bin_adc_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_ADC, res, "Num");
    }

    if(res) {
        res = bin_adc_raw_reg_diag(num);
        log_info_res(BIN_ADC, res, "RegMap");
    } else {
        LOG_ERROR(BIN_ADC, "Usage: bin_adcrr num");
    }
    return res;
}

bool bin_adc_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_ADC, res, "Num");
    }

    if(res) {
        res = bin_adc_diag_one(num);
        log_info_res(BIN_ADC, res, "Diag");

        res = bin_adc_diag();
        log_info_res(BIN_ADC, res, "Diag");
    } else {
        LOG_ERROR(BIN_ADC, "Usage: fdat");
    }

    return res;
}

bool bin_adc_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_ADC, res, "Num");
    }

    if(0 == argc) {
        res = bin_adc_mcal_init();
        log_info_res(BIN_ADC, res, "Init");
    }
    return res;
}

bool bin_adc_show_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        num = 1;
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BIN_ADC, res, "Num");
    }

    if(res) {
        res = bin_adc_show_sample(num);
        log_info_res(BIN_ADC, res, "showSample");
    }
    return res;
}


