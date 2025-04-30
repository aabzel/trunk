#include "timer_commands.h"

#include <inttypes.h>

#include "clock.h"
#include "common_diag.h"
#include "convert.h"
#include "data_utils.h"
#include "log.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "timer_mcal.h"
#include "timer_utils.h"

bool timer_diag_compare_complimentary_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_compare_complimentary();
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}

bool timer_diag_compare_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_compare();
    } else {
        LOG_ERROR(TIMER, "Usage: tdc");
    }

    return res;
}

bool timer_diag_ll_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag_ll();
    } else {
        LOG_ERROR(TIMER, "Usage: tdl");
    }

    return res;
}

bool timer_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = timer_diag();
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

bool timer_period_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t period_ms = 1000;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr index %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &period_ms);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr period_ms %s", argv[1]);
        }
    }

    if(res) {
        double pesiod_s = MSEC_2_SEC(period_ms);
        switch(argc) {
        case 2: {
            LOG_INFO(TIMER, "Set:Timer:%u,Period:%f s", num, pesiod_s);
            res = timer_period_set_s(num, MSEC_2_SEC(period_ms));
        } break;
        case 1: {
            pesiod_s = timer_period_get_s(num);
            LOG_INFO(TIMER, "Get,Timer:%u, Period:%f s", num, pesiod_s);
        } break;
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr TimerMum PeriodMs");
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
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TimerNum %s", argv[0]);
        }
        res = try_str2bool(argv[1], &on_off);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr OnOff %s", argv[1]);
        }
    }
    if(res) {
        res = timer_ctrl(num, on_off);
        if(res) {
            LOG_INFO(TIMER, "Set %u %s", num, OnOff2Str(on_off));
        } else {
            LOG_ERROR(TIMER, "Set %u %s", num, OnOff2Str(on_off));
        }
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
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TimerNum %s", argv[0]);
        }
        res = try_str2uint8(argv[1], &channel);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TimerNum %s", argv[1]);
        }
        res = try_str2uint32(argv[2], &compare_value);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr compare_value %s", argv[2]);
        }
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
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TimerNum %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &overflow);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr overflow %s", argv[1]);
        }
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
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr TimerMum PeriodMs");
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
    } else {
        LOG_ERROR(TIMER, "Usage: tcd");
    }

    return res;
}

bool timer_frequency_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    double frequency_hz = 0.0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(TIMER, "ParseErr TimerNum %s", argv[0]);
        }
    }

    if(2 <= argc) {
        res = try_str2double(argv[1], &frequency_hz);
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
        }
    } else {
        LOG_ERROR(TIMER, "Usage: tpr TimerMum PeriodMs");
        res = false;
    }

    return res;
}
