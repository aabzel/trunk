#include "max_heap_commands.h"

#include "convert.h"
#include "log.h"
#include "max_heap.h"

bool max_heap_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MAX_HEAP, res, "Num");
    }

    if(res) {
        res = max_heap_diag(num);
    } else {
        LOG_ERROR(MAX_HEAP, "Usage: hxd Num");
    }

    return res;
}

bool max_heap_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = max_heap_mcal_init();
        log_info_res(MAX_HEAP, res, "Init");
    }
    return res;
}

bool max_heap_push_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t new_value = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MAX_HEAP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &new_value);
        log_info_res(MAX_HEAP, res, "InVal");
    }

    if(res) {
        LOG_INFO(MAX_HEAP, "AddNewValue:%d", new_value);
        res = max_heap_push_h(num, new_value);
        log_info_res(MAX_HEAP, res, "Push");
    }

    return res;
}

bool max_heap_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MAX_HEAP, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = max_heap_pull_h(num, &new_value);
        log_info_res(MAX_HEAP, res, "Push");
        if(res) {
            LOG_INFO(MAX_HEAP, "GetValue:%d", new_value);
        }
    }
    return res;
}

bool max_heap_peek_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MAX_HEAP, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = max_heap_peek_h(num, &new_value);
        log_info_res(MAX_HEAP, res, "Peek");
        if(res) {
            LOG_INFO(MAX_HEAP, "PeekValue:%d", new_value);
        }
    }

    return res;
}
