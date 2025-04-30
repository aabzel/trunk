#include "stack_frame_commands.h"

#include "log.h"
#include "stack_frame_diag.h"
#include "stack_frame.h"


bool stack_frame_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = stack_frame_init();
    } else {
        LOG_ERROR(STACK_FRAME, "Usage: stack_framei");
    }
    return res;
}

bool stack_frame_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    return res;
}


