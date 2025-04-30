#include "timer_mcal.h"

#include <stdbool.h>
#include <stdint.h>
#include <string.h>

#include "data_utils.h"
#include "float_utils.h"
#include "log.h"
#include "sys_config.h"
#include "time_mcal.h"
#include "timer_config.h"
#include "timer_utils.h"

#include "code_generator.h"

COMPONENT_GET_NODE(Timer, timer)

COMPONENT_GET_CONFIG(Timer, timer)

uint32_t TimerGetCntFreq(uint32_t cnt_period_us) {
    uint32_t freq;
    freq = (uint32_t)(1.0 / USEC_2_SEC(cnt_period_us));
#ifdef HAS_LOG
    LOG_INFO(TIMER, "DesCntFreq:%u Hz", freq);
#endif
    return freq;
}

double timer_period_get_s(uint8_t num) {
    double period_s = 0;
    uint32_t period = timer_period_get(num);
    double tick_s = timer_tick_get_s(num);
    period_s = tick_s * ((double)period);
    LOG_PARN(TIMER, "TIMER%u,Get,Tick:%f s,Per:%u=%f s", num, tick_s, period, period_s);
    return period_s;
}

double timer_counter_get_s(uint8_t num) {
    double counter_s = 0.0;
    uint32_t counter = timer_counter_get(num);
    double tick_s = timer_tick_get_s(num);
    counter_s = tick_s * ((double)counter);
    return counter_s;
}

double timer_get_s(uint8_t num) {
    double up_time_s = 0.0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        double period_s = timer_period_get_s(num); // 0.065534000000000009
        double counter_s = timer_counter_get_s(num);
        up_time_s = period_s * ((double)Node->overflow) + counter_s;
    }
    return up_time_s;
}

uint32_t timer_get_ms(uint8_t num) {
    uint32_t up_time_ms = 0;
    double up_time_s = timer_get_s(num);
    up_time_ms = SEC_2_MSEC(up_time_s);
    return up_time_ms;
}

__attribute__((weak)) uint32_t timer_period_get(uint8_t num) { return 0; }

__attribute__((weak)) bool timer_ctrl(uint8_t num, bool on_off) {
    bool res = false;
    LOG_ERROR(TIMER, "%s NotImplemented", __FUNCTION__);
    return res;
}

__attribute__((weak)) uint32_t timer_get_auto_reload(uint8_t num) { return 0; }

__attribute__((weak)) TimerDir_t timer_dir_get(uint8_t num) { return CNT_DIR_UNDEF; }

__attribute__((weak)) uint8_t timer_bitness_get(uint8_t num) { return 0; }

__attribute__((weak)) bool timer_compare_set(uint8_t num, TimerCapComChannel_t channel, uint32_t compare_value) {
    return false;
}

__attribute__((weak)) bool timer_channel_ctrl(uint8_t num, TimerCapComChannel_t channel, bool on_off) { return false; }

__attribute__((weak)) bool timer_out_channel_pad_get(uint8_t num, TimerCapComChannel_t channel, Pad_t* const Pad) {
    return false;
}

__attribute__((weak)) int32_t timer_bus_clock_get(uint8_t num) { return 0; }

__attribute__((weak)) uint32_t timer_get_cc_val(uint8_t num, TimerCapComChannel_t chaneel) { return 0; }

__attribute__((weak)) uint32_t timer_ccc_val_get(uint8_t num, TimerCapComChannel_t chaneel) { return 0; }

__attribute__((weak)) uint32_t timer_counter_get(uint8_t num) { return 0; }

__attribute__((weak)) bool timer_period_set_s(uint8_t num, double period_s) { return false; }

__attribute__((weak)) uint32_t timer_cc_val_get(uint8_t num, TimerCapComChannel_t channel) { return 0; }

double timer_calc_real_period_s(uint32_t bus_clock, uint32_t prescaler, uint32_t laod) {
    double calc_period_s = 0.0;
    double cpu_period = 1.0 / ((double)bus_clock);
    calc_period_s = cpu_period * ((double)((prescaler + 1U) * ((double)laod)));
    return calc_period_s;
}

