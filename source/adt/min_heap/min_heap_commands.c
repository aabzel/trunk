#include "min_heap_commands.h"

#include "convert.h"
#include "log.h"
#include "min_heap.h"

bool min_heap_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MIN_HEAP, res, "Num");
    }

    if(res) {
        res = min_heap_diag(num);
    } else {
        LOG_ERROR(MIN_HEAP, "Usage: hxd Num");
    }

    return res;
}

bool min_heap_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = min_heap_mcal_init();
        log_info_res(MIN_HEAP, res, "Init");
    }
    return res;
}

bool min_heap_push_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t new_value = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MIN_HEAP, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &new_value);
        log_info_res(MIN_HEAP, res, "InVal");
    }

    if(res) {
        LOG_INFO(MIN_HEAP, "AddNewValue:%d", new_value);
        res = min_heap_push_h(num, new_value);
        log_info_res(MIN_HEAP, res, "Push");
    }

    return res;
}

bool min_heap_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MIN_HEAP, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = min_heap_pull_h(num, &new_value);
        log_info_res(MIN_HEAP, res, "Push");
        if(res) {
            LOG_INFO(MIN_HEAP, "GetValue:%d", new_value);
        }
    }
    return res;
}

bool min_heap_peek_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(MIN_HEAP, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = min_heap_peek_h(num, &new_value);
        log_info_res(MIN_HEAP, res, "Peek");
        if(res) {
            LOG_INFO(MIN_HEAP, "PeekValue:%d", new_value);
        }
    }

    return res;
}
