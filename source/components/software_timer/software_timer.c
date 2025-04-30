#include "software_timer.h"

#include <stddef.h>

#ifdef HAS_PASTILDA
#include "pastilda_config.h"
#endif

#ifdef HAS_INDICATION
#include "indication.h"
#endif

#include "common_diag.h"
#include "flash_mcal.h"
#include "log.h"
#include "software_timer_diag.h"
#include "sw_timer_config.h"
#include "time_mcal.h"

SoftwareTimer_t* SwTimerGetNode(uint8_t num) {
    SoftwareTimer_t* node = NULL;
    uint32_t i = 0;
    uint32_t cnt = software_timer_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(SoftwareTimerInstance[i].valid) {
            if(num == SoftwareTimerInstance[i].num) {
                node = &SoftwareTimerInstance[i];
                break;
            }
        }
    }
    return node;
}

const SoftwareTimerConfig_t* SwTimerGetConfigNode(uint8_t num) {
    const SoftwareTimerConfig_t* Config = 0;
    uint32_t i = 0;
    uint32_t cnt = software_timer_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(SoftwareTimerConfig[i].valid) {
            if(num == SoftwareTimerConfig[i].num) {
                Config = &SoftwareTimerConfig[i];
                break;
            }
        }
    }
    return Config;
}

static bool sw_timer_init_one(uint32_t num) {
    bool res = false;
    LOG_INFO(SW_TIMER, "Init %u", num);
    const SoftwareTimerConfig_t* Config = SwTimerGetConfigNode(num);
    if(Config) {
        SoftwareTimer_t* Node = SwTimerGetNode(num);
        if(Node) {
            switch((uint8_t)Config->dir) {
            case SW_TIMER_CNT_DIR_UP:
                Node->cnt = 0;
                break;
            case SW_TIMER_CNT_DIR_DOWN:
                Node->cnt = Config->period_ms;
                break;
            }

            Node->err_cnt = 0;
            Node->handler_cnt = 0;
            Node->dir = Config->dir;
            Node->handler = Config->handler;
            Node->mode = Config->mode;
            Node->on_off = Config->on_off;
            Node->period_ms = Config->period_ms;
            Node->phase_ms = Config->phase_ms;
            Node->spare = Config->spare;
            Node->valid = true;
            res = true;
        } else {
            LOG_ERROR(SW_TIMER, "NodeErr %u", num);
            res = false;
        }
    } else {
        LOG_ERROR(SW_TIMER, "ConfErr %u", num);
        res = false;
    }

    return res;
}

bool sw_timer_fast_ctrl(uint32_t num, bool on_off) {
    bool res = false;
    LOG_DEBUG(SW_TIMER, "Set Num:%u En:%s", num, OnOff2Str(on_off));
    SoftwareTimer_t* Node = SwTimerGetNode(num);
    if(Node) {
        Node->on_off = on_off;
        res = true;
        LOG_DEBUG(SW_TIMER, "SetDone Num:%u ", num);
    } else {
        LOG_ERROR(SW_TIMER, "%u NodeErr", num);
    }
    return res;
}

bool sw_timer_ctrl(uint32_t num, uint32_t period_ms, uint32_t phase_ms, SwTimerMode_t mode, SwTimerCntDir_t dir,
                   bool on_off) {
    bool res = false;
#ifdef HAS_SOFTWARE_TIMER_DIAG
    LOG_INFO(SW_TIMER, "Set Num:%u Per:%u ms Phase %u ms Mode:%s Dir:%s En:%s", num, period_ms, phase_ms,
             SwTimMode2Str(mode), SwTimDir2Str(dir), OnOff2Str(on_off));
#endif
    SoftwareTimer_t* Node = SwTimerGetNode(num);
    if(Node) {
        switch((uint8_t)dir) {
        case SW_TIMER_CNT_DIR_UP:
            Node->cnt = 0;
            break;
        case SW_TIMER_CNT_DIR_DOWN:
            Node->cnt = period_ms;
            break;
        }
        Node->isr = false;
        Node->period_ms = period_ms;
        Node->phase_ms = phase_ms;
        Node->dir = dir;
        Node->mode = mode;
        Node->on_off = on_off;
        res = true;
        LOG_INFO(SW_TIMER, "SetDone Num:%u ", num);
    } else {
        LOG_ERROR(SW_TIMER, "%u NodeErr", num);
    }
    return res;
}

