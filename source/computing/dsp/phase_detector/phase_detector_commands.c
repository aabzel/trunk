#include "phase_detector_commands.h"

#include "convert.h"
#include "phase_detector.h"
#include "log.h"

bool phase_detector_half_cos_command(int32_t argc, char* argv[]){
    bool res = false;
    char file_name[300]="";
    double f_signal = 0.0;
    if(0<=argc) {
        res = true;
    }

    if(1<=argc) {
        res = try_str2double(argv[0], &f_signal);
    }

    if(2<=argc) {
        res = strcpy(file_name,argv[1]);
    }

    if(res) {
        res = phase_detector_half_cos(f_signal, file_name);
        res=log_res(PHASE_DETECTOR,  res, "ProcHalfCos");
    }else{
        LOG_ERROR(PHASE_DETECTOR, "Usage: padp Fsignal FileName");
    }

    return res;
}


bool phase_detector_proc_command(int32_t argc, char* argv[]){
    bool res = false;
    char file_name[300]="";
    double f_signal = 0.0;
    if(0<=argc) {
        res = true;
    }

    if(1<=argc) {
        res = try_str2double(argv[0], &f_signal);
    }

    if(2<=argc) {
        res = strcpy(file_name,argv[1]);
    }

    if(res) {
        res = phase_detector_proc_file(f_signal, file_name);
        res=log_res(PHASE_DETECTOR,  res, "Proc");
    }else{
        LOG_ERROR(PHASE_DETECTOR, "Usage: padp Fsignal FileName");
    }

    return res;
}



bool phase_detector_init_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res){
        res = phase_detector_init_one(num);
        res = log_res(PHASE_DETECTOR,  res, "Init");
    }else{
        LOG_ERROR(PHASE_DETECTOR, "Usage: fis Num M FcHz");
    }

    return res;
}

bool phase_detector_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1==argc){
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = phase_detector_diag(num);
        res=log_res(PHASE_DETECTOR,  res, "Diag");
    }else{
        LOG_ERROR(PHASE_DETECTOR, "Usage: fis Num M FcHz");
    }
    return res;
}

