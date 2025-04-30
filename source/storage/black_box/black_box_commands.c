#include "black_box_commands.h"

#include "log.h"
#include "black_box_diag.h"

bool black_box_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = black_box_diag();
    }
    return res;
}


