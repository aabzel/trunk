#include "rec_play_commands.h"

#include "convert.h"
#include "log.h"
#include "rec_play_mcal.h"

bool rec_play_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(REC_PLAY, res, "Num");
    }

    if(res) {
        res = rec_play_raw_reg_diag(num);
        log_info_res(REC_PLAY, res, "RegMap");
    } else {
        LOG_ERROR(REC_PLAY, "Usage: rec_playrr num");
    }
    return res;
}

bool rec_play_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(REC_PLAY, res, "Num");
    }

    if(res) {
        res = rec_play_diag_one(num);
        log_info_res(REC_PLAY, res, "Diag");

        res = rec_play_diag();
        log_info_res(REC_PLAY, res, "Diag");
    } else {
        LOG_ERROR(REC_PLAY, "Usage: rpd");
    }

    return res;
}

bool rec_play_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(REC_PLAY, res, "Num");
    }

    if(0 == argc) {
        res = rec_play_mcal_init();
        log_info_res(REC_PLAY, res, "Init");
    } else {
        LOG_ERROR(REC_PLAY, "Usage: rpi");
    }

    return res;
}

/*
rec_play_start 2
*/
bool rec_play_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    float duration_s = 10;

    if(1 <= argc) {
        res = try_str2float(argv[0], &duration_s);
        log_info_res(SOUND_RECORDER, res, "Duration");
    }

    if(res) {
        res = rec_play_start(1, "test.wav", duration_s);
    } else {
        LOG_ERROR(SOUND_RECORDER, "Usage: rps RecDurationS");
    }

    return res;
}

bool rec_play_start_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    float duration_s = 10;

    if(1 <= argc) {
        res = try_str2float(argv[0], &duration_s);
        log_info_res(SOUND_RECORDER, res, "Duration");
    }

    if(res) {
        res = rec_play_start_test(1, duration_s);
    } else {
        LOG_ERROR(SOUND_RECORDER, "Usage: sorrt  DurationS");
    }

    return res;
}
