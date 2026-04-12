#include "hash_table_commands.h"

#include "convert.h"
#include "hash_table.h"
#include "log.h"

bool hash_table_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = hash_table_diag();
    } else {
        LOG_ERROR(HASH_TABLE, "Usage: fdat");
    }

    return res;
}

bool hash_table_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = hash_table_mcal_init();
        if(false == res) {
            LOG_ERROR(HASH_TABLE, "Init" LOG_ER);
        } else {
            LOG_INFO(HASH_TABLE, "Init" LOG_OK);
        }
    }
    return res;
}

bool hash_table_pull_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = hash_table_pull(num, &new_value);
        log_info_res(HASH_TABLE, res, "Push");
        if(res) {
            LOG_INFO(HASH_TABLE, "GetValue:%d", new_value);
        }
    }
    return res;
}

bool hash_table_push_command(int32_t argc, char* argv[]) {
    bool res = false;
    int32_t new_value = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int32(argv[1], &new_value);
        log_info_res(HASH_TABLE, res, "InVal");
    }

    if(res) {
        LOG_INFO(HASH_TABLE, "AddNewValue:%d", new_value);
        res = hash_table_push(num, new_value);
        log_info_res(HASH_TABLE, res, "Push");
    }

    return res;
}

bool hash_table_peek_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE, res, "Num");
    }

    if(res) {
        int32_t new_value = 0;
        res = hash_table_peek(num, &new_value);
        log_info_res(HASH_TABLE, res, "Peek");
        if(res) {
            LOG_INFO(HASH_TABLE, "Value:%d,Present", new_value);
        }
    }

    return res;
}
