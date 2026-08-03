#include "correlator_s16_commands.h"

#include "convert.h"
#include "correlator_s16.h"
#include "log.h"

// correlator_s16_proc_file

/*
 correlator_s16_proc_file 8 directionNorm.csv 3 9
 * */
bool correlator_s16_proc_file_command(int32_t argc, char* argv[]) {
    bool res = false;
#ifdef HAS_FILE_PC
    uint8_t num = 1;
    uint16_t column_x = 1;
    uint16_t column_y = 1;
    if(4 == argc) {
        res = try_str2uint8(argv[0], &num);
        // file name
        res = try_str2uint16(argv[2], &column_x);
        res = try_str2uint16(argv[3], &column_y);
    }

    if(res) {
        res = correlator_s16_proc_file(num, argv[1], column_x, column_y);
        log_res(CORRELATOR_S16, res, "FrocFile");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: fipf Num FileName colomn");
    }
#endif

    return res;
}

bool correlator_s16_calc_frequency_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    double f_step = 0.0;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &f_step);
    }

    if(res) {
        res = correlator_s16_calc_frequency_response(num, f_step);
        log_res(CORRELATOR_S16, res, "CalcFrequencyFesponse");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: ffr Num");
    }

    return res;
}

bool correlator_s16_impulse_response_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = correlator_s16_impulse_response(num);
        log_res(CORRELATOR_S16, res, "impulse_response");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: ffr Num");
    }

    return res;
}

bool correlator_s16_proc_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double value = 0.0;

    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2double(argv[1], &value);
    }

    if(res) {
        int64_t out = 0;
        LOG_INFO(CORRELATOR_S16, "Proc,In:%f", value);
        res = correlator_s16_proc_in_out(num, (int16_t)value, &out);
        log_res(CORRELATOR_S16, res, "proc_in_out");
        if(res) {
            LOG_INFO(CORRELATOR_S16, "Out:%f", out);
        } else {
            LOG_ERROR(CORRELATOR_S16, "Out:%f", out);
        }
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: fis Num M FcHz");
    }

    return res;
}

bool correlator_s16_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);

    if(res) {
        res = correlator_s16_init_one(num);
        log_res(CORRELATOR_S16, res, "init_one");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: fis Num M FcHz");
    }

    return res;
}

bool correlator_s16_reset_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {

        res = correlator_s16_reset_one(num);
        log_res(CORRELATOR_S16, res, "reset_one");
    }

    return res;
}

bool correlator_s16_graphviz_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    res = try_str2uint8(argv[0], &num);
    if(res) {
        res = false;
#ifdef HAS_CORRELATOR_S16_DIAG
        res = correlator_s16_generate_graphviz(num);
#endif
        log_res(CORRELATOR_S16, res, "generate_graphviz");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: fis Num M FcHz");
    }
    return res;
}

bool correlator_s16_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 == argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
#ifdef HAS_CORRELATOR_S16_DIAG
        res = correlator_s16_diag(num);
        res = correlator_s16_diag_mem(num);
#endif
        log_res(CORRELATOR_S16, res, "diag");
    } else {
        LOG_ERROR(CORRELATOR_S16, "Usage: fis Num M FcHz");
    }
    return res;
}
