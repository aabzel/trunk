#include "erm_commands.h"

#include "convert.h"
#include "log.h"
#include "erm_mcal.h"

bool erm_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    res = erm_diag();

    return res;
}


bool erm_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }
    if(res) {
        res = erm_init_one(num);
    }
    return res;
}
