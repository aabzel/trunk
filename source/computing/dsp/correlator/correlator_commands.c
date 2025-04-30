#include "correlator_commands.h"

#include "std_includes.h"
#include "convert.h"
#include "correlator.h"
#include "log.h"


//psd 1
bool correlator_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(CORRELATOR, "Arg1 FreqErr %s", argv[0]);
        }
    }

    if(res) {
        res = correlator_diag(num);
        if(res) {
        } else {
            LOG_ERROR(CORRELATOR, "GenerateErr");
        }
    } else {
        LOG_ERROR(CORRELATOR, "Usage: cod Num");
    }
    return res;
}

