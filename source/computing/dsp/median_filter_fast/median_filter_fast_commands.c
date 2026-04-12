#include "median_filter_fast_commands.h"

#include "convert.h"
#include "log.h"
#include "median_filter_fast.h"
#include "std_includes.h"

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
#ifdef HAS_FILE_PC
bool median_filter_fast_calc_frequency_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
    }
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = median_filter_fast_calc_frequency_response(num);
    } else {
        LOG_ERROR(MEDIAN_FILTER_FAST, "Usage: iifr num");
    }
    return res;
}

#endif

#ifdef HAS_FILE_PC
bool median_filter_fast_calc_frequency_response_norm_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 == argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = median_filter_fast_calc_frequency_response_norm(num);
    } else {
        LOG_ERROR(MEDIAN_FILTER_FAST, "Usage: iifrn num");
    }
    return res;
}
#endif

bool median_filter_fast_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = median_filter_fast_diag();
    } else {
        LOG_ERROR(MEDIAN_FILTER_FAST, "Usage: median_filter_fast");
    }
    return res;
}

bool median_filter_fast_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
    }

    if(res) {

    } else {
        LOG_ERROR(MEDIAN_FILTER_FAST, "Usage: iip In");
    }
    return res;
}
