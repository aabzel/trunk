#include "fw_loader_commands.h"

#include "string.h"

#include "convert.h"
#include "fw_loader.h"
#include "log.h"
#include "fw_loader_diag.h"

/*
ll serialPort debug; fwp 2
 */
bool fw_loader_ping_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0 ;
    if(0 == argc) {
        res = true;
    } else {
    }

    if ( 1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(FW_LOADER ,res, "Num");
    }

    if(res) {
        res = fw_loader_ping(num);
        log_info_res(FW_LOADER ,res, "Ping");
    } else {
        LOG_ERROR(FW_LOADER, "Usage: fwp Num");
    }
    return res;
}

/*
  fwd FirmWareDump.bin 4 56000 1024
 */
bool fw_loader_download_command(int32_t argc, char* argv[]) {
    bool res = false;

    uint8_t com_port_num = 0 ;
    uint32_t bit_rate_hz = 56000 ;
    uint32_t size = 512*1024;
    char fileName[200] = {0};
    if(0 <= argc) {
        res = false;
    }

    if ( 1 <= argc) {
        res = strcpy(fileName, argv[0]);
        log_info_res(FW_LOADER ,res, "FileName");
    }

    if ( 2 <= argc) {
        res = try_str2uint8(argv[1],&com_port_num);
        log_info_res(FW_LOADER ,res, "ComPort");
    }

    if ( 3 <= argc) {
        res = try_str2uint32( argv[2],&bit_rate_hz);
        log_info_res(FW_LOADER ,res, "BitRate");
    }

    if ( 4 <= argc) {
        res = try_str2uint32(argv[3], &size);
        log_info_res(FW_LOADER ,res, "Size");
    }

    if(res) {
        res = fw_loader_download_firmware(fileName, com_port_num, bit_rate_hz, size);
        log_info_res(FW_LOADER, res, "ReadFwDump");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwd FileName COMnum BitRate");
    }
    return res;
}


/*
  fwl FirmWareDump.bin 4 56000 1024
 */
bool fw_loader_upload_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t com_port_num = 0 ;
    uint32_t bit_rate_hz = 56000 ;
    uint32_t pause_ms = 20;
    char fileName[200] = {0};

    if(0 <= argc) {
        res = false;
    }

    if ( 1 <= argc) {
        res = strcpy(fileName, argv[0]);
        log_info_res(FW_LOADER ,res, "FileName");
    }

    if ( 2 <= argc) {
        res = try_str2uint8(argv[1], &com_port_num);
        log_info_res(FW_LOADER ,res, "ComPort");
    }

    if ( 3 <= argc) {
        res = try_str2uint32( argv[2], &bit_rate_hz);
        log_info_res(FW_LOADER ,res, "BitRate");
    }

    if ( 4 <= argc) {
        res = try_str2uint32( argv[3], &pause_ms);
        log_info_res(FW_LOADER ,res, "Pause");
    }

    if(res) {
        res = fw_loader_upload_file(fileName, com_port_num, bit_rate_hz, pause_ms);
        log_info_res(FW_LOADER ,res, "UpLoadFile");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwl FileName COMx BitRateHz BytePauseMs");
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
        log_info_res(FW_LOADER ,res, "Num");
    }

    if (2 <= argc) {
    	res = try_str2uint32(argv[1], &address);
    	log_info_res(FW_LOADER ,res, "Addr");
        res = true;
    }

    if(res) {
        res = fw_loader_jump(num, address);
        log_info_res(FW_LOADER, res, "Jump");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwj Num Addr");
    }

    return res;
}

/*
 fwe 3 56000 20
 * */
bool fw_loader_erase_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t com_port_num = 0 ;
    uint32_t bit_rate_hz = 56000 ;
    uint32_t pause_ms = 20;

    if(0 <= argc) {
        res = false;
    }

    if ( 1 <= argc) {
        res = try_str2uint8(argv[0], &com_port_num);
        log_info_res(FW_LOADER ,res, "ComPort");
    }

    if ( 2 <= argc) {
        res = try_str2uint32( argv[1], &bit_rate_hz);
        log_info_res(FW_LOADER ,res, "BitRate");
    }

    if ( 3 <= argc) {
        res = try_str2uint32( argv[2], &pause_ms);
        log_info_res(FW_LOADER ,res, "Pause");
    }

    if(res) {
        res = fw_loader_erase_chip_cfg( com_port_num, bit_rate_hz, pause_ms);
        log_info_res(FW_LOADER ,res, "EraseChip");
    }else {
        LOG_ERROR(FW_LOADER, "Usage: fwe   COMx BitRateHz BytePauseMs");
    }

    return res;
}
