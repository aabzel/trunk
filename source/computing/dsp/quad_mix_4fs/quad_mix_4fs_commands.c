#include "quad_mix_4fs_commands.h"

#include "convert.h"
#include "quad_mix_4fs.h"
#include "log.h"

bool quad_mix_4fs_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res) {
        res = quad_mix_4fs_init_one(num);
    } else {
        LOG_ERROR(QUAD_MIX_4FS, "Usage: fis Num M FcHz");
    }

    return res;
}

bool quad_mix_4fs_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = quad_mix_4fs_diag(num);
    } else {
        LOG_ERROR(QUAD_MIX_4FS, "Usage: fis Num M FcHz");
    }
    return res;
}
