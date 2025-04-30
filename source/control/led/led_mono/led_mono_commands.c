#include "led_mono_commands.h"

#include <inttypes.h>
#include <stdio.h>

#include "convert.h"
#include "data_utils.h"
#include "gpio_mcal.h"
#include "led_config.h"
#include "led_drv.h"
#include "led_mono_diag.h"
#include "log.h"
#include "log_utils.h"

bool led_mono_get_command(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = led_mono_diag();
    } else {
        LOG_ERROR(LED, "Usage: lmg");
    }
    return res;
}

bool led_mono_set_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t in_duty = 0;
    LedMonoHandle_t* Node = NULL;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LED, "Unable to extract Num %s", argv[0]);
        } else {
            Node = LedMonoGetNode(num);
            if(Node) {
                LOG_INFO(LED, "LedPtrOk!");
                res = true;
            } else {
                LOG_ERROR(LED, "NoLedPtr%u");
                res = false;
            }
        }
    }

    if(2 <= argc) {
        if(Node) {
            res = try_str2uint32(argv[1], &Node->period_ms);
            if(false == res) {
                LOG_ERROR(LED, "Unable to extract period %s", argv[1]);
            }
        }
    }

    if(3 <= argc) {
        if(Node) {
            res = try_str2uint8(argv[2], &in_duty);
            if(false == res) {
                LOG_ERROR(LED, "Unable to extract duty %s", argv[2]);
            } else {
                if(in_duty <= 100) {
                    Node->duty = in_duty;
                }
            }
        }
    }

    if(4 <= argc) {
        if(Node) {
            res = try_str2uint32(argv[3], &Node->phase_ms);
            if(false == res) {
                LOG_ERROR(LED, "Unable to extract phase %s", argv[3]);
            }
        }
    }

    if(false == res) {
        LOG_ERROR(LED, "Usage: lms num period_ms duty phase_ms");
        LOG_INFO(LED, "period");
        LOG_INFO(LED, "duty 0....100");
        LOG_INFO(LED, "phase");
    }
    return res;
}

bool led_mono_blink_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t duration_ms = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(LED, "Unable to extract Num %s", argv[0]);
        } else {
            LOG_INFO(LED, "Ok");
        }
    }
    if(2 <= argc) {
        res = try_str2uint32(argv[1], &duration_ms);
        if(false == res) {
            LOG_ERROR(LED, "Unable to extract duration_ms %s", argv[1]);
        }
    }

    if(res) {
        res = led_mono_blink(num, duration_ms);
        if(res) {
            LOG_INFO(LED, "Ok");
        }
    }

    if(false == res) {
        LOG_ERROR(LED, "Usage: lmb num duration_ms");
    }
    return res;
}

bool led_mono_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Num %s", argv[0]);
        } else {
        }
    }

    if(res) {
        res = led_mono_init_one(num);
        if(res) {
            LOG_INFO(LED, "Ok");
        }
    }
    return res;
}

bool led_mono_mode_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t mode = LED_MODE_UNDEF;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Num %s", argv[0]);
        } else {
        }
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &mode);
        if(false == res) {
            LOG_ERROR(SYS, "ParseErr Mode %s", argv[1]);
        } else {
        }
    }

    if(res) {
        LOG_INFO(LED, "try set mode");
        res = led_mono_mode_set(num, (LedMode_t)mode);
        if(res) {
            LOG_INFO(LED, "Ok");
        }
    } else {
        LOG_ERROR(LED, "Usage: lmm num mode");
    }
    return res;
}
