#include "loopback_audio_commands.h"

#include "convert.h"
#include "log.h"
#include "loopback_audio_mcal.h"
#include "test_loopback_audio.h"

bool loopback_audio_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(res) {
        res = loopback_audio_raw_reg_diag(num);
        log_info_res(LOOPBACK_AUDIO, res, "RegMap");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: loopback_audiorr num");
    }
    return res;
}

bool loopback_audio_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(res) {
        res = loopback_audio_diag_one(num);
        log_info_res(LOOPBACK_AUDIO, res, "Diag");

        res = loopback_audio_diag();
        log_info_res(LOOPBACK_AUDIO, res, "Diag");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: fdat");
    }

    return res;
}

bool loopback_audio_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(0 == argc) {
        res = loopback_audio_mcal_init();
        log_info_res(LOOPBACK_AUDIO, res, "Init");
    }
    return res;
}

/*
 las 1 RbUt29786_10s.wav
 * */
bool loopback_audio_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char PlayFile[300] = {0};
    char RecFile[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(2 <= argc) {
        strncpy(PlayFile, argv[1], sizeof(PlayFile));
        res = true;
    }

    if(3 <= argc) {
        strncpy(RecFile, argv[2], sizeof(RecFile));
        res = true;
    }

    if(res) {
        res = loopback_audio_play_rec_file(num, PlayFile, RecFile);
        log_info_res(LOOPBACK_AUDIO, res, "PlayRec");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: las num FileNamePlay FileNameRec");
    }
    return res;
}

bool loopback_audio_play_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char PlayFile[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(2 <= argc) {
        strncpy(PlayFile, argv[1], sizeof(PlayFile));
        res = true;
    }

    if(res) {
        res = loopback_audio_play_file(num, PlayFile);
        log_info_res(LOOPBACK_AUDIO, res, "Play");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: laps num FileNamePlay ");
    }
    return res;
}

/*
 loopback_audio_rec_start 1 rec16.wav 3
  loopback_audio_rec_start 1 rec15.wav 3
  loopback_audio_rec_start 1 rec12.wav 3
*/
bool loopback_audio_rec_start_command(int32_t argc, char* argv[]) {
    bool res = false;
    float duration_s = 3.0f;
    uint8_t num = 1;
    char RecFile[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(2 <= argc) {
        strncpy(RecFile, argv[1], sizeof(RecFile));
        res = true;
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &duration_s);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(res) {
        res = loopback_audio_rec_file(num, RecFile, duration_s);
        log_info_res(LOOPBACK_AUDIO, res, "Rec");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: lars num FileRec DurationS");
    }
    return res;
}

bool loopback_audio_play_rec_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char PlayFileName[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(2 <= argc) {
        strncpy(PlayFileName, argv[1], sizeof(PlayFileName));
        res = true;
    }

    if(res) {
        res = test_loopback_audio_rec_play_one(num, PlayFileName);
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: laprt num PlayFile");
    }
    return res;
}

/*
 lart 1 4
 */
bool loopback_audio_rec_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    float duration_s = 3.0f;
    uint8_t num = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(LOOPBACK_AUDIO, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &duration_s);
        log_info_res(LOOPBACK_AUDIO, res, "Duration");
    }

    if(res) {
        res = loopback_audio_rec_test(num, duration_s);
        log_info_res(LOOPBACK_AUDIO, res, "RecTest");
    } else {
        LOG_ERROR(LOOPBACK_AUDIO, "Usage: lart num DurationS");
    }
    return res;
}
