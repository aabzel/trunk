#include "bts724g_commands.h"

#include "bts724g_mcal.h"
#include "convert.h"
#include "test_bts724g.h"
#include "log.h"

bool bts724g_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    uint8_t num = 1;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BTS724G, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2bool(argv[1], &on_off);
        log_info_res(BTS724G, res, "Num");
    }

    if(res) {
        res = bts724g_set(num, on_off);
        log_info_res(BTS724G, res, "Set");
    } else {
        LOG_ERROR(BTS724G, "Usage: btss num OnIff");
    }
    return res;
}

bool bts724g_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BTS724G, res, "Num");
    }

    if(res) {
        // res = bts724g_diag_one(num);
        // log_info_res(BTS724G, res, "Diag");

        res = bts724g_diag("", "");
        log_info_res(BTS724G, res, "Diag");
    } else {
        LOG_ERROR(BTS724G, "Usage: fdat");
    }

    return res;
}

bool bts724g_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BTS724G, res, "Num");
    }

    if(0 == argc) {
        res = bts724g_mcal_init();
        log_info_res(BTS724G, res, "Init");
    }
    return res;
}

bool bts724g_duty_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float duty_cycle = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BTS724G, res, "Num");
    }

    if(2 <= argc) {

        res = try_str2float(argv[1], &duty_cycle);
        if(false == res) {
            LOG_ERROR(BTS724G, "ParseErr Duty %s", argv[1]);
        }
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = bts724g_duty_get(num, &duty_cycle);
            if(res) {
                LOG_INFO(BTS724G, "Get,DutyOk PWM%u,Duty:%6.2f%%", num, duty_cycle);
            } else {
                LOG_ERROR(BTS724G, "Get,DutyErr PWM%u", num);
            }
        } break;
        case 2: {
            res = bts724g_duty_set(num, duty_cycle);
            if(res) {
                LOG_INFO(BTS724G, "Set,DutyOk,PWM%u,Duty:%6.2f %%", num, duty_cycle);
            } else {
                LOG_ERROR(BTS724G, "Set,DutyErr,PWM%u", num);
            }
        } break;
        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(BTS724G, "Usage: pdu Num Duty");
    }
    return res;
}

bool bts724g_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float frequency_hz = 0.0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(BTS724G, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &frequency_hz);
        log_res(BTS724G, res, "Freq");
    }

    if(res) {
        switch(argc) {
        case 1: {
            res = bts724g_frequency_get(num, &frequency_hz);
            if(res) {
                LOG_INFO(BTS724G, "PWM%u,Get,Freq:%f Hz", num, frequency_hz);
            }
        } break;
        case 2: {
            LOG_INFO(BTS724G, "PWM%u Freq:%f Hz", num, frequency_hz);
            res = bts724g_frequency_set(num, frequency_hz);
            if(res) {
                LOG_INFO(BTS724G, "FreqSetOk");
            } else {
                LOG_ERROR(BTS724G, "FreqSetErr");
            }
        } break;
        default: {
            res = false;
        } break;
        }
    } else {
        LOG_ERROR(BTS724G, "Usage: pf PwmNum FrequencyHz");
    }
    return res;
}

bool bts724g_test_overtemperature_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 1;
    uint32_t wait_pause_ms = 1;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(BTS724G, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &wait_pause_ms);
        log_info_res(BTS724G, res, "wait_pause_ms");
    }

    if(res) {
        res = test_bts724g_overtemperature_one(num,   wait_pause_ms);
        log_info_res(BTS724G, res, "TestOverTemp");
    } else {
        LOG_ERROR(BTS724G, "Usage: btso Num TimeOutMs");
    }
    return res;
}
