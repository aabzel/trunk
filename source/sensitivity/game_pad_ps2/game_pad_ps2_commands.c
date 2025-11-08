#include "game_pad_ps2_commands.h"

#include "convert.h"
#include "log.h"
#include "game_pad_ps2.h"

bool game_pad_ps2_reg_map_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GAME_PAD_PS2, res, "Num");
    }

    if(res) {
        res = game_pad_ps2_raw_reg_diag(num);
        log_info_res(GAME_PAD_PS2, res, "RegMap");
    } else {
        LOG_ERROR(GAME_PAD_PS2, "Usage: game_pad_ps2rr num");
    }
    return res;
}

bool game_pad_ps2_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1 ;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GAME_PAD_PS2, res, "Num");
    }

    if(res) {
        res = game_pad_ps2_diag_one(num);
        log_info_res(GAME_PAD_PS2, res, "Diag");

        res = game_pad_ps2_diag();
        log_info_res(GAME_PAD_PS2, res, "Diag");
    } else {
        LOG_ERROR(GAME_PAD_PS2, "Usage: fdat");
    }

    return res;
}

bool game_pad_ps2_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0 ;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GAME_PAD_PS2, res, "Num");
    }

    if(0 == argc) {
        res = game_pad_ps2_mcal_init();
        log_info_res(GAME_PAD_PS2, res, "Init");
    }
    return res;
}

/*
 gpp2t 1 2 0xff   ;    gpp2d
 gpp2t 1 3 0xff   ;    gpp2d
 gpp2t 1 4 0xff   ;    gpp2d
 gpp2t 1 5 0xff   ;    gpp2d
 gpp2t 1 6 0xff   ;    gpp2d
 gpp2t 1 7 0xff   ;     gpp2d 1
 gpp2t 1 8 0xff   ;    gpp2d
  gpp2t 1 9 0xff
 * */
bool game_pad_ps2_tx_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1 ;
    uint8_t offset = 0 ;
    uint8_t value = 0 ;

    if(0 <= argc) {
        res = true;
        offset = 2 ;
        value = 0 ;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GAME_PAD_PS2, res, "Num");
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &offset);
        log_info_res(GAME_PAD_PS2, res, "offset");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &value);
        log_info_res(GAME_PAD_PS2, res, "value");
    }

    if(res) {
        res = game_pad_ps2_tx_set(num, offset, value);
        log_info_res(GAME_PAD_PS2, res, "value");
    }else {
        LOG_ERROR(GAME_PAD_PS2, "Usage: gpp2t num offset value");
    }

    return res;
}

/*
 gpp2r 1 1 0xff
  gpp2r 1 1 0x45
 gpp2r 1 2 0xff
 gpp2r 1 2 0x45
  gpp2r 1 2 150
  gpp2d
 */
bool game_pad_ps2_motor_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1 ;
    uint8_t motor_num = 0 ;
    uint8_t current = 0 ;

    if(0 <= argc) {
        res = true;
        current = 0 ;
        motor_num = 1 ;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(GAME_PAD_PS2, res, "Num");
    }
    if(2 <= argc) {
        res = try_str2uint8(argv[1], &motor_num);
        log_info_res(GAME_PAD_PS2, res, "MotorNum");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &current);
        log_info_res(GAME_PAD_PS2, res, "Current");
    }

    if(res){
        res = game_pad_ps2_motor_set(num, (GamePadPs2Motor_t)motor_num, current);
        log_info_res(GAME_PAD_PS2, res, "MotorCtrl");
    }else {
        LOG_ERROR(GAME_PAD_PS2, "Usage: gpp2r num MotorN Current");
    }

    return res;
}
