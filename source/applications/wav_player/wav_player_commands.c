#include "wav_player_commands.h"

#include "convert.h"
#include "log.h"
#include "wav_player_mcal.h"

bool wav_player_play_file_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    char path[300] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(WAV_PLAYER, res, "Num");
    }

    if(2 <= argc) {
        res = strncpy(path, argv[1], sizeof(path));
    }

    if(res) {
        res = wav_player_play_file(num, path);
        log_info_res(WAV_PLAYER, res, "PlayFile");
    } else {
        LOG_ERROR(WAV_PLAYER, "Usage: wpf num FileName");
    }
    return res;
}

bool wav_player_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(WAV_PLAYER, res, "Num");
    }

    if(res) {
        res = wav_player_diag_one(num);
        log_info_res(WAV_PLAYER, res, "Diag");

        res = wav_player_diag();
        log_info_res(WAV_PLAYER, res, "Diag");
    } else {
        LOG_ERROR(WAV_PLAYER, "Usage: wpd");
    }

    return res;
}

bool wav_player_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(WAV_PLAYER, res, "Num");
    }

    if(0 == argc) {
        res = wav_player_mcal_init();
        log_info_res(WAV_PLAYER, res, "Init");
    } else {
        LOG_ERROR(WAV_PLAYER, "Usage: wpi");
    }
    return res;
}
