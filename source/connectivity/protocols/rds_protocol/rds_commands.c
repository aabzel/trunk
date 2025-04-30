#include "rds_commands.h"

#include <stdbool.h>
#include <stdio.h>


#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "rds_diag.h"
#include "rds_protocol.h"


bool rds_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }
    if(res) {
        res = rds_protocol_init();
    } else {
        LOG_ERROR(RDS, "Usage: rdsi");
    }
    return res;
}

bool rds_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    }

    if(res) {
        res = rds_diag();
    } else {
        LOG_ERROR(RDS, "Usage: rdsd");
    }
    return res;
}

bool rds_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint16_t Word[4] = {0, 0, 0, 0};
    if(4 == argc) {
        uint32_t i = 0;
        for(i = 0; i < 4; i++) {
            res = try_str2uint16(argv[i], &Word[i]);
            if(false == res) {
                LOG_ERROR(SYS, "ParseErr Word%u %s", i, argv[i]);
            }
        }
    }

    if(res) {
        res = rds_proc_message(Word);
    } else {
        LOG_ERROR(RDS, "Usage: rdsp Word1 Word2 Word3 Word4");
    }
    return res;
}