uint32_t sw_timer_get_spare(void) {
    uint32_t num = 0;
    uint32_t i = 0;
    bool spot = false;
    uint32_t cnt = software_timer_get_cnt();
    LOG_DEBUG(SW_TIMER, "Cnt: %u", cnt);
    for(i = 0; i <= cnt; i++) {
        SoftwareTimer_t* Node = SwTimerGetNode(i);
        if(Node) {
            if(Node->spare) {
                if(false == Node->on_off) {
                    num = i;
                    spot = true;
                    break;
                }
            }
        }
    }

    if(false == spot) {
        LOG_ERROR(SW_TIMER, "LackSpare");
    }
    return num;
}

static bool TimerDone(void) {
    LOG_WARNING(SW_TIMER, "TimerDone!");
    bool res = false;
#ifdef HAS_PASTILDA
    res = indication_alarm(PastildaConfig.led_num);
#endif
    return res;
}

bool sw_timer_add_new(uint32_t period_s) {
    bool res = false;
    LOG_INFO(SW_TIMER, "TryAddNewTimer %s", period_s);
    uint32_t num = sw_timer_get_spare();
    if(num) {
        LOG_INFO(SW_TIMER, "Spot %u", num);
        res = sw_timer_set_handler(num, (uint32_t)TimerDone);
        if(res) {
            res = sw_timer_ctrl(num, SEC_2_MSEC(period_s), 0, SW_TIMER_MODE_SINGLE, SW_TIMER_CNT_DIR_DOWN, true);
        }
    }
    return res;
}

bool sw_timer_init(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t ok_cnt = 0;
    uint32_t cnt = software_timer_get_cnt();
    LOG_INFO(SW_TIMER, "Init %u", cnt);
    for(i = 0; i <= cnt; i++) {
        res = sw_timer_init_one(i);
        if(false == res) {
            LOG_ERROR(SW_TIMER, "InitErr %u", i);
        } else {
            ok_cnt++;
        }
    }

    if(0 < ok_cnt) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool sw_timer_poll(void) {
    bool res = false;
    uint32_t i = 0;
    uint32_t cnt = software_timer_get_cnt();
    for(i = 0; i <= cnt; i++) {
        SoftwareTimer_t* Node = SwTimerGetNode(i);
        if(Node) {
            if(Node->isr) {
                Node->isr = false;
#ifdef HAS_SOFTWARE_TIMER_DIAG
                LOG_WARNING(SW_TIMER, "%u=%s Overflow IsrCnt %u", i, SwTimNum2Str(i), Node->handler_cnt);
#endif
                res = is_flash_addr((uint32_t)Node->handler);
                if(res) {
                    Node->handler();
                } else {
                    LOG_ERROR(SW_TIMER, "%u,InvalidIsr,0x%x", i, Node->handler);
                }
                res = true;
            }
        }
    }
    return res;
}

bool sw_timer_set_handler(uint32_t num, uint32_t handler_address) {
    bool res = false;
    LOG_INFO(SW_TIMER, "SetHandler Num:%u Addr:0x%08x", num, handler_address);
    SoftwareTimer_t* Node = SwTimerGetNode(num);
    if(Node) {
        LOG_INFO(SW_TIMER, "SetIsrAddr 0x%08x ", handler_address);
        Node->handler = (SwHandler_t)handler_address;
        res = true;
    } else {
        LOG_ERROR(SW_TIMER, "%u NodeErr", num);
    }
    return res;
}
