#include "timer_mcal.h"

#include <string.h>

#include "code_generator.h"
#include "compiler_const.h"
#include "data_utils.h"
#include "float_utils.h"
#include "microcontroller_const.h"
#include "std_includes.h"
#include "time_mcal.h"
#include "timer_config.h"
#include "timer_utils.h"

#ifdef HAS_DEBUGGER
#include "debugger.h"
#endif

#ifdef HAS_LOG
#include "log.h"
#endif

COMPONENT_GET_NODE(Timer, timer)

COMPONENT_GET_CONFIG(Timer, timer)

uint32_t TimerGetCntFreq(uint32_t cnt_period_us) {
    uint32_t freq;
    freq = (uint32_t)(1.0 / USEC_2_SEC(cnt_period_us));
#ifdef HAS_LOG
    LOG_DEBUG(TIMER, "DesCntFreq:%u Hz", freq);
#endif
    return freq;
}

float timer_period_get_s(uint8_t num) {
    float period_s = 0;
    uint32_t period = timer_period_get(num);
    float tick_s = timer_tick_get_s(num);
    period_s = tick_s * ((float)period);
#ifdef HAS_LOG
    LOG_PARN(TIMER, "TIMER%u,Get,Tick:%f s,Per:%u=%f s", num, tick_s, period, period_s);
#endif
    return period_s;
}

/*  TODO calc from registers   */
uint32_t timer_get_int_period_ms(uint8_t num) {
    uint32_t period_ms = 0;
    const TimerConfig_t* Config = TimerGetConfig(num);
    if(Config) {
        period_ms = (uint32_t)(1000.0 * Config->period_s);
    }

    return period_ms;
}

float timer_counter_get_s(uint8_t num) {
    float counter_s = 0.0;
    uint32_t counter = timer_counter_get(num);
    float tick_s = timer_tick_get_s(num);
    counter_s = tick_s * ((float)counter);
    return counter_s;
}

uint32_t timer_counter_get_us(const uint8_t num) {
    uint32_t counter = timer_counter_get(num);
    float tick_s = timer_tick_get_s(num);
    uint32_t counter_us = 0;
    counter_us = ((uint32_t)(1000000.0 * tick_s)) * counter;
    return counter_us;
}

float timer_get_s(uint8_t num) {
    float up_time_s = 0.0;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        float period_s = timer_period_get_s(num); // 0.065534000000000009
        float counter_s = timer_counter_get_s(num);
        up_time_s = period_s * ((float)Node->int_cnt) + counter_s;
    }
    return up_time_s;
}

uint32_t timer_get_ms(uint8_t num) {
    uint32_t up_time_ms = 0;
    float up_time_s = timer_get_s(num);
    up_time_ms = SEC_2_MSEC(up_time_s);
    return up_time_ms;
}

_WEAK_FUN_ uint32_t timer_get_auto_reload(uint8_t num) {
#ifdef HAS_LOG
    LOG_DEBUG(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_ bool timer_init_one(uint8_t num) {
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
    return false;
}

_WEAK_FUN_
uint32_t timer_period_get(uint8_t num) {
    uint32_t period = 0;
    return period;
}

_WEAK_FUN_ TimerDir_t timer_dir_get(uint8_t num) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return TIMER_CNT_DIR_UNDEF;
}

_WEAK_FUN_ uint8_t timer_bitness_get(uint8_t num) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_ bool timer_compare_set(uint8_t num, TimerOutChannel_t channel, uint32_t compare_value) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return false;
}

_WEAK_FUN_ bool timer_channel_ctrl(uint8_t num, TimerOutChannel_t channel, bool on_off) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return false;
}

_WEAK_FUN_ bool timer_out_channel_pad_get(uint8_t num, TimerOutChannel_t channel, Pad_t* const Pad) {
#ifdef HAS_LOG

    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return false;
}

_WEAK_FUN_
int32_t timer_bus_clock_get(uint8_t num) {
    int32_t clock_hz = -1;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return clock_hz;
}

_WEAK_FUN_
bool timer_channel_is_work(const uint8_t num, const TimerOutChannel_t channel) {
    int32_t clock_hz = -1;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return clock_hz;
}

