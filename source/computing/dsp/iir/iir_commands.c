#include "iir_commands.h"

#include <stdbool.h>
#include <stdint.h>

#include "convert.h"
#include "iir.h"
#include "log.h"

/*iilp 1 1
iilp 1 0.001
iilp 1 20
iilp 1 0.1
iilp 1 1
iilp 1 10  1193Hz
iilp 1 100  114Hz
iilp 4 1000 11Hz

iilp 1 5000  2Hz
iilp 1 10000  1Hz
iilp 1 2  hi pass

 */
bool iir_lowpas_1st_order_command(int32_t argc, char* argv[]) {
    bool res = false;
    double k = 0.0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &k);
    }

    if(res) {
        if(2 == argc) {
            res = iir_lowpas_1st_order(num, k);
            log_res(IIR, res, "LopPas,1st,Order");
        }
    } else {
        LOG_ERROR(IIR, "Usage: iilp num k");
    }

    return res;
}

bool iir_lowpas_1st_order_v2_command(int32_t argc, char* argv[]) {
    bool res = false;
    double x = 0.0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &x);
    }

    if(res) {
        if(2 == argc) {
            res = iir_lowpas_1st_order_v2(num, x);
            log_res(IIR, res, "LopPas,1st,Order,V2");
        }
    } else {
        LOG_ERROR(IIR, "Usage: iilp2 num x");
    }

    return res;
}

bool iir_calc_frequency_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = iir_calc_frequency_response(num);
    } else {
        LOG_ERROR(IIR, "Usage: iifr num");
    }
    return res;
}

bool iir_calc_frequency_response_norm_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = iir_calc_frequency_response_norm(num);
    } else {
        LOG_ERROR(IIR, "Usage: iifrn num");
    }
    return res;
}

bool iir_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = iir_diag();
    } else {
        LOG_ERROR(IIR, "Usage: iir");
    }
    return res;
}

bool iir_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
    }

    if(res) {

    } else {
        LOG_ERROR(IIR, "Usage: iip In");
    }
    return res;
}
