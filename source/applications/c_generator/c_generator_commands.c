#include "c_generator_commands.h"

#include "c_generator.h"
#include "c_generator_diag.h"
#include "cli_diag.h"
#include "convert.h"
#include "log.h"

bool c_generator_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = c_generator_diag();
    } else {
        LOG_ERROR(C_GENERATOR, "Usage: cgd");
    }
    return res;
}

bool c_generator_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 <= argc) {
        res = true;
    }

    if(res) {
    } else {
        LOG_ERROR(C_GENERATOR, "Usage: cgr");
    }
    return res;
}

bool c_generator_function_cap_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(1 == argc) {
        res = true;
    }

    if(res) {
        res = c_generator_function_cap(argv[0]);
    } else {
        LOG_ERROR(C_GENERATOR, "Usage: cgf FunctionName");
    }
    return res;
}