__attribute__((weak)) bool timer_init_custom(void) {
    bool res = true;
    LOG_ERROR(TIMER, "[%s] NotImplemented", __FUNCTION__);
    return res;
}

double TimerConfigToPeriodSec(const TimerConfig_t* const Config) {
    double des_period_s = 0.0;
    if(0 < Config->period_ms) {
        des_period_s = MSEC_2_SEC(Config->period_ms);
    } else {
        if(0 < Config->period_us) {
            des_period_s = USEC_2_SEC(Config->period_us);
        } else {
            des_period_s = NSEC_2_SEC(Config->period_ns);
        }
    }
    return des_period_s;
}

bool timer_calc_registers(uint32_t period_ms, uint32_t period_us, uint32_t period_ns, uint32_t bus_clock,
                          uint32_t prescaler, uint32_t* out_load, uint32_t max_val) {
    bool res = true;
    if(max_val) {
        LOG_DEBUG(TIMER, "Per:%u ms BusFreq:%u Hz Psc %u", period_ms, bus_clock, prescaler);
        double des_period_s = 0.0;
        if(0 < period_ms) {
            des_period_s = MSEC_2_SEC(period_ms);
        } else {
            if(0 < period_us) {
                des_period_s = USEC_2_SEC(period_us);
            } else {
                des_period_s = NSEC_2_SEC(period_ns);
            }
        }

        uint64_t load = 0;
        double bus_period_s = 1.0 / ((double)bus_clock);
        double calc_period_s = 0.0;

        load = (uint32_t)(des_period_s / ((double)bus_period_s * ((double)(prescaler + 1U))));
        if(max_val < load) {
            LOG_ERROR(TIMER, "NotEnoughBitDepth:Need:%u,Max:%u", load, max_val);
            res = false;
        } else {
            res = true;
        }
        if(res) {
            calc_period_s = timer_calc_real_period_s(bus_clock, prescaler, (uint32_t)load);
            double err = bus_period_s * 100000.0;
            if(false == is_double_equal_absolute(calc_period_s, des_period_s, err)) {
                LOG_WARNING(TIMER, "PeriodsDifferent des [%f] calc [%f] s Err[%f]", des_period_s, calc_period_s, err);
                res = false;
            }
            res = true;
            (*out_load) = (uint32_t)load;
        } else {
            *out_load = 0xFFFF - 1;
            res = false;
        }
    }

    return res;
}

uint32_t timer_calc_prescaler(uint32_t bus_clock_hz, uint32_t des_tick_per_ns, uint32_t max_prescaler) {
    uint32_t prescaler = 0;
    double des_tick_per_s = NSEC_2_SEC(des_tick_per_ns);
    double tick_s = 1.0 / ((double)bus_clock_hz);
    prescaler = des_tick_per_s / tick_s;
    if(max_prescaler < prescaler) {
        LOG_ERROR(TIMER, "PCS OverFlow Calc:%u Max:%u", prescaler, max_prescaler);
        prescaler = max_prescaler;
    } else {
        LOG_INFO(TIMER, "PCS:%u", prescaler);
    }

    if(!prescaler) {
        prescaler = 1;
    }
    return prescaler;
}

uint32_t timer_get_tick_period_us(uint8_t num) {
    uint32_t cnt_period_us = 0;
    uint32_t i = 0;
    for(i = 0; i < timer_get_cnt(); i++) {
        if(num == TimerConfig[i].num) {
            cnt_period_us = TimerConfig[i].cnt_period_ns * 1000;
            break;
        }
    }
    return cnt_period_us;
}

uint32_t timer_get_int_period_ms(uint8_t num) {
    uint32_t period_ms = 0;
    uint32_t i = 0;
    for(i = 0; i < timer_get_cnt(); i++) {
        if(num == TimerConfig[i].num) {
            period_ms = TimerConfig[i].period_ms;
            break;
        }
    }
    return period_ms;
}

bool timer_is_valid(uint8_t num) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        const TimerConfig_t* Config = TimerGetConfig(num);
        if(Config) {
            res = true;
        }
    }
    return res;
}

bool timer_overflow_set(uint8_t num, uint32_t overflow) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        Node->overflow = overflow;
        res = true;
    }
    return res;
}

