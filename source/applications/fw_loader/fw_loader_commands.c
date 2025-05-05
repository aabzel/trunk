#include "fw_loader_commands.h"

#include "string.h"

#include "convert.h"
#include "fw_loader.h"
#include "log.h"
#include "fw_loader_diag.h"

bool fw_loader_chirp_correlation_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0 ;
    char file_name[100] = "";
    if(0 == argc) {
        res = true;
    } else {
    }

    if ( 1<= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        LOG_INFO(FW_LOADER, "argv0 [%s]", argv[1]);
        strcpy(file_name, argv[1]);
        LOG_INFO(FW_LOADER, "FileName:[%s]", file_name);
        res = true;
    }

    if(res) {
        res = fw_loader_chirp_correlation(num, file_name);
    } else {
        LOG_ERROR(FW_LOADER, "Usage: scc Num File");
    }
    return res;
}


bool cmd_fw_loader_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(FW_LOADER, "Usage: sd");
    }

    res = fw_loader_diag();
    return res;
}


/*
sc rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 fw_loader_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 */
bool fw_loader_convolution_command(int32_t argc, char* argv[]){
    bool res = false;
    if(2 <= argc) {
    	LOG_INFO(FW_LOADER, "0:[%s]", argv[0]);
    	LOG_INFO(FW_LOADER, "1:[%s]", argv[1]);
        res = fw_loader_convolution( argv[0], argv[1]);
        log_res(FW_LOADER ,res, "Convolution");
    } else {
        LOG_ERROR(FW_LOADER, "Usage: sñ Rec Pulse");
    }
    return res;
}
