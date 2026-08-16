#include "local_oscillator_commands.h"

#include "convert.h"
#include "local_oscillator_mcal.h"
#include "log.h"

bool local_oscillator_calc_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t num = 0;
    int32_t phase = 0;

    if(1 <= argc) {
        res = try_str2int32(argv[0], &num);
        log_info_res(LOCAL_OSCILLATOR, res, "Num");
    }

    if(1 <= argc) {
        res = try_str2int32(argv[0], &phase);
        log_info_res(LOCAL_OSCILLATOR, res, "phase");
    }

    if(res) {
        int32_t cos4 = cos4_int(num, phase);
        int32_t sin4 = sin4_int(num, phase);
        LOG_INFO(LOCAL_OSCILLATOR, "n:%d,pha:%d,cos4:%d", num, phase, cos4);
        LOG_INFO(LOCAL_OSCILLATOR, "n:%d,pha:%d,sin4:%d", num, phase, sin4);
    }

    return res;
}
