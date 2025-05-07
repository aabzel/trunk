#include "fw_loader_commands.h"

#include "string.h"

#include "convert.h"
#include "fw_loader.h"
#include "log.h"
#include "fw_loader_diag.h"

bool fw_loader_ping_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0 ;
    if(0 == argc) {
        res = true;
    } else {
    }

    if ( 1<= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(FW_LOADER ,res, "Num");
    }

    if(res) {
        res = fw_loader_ping(num);
        log_res(FW_LOADER ,res, "Ping");
    } else {
        LOG_ERROR(FW_LOADER, "Usage: fwp Num");
    }
    return res;
}


bool fw_loader_download_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0 ;
    if(0 <= argc) {
        res = true;
    }


    if ( 1<= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(FW_LOADER ,res, "Num");
    }

    if(res){
        res = fw_loader_download(num);
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwd Num");
    }
    return res;
}


/*
sc rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 fw_loader_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 */
bool fw_loader_upload_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0 ;
    char hex_file[100] = "";


    if ( 0<= argc) {
        res = true;
    }

    if ( 1<= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(FW_LOADER ,res, "Num");
    }

    if(2<= argc) {
        LOG_INFO(HEX_BIN, "argv0 [%s]", argv[1]);
        strcpy(hex_file, argv[1]);
        LOG_INFO(HEX_BIN, "FileName [%s]", hex_file);
        res = true;
    }

    if(res){
        res = fw_loader_upload(num,hex_file);
        log_res(FW_LOADER ,res, "UpLoad");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwl Num hex");
    }

    return res;
}

/*
  fwj 1
 * */
bool fw_loader_jump_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0 ;
    uint32_t address = 0x80000000 ;

    if ( 0 <= argc) {
        res = true;
    }

    if ( 1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(FW_LOADER ,res, "Num");
    }

    if (2 <= argc) {
    	res = try_str2uint32(argv[1], &address);
    	log_res(FW_LOADER ,res, "Addr");
        res = true;
    }

    if(res) {
        res = fw_loader_jump(num, address);
        log_res(FW_LOADER, res, "Jump");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwj Num Addr");
    }

    return res;
}

