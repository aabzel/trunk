#include "drv8870_commands.h"

#include "convert.h"
#include "drv8870_mcal.h"
#include "log.h"

#ifdef HAS_TEST_DRV8870
#include "test_drv8870.h"
#endif

/*
    d88f 1 50
   d88f 1 100
  d88f 1 200
 d88f 1 400
  d88f 1 3200
 */
bool drv8870_freq_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float freq_hz = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(DRV8870, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &freq_hz);
        log_info_res(DRV8870, res, "Freq");
    }

    if(res) {
        res = drv8870_freq_set(num, freq_hz);
        log_res(DRV8870, res, "Set");
    } else {
        LOG_ERROR(DRV8870, "Usage: d88f N freq");
    }
    return res;
}

/*
 d88s 1 2 30
 d88s 1 2 60
 d88s 1 2 80
 */
bool drv8870_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t mode = DRV8870_MODE_BRAKE;
    uint8_t num = 0;
    float set_duty = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(DRV8870, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mode);
        log_info_res(DRV8870, res, "Mode");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &set_duty);
        log_info_res(DRV8870, res, "ThrottleDuty");
    }

    if(res) {
        res = drv8870_set(num, (Drv8870Mode_t)mode, set_duty);
        log_res(DRV8870, res, "Set");
    } else {
        LOG_ERROR(DRV8870, "Usage: d88s N mode dutu");
    }
    return res;
}

bool drv8870_diag_command(int32_t argc, char* argv[]) {
    bool res = false;

    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = drv8870_diag();
        log_res(DRV8870, res, "Init");
    } else {
        LOG_ERROR(DRV8870, "Usage: fdat");
    }

    return res;
}

bool drv8870_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = drv8870_mcal_init();
        log_res(DRV8870, res, "Init");
    }
    return res;
}

bool drv8870_test_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t pause_ms = 3000;
    float duty = 50.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(DRV8870, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &duty);
        log_info_res(DRV8870, res, "Duty");
    }

    if(3 <= argc) {
        res = try_str2uint32(argv[2], &pause_ms);
        log_info_res(DRV8870, res, "Pause");
    }

    if(res) {
        res = test_drv8870_cw_ccw_one(num, duty, pause_ms);
        log_res(DRV8870, res, "Test");
    } else {
        LOG_ERROR(DRV8870, "Usage: d88t N Duty Pause");
    }

    return res;
}
