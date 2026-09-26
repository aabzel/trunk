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

bool wav_generate_signal_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint8_t dds_num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(WAV, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dds_num);
        log_res(WAV, res, "DdsNum");
    }

    if(res) {
        res = wav_generate_signal(num, dds_num, "Rec");
        res = log_info_res(WAV, res, "GenerateSignal");
    } else {
        LOG_ERROR(WAV, "Usage: wgs Num DdsNum");
    }
    return res;
}

bool wav_generate_from_dds_command(int32_t argc, char* argv[]) {
    bool res = false;
    char FileName[80] = {0};
    uint8_t dds_num = 1;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(WAV, res, "Num");
    }

    if(2 <= argc) {
        strcpy(FileName, argv[1]);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &dds_num);
        log_res(WAV, res, "DdsNum");
    }

    if(res) {
        res = wav_generate(num, FileName, dds_num);
        res = log_info_res(WAV, res, "Generate");
    } else {
        LOG_ERROR(WAV, "Usage: wgdds Num FileName DdsNum");
    }
    return res;
}

/*
 wav_shift_right out.wav 0.5
 * */
bool wav_shift_right_command(int32_t argc, char* argv[]) {
    bool res = false;
    char name[80] = {0};
    float duration_s = 0.0;
    memset(name, 0, sizeof(name));

    if(1 <= argc) {
        strcpy(name, argv[0]);
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &duration_s);
        log_res(WAV, res, "durationS");
    }

    if(res) {
        res = wav_shift_right(name, duration_s);
    } else {
        LOG_ERROR(WAV, "Usage: wsr FileName Duration");
    }

    return res;
}

bool wav_shift_right2_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    float shift_timeout_s = 0.0f;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(WAV, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &shift_timeout_s);
        log_res(WAV, res, "durationS");
    }

    if(res) {
        res = wav_shift_right2(num, shift_timeout_s);
    } else {
        LOG_ERROR(WAV, "Usage: wsr2 Num ShiftTimeOutS");
    }

    return res;
}

bool wav_duration_command(int32_t argc, char* argv[]) {
    bool res = false;
    float duration_s = 3.0;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(WAV, res, "Num");
    }

    if(1 <= argc) {
        res = try_str2float(argv[1], &duration_s);
        log_res(WAV, res, "duration");
    }

    if(res) {
        switch(argc) {
        case 1: {
            duration_s = wav_duration_get(num);
        } break;

        case 2: {
            res = wav_duration_set(num, duration_s);
        } break;

        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(WAV, "Usage: wad Num DurationS");
    }

    return res;
}

/*
wav_gen2ch_from_dds 1 1 2
 */
bool wav_generate_2_channel_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t wav_num = 1;
    uint8_t dds1_num = 1;
    uint8_t dds2_num = 2;
    float duration_s = 5;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &wav_num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &dds1_num);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &dds2_num);
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &duration_s);
    }

    if(res) {
        res = wav_generate_2_channel(wav_num, dds1_num, dds2_num, duration_s);
    } else {
        LOG_ERROR(WAV, "Usage: wg2ch WavNum DDS1 DDS2 DurationS");
    }

    return res;
}

bool wav_load_command(int32_t argc, char* argv[]) {
    bool res = false;
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
        res = false;
#ifdef HAS_PC
        res = wav_load(wav_num, file_name);
#endif
        log_res(WAV, res, "Load");
    } else {
        LOG_ERROR(WAV, "Usage: wld WavNum FileName");
    }
    return res;
}

bool wav_sample_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t wav_num = 1;
    uint32_t sampling_frequency_hz = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &wav_num);
        log_res(WAV, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &sampling_frequency_hz);
        log_res(WAV, res, "samplingFrequencyHz");
    }

    if(res) {
        switch(argc) {
        case 1: {
            sampling_frequency_hz = wav_sampling_frequency_get(wav_num);
        } break;

        case 2: {
            res = wav_sampling_frequency_set(wav_num, sampling_frequency_hz);
        } break;

        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(WAV, "Usage: wavsf WavNum sampling_frequency");
    }
    return res;
}
