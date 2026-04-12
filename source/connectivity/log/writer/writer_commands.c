#include "writer_commands.h"

#include "convert.h"
#include "log.h"
#include "writer.h"


bool writer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = writer_diag();
    } else {
        LOG_ERROR(WRITER, "Usage: fdat");
    }

    return res;
}

bool writer_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = writer_mcal_init();
        if(false == res) {
            LOG_ERROR(WRITER, "Init" LOG_ER);
        } else {
            LOG_INFO(WRITER, "Init" LOG_OK);
        }
    }
    return res;
}
