#include "spifi_custom_commands.h"

#include <string.h>
#include <stdio.h>

#include "spifi_mcal.h"
#include "spifi_custom_diag.h"
#include "std_includes.h"
#include "convert.h"
#include "log.h"

bool spifi_custom_diag_command(int32_t argc, char* argv[]){
    bool res = false ;
    res = spifi_custom_diag();
    return res;
}

bool spifi_diag_low_level_command(int32_t argc, char* argv[]){
    bool res = false ;
    res = spifi_diag_low_level();
    log_res(SPIFI, res, "DiagLL");
    return res;
}


bool spifi_raw_reg_command(int32_t argc, char* argv[]){
    bool res = false ;
    res = spifi_raw_reg();
    log_res(SPIFI, res, "RawDiag");
    return res;
}

bool spifi_reset_command(int32_t argc, char* argv[]){
    bool res = false ;
    res = spifi_reset(0);
    log_res(SPIFI, res, "Reset");
    return res;
}

bool spifi_page_program_command(int32_t argc, char* argv[]){
    bool res = false ;
    uint32_t byte_address = 0 ;
    uint8_t wrData[256] = {0};
    uint32_t size =  0;

    if(1 <= argc) {
        res = try_str2uint32(argv[0], &byte_address);
    }

    if(2 <= argc) {
        res = try_str2array(argv[1], wrData, sizeof(wrData), &size);
        if(false == res) {
            LOG_WARNING(UART, "ExtractHexArrayErr  [%s]", argv[1]);
            snprintf((char*)wrData, sizeof(wrData), "%s", argv[1]);
            size = strlen(argv[1]);
            res = true;
        }
    }

    if(res) {
        res = spifi_page_program(1, byte_address, wrData, size);
        log_res(SPIFI, res, "PageProgram");
    }else {
        LOG_ERROR(SPIFI, "Usage: sfpp hex_string");
    }

    return res;
}