/*comparator values*/
_WEAK_FUN_ uint32_t timer_get_cc_val(uint8_t num, TimerOutChannel_t chaneel) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_
uint32_t timer_prescaler_get(uint8_t num) {
    uint32_t prescaler = 0xFF;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return prescaler;
}

_WEAK_FUN_
bool timer_ctrl(uint8_t num, bool on_off) {
    bool res = false;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return res;
}

_WEAK_FUN_
bool timer_get_status(uint8_t num) {
    uint8_t status = 0xFF;
    return status;
}

_WEAK_FUN_ uint32_t timer_ccc_val_get(uint8_t num, TimerOutChannel_t chaneel) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_
ClockBus_t timer_clock_bus_name_get(const uint8_t num) {
    ClockBus_t clock_bus = CLOCK_BUS_UNDEF;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return clock_bus;
}

_WEAK_FUN_ uint32_t timer_counter_get(uint8_t num) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_
bool timer_period_set_ll(TimerHandle_t* const Node, uint32_t period) {
    bool res = false;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return res;
}

_WEAK_FUN_
bool timer_period_set_s(uint8_t num, float period_s) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        float tick_s = timer_tick_get_s(num);
        uint32_t period = (uint32_t)(period_s / tick_s);
        LOG_DEBUG(TIMER, "TIMER%u,Set,Period:%f s,Tick:%f s,Period:%u", num, period_s, tick_s, period);
        res = timer_period_set_ll(Node, period);
        if(res) {
#ifdef HAS_LOG
            LOG_DEBUG(TIMER, "TIMER%u Period %f SetOk", num, period_s);
#endif
        } else {
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "TIMER%u,PeriodSetErr,Per:%u", num, period);
#endif
        }
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TIMER, "TIMER%u,NodeErr", num);
#endif
    }
    return res;
}

_WEAK_FUN_ uint32_t timer_cc_val_get(uint8_t num, TimerOutChannel_t channel) {
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return 0;
}

_WEAK_FUN_
float timer_calc_real_period_s(uint32_t bus_clock, uint32_t prescaler, uint32_t laod) {
    float calc_period_s = 0.0;
    float cpu_period = 1.0 / ((float)bus_clock);
    calc_period_s = cpu_period * ((float)((prescaler + 1U) * ((float)laod)));
    return calc_period_s;
}

_WEAK_FUN_ bool timer_init_custom(void) {
    bool res = true;
#ifdef HAS_LOG
    LOG_ERROR(TIMER, "[%s]NotImplemented", __FUNCTION__);
#endif
    return res;
}

float TimerConfigToPeriodSec(const TimerConfig_t* const Config) {
    float des_period_s = Config->period_s;
    return des_period_s;
}

bool TimerIsValidSlaveConfig(const TimerConfig_t* const Config) {
    bool res = true;

    if(TIMER_ROLE_SLAVE == Config->role) {
        ifn(Config->slave_input_trigger) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,slave_input_trigger", Config->num);
#endif
        }

        ifn(Config->slave_trigger_polarity) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,slave_trigger_polarity", Config->num);
#endif
        }

        ifn(Config->slave_mode) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,slave_mode", Config->num);
#endif
        }
    }
    return res;
}

bool TimerIsValidConfig(const TimerConfig_t* const Config) {
    bool res = false;
    if(Config) {
        res = true;

        res = timer_is_valid(Config->num);
        ifn(res) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,TimerNum,Err", Config->num);
#endif
        }

        ifn(Config->role) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,Role", Config->num);
#endif
        }

        ifn(0.0f < Config->period_s) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,Period", Config->num);
#endif
        }

        ifn(0.0f < Config->cnt_period_ns) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,CntPeriod", Config->num);
#endif
        }

        ifn(Config->name) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,Name", Config->num);
#endif
        }

        ifn(Config->dir) {
            res = false;
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "%u,Cfg,Err,Dir", Config->num);
#endif
        }
    }
    return res;
}

