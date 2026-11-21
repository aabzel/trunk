#include "ili9341_commands.h"

#include "convert.h"
#include "log.h"
#include "array_diag.h"
#include "ili9341_mcal.h"

bool ili9341_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ILI9341, res, "Num");
    }

    if(res) {
        res = ili9341_raw_reg_diag(num);
        log_info_res(ILI9341, res, "RegMap");
    } else {
        LOG_ERROR(ILI9341, "Usage: ili9341rr num");
    }
    return res;
}

bool ili9341_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ILI9341, res, "Num");
    }

    if(res) {
        res = ili9341_diag_one(num);
        log_info_res(ILI9341, res, "Diag");

        res = ili9341_diag();
        log_info_res(ILI9341, res, "Diag");
    } else {
        LOG_ERROR(ILI9341, "Usage: fdat");
    }

    return res;
}

bool ili9341_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ILI9341, res, "Num");
    }

    if(0 == argc) {
        res = ili9341_mcal_init();
        log_info_res(ILI9341, res, "Init");
    }
    return res;
}

/*
  ili9341_cmd 1 0x36 0x48
  ili9341_cmd 1 0x36 0x28
 * */
bool ili9341_cmd_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t size = 0;
    uint8_t num = 0;
    uint8_t command = 0;
    uint8_t data[256]={0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ILI9341, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &command);
        log_info_res(ILI9341, res, "command");
    }

    if(3 <= argc) {
        res = try_str2array(argv[2], data, sizeof(data), &size);
        if(false == res) {
            LOG_WARNING(ILI9341, "ExtractHexArrayErr [%s]", argv[1]);
            snprintf((char*)data, sizeof(data), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res){
        res = ili9341_write_cmd_param(num, command, data, size);
    } else {
        LOG_ERROR(ILI9341, "Usage: ilic N Cmd Data");
    }
    return res;
}

bool ili9341_writer_set_command(int32_t argc, char* argv[]){
    bool res = false;
    res = ili9341_writer_set(1);
    return res;
}


bool ili9341_read_memory_command(int32_t argc, char* argv[]){
    bool res;
    uint32_t cnt=0;
    uint8_t num = 0;
    uint16_t words[128]={0};
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(ILI9341, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &cnt);
        log_info_res(ILI9341, res, "Cnt");
    }

    if(res) {
        res = ili9341_read_memory( num, words, cnt);
        array_u16_print(words, cnt);
    } else {
        LOG_ERROR(ILI9341, "Usage: ilirm N WordCnt");
    }
    return res;
}
