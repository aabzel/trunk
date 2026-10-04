#include "gd5f1gq5_commands.h"

#include "array.h"
#include "array_diag.h"
#include "convert.h"
#include "gd5f1gq5_mcal.h"
#include "log.h"

bool gd5f1gq5_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(res) {
        res = gd5f1gq5_raw_reg_diag(num);
        log_info_res(GD5F1GQ5, res, "RegMap");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5f1gq5rr num");
    }
    return res;
}

bool gd5f1gq5_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(res) {
        res = gd5f1gq5_diag_one(num);
        log_info_res(GD5F1GQ5, res, "Diag");

        res = gd5f1gq5_diag();
        log_info_res(GD5F1GQ5, res, "Diag");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5d N");
    }

    return res;
}

bool gd5f1gq5_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(res) {
        res = gd5f1gq5_mcal_init();
        log_info_res(GD5F1GQ5, res, "Init");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5i N");
    }
    return res;
}

bool gd5f1gq5_get_features_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;

    if(0 <= argc) {
        res = true;
        num = 1;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(res) {
        res = gd5f1gq5_get_features_diag(num);
        log_info_res(GD5F1GQ5, res, "GetFeature");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5gf N");
    }
    return res;
}

bool gd5f1gq5_write_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    bool on_off = false;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_info_res(GD5F1GQ5, res, "WrEn");
    }

    if(res) {
        switch(argc) {
        case 1: {
            on_off = gd5f1gq5_get_write_enable(num);
            LOG_INFO(GD5F1GQ5, "N:%u,En:%u", num, on_off);
        } break;

        case 2: {
            res = gd5f1gq5_write_ctrl(num, on_off);
            log_info_res(GD5F1GQ5, res, "WrCtrl");
        } break;

        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5wc N En");
    }
    return res;
}

/*
 gd5rc 1 0x0 128
 gd5rc 1 0x1 128
 gd5rc 1 0x2 128
  gd5rc 1 0x3 128
    gd5rc 1 0x4 128
    gd5rc 1 0x5 32; gd5rc 1 0x6 32
 */
bool gd5f1gq5_read_cache_command(int32_t argc, char* argv[]) {

    bool res = false;
    uint8_t num = 1;
    uint8_t data[512] = {0};
    uint32_t address = 0;
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_info_res(GD5F1GQ5, res, "address");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[2], &size);
        log_info_res(GD5F1GQ5, res, "size");
    }

    if(res) {
        if(size <= sizeof(data)) {

            res = gd5f1gq5_read_from_cache(num, address, data, size);
            if(res) {
                LOG_INFO(GD5F1GQ5, "SZ:%u,Dat:%s", size, ArrayToStr(data, size));
            }
        }
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5rc N Addr size");
    }
    return res;
}

/*
gd5f1gq5_read_page 1 128 125
gd5f1gq5_read_page 1 2095104 2048
gd5f1gq5_read_page 1 2095104 512
*/
bool gd5f1gq5_read_page_command(int32_t argc, char* argv[]) {

    bool res = false;
    uint8_t num = 1;
    uint8_t data[512] = {0};
    uint32_t address = 0;
    uint32_t size = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_info_res(GD5F1GQ5, res, "address");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[2], &size);
        log_info_res(GD5F1GQ5, res, "size");
    }

    if(res) {
        res = false;
        if(size <= sizeof(data)) {
            res = gd5f1gq5_read_page(num, address, data, size);
            if(res) {
                LOG_INFO(GD5F1GQ5, "SZ:%u,Dat:%s", size, ArrayToStr(data, size));
            }
        }
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5rp N Addr Size");
    }
    return res;
}

bool gd5f1gq5_read_block_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t block_num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &block_num);
        log_info_res(GD5F1GQ5, res, "blockNum");
    }

    if(res) {
        res = false;
        res = gd5f1gq5_read_block(num, block_num);
        log_info_res(GD5F1GQ5, res, "readBlockNum");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5rb N BlkNum");
    }
    return res;
}

/*
ll gd5f1gq5 debug;gd5f1gq5_write_page 1 0x00020000 0

0x00020000
gd5f1gq5_read_page 1 0x00020000 500
gd5f1gq5_read_page 1 2097152 500
gd5f1gq5_read_page 1 2224128 500
2095104+2048=2097152
2095104+63*2048=2224128

*/
bool gd5f1gq5_write_page_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t data[2048] = {0};
    uint32_t address = GD5F1GQ5_PAGE_COUNT;
    uint8_t seed = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_info_res(GD5F1GQ5, res, "address");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[2], &seed);
        log_info_res(GD5F1GQ5, res, "seed");
    }

    if(res) {
        array_incr(data, sizeof(data), seed);
        LOG_INFO(GD5F1GQ5, "SZ:%u,Dat:%s", sizeof(data), ArrayToStr(data, sizeof(data)));
        res = gd5f1gq5_page_program(num, address, data, sizeof(data));
        log_info_res(GD5F1GQ5, res, "pageProgram");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5wp N Addr seed");
    }
    return res;
}

bool gd5f1gq5_read_to_cache_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_info_res(GD5F1GQ5, res, "address");
    }

    if(res) {
        res = gd5f1gq5_read_to_cache(num, address);
        log_info_res(GD5F1GQ5, res, "ReadToCache");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5rtc N Addr ");
    }
    return res;
}

/*
gd5f1gq5_block_erase 1 0
 */
bool gd5f1gq5_block_erase_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t address = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GD5F1GQ5, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &address);
        log_info_res(GD5F1GQ5, res, "address");
    }

    if(res) {
        res = gd5f1gq5_erase_block(num, address);
        log_info_res(GD5F1GQ5, res, "eraseBlock");
    } else {
        LOG_ERROR(GD5F1GQ5, "Usage: gd5be N Addr");
    }

    return res;
}
