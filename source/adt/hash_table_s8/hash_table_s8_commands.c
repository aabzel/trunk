#include "hash_table_s8_commands.h"

#include "convert.h"
#include "hash_table_s8.h"
#include "log.h"

bool hash_table_s8_diag_command(int8_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }
    if(res) {
        res = hash_table_s8_diag();
    } else {
        LOG_ERROR(HASH_TABLE_S8, "Usage: fdat");
    }

    return res;
}

bool hash_table_s8_init_command(int8_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = hash_table_s8_mcal_init();
        if(false == res) {
            LOG_ERROR(HASH_TABLE_S8, "Init" LOG_ER);
        } else {
            LOG_INFO(HASH_TABLE_S8, "Init" LOG_OK);
        }
    }
    return res;
}

bool hash_table_s8_pull_command(int8_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE_S8, res, "Num");
    }

    if(res) {
        int8_t new_value = 0;
        res = hash_table_s8_pull(num, &new_value);
        log_info_res(HASH_TABLE_S8, res, "Push");
        if(res) {
            LOG_INFO(HASH_TABLE_S8, "GetValue:%d", new_value);
        }
    }
    return res;
}

bool hash_table_s8_push_command(int8_t argc, char* argv[]) {
    bool res = false;
    int8_t new_value = 0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE_S8, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2int8(argv[1], &new_value);
        log_info_res(HASH_TABLE_S8, res, "InVal");
    }

    if(res) {
        LOG_INFO(HASH_TABLE_S8, "AddNewValue:%d", new_value);
        res = hash_table_s8_push(num, new_value);
        log_info_res(HASH_TABLE_S8, res, "Push");
    }

    return res;
}

bool hash_table_s8_check_command(int8_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(HASH_TABLE_S8, res, "Num");
    }

    if(res) {
        int8_t new_value = 0;
        res = hash_table_s8_check(num, new_value);
        log_info_res(HASH_TABLE_S8, res, "Peek");
        if(res) {
            LOG_INFO(HASH_TABLE_S8, "Value:%d,Present", new_value);
        }
    }

    return res;
}
