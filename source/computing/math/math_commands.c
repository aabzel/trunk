#include "math_commands.h"

#include <stdio.h>
#include <string.h>

#include "log.h"
#include "vector_diag.h"

bool math_vector_angle_command(int32_t argc, char* argv[]) {
    bool res = false;

    char keyWord1[20] = "";
    char keyWord2[20] = "";

    if(0 <= argc) {
        strncpy(keyWord1, "", sizeof(keyWord1));
        strncpy(keyWord2, "", sizeof(keyWord2));
        res = true;
    }

    if(1 <= argc) {
        strncpy(keyWord1, argv[0], sizeof(keyWord1));
        res = true;
    }

    if(2 <= argc) {
        strncpy(keyWord2, argv[1], sizeof(keyWord2));
        res = true;
    }

    if(2 < argc) {
        LOG_ERROR(MATH, "Usage: mva keyWord");
    }

    if(res) {
#ifdef HAS_MATH_VECTOR
        res = math_vector_angle_diag(keyWord1, keyWord2);
#endif
    }
    return res;
}
