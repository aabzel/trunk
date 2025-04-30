#include "sw_nvram_commands.h"

#include <stdint.h>
#include <stdio.h>

#include "convert.h"
#include "debug_info.h"
#include "log.h"
#include "sw_nvram_config.h"
#include "sw_nvram_diag.h"
#include "sw_nvram.h"

#ifdef HAS_DOT
#include "dot.h"
#endif

#ifndef HAS_SW_NVRAM
#error "+ HAS_SW_NVRAM"
#endif

#ifndef HAS_SW_NVRAM_COMMANDS
#error "+ HAS_SW_NVRAM_COMMANDS"
#endif

bool sw_nvram_write_command(int32_t argc, char* argv[]){
    bool res = false;
    size_t size = 0;
    uint8_t buff[125 + 1];
    uint32_t address = 0;
    memset(buff, 0xFF, sizeof(buff));

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], buff, sizeof(buff), &size);
        if(false == res) {
            LOG_WARNING(NVRAM, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)buff, sizeof(buff), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res= sw_nvram_write(1,address, buff, size);
    }

    return res;
}

bool sw_nvram_read_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(res) {
        uint32_t size = 0;
        uint8_t data[256];
        memset(data,0,sizeof(data));
        res = sw_nvram_read(1,address, data, &size);
        if(res) {
            LOG_INFO(NVRAM, "ReadOk Addr %u size: %u", address, size);
        }else {
            LOG_ERROR(NVRAM, "ReadErr Addr %u", address);
        }
    }
    return res;
}

bool sw_nvram_delete_command(int32_t argc, char* argv[]){
    bool res = false;
    uint32_t address = 0;
    if(1 <= argc) {
        res = try_str2uint32(argv[0], &address);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr block_numb  %s", argv[0]);
        }
    }

    if(res) {
        res = sw_nvram_delete(1,address);
    }
    return res;
}

bool sw_nvram_init_command(int32_t argc, char* argv[]){
    bool res = false;
    res = sw_nvram_init();
    return res;
}

bool sw_nvram_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    (void)argv;
    if(0 == argc) {
        res = sw_nvram_diag();
    } else {
        LOG_ERROR(NVRAM, "Usage: nvrd");
    }
    return res;
}

bool sw_nvram_final_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    (void)argv;
    if(0 == argc) {
        res = sw_nvram_final_diag();
    } else {
        LOG_ERROR(NVRAM, "Usage: nvrfd");
    }
    return res;
}

bool sw_nvram_draw_tree_command(int32_t argc, char* argv[]){
    bool res = false;

    if(1==argc){
        res = true;
    }

    if(res) {
#ifdef HAS_DOT
        res= sw_nvram_draw_tree_compose(argv[0]);
#endif

    }
    return res;
}

bool sw_nvram_capacity_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num=1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr num  %s", argv[0]);
        }
    }

    if(res) {
        res= sw_nvram_capacity(num);
    }
    return res;
}

bool sw_nvram_toggle_page_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num=1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(NVRAM, "ParseErr num  %s", argv[0]);
        }
    }

    if(res) {
        res = false;
        NvRamItem_t* Node = NvRamGetNode(num);
        if(Node) {
            res= sw_nvram_toggle_page(Node);
        }
    }else{
        LOG_ERROR(NVRAM, "Usage: nvro num");
    }

	return res;
}