bool timer_duty_get(uint8_t num, TimerCapComChannel_t channel, double* const duty) {
    bool res;
    if(duty) {
        double duty_cycle = 0.0;
        uint32_t period = timer_period_get(num);
        uint32_t comparator = timer_cc_val_get(num, channel);
        duty_cycle = ((double)(100 * comparator)) / ((double)period);
        *duty = duty_cycle;
        res = true;
    }
    return res;
}

double timer_tick_get_s(uint8_t num) {
    double tick_s = -10;
    double bus_clock = (double)timer_bus_clock_get(num);
    if(0.0 < bus_clock) {
        uint32_t prescaler = timer_prescaler_get(num); // 62888
        // see page 251 14.1.3.2 Counting mode
        tick_s = ((double)(prescaler + 1)) / bus_clock;
    }
    return tick_s;
}

bool timer_frequency_get(uint8_t num, double* const frequency_hz) {
    bool res = false;
    if(frequency_hz) {
        *frequency_hz = -1.0;
        double period_s = timer_period_get_s(num);
        if(0.0 < period_s) {
            *frequency_hz = 1.0 / period_s;
            res = true;
        }
    }
    return res;
}

bool timer_frequency_set(uint8_t num, double frequence_hz) {
    bool res = false;
    double period_s = 1.0 / frequence_hz;
    LOG_INFO(TIMER, "TIMER%u SetFreq:%f Hz,Period:%f s", num, frequence_hz, period_s);
    res = timer_period_set_s(num, period_s);
    if(res) {
        LOG_INFO(TIMER, "TIMER%u FreqSetOk", num);
    } else {
        LOG_ERROR(TIMER, "TIMER%u FreqSetErr", num);
    }
    return res;
}

__attribute__((weak)) uint32_t timer_prescaler_get(uint8_t num) { return 0; }

/*
 * duration of one cnt increase
 * */
__attribute__((weak)) uint32_t timer_get_tick_us(uint8_t num) {
    uint32_t tick_us = 0;
    uint32_t prescaler = timer_prescaler_get(num);
    if(prescaler) {
        double tick_s = 0.0;
        double bus_clock = timer_bus_clock_get(num);
        if(0.0 < bus_clock) {
            tick_s = ((double)prescaler) / bus_clock;
            tick_us = (uint32_t)sec_to_usec(tick_s);
        }
    }
    return tick_us;
}

bool timer_overflow_get(uint8_t num, uint32_t* const overflow) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        if(overflow) {
            *overflow = Node->overflow;
            res = true;
        }
    }
    return res;
}

uint64_t timer_get_period_us(uint8_t num) {
    uint64_t real_period_us = 0;
    uint32_t reload = 0;
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        double fck = (double)timer_bus_clock_get(num);
        double tf = 1.0 / fck;
        uint32_t prescaler = 0;
        prescaler = timer_prescaler_get(num);

        double t_psc = tf * ((double)prescaler);

        real_period_us = (uint64_t)(t_psc * ((double)reload)) * 1000000.0;
    }
    return real_period_us;
}

double timer_get_period_s(uint8_t num) {
    double real_period_s = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        double fck = (double)timer_bus_clock_get(num);
        double tf = 1.0 / fck;

        double t_psc = tf * ((double)prescaler);

        real_period_s = (t_psc * ((double)reload));
    }
    return real_period_s;
}

uint64_t timer_get_us(uint8_t num) {
    uint64_t up_time_us = 0;
    double time_s = timer_get_s(num);
    up_time_us = (uint64_t)SEC_2_USEC(time_s);
    return up_time_us;
}

uint32_t timer_period_get_ms(uint8_t num) {
    uint32_t period_ms = 0;
    uint32_t period = timer_period_get(num);
    double tick_s = 0.0;
    tick_s = timer_tick_get_s(num);
    period_ms = SEC_2_MSEC(((double)period) * tick_s);
    return period_ms;
}

bool timer_init_common(const TimerConfig_t* const Config, TimerHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->interrupt_on = Config->interrupt_on;
            Node->dir = Config->dir;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT_CNT(TIMER, TIMER, timer, TIMER_MAX_NUM)
