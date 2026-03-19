#include "timer_commands.h"

#include <inttypes.h>

#include "clock_mcal.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "microcontroller_const.h"
#include "time_mcal.h"
#include "timer_mcal.h"
#include "timer_utils.h"

bool timer_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 == argc) {
        res = timer_mcal_init();
        log_res(TIMER, res, "Init");
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }

    if(res) {
        res = timer_init_one(num);
        log_res(TIMER, res, "InitOne");
    } else {
        LOG_ERROR(TIMER, "Usage: tmi N");
    }

    return res;
}

bool timer_diag_compare_complimentary_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_compare_complimentary();
        log_res(TIMER, res, "ComCom");
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}

bool timer_diag_compare_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_compare();
        log_res(TIMER, res, "Com");
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}

bool timer_diag_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_ll();
        log_res(TIMER, res, "LlDiag");
    } else {
        LOG_ERROR(TIMER, "Usage: tdl");
    }

    return res;
}

bool timer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag();
        log_res(TIMER, res, "Diag");
    } else {
        LOG_ERROR(TIMER, "Usage: td");
    }

    return res;
}

bool timer_prescaler_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t timer_inst = 0;
    uint8_t prescaler = 0;
    if(3 == argc) {
        res = true;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            if(false == res) {
                LOG_ERROR(TIMER, "ParseErr num %s", argv[0]);
            }
        }

        if(res) {
            res = try_str2uint8(argv[1], &timer_inst);
            if(false == res) {
                LOG_ERROR(TIMER, "ParseErr timer_inst %s", argv[1]);
            }
            if(4 <= timer_inst) {
                res = false;
            }
        }

        if(res) {
            res = try_str2uint8(argv[2], &prescaler);
            if(false == res) {
                LOG_ERROR(TIMER, "ParseErr prescaler %s", argv[2]);
            }
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tsp base inst prescaler");
    }

    if(res) {
        res = false;
    }

    return res;
}

bool timer_set_laod_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t timer_inst = 0;
    uint32_t load = 0;
    if(3 == argc) {
        res = true;
        if(res) {
            res = try_str2uint8(argv[0], &num);
            log_res(TIMER, res, "Num");
        }

        if(res) {
            res = try_str2uint8(argv[1], &timer_inst);
            if(false == res) {
                LOG_ERROR(TIMER, "ParseErr timer_inst %s", argv[1]);
            }
            if(4 <= timer_inst) {
                res = false;
            }
        }

        if(res) {
            res = try_str2uint32(argv[2], &load);
            if(false == res) {
                LOG_ERROR(TIMER, "ParseErr load %s", argv[2]);
            }
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tsl base inst load");
    }

    if(res) {
    }

    return res;
}
// tp 1 810ns
bool timer_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float period_s = 1.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &period_s);
        log_res(TIMER, res, "Period");
    }

    if(res) {
        switch(argc) {
        case 2: {
            LOG_INFO(TIMER, "Set:Timer:%u,Period:%f s", num, period_s);
            res = timer_period_set_s(num, period_s);
            log_res(TIMER, res, "SetPeriod");
        } break;
        case 1: {
            period_s = timer_period_get_s(num);
            log_res(TIMER, res, "GetPeriod");
            LOG_INFO(TIMER, "Get,Timer:%u, Period:%f s", num, period_s);
        } break;
        default:
            res = false;
            break;
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr Num PeriodS");
        res = false;
    }
    return res;
}

bool timer_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    uint8_t num = 0;
    if(2 == argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
        res = try_str2bool(argv[1], &on_off);
        log_res(TIMER, res, "En");
    }

    if(res) {
        res = timer_ctrl(num, on_off);
        log_res(TIMER, res, "Ctrl");
    } else {
        LOG_ERROR(TIMER, "Usage: tct num OnOff");
    }

    return res;
}

bool timer_channel_ctrl_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    bool on_off = 0;
    TimerCapComChannel_t channel = TIMER_CC_UNDEF;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
        res = try_str2uint8(argv[1], &channel);
        log_res(TIMER, res, "Ch");
        res = try_str2bool(argv[2], &on_off);
        log_res(TIMER, res, "En");
    }

    if(res) {
        LOG_INFO(TIMER, "%u SetComp %u", num, channel);
        res = timer_channel_ctrl(num, channel, on_off);
        if(res) {
        } else {
            LOG_ERROR(TIMER, "%u  SetComp %u", num, channel);
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tcc num channel OnOff");
    }

    return res;
}

bool timer_compare_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t compare_value = 0;
    TimerCapComChannel_t channel = TIMER_CC_UNDEF;
    if(3 == argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");

        res = try_str2uint8(argv[1], &channel);
        log_res(TIMER, res, "Channel");

        res = try_str2uint32(argv[2], &compare_value);
        log_res(TIMER, res, "CompareValue");
    }

    if(res) {
        res = timer_compare_set(num, channel, compare_value);
        if(res) {
            LOG_INFO(TIMER, "%u SetComp %u", num, channel);
            res = timer_channel_ctrl(num, channel, true);
        } else {
            LOG_ERROR(TIMER, "%u  SetComp %u", num, channel);
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tsc num channel compare_value");
    }

    return res;
}

// to 2 1000000
// to 2 500000
// to 2 200000
// to 2 90000
// to 2 80000
bool timer_overflow_command(int32_t argc, char* argv[]) {
    uint32_t overflow = 0;

    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &overflow);
        log_res(TIMER, res, "Overflow");
    }

    if(res) {
        switch(argc) {
        case 2: {
            LOG_INFO(TIMER, "Set:Timer:%u,Overflow:%u ", num, overflow);
            res = timer_overflow_set(num, overflow);
        } break;
        case 1: {
            res = timer_overflow_get(num, &overflow);
            LOG_INFO(TIMER, "Get,Timer:%u,Overflow:%u s", num, overflow);
        } break;
        default:
            res = false;
            break;
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr Num PeriodMs");
        res = false;
    }

    return res;
}

bool timer_channel_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 <= argc) {
        res = true;
    }

    if(res) {
        res = timer_channel_diag();
        log_res(TIMER, res, "ChDiag");
    } else {
        LOG_ERROR(TIMER, "Usage: tcd");
    }

    return res;
}

bool timer_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    float frequency_hz = 0.0;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &frequency_hz);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr FrequencyHz:%s", argv[1]);
        }
    }

    if(res) {
        switch(argc) {
        case 2: {
            LOG_INFO(TIMER, "Set:Timer:%u,Frequency:%u Hz", num, frequency_hz);
            res = timer_frequency_set(num, frequency_hz);
        } break;
        case 1: {
            res = timer_frequency_get(num, &frequency_hz);
            LOG_INFO(TIMER, "Get,Timer:%u,Frequency:%u Hz", num, frequency_hz);
        } break;
        default:
            res = false;
            break;
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr Num PeriodMs");
        res = false;
    }

    return res;
}

bool timer_diag_raw_reg_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_res(TIMER, res, "Num");
    }

    if(res) {
        res = timer_raw_reg_diag(num);
        log_res(TIMER, res, "RawReg");
    } else {
        LOG_ERROR(TIMER, "Usage: tdrr Num");
        res = false;
    }

    return res;
}

bool timer_diag_interrupt_command(int32_t argc, char* argv[]) {
    bool res = true;

    if(res) {
        res = timer_diag_interrupt();
        log_res(TIMER, res, "DiagInterrupts");
    } else {
        LOG_ERROR(TIMER, "Usage: tdint Num");
        res = false;
    }

    return res;
}
