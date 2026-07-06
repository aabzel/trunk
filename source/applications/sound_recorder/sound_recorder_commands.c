#include "sound_recorder_commands.h"

#include "convert.h"
#include "log.h"
#include "sound_recorder_mcal.h"

bool sound_recorder_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SOUND_RECORDER, res, "Num");
    }

    if(res) {
        res = sound_recorder_diag_one(num);
        log_info_res(SOUND_RECORDER, res, "Diag");

        res = sound_recorder_diag();
        log_info_res(SOUND_RECORDER, res, "Diag");
    } else {
        LOG_ERROR(SOUND_RECORDER, "Usage: fdat");
    }

    return res;
}

bool sound_recorder_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SOUND_RECORDER, res, "Num");
    }

    if(0 == argc) {
        res = sound_recorder_mcal_init();
        log_info_res(SOUND_RECORDER, res, "Init");
    }
    return res;
}

bool sound_recorder_test_rec_command(int32_t argc, char* argv[]){
    bool res = false;
    float duration_s = 10;

    if(1 <= argc) {
        res = try_str2float(argv[0], &duration_s);
        log_info_res(SOUND_RECORDER, res, "Duration");
    }

    if(res) {
        res = sound_recorder_test_start(1, duration_s) ;
    } else {
        LOG_ERROR(SOUND_RECORDER, "Usage: sorrt  DurationS");
    }

    return res;
}



bool sound_recorder_rec_command(int32_t argc, char* argv[]){
    bool res = false;
    float duration_s = 3;
    char file_name[80]={0};

    if(1 <= argc) {
        strcpy(file_name,argv[0]);
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &duration_s);
        log_info_res(SOUND_RECORDER, res, "Duration");
    }


    if(res) {
        res = sound_recorder_start(1, file_name,   duration_s) ;
        //log_info_res(SOUND_RECORDER, res, "RecStart");
    } else {
        LOG_ERROR(SOUND_RECORDER, "Usage: sorr FileName DurationS");
    }

    return res;
}