_WEAK_FUN_
bool timer_calc_registers(float des_period_s, uint32_t bus_clock, uint32_t prescaler, uint32_t* out_load,
                          uint32_t max_val) {
    bool res = true;
    if(max_val) {
#ifdef HAS_LOG
        LOG_DEBUG(TIMER, "Per:%f s BusFreq:%u Hz Psc %u", des_period_s, bus_clock, prescaler);
#endif

        uint64_t load = 0;
        float bus_period_s = 1.0f / ((float)bus_clock);
        float calc_period_s = 0.0f;

        load = (uint32_t)(des_period_s / ((float)bus_period_s * ((float)(prescaler + 1U))));
        if(max_val < load) {
            LOG_ERROR(TIMER, "NotEnoughBitDepth:Need:%u,Max:%u", load, max_val);
            res = false;
        } else {
            res = true;
        }
        if(res) {
            calc_period_s = timer_calc_real_period_s(bus_clock, prescaler, (uint32_t)load);
            float err = bus_period_s * 100000.0;
            if(false == is_float_equal_absolute(calc_period_s, des_period_s, err)) {
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

_WEAK_FUN_
uint32_t timer_calc_prescaler(uint32_t bus_clock_hz, uint32_t des_tick_per_ns, uint32_t max_prescaler) {
    uint32_t prescaler = 0;
    // ASSERT_CRITICAL(bus_clock_hz);
    if(bus_clock_hz) {
        float des_tick_per_s = NSEC_2_SEC(des_tick_per_ns);
        float tick_s = 1.0 / ((float)bus_clock_hz);
        prescaler = des_tick_per_s / tick_s;
        if(max_prescaler < prescaler) {
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "PCS OverFlow Calc:%u Max:%u", prescaler, max_prescaler);
#endif
            prescaler = max_prescaler;
        } else {
#ifdef HAS_LOG
            LOG_DEBUG(TIMER, "PCS:%u", prescaler);
#endif
        }

        if(!prescaler) {
            prescaler = 1;
        }
    }else{
#ifdef HAS_LOG
            LOG_ERROR(TIMER, "busC"
                    "lockZero");
#endif
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

_WEAK_FUN_
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

_WEAK_FUN_
bool timer_overflow_set(uint8_t num, uint32_t overflow) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        Node->int_cnt = overflow;
        res = true;
    }
    return res;
}

bool timer_duty_get(uint8_t num, TimerOutChannel_t channel, float* const duty) {
    bool res;
    if(duty) {
        float duty_cycle = 0.0;
        uint32_t period = timer_period_get(num);
        uint32_t comparator = timer_cc_val_get(num, channel);
        duty_cycle = ((float)(100 * comparator)) / ((float)period);
        *duty = duty_cycle;
        res = true;
    }
    return res;
}

_WEAK_FUN_
float timer_tick_get_s(uint8_t num) {
    float tick_s = -10;
    float bus_clock = (float)timer_bus_clock_get(num);
    if(0.0 < bus_clock) {
        uint32_t prescaler = timer_prescaler_get(num); // 62888
        // see page 251 14.1.3.2 Counting mode
        tick_s = ((float)(prescaler)) / bus_clock;
    }
    return tick_s;
}

_WEAK_FUN_
bool timer_frequency_get(uint8_t num, float* const frequency_hz) {
    bool res = false;
    if(frequency_hz) {
        *frequency_hz = -1.0;
        float period_s = timer_period_get_s(num);
        if(0.0 <= period_s) {
            *frequency_hz = 1.0 / period_s;
            res = true;
        }
    }
    return res;
}

_WEAK_FUN_
bool timer_frequency_set(uint8_t num, float frequence_hz) {
    bool res = false;
    float period_s = 1.0 / frequence_hz;
#ifdef HAS_LOG
    LOG_DEBUG(TIMER, "TIMER%u,SetFreq:%f Hz,Period:%fs", num, frequence_hz, period_s);
#endif
    res = timer_period_set_s(num, period_s);
    if(res) {
#ifdef HAS_LOG
        LOG_DEBUG(TIMER, "TIMER%u,FreqSetOk", num);
#endif
    } else {
#ifdef HAS_LOG
        LOG_ERROR(TIMER, "TIMER%u,FreqSetErr,Per:%fs", num, period_s);
#endif
    }
    return res;
}

/*
  duration of one cnt increase
 */
_WEAK_FUN_ uint32_t timer_get_tick_us(uint8_t num) {
    uint32_t tick_us = 0;
    uint32_t prescaler = timer_prescaler_get(num);
    if(prescaler) {
        float tick_s = 0.0;
        float bus_clock = timer_bus_clock_get(num);
        if(0.0 < bus_clock) {
            tick_s = ((float)prescaler) / bus_clock;
            tick_us = (uint32_t)sec_to_usec(tick_s);
        }
    }
    return tick_us;
}

_WEAK_FUN_
bool timer_overflow_get(uint8_t num, uint32_t* const overflow) {
    bool res = false;
    TimerHandle_t* Node = TimerGetNode(num);
    if(Node) {
        if(overflow) {
            *overflow = Node->int_cnt;
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
        float fck = (float)timer_bus_clock_get(num);
        float tf = 1.0f / fck;
        uint32_t prescaler = 0;
        prescaler = timer_prescaler_get(num);

        float t_psc = tf * ((float)prescaler);

        real_period_us = (uint64_t)(t_psc * ((float)reload)) * 1000000.0;
    }
    return real_period_us;
}

#if 0
_WEAK_FUN_
float timer_get_period_s(uint8_t num) {
    float real_period_s = 0;
    uint32_t prescaler = 0;
    uint32_t reload = 0;
    TimerHandle_t* Node = NULL;
    Node = TimerGetNode(num);
    if(Node) {
        float fck = (float)timer_bus_clock_get(num);
        float tf = 1.0 / fck;

        float t_psc = tf * ((float)prescaler);

        real_period_s = (t_psc * ((float)reload));
    }
    return real_period_s;
}
#endif

uint64_t timer_get_us(uint8_t num) {
    uint64_t up_time_us = 0;
    float time_s = timer_get_s(num);
    up_time_us = (uint64_t)SEC_2_USEC(time_s);
    return up_time_us;
}

_WEAK_FUN_
uint32_t timer_period_to_us(const uint8_t num, const uint32_t period) {
    uint32_t period_us = 0;
    float tick_s = 0.0;
    tick_s = timer_tick_get_s(num);
    period_us = SEC_2_USEC(((float)period) * tick_s);
    return period_us;
}

_WEAK_FUN_
uint32_t timer_period_to_ms(uint8_t num, uint32_t period) {
    uint32_t period_ms = 0;
    float tick_s = 0.0;
    tick_s = timer_tick_get_s(num);
    period_ms = SEC_2_MSEC(((float)period) * tick_s);
    return period_ms;
}

_WEAK_FUN_
uint32_t timer_period_get_ms(uint8_t num) {
    uint32_t period_ms = 0;
    uint32_t period = timer_period_get(num);
    period_ms = timer_period_to_ms(num, period);
    return period_ms;
}

_WEAK_FUN_
bool timer_init_common(const TimerConfig_t* const Config, TimerHandle_t* const Node) {
    bool res = false;
    if(Config) {
        if(Node) {
            Node->num = Config->num;
            Node->period_s = Config->period_s;
            Node->name = Config->name;
            Node->on_off = Config->on_off;
            Node->cnt_period_ns = Config->cnt_period_ns;
            Node->interrupt_on = Config->interrupt_on;
            Node->role = Config->role;
            Node->dir = Config->dir;
            Node->master_out_trigger = Config->master_out_trigger;
            Node->slave_trigger_prescaler = Config->slave_trigger_prescaler;
            Node->slave_trigger_filter = Config->slave_trigger_filter;
            Node->slave_input_trigger = Config->slave_input_trigger;
            Node->slave_trigger_polarity = Config->slave_trigger_polarity;
            Node->ComparatorHandler = Config->ComparatorHandler;
            Node->PeriodDoneHandler = Config->PeriodDoneHandler;
            Node->slave_mode = Config->slave_mode;
            Node->valid = true;
            res = true;
        }
    }
    return res;
}


COMPONENT_INIT_PATTERT_CNT(TIMER, TIMER, timer, TIMER_MAX_NUM)
