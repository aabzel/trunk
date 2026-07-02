#include "wav_commands.h"

#include "convert.h"
#include "log.h"
#include "wav.h"

bool wav_info_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[100] = "";
    if(0 == argc) {
        res = false;
    }

    if(1 <= argc) {
        LOG_INFO(WAV, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(WAV, "FileName:[%s]", file_name);
        res = true;
    }

    if(res) {
        res = wav_info_sample(file_name);
        if(res) {
            LOG_INFO(WAV, "Ok");
        } else {
            LOG_ERROR(WAV, "Err");
        }
    }
    return res;
}

bool wav_info_command(int32_t argc, char* argv[]) {
    bool res = false;
    char file_name[100] = "";
    if(0 == argc) {
        res = false;
    }

    if(1 <= argc) {
        LOG_INFO(WAV, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(WAV, "FileName:[%s]", file_name);
        res = true;
    }

    if(res) {
        res = wav_info(file_name);
        if(res) {
            LOG_INFO(WAV, "Ok");
        } else {
            LOG_ERROR(WAV, "Err");
        }
    }
    return res;
}

bool wav_diag_command(int32_t argc, char* argv[]) { return false; }

bool wav_proc_iir_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t iir_num = 1;
    char file_name[100] = "";
    if(0 == argc) {
        res = false;
    }
    if(1 <= argc) {
        LOG_INFO(WAV, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(WAV, "FileName:[%s]", file_name);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &iir_num);
    }

    if(res) {
        res = wav_proc_iir_sample(file_name, iir_num);
        if(res) {
            LOG_INFO(WAV, "Ok");
        } else {
            LOG_ERROR(WAV, "Err");
        }
    }
    return res;
}

bool wav_proc_fir_sample_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t fir_num = 1;
    char file_name[100] = "";
    if(0 == argc) {
        res = false;
    }
    if(1 <= argc) {
        LOG_INFO(WAV, "argv0 [%s]", argv[0]);
        strcpy(file_name, argv[0]);
        LOG_INFO(WAV, "FileName:[%s]", file_name);
        res = true;
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &fir_num);
    }

    if(res) {
        res = wav_proc_fir_sample(file_name, fir_num);
        if(res) {
            LOG_INFO(WAV, "Ok");
        } else {
            LOG_ERROR(WAV, "Err");
        }
    }
    return res;
}


bool wav_generate_from_dds_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t wav_num = 1;
    uint8_t dds_num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &wav_num);
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dds_num);
    }

    if(res){
        res = wav_generate(wav_num  , dds_num);
        res = log_info_res(WAV, res, "Generate");
    }else {
        LOG_ERROR(WAV, "Usage: wpgd WavNum DDS1");
    }
    return res;
}
//wg2�h 1 1 2

bool wav_generate_2_channel_command(int32_t argc, char* argv[]){
    bool res  = false;
    uint8_t wav_num = 1;
    uint8_t dds1_num = 1;
    uint8_t dds2_num = 2;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &wav_num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dds1_num);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &dds2_num);
    }

    if(res) {
        res = wav_generate_2_channel(wav_num, dds1_num, dds2_num);
    }else {
        LOG_ERROR(WAV, "Usage: wg2ch WavNum DDS1 DDS2");
    }

    return res;
}


bool wav_load_command(int32_t argc, char* argv[]){
    bool res  = false;
    uint8_t wav_num = 1;
    char file_name[200] = "";
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &wav_num);
        log_res(WAV, res, "Num");
    }

    if(1 <= argc) {
        strcpy(file_name, argv[1]);
        LOG_INFO(WAV, "FileName:[%s]", file_name);
        res = true;
    }

    if(res) {
        res = wav_load(wav_num, file_name);
        log_res(WAV, res, "Load");
    }else {
        LOG_ERROR(WAV, "Usage: wld WavNum FileName");
    }
    return res;
}
