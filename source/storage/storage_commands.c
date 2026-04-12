#include "storage_commands.h"

#include <stdio.h>
#include <stdlib.h>

#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "std_includes.h"
#include "str_utils.h"
#include "table_utils.h"
#include "writer_config.h"

bool malloc_try_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &size);
        log_res(STORAGE, res, "Size");
    }

    if(res) {
        res = false;
        volatile uint8_t* data = (uint8_t*)malloc(size);
        if(data) {
            LOG_INFO(STORAGE, "Malloc:%u Byte,Ok,Addr:0x%08p", size, data);
            memset(data, 0x44, size);
            free(data);
            LOG_INFO(STORAGE, "Free%u,Byte,Ok", size);
            res = true;
        } else {
            LOG_ERROR(STORAGE, "Malloc:%u Byte,Err", size);
        }
    } else {
        LOG_ERROR(STORAGE, "Usage: malloc size");
    }

    return res;
}
