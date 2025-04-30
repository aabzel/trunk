#include "super_cycle_commands.h"

#include "convert.h"
#include "log.h"
#include "super_cycle.h"
#include "super_cycle_diag.h"

bool super_cycle_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = super_cycle_init();
    }
    return res;
}

bool super_cycle_diag_command(int32_t argc, char* argv[]) {
    bool res = super_cycle_diag();
    return res;
}

bool super_cycle_iteration_sleep_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t iteration_sleep_ms = 5;

    if(1 <= argc) {
        res = try_str2int32(argv[0], &iteration_sleep_ms);
    }

    if(res) {
        SuperCycle.iteration_sleep_ms = iteration_sleep_ms;
        LOG_INFO(SUPER_CYCLE, "SetOk %d ms", iteration_sleep_ms);
    }

    return res;
}
